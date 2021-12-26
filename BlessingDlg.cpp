
// BlessingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Blessing.h"
#include "afxdialogex.h"
#include "BlessingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBlessingDlg 对话框




CBlessingDlg::CBlessingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBlessingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurrentInterface=Interface_Copy;
	m_nCurrentRender=0;
	m_nTime=400;
	m_nCurrentX=40;
	m_nCurrentY=0;
	m_nTimerCount=0;
	m_nLoginSelection=Option_Start;
	m_nCurrentOutput=0;
	m_nSpeedY=10;
	m_bCanMove=true;
	m_CopyCur.m_pObject=NULL;
	m_copy[0].m_nWidth=60;
	m_copy[1].m_nWidth=91;
	m_copy[0].m_pObject=new int[15*60];
	m_copy[1].m_pObject=new int[15*91];
	int copy0[15*60]=
	{
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,6,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,8,0,0,8,0,0,8,0,0,8,0,0,0,0,0,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,
		3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,3,0,0,0,0,0,0,0,4,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
		3,0,0,0,0,0,0,0,0,0,0,0,3,0,3,3,3,0,0,3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,
		3,0,0,0,0,0,0,0,0,0,3,0,3,0,3,3,3,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,
		3,0,0,0,0,0,0,0,3,0,3,0,3,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
	};
	int copy1[15*91]=
	{
		01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,
		01,00,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,11,11,11,11,00,00,11,00,00,00,00,00,00,00,11,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,00,00,00,00,11,00,00,11,11,11,11,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,11,11,11,11,00,00,11,00,00,00,00,00,00,00,11,00,00,11,00,00,00,00,00,00,00,00,00,00,00,11,00,00,00,00,11,00,00,11,11,11,11,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,11,11,00,00,00,11,00,00,00,00,00,11,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,11,00,00,11,00,00,00,11,11,00,00,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,11,11,00,00,00,11,00,00,00,00,00,11,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,11,00,00,11,00,00,00,11,11,00,00,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,11,11,00,00,00,00,11,00,00,00,11,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,11,11,00,00,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,11,11,00,00,00,00,11,00,00,00,11,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,00,00,11,11,00,00,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,00,00,00,00,11,11,00,00,11,11,00,00,00,00,00,11,00,11,00,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,00,00,11,11,00,00,11,11,00,00,11,11,00,00,00,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,11,11,11,11,11,11,11,00,00,11,11,11,11,11,11,00,00,00,00,00,11,00,11,00,00,00,00,00,11,00,00,00,00,00,00,00,00,00,00,00,00,00,11,11,00,00,00,00,11,11,11,11,11,11,00,00,11,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,
		01,00,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,11,11,11,11,11,11,11,00,00,11,11,11,11,11,11,00,00,00,00,00,00,11,00,00,00,00,00,00,11,11,11,11,11,11,00,00,00,00,00,00,00,00,11,11,00,00,00,00,11,11,11,11,11,11,00,00,11,11,11,11,11,11,11,00,00,00,00,00,00,00,00,00,
		01,9,10,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
		01,10,10,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
		01,10,10,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
		03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,
		03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03,03
	};
	memcpy(m_copy[0].m_pObject,&copy0,sizeof(int)*15*60);
	memcpy(m_copy[1].m_pObject,&copy1,sizeof(int)*15*91);

}

void CBlessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlessingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_MESSAGE(UM_TIMER,OnTimerProc)  
END_MESSAGE_MAP()


// CBlessingDlg 消息处理程序

BOOL CBlessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_RoseDlg.Create(IDD_ROSE_DIALOG,this);
	m_TextDlg[0].Create(IDD_TEXT_DIALOG,this);
	m_TextDlg[1].Create(IDD_TEXT_DIALOG,this);
	m_TextDlg[2].Create(IDD_TEXT_DIALOG,this);
	m_TextDlg[3].Create(IDD_TEXT_DIALOG,this);
	m_TextDlg[4].Create(IDD_TEXT_DIALOG,this);
	m_TextDlg[0].SetText(L"我",255);
	m_TextDlg[1].SetText(L"想",255);
	m_TextDlg[2].SetText(L"告",255);
	m_TextDlg[3].SetText(L"诉",255);
	m_TextDlg[4].SetText(L"你",255);
	// TODO: 在此添加额外的初始化代码
	if (!d3dCreate(m_hWnd,WINDOW_WIDTH,WINDOW_HEIGHT,TRUE))
		PostQuitMessage(0);
	if (!InitKeyBoard(AfxGetApp()->m_hInstance))
		PostQuitMessage(0);

	if (D3DXCreateFontW(d3d_Device,15,0,0,1,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"宋体",&m_pFontSimsun_PUA)!=S_OK)
	{
		AfxMessageBox(L"无法找到系统字体“宋体”！");
		PostQuitMessage(NULL);
	}
	d3d_Device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	d3d_Device->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE);
	d3d_Device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	d3d_Device->SetRenderState(D3DRS_LIGHTING,FALSE);
	d3d_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
	d3d_Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	d3d_Device->SetTextureStageState(0, D3DTSS_CONSTANT, D3DCOLOR_ARGB(128,255,255,255));
	d3d_Device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );  
	d3d_Device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
	d3d_Device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);

//  	if (!m_mciBackground.Open(L"Music\\Background.mp3"))
//  	{
//  		AfxMessageBox(L"缺失“Music”目录中的音频文件！");
//  		PostQuitMessage(NULL);
//  	}
// 	m_mciBackground.Play();

	//

	m_CopyCur=m_copy[0];
	//
	m_textMario[0][0].CreateFromFile(L"Textures\\Idle.png");
	m_textMario[0][1].CreateFromFile(L"Textures\\Run_0.png");
	m_textMario[0][2].CreateFromFile(L"Textures\\Run_1.png");
	m_textMario[0][3].CreateFromFile(L"Textures\\Jump.png");
	m_textMario[0][4].CreateFromFile(L"Textures\\Squat.png");
	m_textMonster1[0].CreateFromFile(L"Textures\\Monster1_0.png");
	m_textMonster1[1].CreateFromFile(L"Textures\\Monster1_1.png");
	m_textMonster1[2].CreateFromFile(L"Textures\\Monster1_2.png");
	m_textMonster2[0].CreateFromFile(L"Textures\\Monster2_0.png");
	m_textMonster2[1].CreateFromFile(L"Textures\\Monster2_1.png");
	m_textMonster2[2].CreateFromFile(L"Textures\\Monster2_2.png");
	m_textQuest[0].CreateFromFile(L"Textures\\Quest_0.png");
	m_textQuest[1].CreateFromFile(L"Textures\\Quest_1.png");
	m_textQuest[2].CreateFromFile(L"Textures\\Quest_2.png");
	m_textQuest[3].CreateFromFile(L"Textures\\Quest_3.png");
	m_textFlower[0].CreateFromFile(L"Textures\\Flower_0.png");
	m_textFlower[1].CreateFromFile(L"Textures\\Flower_1.png");
	m_textFlower[2].CreateFromFile(L"Textures\\Flower_2.png");

	m_textWall[0].CreateFromFile(L"Textures\\Wall1.png");
	m_textWall[1].CreateFromFile(L"Textures\\Wall2.png");
	m_textWall[2].CreateFromFile(L"Textures\\Wall3.png");

	m_textTunnel.CreateFromFile(L"Textures\\Tunnel.png");

	m_textSmallFireball[0].CreateFromFile(L"Textures\\SmallFireball_0.png");
	m_textSmallFireball[1].CreateFromFile(L"Textures\\SmallFireball_1.png");
	m_textSmallFireball[2].CreateFromFile(L"Textures\\SmallFireball_2.png");

	m_textGold[0].CreateFromFile(L"Textures\\Gold_0.png");
	m_textGold[1].CreateFromFile(L"Textures\\Gold_1.png");
	m_textGold[2].CreateFromFile(L"Textures\\Gold_2.png");

	MoveWindow(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
	CenterWindow();
	timeBeginPeriod( 1 );
	timeSetEvent(1000/35,0,(LPTIMECALLBACK)TimerCallBack,(DWORD)this->m_hWnd,TIME_PERIODIC);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CBlessingDlg::OnPaint()
{
	CPaintDC dc(this);
	d3d_Device->BeginScene();
	d3dClear(D3DCOLOR_XRGB(0,0,0));
	switch(m_nCurrentInterface)
	{
	case Interface_Copy:
		RenderScene();
		CString str;
		str.Format(L"%d,%d",m_nCurrentX,m_nCurrentY);
		CRect rt(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
		m_pFontSimsun_PUA->DrawTextW(NULL,str,-1,&rt,DT_LEFT|DT_TOP,D3DCOLOR_XRGB(255,255,255));
		break;
	}
	d3d_Device->EndScene();
	d3d_Device->Present(NULL,NULL,NULL,NULL);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBlessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CBlessingDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


BOOL CBlessingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			if (m_nCurrentInterface==Interface_Login)
			{
				switch(m_nLoginSelection)
				{
				case Option_Help:
					m_nCurrentInterface=Interface_Help;
					break;
				case Option_Start:
					m_nCurrentInterface=Interface_Copy;
					break;
				}
				Invalidate();
			}
			return 1;
			break;
		case VK_ESCAPE:
			if (m_nCurrentInterface==Interface_Help)
				m_nCurrentInterface=Interface_Login;
			return 1;
			break;
		case VK_UP:
			if (m_nCurrentInterface==Interface_Login)
			{
				if (m_nLoginSelection==Option_Start)
					m_nLoginSelection=Option_Help;
				else
					m_nLoginSelection=Option_Start;
				Invalidate(TRUE);
			}
			break;
		case VK_DOWN:
			if (m_nCurrentInterface==Interface_Login)
			{
				if (m_nLoginSelection==Option_Help)
					m_nLoginSelection=Option_Start;
				else
					m_nLoginSelection=Option_Help;
				Invalidate(TRUE);
			}
			break;
		}
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CBlessingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	d3dRelease();
	m_pFontSimsun_PUA->Release();
	m_pFontSimsun_PUA=NULL;
}
