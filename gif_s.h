#pragma once
typedef struct GifHeader
{
  char signature[3];
  char version[3];
} GIF_HEADER;

typedef struct Color
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} COLOR;

typedef COLOR *COLORTABLE;


/*
        Global Color Table Flag       1 Bit
        Color Resolution              3 Bits
        Sort Flag                     1 Bit
        Size of Global Color Table    3 Bits
    */
typedef struct LSD_Flags
{
  unsigned char hasColorTableFlag;
  unsigned char colorDepth;
  unsigned char isSorted;
  unsigned short globalColorTableSize;
} GIF_LOGICAL_SCREEN_DESCRIPTOR_FLAGS;

typedef struct ScreenDescriptor
{
  //Upper half => width
  //lower half => height
  unsigned short width;
  unsigned short height;

  GIF_LOGICAL_SCREEN_DESCRIPTOR_FLAGS flags;

  //Background Color index
  unsigned char backgoundColorIndex;
  unsigned char aspectRatio;

} GIF_LOGICAL_SCREEN_DESCRIPTOR;

typedef struct Gif
{
  GIF_HEADER header;
  GIF_LOGICAL_SCREEN_DESCRIPTOR logicalScreenDescriptor;
  COLORTABLE globalColorTable;
} GIF;
