#include "CUBE.h"
#include "CAMERA.h"
#include "VIEW.h"
#include "LIGHT.h"
#include "TEXTURE.h"
#include <cmath>

const unsigned int FRAMEBUFFER_SIZE = WINDOW_ALIGN(500 * 500 * 3);
unsigned char      FRAMEBUFFER[FRAMEBUFFER_SIZE];

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ OBJECTS_CREATION ++++++++++++++++++++

CUBE   cube;
CAMERA camera;
VERTEX camera_position = { 0.5f, 0.5f, 0.8f };
VERTEX cube_vertices[8] = {
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, +0.5f, -0.5f },
	{ +0.5f, -0.5f, -0.5f },
	{ +0.5f, +0.5f, -0.5f },
	{ -0.5f, -0.5f, +0.5f },
	{ -0.5f, +0.5f, +0.5f },
	{ +0.5f, -0.5f, +0.5f },
	{ +0.5f, +0.5f, +0.5f }
};
GENERAL_COLORS cube_color = GENERAL_COLORS::GEN_COL_RED;
LIGHT  light;
VERTEX light_source = { 10.0f, 0.0f, 0.0f };

TEXTURE texture;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ END OF OBJECTS_CREATION ++++++++++++

float step = 1.0f;
void example_Z_rotate(float deg, CUBE* cu)
{
	float degree = DEG_TO_RADIAN(deg);
	for (size_t i = 0; i < 8; i++)
	{
		VERTEX* v = &cu->vertices[i];
		float y_tmp = v->y;
		float x_tmp = v->x;

		v->x = x_tmp*cos(degree) - y_tmp*sin(degree);
		v->y = x_tmp*sin(degree) + y_tmp*cos(degree);
	}
}
void example_Y_rotate(float deg, CUBE* cu)
{
	float degree = DEG_TO_RADIAN(deg);
	for (size_t i = 0; i < 8; i++)
	{
		VERTEX* v = &cu->vertices[i];
		float x_tmp = v->x;
		float z_tmp = v->z;

		v->x = x_tmp*cos(degree) - z_tmp*sin(degree);
		v->z = x_tmp*sin(degree) + z_tmp*cos(degree);
	}	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT:
		for (size_t i = 0; i <= 1000; i++)
		{
			init_scene(FRAMEBUFFER, FRAMEBUFFER_SIZE, &cube, cube_vertices, &camera, &camera_position, cube_color);
			//register_light_source(&light, &light_source);
			example_Y_rotate((float)i, &cube);
			scene_view(hwnd, &cube, &camera, NULL, &texture, FRAMEBUFFER);
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			//WAIT;
		}
		break;
	case WM_CLOSE: break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default: break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
	TCHAR szAppName[] = L"Test";
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass)) exit(0);
	HWND hwnd = CreateWindow(szAppName,L"IMAN",WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,0,0,500,500,NULL, NULL,hInstance,NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
