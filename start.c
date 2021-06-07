#include "gif_rw.h"

int main(int argc, char const *argv[])
{
  GIF gif;
  readGif(&gif, "test1.gif");
  freeGif(&gif);
  return 0;
}
