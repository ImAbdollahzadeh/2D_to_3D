#include "PAINT.h"
#include <cmath>

typedef struct _TRIANGLE {
	VERTEX real_v1;
	VERTEX real_v2;
	VERTEX real_v3;
} TRIANGLE;

typedef struct _PARALLELOGRAM {
	VERTEX   v1;
	VERTEX   v2;
	VERTEX   v3;
	VERTEX   v4;
	TRIANGLE triangles[2];
} PARALLELOGRAM;

#define CROSS_PRODUCT(VEC1, VEC2, RESULT) do {     \
RESULT->x = (VEC1->y*VEC2->z) - (VEC1->z*VEC2->y); \
RESULT->y = (VEC1->z*VEC2->x) - (VEC1->x*VEC2->z); \
RESULT->z = (VEC1->x*VEC2->y) - (VEC1->y*VEC2->x); \
} while (0)

#define calculate_plane_normal(FACE, NORM) do {    \
VERTEX A;                                          \
A.x = FACE->v1.x - FACE->v2.x;                     \
A.y = FACE->v1.y - FACE->v2.y;                     \
A.z = FACE->v1.z - FACE->v2.z;                     \
                                                   \
VERTEX B;                                          \
B.x = FACE->v1.x - FACE->v3.x;                     \
B.y = FACE->v1.y - FACE->v3.y;                     \
B.z = FACE->v1.z - FACE->v3.z;                     \
                                                   \
VERTEX N;                                          \
CROSS_PRODUCT((&A),(&B),(&N));                     \
float size = sqrt((N.x*N.x)+(N.y*N.y)+(N.z*N.z));  \
NORM->x = N.x / (size);                            \
NORM->y = N.y / (size);                            \
NORM->z = N.z / (size);                            \
} while(0);

#define paint_line_impl(fb, v1, v2, color) do {                               \
	float x0 = (float)(v1->y);												  \
	float y0 = (float)(v1->z);												  \
	float x =  (float)(v2->y);												  \
	float y =  (float)(v2->z);												  \
	int dx = x - x0;														  \
	int dy = y - y0;														  \
	int dxabs = abs(dx);													  \
	int dyabs = abs(dy);													  \
	int sdx = sgn(dx);														  \
	int sdy = sgn(dy);														  \
	if (dxabs >= dyabs) {													  \
		float slope = (float)dy / (float)dx;								  \
		for (int i = 0; i != dx; i += sdx) {	     						  \
			int px = i + x0;												  \
			int py = slope*i + y0;											  \
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)				  \
				SET_BIG_PIXEL(fb, px, py, color);							  \
		}																	  \
	}																		  \
	else {																	  \
		float slope = (float)dx / (float)dy;								  \
		for (int i = 0; i != dy; i += sdy) {			     			      \
			int px = slope*i + x0;											  \
			int py = i + y0;												  \
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)				  \
				SET_BIG_PIXEL(fb, px, py, color);							  \
		}																	  \
	}																		  \
}while (0);																	  

void debug_paint_line_impl(unsigned char* fb, VERTEX* v1, VERTEX* v2, unsigned int color) {                               
	float x0 = (float)(v1->y);												  
	float y0 = (float)(v1->z);												  
	float x =  (float)(v2->y);												  
	float y =  (float)(v2->z);												  
	int dx = x - x0;														  
	int dy = y - y0;														  
	int dxabs = abs(dx);													  
	int dyabs = abs(dy);													  
	int sdx = sgn(dx);														  
	int sdy = sgn(dy);														  
	if (dxabs >= dyabs) {													  
		float slope = (float)dy / (float)dx;								  
		for (int i = 0; i != dx; i += sdx) {							  
			int px = i + x0;												  
			int py = slope*i + y0;											  
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)				  
				SET_PIXEL(fb, px, py, color);							  
		}																	  
	}																		  
	else {																	  
		float slope = (float)dx / (float)dy;								  
		for (int i = 0; i != dy; i += sdy) {						      
			int px = slope*i + x0;											  
			int py = i + y0;												  
			if (px <= 500 && py <= 500 && px >= 0 && py >= 0)				  
				SET_PIXEL(fb, px, py, color);							  
		}																	  
	}																		  
}
#define paint_tri_impl(fb, t, color) do {                       \
	VERTEX orig = t->real_v1;									\
	VERTEX v2 = t->real_v2;										\
	VERTEX v3 = t->real_v3;										\
	VERTEX trg;													\
																\
	float epsilon = 0.0000000001f;								\
																\
	float m = (v3.z - v2.z)/(epsilon + (v3.y - v2.y));			\
																\
	float y_min = v3.y < v2.y ? v3.y : v2.y;					\
	float y_max = v3.y < v2.y ? v2.y : v3.y;					\
																\
	/* prevent -/+ infinity flicker	*/							\
	if (m > 100.0f || m < -100.0f)	     						\
		return;													\
																\
	float delta_y = (y_max - y_min) / 1000.0f;					\
																\
	float constant = (v2.z - m*v2.y);							\
	float i = 0.0f;												\
	float delta = 0.0f;											\
	while (i < 1001.0f)											\
	{															\
		trg.y = y_min + delta;									\
		trg.z = m * trg.y + constant;							\
		paint_line_impl(fb, (&orig), (&trg), color);			\
		i++;													\
		delta += delta_y;										\
	}															\
} while(0);

void debug_paint_tri_impl(unsigned char*fb, TRIANGLE* t, unsigned int color)  {                       
	VERTEX orig = t->real_v1;									
	VERTEX v2 = t->real_v2;										
	VERTEX v3 = t->real_v3;										
	VERTEX trg;													
																
	float epsilon = 0.0000000001f;								
																
	float m = (v3.z - v2.z)/(epsilon + (v3.y - v2.y));			
																
	float y_min = v3.y < v2.y ? v3.y : v2.y;					
	float y_max = v3.y < v2.y ? v2.y : v3.y;
	float z_min = v3.z < v2.z ? v3.z : v2.z;
	float z_max = v3.z < v2.z ? v2.z : v3.z;
																
	/* prevent -/+ infinity flicker	*/							
	if (m > 100.0f || m < -100.0f)							
		return;													
																
	float delta_y = (y_max - y_min) / 1000.0f;	
	float constant = (v2.z - m*v2.y);

	float i = 0.0f;												
	float delta = 0.0f;											
	while (i < 1001.0f)											
	{															
		trg.y = y_min + delta;
		trg.z = m * trg.y + constant;	
		debug_paint_line_impl(fb, (&orig), (&trg), color);			
		i++;													
		delta += delta_y;										
	}															
} 

void paint_Parallelogram(unsigned char* fb, PARALLELOGRAM* p, unsigned int color)
{	
	p->triangles[0] = { p->v2, p->v3, p->v4 };
	p->triangles[1] = { p->v1, p->v2, p->v3 };

	paint_tri_impl(fb, (&p->triangles[0]), color);
	paint_tri_impl(fb, (&p->triangles[1]), color);
}

void cube_paint_cube(unsigned char* fb, CUBE* cu, LIGHT* lt)
{
	// there are 6 faces, but there are only 3 of them visible

	PARALLELOGRAM faces[6] = {
		{ cu->vertices[0], cu->vertices[1], cu->vertices[2], cu->vertices[3] },
		{ cu->vertices[4], cu->vertices[5], cu->vertices[6], cu->vertices[7] },
		{ cu->vertices[0], cu->vertices[2], cu->vertices[4], cu->vertices[6] },
		{ cu->vertices[1], cu->vertices[3], cu->vertices[5], cu->vertices[7] },
		{ cu->vertices[2], cu->vertices[3], cu->vertices[6], cu->vertices[7] },
		{ cu->vertices[0], cu->vertices[1], cu->vertices[4], cu->vertices[5] }
	};

	GENERAL_COLORS color = cu->color;
	unsigned int   color_effected_by_light[6];
	VERTEX         normal[6];

	if (lt) {
		for (size_t i = 0; i < 6; i++) {
			calculate_plane_normal((&faces[i]), (&normal[i]));
			light_effect_on_plane(lt, color, &color_effected_by_light[i], &normal[i]);
		}
	}

	for (size_t i = 0; i < 6; i++)
		paint_Parallelogram(fb, &faces[i], (lt)?color_effected_by_light[i]:color);
}
