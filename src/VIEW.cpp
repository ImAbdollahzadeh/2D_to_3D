#include "VIEW.h"
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#define WINDOW_ALIGN(X) ((X+31)&~31)

HBITMAP create_bmp(HDC dc, void* fb) {
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 500;
	bmi.bmiHeader.biHeight = -500;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	void* fb_ptr = NULL;
	HBITMAP hbitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void**)&fb_ptr, NULL, 0);
	unsigned long long* dst = (unsigned long long*)fb_ptr;
	unsigned long long* org = (unsigned long long*)fb;
	unsigned int step = WINDOW_ALIGN(500 * 500 * 3);
	do { *dst++ = *org++; } while (step -= 8);
	return hbitmap;
}

void blit(HWND hwnd, unsigned char* fb)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, create_bmp(hdc, fb));
	BitBlt(hdc, 0, 0, 500, 500, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	EndPaint(hwnd, &ps);
}

void final_view(float z, float y, VERTEX* v)
{
	float tmp_y = v->y;
	float tmp_x = v->x;
	float tmp_z = v->z;

	v->x = tmp_x*cos(DEG_TO_RADIAN(z)) - tmp_y*sin(DEG_TO_RADIAN(z));
	v->y = tmp_x*sin(DEG_TO_RADIAN(z)) + tmp_y*cos(DEG_TO_RADIAN(z));
	v->z = tmp_z;

	tmp_y = v->y;
	tmp_x = v->x;
	tmp_z = v->z;

	v->x = tmp_x*cos(DEG_TO_RADIAN(y)) - tmp_z*sin(DEG_TO_RADIAN(y));
	v->z = tmp_x*sin(DEG_TO_RADIAN(y)) + tmp_z*cos(DEG_TO_RADIAN(y));
	v->y = tmp_y;
}

void rotations_2D(CAMERA* cam, VERTEX* v)
{
	float y_rot = cam->view_y_rot;
	float z_rot = cam->view_z_rot;
	float x_rot = cam->view_x_rot;

	final_view(z_rot, y_rot, v);
}

void wait(void)
{ 
	for (int i = 0; i < 15000000; i++) 
		int s = 0;
}

void scene_view(HWND hwnd, CUBE* cu, CAMERA* cam, LIGHT* lt, TEXTURE* texture, unsigned char* fb)
{
	for (size_t i = 0; i < 8; i++)
		rotations_2D(cam, &cu->vertices[i]);

	rotations_2D(cam, &cam->ritcol.x_head);
	rotations_2D(cam, &cam->ritcol.y_head);
	rotations_2D(cam, &cam->ritcol.z_head);

	update_lines_from_vertices(cu);
	draw_vertices(fb, cu, cam);

	//paint_cube(fb, cu, lt);

	if (texture) {
		BMP bitmap;
		bitmap_creation("bob_lila.bmp", &bitmap);
		cube_texture_cube(fb, cu, &bitmap);
		release_bitmap(&bitmap);
	}		

	draw_lines(fb, cu, cam);
	draw_ritcol(fb, cam);
	blit(hwnd, fb);
}

void paint_cube(unsigned char* fb, CUBE* cu, LIGHT* lt)
{
	cube_paint_cube(fb, cu, lt);
}
