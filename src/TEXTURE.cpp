#include "TEXTURE.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)


/*
 BMP* PTR_BITMAP
 int  I
 int  J 
 */
#define PIXEL(PTR_BITMAP,I,J) PTR_BITMAP->data[3*((J*PTR_BITMAP->width)+(I))]

#define PI 3.14159265359
#define RADIAN_TO_DEG(rad) ((180.00f/(PI))*rad)
#define DEG_TO_RADIAN(deg) (((PI)/180.00f)*deg)


 /*
  unsigned char r
  unsigned char g
  unsigned char b
 */
#define RGB_COMBINE(r, g, b) ((b)<<16) | ((g)<<8) | (r)

typedef struct _VECTOR_2D {
	float y;
	float z;
} VECTOR_2D;


/*
 VECTOR_2D* res
 VECTOR_2D* v1
 VECTOR_2D* v2
 VECTOR_2D* orig
 */
#define parallelogram_law(res, v1, v2, orig) do                   \
{																  \
	VECTOR_2D V1 = { v1->y - orig->y, v1->z - orig->z };		  \
	VECTOR_2D V2 = { v2->y - orig->y, v2->z - orig->z };		  \
																  \
	float epsilon = 0.00000001f;								  \
																  \
	float b = RADIAN_TO_DEG(atan(V2.z / (V2.y + epsilon)));		  \
	float a = RADIAN_TO_DEG(atan(V1.z / (V1.y + epsilon)));		  \
																  \
	float A = sqrt((V1.y*V1.y) + (V1.z*V1.z));					  \
	float B = sqrt((V2.y*V2.y) + (V2.z*V2.z));					  \
																  \
	res->y = B*cos(DEG_TO_RADIAN(b)) + A*cos(DEG_TO_RADIAN(a));	  \
	res->z = B*sin(DEG_TO_RADIAN(b)) + A*sin(DEG_TO_RADIAN(a));	  \
} while (0);

void transform(unsigned char* fb, VERTEX* v1, VERTEX* v2, VERTEX* v3, float x, float y, float z, unsigned char* pixel)
{
	float X, Y;

	VECTOR_2D Tx, Ty, T, V12, V13;
	VECTOR_2D Orig = { v1->y, v1->z };

	V12.y = v2->y - v1->y;
	V12.z = v2->z - v1->z;

	V13.y = v3->y - v1->y;
	V13.z = v3->z - v1->z;

	Tx.y = v1->y + (y / 250.0f)*(V12.y);
	Tx.z = v1->z + (y / 250.0f)*(V12.z);

	Ty.y = v1->y + (z / 250.0f)*(V13.y);
	Ty.z = v1->z + (z / 250.0f)*(V13.z);

	parallelogram_law((&T), (&Tx), (&Ty), (&Orig));

	if (v1->y <= v2->y && v1->y <= v3->y)
	{
		X = v1->y + T.y;
		Y = v1->z + T.z;
	}
	else if (v1->y > v2->y && v1->y <= v3->y)
	{
		X = v2->y + T.y;
		Y = v2->z + T.z;
	}
	else if (v1->y <= v2->y && v1->y > v3->y)
	{
		X = v3->y + T.y;
		Y = v3->z + T.z;
	}	

	if (X <= 500 && Y <= 500 && X >= 0 && Y >= 0)
	{
		unsigned char red   = pixel[0];
		unsigned char green = pixel[1];
		unsigned char blue  = pixel[2];

		SET_PIXEL(fb, (int)X, (int)Y, RGB_COMBINE(blue, green, red));
	}
}

void texture_faces(unsigned char* fb, TEXTURE* tx, BMP* bitmap)
{
	unsigned int w = bitmap->width;
	unsigned int h = bitmap->height;

	float x_scale = (float)w / 250.0f;
	float y_scale = (float)h / 250.0f;

	for (size_t i = 0; i < 250; i++)
	{
		for (size_t j = 0; j < 250; j++)
		{
			unsigned char* pixel = &PIXEL((bitmap), int(i* x_scale), int(j* y_scale));
			transform(fb, &tx->v1, &tx->v2, &tx->v3, 0.0f, i, j, pixel);
		}
	}
}

void cube_texture_cube(unsigned char* fb, CUBE* cu, BMP* bitmap)
{
	TEXTURE faces[6] = {
		{ cu->vertices[0], cu->vertices[1], cu->vertices[2], cu->vertices[3] },
		{ cu->vertices[4], cu->vertices[5], cu->vertices[6], cu->vertices[7] },
		{ cu->vertices[0], cu->vertices[2], cu->vertices[4], cu->vertices[6] },
		{ cu->vertices[1], cu->vertices[3], cu->vertices[5], cu->vertices[7] },
		{ cu->vertices[2], cu->vertices[3], cu->vertices[6], cu->vertices[7] },
		{ cu->vertices[0], cu->vertices[1], cu->vertices[4], cu->vertices[5] }
	};

	for (size_t i = 0; i < 6; i++)
		texture_faces(fb, &faces[i], bitmap);
}

void bitmap_creation(const char* bmp_image_address, BMP* bitmap)
{
	if (!bmp_image_address || !bitmap)
		return;

	FILE* f = fopen(bmp_image_address, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f);
	bitmap->width = *(unsigned int*)&info[18];
	bitmap->height = *(unsigned int*)&info[22];
	unsigned int size = WINDOW_ALIGN((bitmap->width * bitmap->height * 3));
	bitmap->data = (unsigned char*)malloc(size);
	fread(bitmap->data, sizeof(unsigned char), size, f);
	fclose(f);
}

void release_bitmap(BMP* bitmap)
{
	free(bitmap->data);
	bitmap->data = NULL;
	bitmap->width = 0;
	bitmap->height = 0;
}
