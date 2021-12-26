
// BlessingDlg.h : 头文件
//
#define UM_TIMER WM_USER+1

#pragma once
#include "RoseDlg.h"
#include "TextDlg.h"
#include "stdafx.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define COPY_HEIGHT 15
#define COPY1_WIDTH  60
#define COPY2_WIDTH  91

enum
{
	Option_Start,
	Option_Help,
};

enum
{
	Interface_Login,
	Interface_Help,
	Interface_Copy,
};
enum
{
	None,
	Wall1,
	Wall2,
	Wall3,
	Quest1,//顶出玫瑰花
	Quest2,
	Quest3,//被顶过的？
	Flower,
	Quest4,//顶出字 
	Tunnel,
	Exist,
	Gold
};
enum
{
	Light_Low,
	Light_Middle,
	Light_High
};
#define ACTION_IDLE   0
#define ACTION_RUN    1
#define ACTION_JUMP   3 
#define ACTION_SQUAT  4 

#define SPEED_MAX_Y  15

class CCopy
{
public:
	int m_nWidth;
	int* m_pObject;
	CCopy()
	{
		m_pObject=NULL;
	}
	~CCopy()
	{
	}
};

// CBlessingDlg 对话框
class CBlessingDlg : public CDialogEx
{
	// 构造
public:
	int m_nCurrentOutput;
	CRoseDlg m_RoseDlg;
	CTextDlg m_TextDlg[5];
	CCopy m_CopyCur;
	CCopy m_copy[2];
	CMCI m_mciBackground;
	LPD3DXFONT m_pFontSimsun_PUA;
	int m_nCurrentInterface;
	int m_nTime;
	int m_nCurrentY;
	int m_nCurrentX;
	bool m_bIsLeft;
	bool m_bCanMove;
	int m_nTimerCount; //计时器

	int m_nSpeedY;

	int m_nLoginSelection;

	CD3DTexture m_textMario[2][5]; //主角图像
	CD3DTexture m_textSmallFireball[3];

	int m_nCurrentRender;

	CD3DTexture m_textMonster1[3];
	CD3DTexture m_textMonster2[3];

	CD3DTexture m_textQuest[4];
	CD3DTexture m_textFlower[3];
	CD3DTexture m_textWall[4];
	CD3DTexture m_textTunnel;
	CD3DTexture m_textGold[3];

	CBlessingDlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_BLESSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 实现
public:
	HICON m_hIcon;
	static void PASCAL TimerCallBack(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
	{
		HWND hWnd=(HWND)dwUser;
		::SendMessage(hWnd,UM_TIMER,0,0);
	} 
	int One2Two(int x,int y,int m,int n)//查找[x][y],mn为下标数
	{	
		return (x*m)+(y);
	}
	void RenderScene()
	{
		//计算绘图区域
		int nSrcX=m_nCurrentX-WINDOW_WIDTH/2;
		if (nSrcX<0)
			nSrcX=0;
		if (nSrcX>m_CopyCur.m_nWidth*32-WINDOW_WIDTH)
			nSrcX=m_CopyCur.m_nWidth*32-WINDOW_WIDTH;

		if (m_bIsLeft)
			if (m_nCurrentRender!=ACTION_SQUAT)
				m_textMario[0][m_nCurrentRender].BltFast(-nSrcX+m_nCurrentX+m_textMario[0][m_nCurrentRender].m_Width,m_nCurrentY,-nSrcX+m_nCurrentX,m_nCurrentY+m_textMario[0][m_nCurrentRender].m_Height);
			else
				m_textMario[0][m_nCurrentRender].BltFast(-nSrcX+m_nCurrentX+m_textMario[0][m_nCurrentRender].m_Width,m_nCurrentY+20,-nSrcX+m_nCurrentX,m_nCurrentY+20+m_textMario[0][m_nCurrentRender].m_Height);
		else
			if (m_nCurrentRender!=ACTION_SQUAT)
				m_textMario[0][m_nCurrentRender].BltFast(m_nCurrentX-nSrcX,m_nCurrentY);
			else
				m_textMario[0][m_nCurrentRender].BltFast(m_nCurrentX-nSrcX,m_nCurrentY+20);

		for (int Y=0;Y<15;Y++)
		{
			for (int X=0;X<m_CopyCur.m_nWidth;X++)
			{
				if ((X+1)*32-nSrcX<0)
					continue;
				if ((X+1)*32-nSrcX>nSrcX+WINDOW_WIDTH)
					continue;

				switch(m_CopyCur.m_pObject[Y*m_CopyCur.m_nWidth+X])
				{
				case None:
					break;
				case Wall1:
					m_textWall[0].BltFast(X*32-nSrcX,Y*32);
					break;
				case Wall2:
					m_textWall[1].BltFast(X*32-nSrcX,Y*32);
					break;
				case Wall3:
					m_textWall[2].BltFast(X*32-nSrcX,Y*32);
					break;
				case Flower:
					{
						int nRange=m_nTimerCount%15;
						int nState;
						if (nRange<15)
							nState=2;
						if (nRange<10)
							nState=1;
						if (nRange<5)
							nState=0;
						m_textFlower[nState].BltFast(X*32-nSrcX,Y*32);
					}
					break;
				case Tunnel:
					m_textTunnel.BltFast(X*32-nSrcX,Y*32);
					break;
				case Quest1:
					{
						int nRange=m_nTimerCount%15;
						int nState;
						if (nRange<15)
							nState=2;
						if (nRange<10)
							nState=1;
						if (nRange<5)
							nState=0;
						m_textQuest[nState].BltFast(X*32-nSrcX,Y*32);
					}
				case Quest2:
					{
						int nRange=m_nTimerCount%15;
						int nState;
						if (nRange<15)
							nState=2;
						if (nRange<10)
							nState=1;
						if (nRange<5)
							nState=0;
						m_textQuest[nState].BltFast(X*32-nSrcX,Y*32);
					}
					break;
				case Quest3:
					m_textQuest[3].BltFast(X*32-nSrcX,Y*32);
					break;
				case Quest4:
					{
						int nRange=m_nTimerCount%15;
						int nState;
						if (nRange<15)
							nState=2;
						if (nRange<10)
							nState=1;
						if (nRange<5)
							nState=0;
						m_textQuest[nState].BltFast(X*32-nSrcX,Y*32);
					}
					break;
				case Gold:
					{
						int nRange=m_nTimerCount%15;
						int nState;
						if (nRange<15)
							nState=2;
						if (nRange<10)
							nState=1;
						if (nRange<5)
							nState=0;
						m_textGold[nState].BltFast(X*32-nSrcX,Y*32);
					}
					break;
				}
			}
		}
	};
// 生成的消息映射函数
virtual BOOL OnInitDialog();
afx_msg void OnPaint();
afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnTimerProc(WPARAM wParam,LPARAM lParam)
	{
		if (m_bCanMove)
		{
			if (IsKeyPressed(DIK_LEFT)||IsKeyPressed(DIK_RIGHT) && !IsKeyPressed(DIK_DOWN))
			{
				if (m_nTimerCount%3==0)
				{
					if (m_nCurrentRender!=ACTION_JUMP)
					{
						m_nCurrentRender+=1;
						if (m_nCurrentRender>ACTION_RUN+1)
							m_nCurrentRender=ACTION_RUN;
					}
				}
			}
			else
				if (m_nCurrentRender!=ACTION_JUMP)
					m_nCurrentRender=ACTION_IDLE;
			if (IsKeyPressed(DIK_DOWN) && m_nCurrentRender!=ACTION_JUMP)
			{
				m_nCurrentRender=ACTION_SQUAT;
				if (m_CopyCur.m_pObject!=NULL)
				{
					switch(m_CopyCur.m_pObject[
						One2Two((5+32+m_textMario[0][m_nCurrentRender].m_Height+m_nCurrentY)/32,
							(m_nCurrentX+16)/32,
							m_CopyCur.m_nWidth,
							15)])
						{
					case Tunnel:
					case Exist:
						m_bCanMove=false;
						m_nCurrentRender=ACTION_IDLE;
						m_nTimerCount=0;
						break;
						}
				}
			}
			if (IsKeyPressed(DIK_LEFT) && m_nCurrentRender!=ACTION_SQUAT)
			{
				m_bIsLeft=true;
				m_nCurrentX-=8;
				for (int i=0;i<m_textMario[0][m_nCurrentRender].m_Height;i++)
				{
					for (int j=0;j<m_textMario[0][m_nCurrentRender].m_Width;j++)
					{
						if (m_CopyCur.m_pObject[One2Two((m_nCurrentY+i)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]!=None)
							m_nCurrentX=32+m_nCurrentX/32*32;
						break;
					}
				}
			}
			if (IsKeyPressed(DIK_RIGHT) && m_nCurrentRender!=ACTION_SQUAT)
			{
				m_bIsLeft=false;
				m_nCurrentX+=8;
				for (int i=0;i<m_textMario[0][m_nCurrentRender].m_Height;i++)
				{
					if (m_CopyCur.m_pObject[One2Two((m_nCurrentY+i)/32,(m_nCurrentX+m_textMario[0][m_nCurrentRender].m_Width+5)/32,m_CopyCur.m_nWidth,15)]!=None)
						m_nCurrentX=m_nCurrentX/32*32;
				}
			}
			if (IsKeyPressed(DIK_C) && m_nCurrentRender!=ACTION_JUMP && !IsKeyPressed(DIK_DOWN))
			{
				sndPlaySound(L"Music\\Jump.wav",SND_ASYNC);
				m_nCurrentRender=ACTION_JUMP;
				m_nSpeedY=-15;
			}

			if (m_CopyCur.m_pObject!=NULL)
			{
				if (m_CopyCur.m_pObject[One2Two((30+m_textMario[0][m_nCurrentRender].m_Height+m_nCurrentY)/32,(m_nCurrentX)/32,m_CopyCur.m_nWidth,15)]==None&&m_nCurrentRender!=ACTION_JUMP && !IsKeyPressed(DIK_DOWN))
				{
					m_nCurrentRender=ACTION_JUMP;
					m_nSpeedY=1;
				}
			}
			if (m_nCurrentRender==ACTION_JUMP)
			{
				m_nSpeedY+=1;
				m_nCurrentY+=m_nSpeedY;
				if (m_nSpeedY>=0) //向下
				{
					for (int j=0;j<m_textMario[0][m_nCurrentRender].m_Width;j++)
					{
						if (m_CopyCur.m_pObject[One2Two((m_textMario[0][m_nCurrentRender].m_Height+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]!=None)
						{
							if (m_nCurrentRender==ACTION_JUMP)
								m_nCurrentRender=ACTION_IDLE;
							m_nCurrentY=-m_textMario[0][m_nCurrentRender].m_Width+(1+(m_nCurrentY)/32)*32;
						}
					}
				}
			}
			if (m_nSpeedY<=0) //向上
			{
				for (int i=0;i<m_textMario[0][m_nCurrentRender].m_Height;i++)
				{
					for (int j=0;j<m_textMario[0][m_nCurrentRender].m_Width;j++)
					{
						if (m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]!=None)
						{
							if (m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest1)
							{
								sndPlaySound(L"Music\\Bomb.wav",SND_ASYNC);
								m_RoseDlg.ShowWindow(SW_SHOW);
								m_RoseDlg.SetTimer(0,1000/50,NULL);
							}

							if (m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest1)
							{
								sndPlaySound(L"Music\\Bomb.wav",SND_ASYNC);
								m_RoseDlg.ShowWindow(SW_SHOW);
								m_RoseDlg.SetTimer(0,1000/50,NULL);
							}
							if (m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest4)
							{
								int nSrcX=m_nCurrentX-WINDOW_WIDTH/2;
								if (nSrcX<0)
									nSrcX=0;
								if (nSrcX>m_CopyCur.m_nWidth*32-WINDOW_WIDTH)
									nSrcX=m_CopyCur.m_nWidth*32-WINDOW_WIDTH;
								CPoint pt;
								pt.SetPoint(m_nCurrentX-nSrcX,m_nCurrentY-32);
								ClientToScreen(&pt);
								m_TextDlg[m_nCurrentOutput].SetPoint(pt,m_bIsLeft);
								m_TextDlg[m_nCurrentOutput].ShowWindow(SW_SHOW);
								m_TextDlg[m_nCurrentOutput].Start();
								m_nCurrentOutput++;
							}
							if (m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest1||
								m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest2||
								m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]==Quest4)	
								m_CopyCur.m_pObject[One2Two((i+m_nCurrentY)/32,(m_nCurrentX+j)/32,m_CopyCur.m_nWidth,15)]=Quest3;
							m_nCurrentY=(1+(m_nCurrentY)/32)*32;
							m_nSpeedY=-m_nSpeedY;
						}
					}
				}
			}
		}
		if (!m_bCanMove)
		{
			m_nCurrentY+=2;
			if (m_nTimerCount>=40)
			{
				m_nCurrentX=100;
				m_nCurrentY=100;
				m_CopyCur=m_copy[1];
				m_bCanMove=true;
			}
		}

		m_nTimerCount++;	

		Invalidate(TRUE);
		return 0;
	}
};