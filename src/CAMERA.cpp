#include "CAMERA.h"
#include <cmath>

void register_camera(CAMERA* cam, VERTEX* position)
{
	if (!cam)
		return;

	float x = position->x;
	float y = position->y;
	float z = position->z;

	float size = sqrt((x*x)+(y*y)+(z*z));
	x /= size;
	y /= size;
	z /= size;

	float epsilon = 0.0000000001f;

	cam->view_z_rot = RADIAN_TO_DEGREE( -(atan(y / (x + epsilon))));
	cam->view_y_rot = RADIAN_TO_DEGREE( +(asin(z)));

	cam->scale = 250.0f / (epsilon + size);
	cam->point_size = 1 + (cam->scale / 36.25f);
	cam->position = *position;

	cam->ritcol.x_head = { 35.0f, 0.0f, 0.0f };
	cam->ritcol.y_head = { 0.0f, 35.0f, 0.0f };
	cam->ritcol.z_head = { 0.0f, 0.0f, -35.0f };
}
