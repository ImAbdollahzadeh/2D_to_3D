#pragma once
#include "VERTEX.h"
#include "GENERAL_COLORS.h"
typedef struct _LIGHT {
	VERTEX       position;
} LIGHT;

void register_light_source(LIGHT* lt, VERTEX* v);
void light_effect_on_plane(LIGHT* lt, GENERAL_COLORS plane_color, unsigned int* effected_color, VERTEX* example_plane_normal);
