#include "LIGHT.h"
#include <cmath>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#define BLUE(CL)   ((CL)>>16)
#define GREEN(CL)  ((CL&0x0000FF00)>>8)
#define RED(CL)    ((CL&0x000000FF))

#define RGB_COMBINE(r, g, b) ((b)<<16) | ((g)<<8) | (r)

#define PI 3.14159265359
#define RADIAN_TO_DEG(rad) ((180.00f/(PI))*rad)
#define DEG_TO_RADIAN(deg) (((PI)/180.00f)*deg)


void register_light_source(LIGHT* lt, VERTEX* v)
{
	if (!lt)
		return;

	lt->position = *v;
}

void light_effect_on_plane(LIGHT* lt, GENERAL_COLORS plane_color, unsigned int* effected_color, VERTEX* example_plane_normal)
{
	if (!lt)
		return;
	
	unsigned int new_color;
	VERTEX plane_normal = *example_plane_normal;
	VERTEX light = lt->position;

	float dot = (plane_normal.x * light.x) + (plane_normal.y * light.y) + (plane_normal.z * light.z);
	float light_vector_size = sqrt((light.x*light.x)+(light.y * light.y)+(light.z*light.z));
	float epsilon = 0.00000000001f;

	float angle_between_plane_and_light = RADIAN_TO_DEG (acos(dot / (light_vector_size)));

	float scale = cos(DEG_TO_RADIAN(angle_between_plane_and_light));

	unsigned char red   = RED  (plane_color);
	unsigned char green = GREEN(plane_color);
	unsigned char blue  = BLUE (plane_color);

	red   = scale * red;
	green = scale * green;
	blue  = scale * blue;

	new_color = RGB_COMBINE(red, green, blue);
	*effected_color = new_color;
}
