#include "stdafx.h"
#include "Input.h"
LPDIRECTINPUT8 g_lpInput;
LPDIRECTINPUTDEVICE8 g_lpInputDevice;
HWND m_hwnd;  
char keyBuffer[256];
DIMOUSESTATE dims;

BOOL InitKeyBoard(HINSTANCE hInst)
{
	if (DirectInput8Create(hInst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&g_lpInput,NULL)!=DI_OK)
		return false;
	if (g_lpInput->CreateDevice(GUID_SysKeyboard,&g_lpInputDevice,0)!=DI_OK)
		return false;
	if (g_lpInputDevice->SetDataFormat(&c_dfDIKeyboard)!=DI_OK)
		return false;
	if (g_lpInputDevice->SetCooperativeLevel(m_hwnd,DISCL_BACKGROUND|DISCL_NONEXCLUSIVE)!=DI_OK)
		return false;
	if (g_lpInputDevice->Acquire()!=DI_OK)
		return false;
	return true;  
}  
BOOL IsKeyPressed(int key)  
{
	if (g_lpInputDevice->GetDeviceState(sizeof(keyBuffer),(LPVOID)keyBuffer)!=DI_OK)
		return false;
	if (keyBuffer[key] & 0x80)
		return true;  
	return false;  
}
BOOL InitMouse(HINSTANCE hInst)
{
	if (DirectInput8Create(hInst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&g_lpInput,0)!=DI_OK)
		return FALSE;
	if (g_lpInput->CreateDevice(GUID_SysMouse,&g_lpInputDevice,0)!=DI_OK)
		return FALSE; 
	//设置鼠标协作等级，设置为后台/非独占模式
	if (g_lpInputDevice->SetCooperativeLevel(m_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
		return FALSE; 
	//设置数据格式,鼠标对应的数据格式为c_dfDIMouse
	if (g_lpInputDevice->SetDataFormat(&c_dfDIMouse)!=DI_OK)
		return FALSE;	
	//获取鼠标
	if (g_lpInputDevice->Acquire()!=DI_OK)
		return FALSE;
	return TRUE;
}
BOOL IsMousePressed(int key)
{
	ZeroMemory( &dims, sizeof(dims));
	g_lpInputDevice->GetDeviceState( sizeof(DIMOUSESTATE), &dims );
	// 	strNewText.Format("L=%d R=%d M=%d X=%4d Y=%4d",  //写入结果,分别为L左
	// 		   
	// 		   //键,R右键,M中键,X鼠标X
	// 		   
	// 		   //值,Y鼠标Y值.前三个值,1
	// 		   
	// 		   //表示按下,0为弹起
	// 		   
	// 		   (dims.rgbButtons[0] & 0x80) ? 1 : 0,
	// 		   (dims.rgbButtons[1] & 0x80) ? 1 : 0,
	// 		   (dims.rgbButtons[2] & 0x80) ? 1 : 0,
	// 		   point.x,point.y
	// 		   );   
	return TRUE;
}
void Release()  
{  
	g_lpInput->Release();  
	g_lpInputDevice->Release();  
}
