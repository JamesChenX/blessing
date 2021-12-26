#pragma once
#include <dinput.h>
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")

extern LPDIRECTINPUT8 g_lpInput;
extern LPDIRECTINPUTDEVICE8 g_lpInputDevice;
extern HWND m_hwnd;  
extern char keyBuffer[256];
extern DIMOUSESTATE dims;

BOOL InitKeyBoard(HINSTANCE hInst);
BOOL IsKeyPressed(int key);
BOOL InitMouse(HINSTANCE hInst);
BOOL IsMousePressed(int key);
void Release();
