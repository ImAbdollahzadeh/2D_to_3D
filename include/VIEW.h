#pragma once
#include "VIEW.h"
#include "VERTEX.h"
#include "CAMERA.h"
#include "CUBE.h"
#include "PAINT.h"
#include "GENERAL_COLORS.h"
#include "LIGHT.h"
#include "TEXTURE.h"

#define WAIT wait();
void wait(void);

HBITMAP create_bmp(HDC dc, void* fb);
void blit(HWND hwnd, unsigned char* fb);
void final_view(float z, float y, VERTEX* v);
void rotations_2D(CAMERA* cam, VERTEX* v);
void paint_cube(unsigned char* fb, CUBE* cu, LIGHT* lt);

void scene_view(HWND hwnd, CUBE* cu, CAMERA* cam, LIGHT* lt, TEXTURE* texture, unsigned char* fb);
