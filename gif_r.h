#pragma once
#include "gif_s.h"
#include "stdio.h"
#include "stdlib.h"

unsigned short cPow(const unsigned char base, unsigned char power){
  unsigned short value = 1;
  for (size_t i = 0; i < power; i++)
  {
    value *= base;
  }
  return value;

}

errno_t loadFile(FILE **p_p_file, const char location[])
{
	errno_t error = fopen_s(p_p_file, location, "r");
}

void readBytes(FILE *p_file, unsigned char block[], size_t times)
{
	for (size_t i = 0; i < times; i++)
	{
		block[i] = fgetc(p_file);
	}
}

void readShort(FILE *p_file, unsigned short p_values[], size_t times)
{
  for (size_t i = 0; i < times; i++)
  {
    p_values[i] = fgetc(p_file) | (fgetc(p_file) << sizeof(char));
  }
  
}

void fetchHeader(FILE *p_file, GIF_HEADER *p_header)
{
	readBytes(p_file, p_header->signature, 3);
	readBytes(p_file, p_header->version, 3);
}

void fetchLogicalScreenDesciptorFlags(FILE *p_file,GIF_LOGICAL_SCREEN_DESCRIPTOR_FLAGS *p_flags){
  unsigned char packet;
  readBytes(p_file, &packet, 1);
  p_flags->hasColorTableFlag = (0x80 & packet) >> 7;
  p_flags->colorDepth = ((0x70 & packet) >> 4) + 1; 
  p_flags->isSorted = (0x08 & packet) >> 3;
  p_flags->globalColorTableSize = cPow(2, (0x07 & packet) + 1);
}



void fetchLogicalScreenDesciptor(FILE *p_file, GIF_LOGICAL_SCREEN_DESCRIPTOR *p_lsd)
{
	readShort(p_file, &p_lsd->width, 1);
	readShort(p_file, &p_lsd->height, 1);
  fetchLogicalScreenDesciptorFlags(p_file, &p_lsd->flags);
  readBytes(p_file, &p_lsd->backgoundColorIndex, 1);
  readBytes(p_file, &p_lsd->aspectRatio, 1);
  p_lsd->aspectRatio = (p_lsd->aspectRatio + 15) / 64;
}

void fetchColorTable(FILE *p_file, COLORTABLE *colors, size_t size){
  if(colors == 0){
    return;
  }
  
  *colors = (COLOR*) calloc(size, sizeof(COLOR));
  for (size_t i = 0; i < size; i++)
  {
    (*colors)[i].red = fgetc(p_file);
    (*colors)[i].green = fgetc(p_file);
    (*colors)[i].blue = fgetc(p_file);
  }
}

errno_t readGif(GIF *p_gif, const char location[])
{
	FILE *p_file;
  errno_t l_errno = loadFile(&p_file, location);
	if(errno > 0){
    return errno;
  }
	fetchHeader(p_file, &p_gif->header);
	fetchLogicalScreenDesciptor(p_file, &p_gif->logicalScreenDescriptor);
  fetchColorTable(p_file, p_gif->logicalScreenDescriptor.flags.hasColorTableFlag ? &p_gif->globalColorTable : 0, p_gif->logicalScreenDescriptor.flags.globalColorTableSize);
  return 0;
}
