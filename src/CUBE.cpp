#include "CUBE.h"
#include "GENERAL_COLORS.h"
#include <cmath>

enum RITCOL_COLOR
{
	R_RED = 0x000000FF,
	R_GREEN = 0x0000FF00,
	R_BLUE = 0x00FF0000
};
enum RITCOL_COLOR_ID
{
	RED = 0x000000FF,
	GREEN = 0x0000FF00,
	BLUE = 0x00FF0000
};
void line_impl(unsigned char* fb, VERTEX* v1, VERTEX* v2)
{
	int dx, dy, sdx, sdy, px, py, dxabs, dyabs;
	double slope;
	double x0 = (double)(v1->y);
	double y0 = (double)(v1->z);
	double x = (double)(v2->y);
	double y = (double)(v2->z);

	dx = x - x0;
	dy = y - y0;
	dxabs = abs(dx);
	dyabs = abs(dy);
	sdx = sgn(dx);
	sdy = sgn(dy);
	if (dxabs >= dyabs) {
		slope = (double)dy / (double)dx;
		for (int i = 0; i != dx; i += sdx) {
			px = i + x0;
			py = slope*i + y0;
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)
				SET_PIXEL(fb, px, py, GENERAL_COLORS::GEN_COL_GRAY);
		}
	}
	else {
		slope = (double)dx / (double)dy;
		for (int i = 0; i != dy; i += sdy) {
			px = slope*i + x0;
			py = i + y0;
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)
				SET_PIXEL(fb, px, py, GENERAL_COLORS::GEN_COL_GRAY);
		}
	}
}

void bullet_impl(unsigned char* fb, CAMERA* cam, VERTEX* v)
{
	for (float i = 0; i < 360.0f; i += 5.0f)
	{
		for (float j = 0; j < cam->point_size; j++)
		{
			int px = v->y + j*cos(DEG_TO_RADIAN(i));
			int py = v->z + j*sin(DEG_TO_RADIAN(i));
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)
				SET_PIXEL(fb, px, py, GENERAL_COLORS::GEN_COL_ORANGE);
		}
	}
}
void draw_vertices(unsigned char* fb, CUBE* cu, CAMERA* cam)
{
	for (size_t i = 0; i < 8; i++)
	{
		VERTEX* v = &cu->vertices[i];
		v->x = 250 + cam->scale*(v->x);
		v->y = 250 + cam->scale*(v->y);
		v->z = 250 + cam->scale*(v->z);
		bullet_impl(fb, cam, v);
	}
}

void draw_lines(unsigned char* fb, CUBE* cu, CAMERA* cam)
{
	for (size_t i = 0; i < 12; i++)
	{
		VERTEX* v1 = &cu->lines[i].vertex1;
		VERTEX* v2 = &cu->lines[i].vertex2;
		v1->x = 250 + cam->scale*(v1->x);
		v1->y = 250 + cam->scale*(v1->y);
		v1->z = 250 + cam->scale*(v1->z);
		v2->x = 250 + cam->scale*(v2->x);
		v2->y = 250 + cam->scale*(v2->y);
		v2->z = 250 + cam->scale*(v2->z);
		line_impl(fb, v1, v2);
	}
}

void init_scene(unsigned char* fb,
	            unsigned int   fb_bytes, 
	            CUBE*          cu, 
	            VERTEX*        cube_vertices,
	            CAMERA*        cam, 
	            VERTEX*        cam_position,
	            GENERAL_COLORS cube_color)
{
	memset(fb, 0x00, fb_bytes);
	register_camera(cam, cam_position);
	cu->vertices[0] = cube_vertices[0]; 
	cu->vertices[1] = cube_vertices[1]; 
	cu->vertices[2] = cube_vertices[2]; 
	cu->vertices[3] = cube_vertices[3]; 
	cu->vertices[4] = cube_vertices[4]; 
	cu->vertices[5] = cube_vertices[5]; 
	cu->vertices[6] = cube_vertices[6]; 
	cu->vertices[7] = cube_vertices[7]; 

	cu->color = cube_color;
}

void update_lines_from_vertices(CUBE* cu)
{
	cu->lines[0] = { cu->vertices[0] , cu->vertices[1] };
	cu->lines[1] = { cu->vertices[0] , cu->vertices[2] };
	cu->lines[2] = { cu->vertices[1] , cu->vertices[3] };
	cu->lines[3] = { cu->vertices[2] , cu->vertices[3] };
	cu->lines[4] = { cu->vertices[4] , cu->vertices[5] };
	cu->lines[5] = { cu->vertices[4] , cu->vertices[6] };
	cu->lines[6] = { cu->vertices[5] , cu->vertices[7] };
	cu->lines[7] = { cu->vertices[6] , cu->vertices[7] };
	cu->lines[8] = { cu->vertices[0] , cu->vertices[4] };
	cu->lines[9] = { cu->vertices[3] , cu->vertices[7] };
	cu->lines[10] = { cu->vertices[1] , cu->vertices[5] };
	cu->lines[11] = { cu->vertices[2] , cu->vertices[6] };
}


void ritcol_line_impl(unsigned char* fb, VERTEX* v1, VERTEX* v2, int id)
{
	int dx, dy, sdx, sdy, px, py, dxabs, dyabs;
	double slope;
	double x0 = (double)(v1->y);
	double y0 = (double)(v1->z);
	double x = (double)(v2->y);
	double y = (double)(v2->z);

	dx = x - x0;
	dy = y - y0;
	dxabs = abs(dx);
	dyabs = abs(dy);
	sdx = sgn(dx);
	sdy = sgn(dy);
	if (dxabs >= dyabs) {
		slope = (double)dy / (double)dx;
		for (int i = 0; i != dx; i += sdx) {
			px = i + x0;
			py = slope*i + y0;
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0) {
				switch (id)
				{
				case RITCOL_COLOR_ID::RED:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_RED);
					break;
				case RITCOL_COLOR_ID::GREEN:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_GREEN);
					break;
				case RITCOL_COLOR_ID::BLUE:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_BLUE);
					break;
				}
			}
		}
	}
	else {
		slope = (double)dx / (double)dy;
		for (int i = 0; i != dy; i += sdy) {
			px = slope*i + x0;
			py = i + y0;
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0) {
				switch (id)
				{
				case RITCOL_COLOR_ID::RED:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_RED);
					break;
				case RITCOL_COLOR_ID::GREEN:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_GREEN);
					break;
				case RITCOL_COLOR_ID::BLUE:
					SET_PIXEL(fb, px, py, RITCOL_COLOR::R_BLUE);
					break;
				}
			}
		}
	}
}

void letter_impl(unsigned char* fb, unsigned char lett, unsigned int color)
{
	switch (lett)
	{
	case 'X':
		for (int i = 5; i <= 10; i++) {
			SET_PIXEL(fb, i, i, color);
			SET_PIXEL(fb, i, (15 - i), color);
		}
		break;
	case 'Y':
		for (int i = 5; i <= 8; i++) {
			SET_PIXEL(fb, (i-1), (i + 10), color);
			SET_PIXEL(fb, (15 - i), (i + 10), color);
			SET_PIXEL(fb, 7, (i + 14), color);
		}
		break;
	case 'Z':
		for (int i = 5; i <= 10; i++) {
			SET_PIXEL(fb, i, 25, color);
			SET_PIXEL(fb, i, 30, color);
			SET_PIXEL(fb, (15 - i), (i + 20), color);
		}
		break;
	}
}

void ritcol_letters_impl(unsigned char* fb, CAMERA* cam)
{
	unsigned char x = cam->ritcol.x_letter;
	unsigned char y = cam->ritcol.y_letter;
	unsigned char z = cam->ritcol.z_letter;

	letter_impl(fb, x, RITCOL_COLOR::R_GREEN);
	letter_impl(fb, y, RITCOL_COLOR::R_BLUE);
	letter_impl(fb, z, RITCOL_COLOR::R_RED);
}

void draw_ritcol(unsigned char* fb, CAMERA* cam)
{
	VERTEX center_of_ritcol = {50, 50, 50};
	cam->ritcol.x_head.x += 50;
	cam->ritcol.x_head.y += 50;
	cam->ritcol.x_head.z += 50;

	cam->ritcol.y_head.x += 50;
	cam->ritcol.y_head.y += 50;
	cam->ritcol.y_head.z += 50;

	cam->ritcol.z_head.x += 50;
	cam->ritcol.z_head.y += 50;
	cam->ritcol.z_head.z += 50;

	VERTEX* v1 = &cam->ritcol.x_head;
	VERTEX* v2 = &cam->ritcol.y_head;
	VERTEX* v3 = &cam->ritcol.z_head;
	ritcol_line_impl(fb, &center_of_ritcol, v1, RITCOL_COLOR_ID::GREEN);
	ritcol_line_impl(fb, &center_of_ritcol, v2, RITCOL_COLOR_ID::BLUE);
	ritcol_line_impl(fb, &center_of_ritcol, v3, RITCOL_COLOR_ID::RED);

	ritcol_letters_impl(fb, cam);
}
