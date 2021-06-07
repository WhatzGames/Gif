#pragma once
#include "gif_s.h"
#include "gif_r.h"
#include "gif_w.h"

void freeGif(GIF *p_gif){
  free(p_gif->globalColorTable);
}
