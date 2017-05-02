#include "headers/vdi.h"
#include <cstring>
#include <unistd.h>
#include <iostream>

using namespace std;

VDIClass::VDIClass(int fd) : fd(fd){
  //this.fd = fd;
  lseek(fd, 0, SEEK_SET);
  read(fd, &header, sizeof(header));
  lseek(fd, header.offset_blocks, SEEK_SET);
  cout << "Header offset blocks amount: " << header.offset_blocks << endl;
  image_map = new __s32[header.disk_size_bytes >> 20];
  read(fd, image_map, (header.disk_size_bytes >> 20));
}

void VDIClass::getBytes(char* data, int startByte, int bytes){
  cout << "Starting byte for retrieval: " << startByte << endl;
  int bytesToGet = bytes;
  int virtualStart = startByte >> 20;
  cout << "Virtual page started at: " << virtualStart << endl;
  int currentBytesRetrieved = 0;
  int currentPage = virtualStart;

  while(bytesToGet - currentBytesRetrieved > 0){
    int realPage = getRealPage(currentPage);
    int bytesLeft = bytesToGet - currentBytesRetrieved;
    char* dataBuffer = new char[bytesLeft];

    if(realPage == -1){
      memset(dataBuffer, 0, bytesLeft);
    }
    else{
      __u32 pageOffset = (header.offset_data + startByte) + ((realPage - currentPage) << 20);
      printf("Bytes left to read: 0x%x\nReal Page: 0x%x\nCurrent Page: 0x%x\nPage Offset: 0x%x\nHeader Offset: 0x%x\n\n",bytesLeft, realPage, currentPage, pageOffset, header.offset_data);
      lseek(fd, pageOffset, SEEK_SET);
      read(fd, dataBuffer, bytesLeft);
    }

    for(int j = 0; j <= bytesLeft; j++){
      data[currentBytesRetrieved + j] = dataBuffer[j];
    }
    currentBytesRetrieved += bytesLeft;
    currentPage++;
  }

  lseek(fd, 0, SEEK_SET);
}

int VDIClass::getRealPage(int page)
{
  return image_map[page];
}

__u32 VDIClass::getBlockSize(){
  return header.block_size;
}
