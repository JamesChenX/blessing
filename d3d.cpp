#include "stdafx.h"
#include "d3d.h"

int g_nLMouseState=MouseState_None;
POINT g_ptCursorPos;

LPDIRECT3D9			d3d_3D ;
LPDIRECT3DDEVICE9	d3d_Device ;

void d3dInit()
{
	d3d_3D = NULL ;
	d3d_Device = NULL ;
}


void d3dRelease()
{
	if( d3d_3D ) d3d_3D->Release();
	if( d3d_Device ) d3d_Device->Release();
}


BOOL d3dCreate( HWND hWnd , int width , int height , BOOL IsWindow )
{
	if( !d3dSetDisplaySize( hWnd , width , height ))
		return false ;
	if( !d3dDeviceCreate( hWnd , IsWindow ))
		return false ;
	d3dClear();
	return true ;
}


BOOL d3dSetDisplaySize( HWND hWnd , int width , int height )
{
	RECT rect ;
	HDC hdc ;
	hdc = GetDC( hWnd );
	rect.left = (GetDeviceCaps( hdc , HORZRES ) - width )/2;
	rect.top = (GetDeviceCaps( hdc , VERTRES ) - height )/2;
	ReleaseDC( hWnd , hdc );
	rect.right = rect.left + width ;
	rect.bottom = rect.top + height ;
	AdjustWindowRectEx( &rect , GetWindowLong( hWnd , GWL_STYLE ) , (GetMenu( hWnd)!=NULL) , GetWindowLong( hWnd , GWL_EXSTYLE) );
	MoveWindow( hWnd , rect.left , rect.top , rect.right - rect.left , rect.bottom - rect.top , true );
	return true ;
}


BOOL d3dDeviceCreate( HWND hWnd , BOOL IsWindow  )
{
	d3d_3D =  Direct3DCreate9( D3D_SDK_VERSION );
	if( !d3d_3D )
		return false ;
	D3DDISPLAYMODE d3ddm ;
	if( d3d_3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) != D3D_OK )
		return false ;
	D3DPRESENT_PARAMETERS d3dpp ;
	memset( &d3dpp , 0 , sizeof( d3dpp ));
	d3dpp.Windowed = IsWindow ;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = d3ddm.Format ;
	d3dpp.hDeviceWindow = hWnd ;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER ;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.MultiSampleType=D3DMULTISAMPLE_NONE;

	if( d3d_3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&d3d_Device) != D3D_OK )
		return false ;
	return true ;
}


void d3dClear( UINT color )
{
	d3d_Device->Clear( 0 , 0 , D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER , color , 1.0f , 0 );
}

d3dHdc::d3dHdc()
{
	m_hdc = 0 ;
	m_Surface = 0 ;
	if( !d3d_Device )
		return ;
	if( d3d_Device->GetBackBuffer( 0 , 0 , D3DBACKBUFFER_TYPE_MONO , &m_Surface ) != D3D_OK )
		return ;
	m_Surface->GetDC( &m_hdc );
}

d3dHdc::~d3dHdc()
{
	Release();
}

void d3dHdc::Release()
{
	if( m_Surface )
	{
		if( m_hdc )
			m_Surface->ReleaseDC( m_hdc );
		m_hdc = NULL ;
		m_Surface = NULL ;
	}

}

CD3DTexture::CD3DTexture()
{
	m_Texture = NULL ;
}

CD3DTexture::~CD3DTexture()
{
	Release();
}

void CD3DTexture::Release()
{
	if( m_Texture )
		m_Texture->Release();
	m_Texture = NULL ;
}

BOOL CD3DTexture::CreateFromFile( LPCTSTR file )
{
	D3DXIMAGE_INFO in ;
	memset( &in , 0 , sizeof( in ));
	Release();
 	D3DXCreateTextureFromFileEx(
 		d3d_Device,
 		file,
 		D3DX_DEFAULT_NONPOW2,
 		D3DX_DEFAULT_NONPOW2,
 		0,
 		0,
 		D3DFMT_UNKNOWN,
 		D3DPOOL_MANAGED,
 		D3DX_DEFAULT,
 		D3DX_DEFAULT,
 		0,
 		&in,
 		NULL,
 		&m_Texture
 		);
// 	D3DXCreateTextureFromFile(
// 		d3d_Device,
// 		file,
// 		&m_Texture);
	if( m_Texture == NULL )
		return false ;
	m_Width = in.Width ;
	m_Height = in.Height ;
	return true ;
}

BOOL CD3DTexture::CreateFromMemory( LPCVOID pSrcData ,UINT SrcDataSize )
{
	D3DXIMAGE_INFO in ;
	memset( &in , 0 , sizeof( in ));
	Release();
 	D3DXCreateTextureFromFileInMemoryEx( 
 		d3d_Device ,
 		pSrcData,
 		SrcDataSize,
 		D3DX_DEFAULT_NONPOW2,
 		D3DX_DEFAULT_NONPOW2,
 		0,
 		0,
 		D3DFMT_A8R8G8B8,
 		D3DPOOL_MANAGED,
 		D3DX_DEFAULT,   //重点！重点！重点！
 		D3DX_DEFAULT,
 		0,
 		&in,
 		NULL,
 		&m_Texture
 		);
	if( m_Texture == NULL )
		return false ;
	m_Width = in.Width ;
	m_Height = in.Height ;
	return true ;
}

void CD3DTexture::BltFast(int x, int y,DWORD dwDiffuse)
{
	D3DVERTEX v[4] ;
	memset( v , 0 , sizeof( v ));
	v[0].x = v[3].x = (float)(x) ;
	v[1].x = v[2].x = (float)(x)+m_Width;
	v[0].y = v[1].y = (float)(y);
	v[2].y = v[3].y = (float)(y)+m_Height;
	
	v[0].rhw = v[1].rhw = v[2].rhw = v[3].rhw = 
		v[0].z = v[1].z = v[2].z = v[3].z = 0.5f ;
	
	v[0].diffuse = v[1].diffuse = v[2].diffuse = v[3].diffuse = dwDiffuse ;
	
	v[1].tu = v[2].tu = 1.0f ;
	v[2].tv = v[3].tv = 1.0f ;
	d3d_Device->SetTexture( 0 , m_Texture );
	d3d_Device->SetFVF( D3DFVF_VERTEX  );
 	d3d_Device->DrawPrimitiveUP( D3DPT_TRIANGLEFAN , 2 , (LPVOID)v , sizeof( D3DVERTEX ));
}
void CD3DTexture::BltFast(int l , int t , int r , int b,DWORD dwDiffuse)
{
 	D3DVERTEX v[4] ;
 	memset( v , 0 , sizeof( v ));

	v[0].x=(float)(l);
	v[0].y=(float)(t);
	v[0].z=0.5f;
	v[0].rhw=0.5f;
	v[0].diffuse=dwDiffuse;
	v[0].tu=0.0f;
	v[0].tv=0.0f;
	
 	v[1].x=(float)r;
 	v[1].y=(float)t;
 	v[1].z=0.5f;
 	v[1].rhw=0.5f;
 	v[1].diffuse=dwDiffuse;
 	v[1].tu=1.0f;
	v[1].tv=0.0f;

	v[2].x=(float)r;
	v[2].y=(float)b;
	v[2].z=0.5f;
	v[2].rhw=0.5f;
	v[2].diffuse=dwDiffuse;
	v[2].tu=1.0f;
	v[2].tv=1.0f;
	
	v[3].x=(float)l;
	v[3].y=(float)b;
	v[3].z=0.5f;
	v[3].rhw=0.5f;
	v[3].diffuse=dwDiffuse;
	v[3].tu=0.0f;
  	v[3].tv=1.0f;

 	d3d_Device->SetTexture( 0 , m_Texture );
 	d3d_Device->SetFVF( D3DFVF_VERTEX  );
 	d3d_Device->DrawPrimitiveUP( D3DPT_TRIANGLEFAN , 2 , (LPVOID)v , sizeof( D3DVERTEX ));
}

void d3dEdit::Init(HWND hWnd,LPD3DXFONT lpFont,int nX,int nY,int nWidth,int nHeight)
{
	m_hWnd=hWnd;
	m_hDC=GetDC(hWnd);
	SetEditPos(nX,nY,nWidth,nHeight);
	m_lpFont=lpFont;
	m_lpText=L"";
	m_dwTextColor=D3DCOLOR_XRGB(255,255,255);
	m_dwFormat=DT_LEFT;
	m_nLimitLength=-1;
	m_bVisible=true;

	m_ptCaret.x=nX;
	m_ptCaret.y=nY;
	m_nAlpha=0;
	m_nDiffuse=D3DCOLOR_ARGB(128,255,255,255);
	m_bIsBrightening=true;
	
	CreateCaret(hWnd,NULL,0,0);
	SetCaretPos(m_rt.left,m_rt.top);
	ShowCaret(m_hWnd);
}

void d3dEdit::SetEditPos(int nX,int nY,int nWidth,int nHeight)
{
	m_rt.left=nX;
	m_rt.top=nY;
	m_rt.right=nX+nWidth;
	m_rt.bottom=nY+nHeight;
}

void d3dEdit::SetFont(LPD3DXFONT lpFont)
{
	m_lpFont=lpFont;
}


void d3dEdit::Render()
{
	if (m_bVisible)
	{
		if (m_lpText!=NULL) //绘制文本
		{
			m_lpFont->DrawTextW(NULL,m_lpText,-1,&m_rt,m_dwFormat,m_dwTextColor);
		}
		UpdateCaret();
	}
}

void d3dEdit::UpdateCaret()
{
	m_ptCaret.x=m_rt.left;
	m_ptCaret.y=m_rt.top;
	HDC hDC=m_lpFont->GetDC();

	if (m_lpText!=NULL)
	{
		SIZE size;
		GetTextExtentPoint32(hDC,m_lpText,wcslen(m_lpText),&size);
		m_ptCaret.x=m_rt.left+size.cx;
		m_ptCaret.y=m_rt.top;
	}
	
	//使插入符闪烁
	if (m_nAlpha==256)
		m_bIsBrightening=false;
	if (m_nAlpha==0)
		m_bIsBrightening=true;
	if (m_bIsBrightening)
		m_nAlpha+=2;
	else
		m_nAlpha-=2;

	//绘制插入符
	TEXTMETRIC tm;
	GetTextMetrics(hDC,&tm);

	ID3DXLine* dxLine;
	D3DXCreateLine(d3d_Device, &dxLine);
	D3DXVECTOR2 vNode[2];              // 线段结点坐标(像素)
	dxLine->SetWidth(2);
	vNode[0] = D3DXVECTOR2(m_ptCaret.x+2,m_ptCaret.y+2);
	vNode[1] = D3DXVECTOR2(m_ptCaret.x+2,m_ptCaret.y+tm.tmHeight+1);
	dxLine->Begin();
	dxLine->Draw(vNode,2,D3DCOLOR_ARGB(m_nAlpha,255,255,255));
	dxLine->End();
	dxLine->Release();

	SetCaretPos(m_ptCaret.x,m_ptCaret.y);
}

void d3dEdit::SetFormat(DWORD dwFormat)
{
	m_dwFormat=dwFormat;
}

void d3dEdit::SetLimitLength(int nLength)
{
	m_nLimitLength=nLength;
}