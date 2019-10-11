#pragma once

#include <Windows.h>
#include "VERTEX.h"
#define PI 3.14159265359
#define RADIAN_TO_DEGREE(rad) (((180.00f)/PI)*rad)
#define DEG_TO_RADIAN(deg) (((PI)/180.00f)*deg)

typedef struct _RITCOL {
	VERTEX x_head;
	VERTEX y_head;
	VERTEX z_head;
	unsigned char x_letter = 'X';
	unsigned char y_letter = 'Y';
	unsigned char z_letter = 'Z';
} RITCOL;

typedef struct _CAMERA {
	VERTEX position;
	float  view_x_rot;
	float  view_y_rot;
	float  view_z_rot;
	float  scale;
	unsigned int point_size;
	RITCOL ritcol;
} CAMERA;

void register_camera(CAMERA* cam, VERTEX* position);
