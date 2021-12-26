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
	//�������Э���ȼ�������Ϊ��̨/�Ƕ�ռģʽ
	if (g_lpInputDevice->SetCooperativeLevel(m_hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)!=DI_OK)
		return FALSE; 
	//�������ݸ�ʽ,����Ӧ�����ݸ�ʽΪc_dfDIMouse
	if (g_lpInputDevice->SetDataFormat(&c_dfDIMouse)!=DI_OK)
		return FALSE;	
	//��ȡ���
	if (g_lpInputDevice->Acquire()!=DI_OK)
		return FALSE;
	return TRUE;
}
BOOL IsMousePressed(int key)
{
	ZeroMemory( &dims, sizeof(dims));
	g_lpInputDevice->GetDeviceState( sizeof(DIMOUSESTATE), &dims );
	// 	strNewText.Format("L=%d R=%d M=%d X=%4d Y=%4d",  //д����,�ֱ�ΪL��
	// 		   
	// 		   //��,R�Ҽ�,M�м�,X���X
	// 		   
	// 		   //ֵ,Y���Yֵ.ǰ����ֵ,1
	// 		   
	// 		   //��ʾ����,0Ϊ����
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
