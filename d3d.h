#pragma once
#include "d3d9.h"
#include "d3dx9tex.h"
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

enum MouseState
{
	MouseState_None,
	MouseState_Down,
	MouseState_Up,
	MouseState_Hover
};

#define D3DFVF_VERTEX  (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct
{
	float x , y , z , rhw ;
	D3DCOLOR  diffuse ;
	float tu, tv;
}D3DVERTEX ;

extern LPDIRECT3D9			d3d_3D ;
extern LPDIRECT3DDEVICE9	d3d_Device ;

void d3dInit();
void d3dRelease();
BOOL d3dCreate( HWND hWnd , int width , int height , BOOL IsWindow  );
BOOL d3dSetDisplaySize( HWND hWnd , int width , int height );
BOOL d3dDeviceCreate( HWND hWnd , BOOL IsWindow );
void d3dClear( UINT color = 0 );

class d3dHdc 
{
private :
	HDC m_hdc ;
	LPDIRECT3DSURFACE9 m_Surface ;

public :
	void Release();
	inline operator HDC(){ return m_hdc ;};
public :
	d3dHdc();
	~d3dHdc();
};


class CD3DTexture
{
public:
	int					m_Width ;
	int					m_Height ;
	LPDIRECT3DTEXTURE9	m_Texture ;
public :
	void BltFast( int x , int y ,DWORD dwDiffuse=-1);
	void BltFast( int l , int t , int r , int b,DWORD dwDiffuse=-1);
public :
	BOOL CreateFromFile( LPCTSTR file );
	BOOL CreateFromMemory( LPCVOID pSrcData ,UINT SrcDataSize );
	void Release();
	inline operator LPDIRECT3DTEXTURE9(){ return m_Texture ;};
public :
	CD3DTexture();
	~CD3DTexture();
};

#define D3DCONTROL 100000
#define D3DBUTTON  D3DCONTROL+10000

class CD3DText ////
{
public:
	RECT m_rt;
	LPWSTR m_lpszText;
	LPD3DXFONT m_lpD3DFont;
	DWORD m_dwTextColor;

	void Init(RECT rt,LPWSTR lpszText,LPD3DXFONT lpD3DFont,DWORD dwTextColor)
	{
		m_rt=rt;
		m_lpszText=lpszText;
		m_lpD3DFont=lpD3DFont;
		m_dwTextColor=dwTextColor;
	}
};

extern int g_nLMouseState;
extern POINT g_ptCursorPos;

class CD3DButton////
{
public:
	RECT m_rtWindow;
	CD3DText m_D3DText;
	CD3DTexture* m_pD3DText[4];//0=������1=���¡�2=������3=��Ч
	bool m_bValid;
	
private:
	int m_nMouseState; //���״̬

public:
	CD3DButton(){};

	CD3DButton(int nX,int nY,int nWidth,int nHeight,LPD3DXFONT lpD3DFont,LPWSTR lpsz,CD3DTexture* pD3DTextNormal,CD3DTexture* pD3DTextDown,CD3DTexture* pD3DTextHover,CD3DTexture* pD3DTextInvalid)
	{
		Init(nX,nY,nWidth,nHeight,lpD3DFont,lpsz,pD3DTextNormal,pD3DTextDown,pD3DTextHover,pD3DTextInvalid);
	}
	CD3DButton(RECT rt,LPD3DXFONT lpD3DFont,LPWSTR lpsz,CD3DTexture* pD3DTextNormal,CD3DTexture* pD3DTextDown,CD3DTexture* pD3DTextHover,CD3DTexture* pD3DTextInvalid)
	{
		Init(rt.left,rt.top,rt.right-rt.left,rt.bottom-rt.top,lpD3DFont,lpsz,pD3DTextNormal,pD3DTextDown,pD3DTextHover,pD3DTextInvalid);
	}
	void Init(int nX,int nY,int nWidth,int nHeight,LPD3DXFONT lpD3DFont,LPWSTR lpsz,CD3DTexture* pD3DTextNormal,CD3DTexture* pD3DTextDown,CD3DTexture* pD3DTextHover,CD3DTexture* pD3DTextInvalid)
	{
		m_rtWindow.left=nX;
		m_rtWindow.top=nY;
		m_rtWindow.right=nX+nWidth;
		m_rtWindow.bottom=nY+nHeight;
		
		m_D3DText.Init(m_rtWindow,lpsz,lpD3DFont,D3DCOLOR_XRGB(221,197,147));
		m_bValid=true;
		m_nMouseState=MouseState_None;

		m_pD3DText[0]=pD3DTextNormal;
		m_pD3DText[1]=pD3DTextDown;
		m_pD3DText[2]=pD3DTextHover;
		m_pD3DText[3]=pD3DTextInvalid;
	}
	void LoadTexture(CD3DTexture* pD3DTextNormal,CD3DTexture* pD3DTextDown,CD3DTexture* pD3DTextHover,CD3DTexture* pD3DTextInvalid)
	{
		m_pD3DText[0]=pD3DTextNormal;
		m_pD3DText[1]=pD3DTextDown;
		m_pD3DText[2]=pD3DTextHover;
		m_pD3DText[3]=pD3DTextInvalid;
	}
	void Render()
	{
		if (!m_bValid)
		{
			if (m_pD3DText[3])
				m_pD3DText[3]->BltFast(m_rtWindow.left,m_rtWindow.top);
			return;
		}
		m_nMouseState=GetMouseStateFromRect(m_rtWindow,g_ptCursorPos);
		switch(m_nMouseState)
		{
		case MouseState_None:
			if(m_pD3DText[0])
				m_pD3DText[0]->BltFast(m_rtWindow.left,m_rtWindow.top);
			break;
		case MouseState_Down:
			if(m_pD3DText[1])
			m_pD3DText[1]->BltFast(m_rtWindow.left,m_rtWindow.top);
			break;
		case MouseState_Hover:
			if(m_pD3DText[2])
			m_pD3DText[2]->BltFast(m_rtWindow.left,m_rtWindow.top);
			break;
		case MouseState_Up:
			if(m_pD3DText[2])
			m_pD3DText[2]->BltFast(m_rtWindow.left,m_rtWindow.top);
			break;
		}

		if (MouseState_Down==m_nMouseState)
		{
			if (m_D3DText.m_lpD3DFont!=NULL && m_D3DText.m_lpszText!=L"")
				m_D3DText.m_lpD3DFont->DrawTextW(NULL,m_D3DText.m_lpszText,-1,&m_D3DText.m_rt,DT_CENTER|DT_VCENTER,m_D3DText.m_dwTextColor);
		}
		else
		{
			if (m_D3DText.m_lpD3DFont!=NULL && m_D3DText.m_lpszText!=L"")
				m_D3DText.m_lpD3DFont->DrawTextW(NULL,m_D3DText.m_lpszText,-1,&m_D3DText.m_rt,DT_CENTER|DT_VCENTER,m_D3DText.m_dwTextColor);
		}

	}
	RECT GetRect()
	{
		return m_rtWindow;
	}
	int GetState()
	{
		return m_nMouseState;
	}
	void SetPos(int nX,int nY,int nWidth,int nHeight)
	{
		m_rtWindow.left=nX;
		m_rtWindow.top=nY;
		m_rtWindow.right=nX+nWidth;
		m_rtWindow.bottom=nY+nHeight;
	}
	void SetFont(LPD3DXFONT lpD3DFont)
	{
		m_D3DText.m_lpD3DFont=lpD3DFont;
	}
	void SetTextColor(DWORD dwTextColor)
	{
		m_D3DText.m_dwTextColor=dwTextColor;
	}
	
	int GetMouseStateFromRect(RECT rt,POINT pt)
	{
		if (PtInRect(&rt,pt))
			if (g_nLMouseState==MouseState_Down)
				return MouseState_Down;
			else
			{
				if (g_nLMouseState==MouseState_Up)
					return MouseState_Up;
				else
					return MouseState_Hover;
			}
			else  //���������ʾ�Ĵ���
				return MouseState_None;
	}
};

class d3dEdit
{
public:
	HWND m_hWnd; //�����ھ��
	HDC m_hDC; //������DC
	RECT m_rt; //�༭�����
	LPD3DXFONT m_lpFont; //��ʾ����
	LPWSTR m_lpText; //��ʾ�ı�
	DWORD m_dwTextColor; //�ı���ɫ
	DWORD m_dwFormat; //�ı������ʽ
	int m_nLimitLength;
	bool m_bVisible;

private:
	POINT m_ptCaret; //�����λ��
	int m_nAlpha;
	DWORD m_nDiffuse;
	bool m_bIsBrightening;
	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;
	
public:
	void Init(HWND hWnd,LPD3DXFONT lpFont,int nX,int nY,int nWidth,int nHeight);
	void SetEditPos(int nX,int nY,int nWidth,int nHeight);
	void UpdateCaret();
	void SetFont(LPD3DXFONT lpFont);
	void Render();
	void SetFormat(DWORD dwFormat);
	void SetLimitLength(int nLength);
};
