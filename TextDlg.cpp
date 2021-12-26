// TextDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Blessing.h"
#include "TextDlg.h"
#include "afxdialogex.h"


// CTextDlg 对话框

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextDlg::IDD, pParent)
{
	m_ptCur.SetPoint(0,0);
	m_strText=L"";
	m_bUp=TRUE;
	m_nVy=-30;
}
CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTextDlg 消息处理程序


BOOL CTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	MoveWindow(0,0,500,500);
	m_font.CreatePointFont(250,L"宋体",NULL);
	HWND hWndStart=::FindWindowW(L"Shell_TrayWnd",NULL);
	::GetWindowRect(hWndStart,&m_rtStart);
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTextDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_nVy+=1;
	m_ptCur.x+=m_X;
	m_ptCur.y+=m_nVy;
	if (m_ptCur.y>=m_rtStart.top)
	{
		m_ptCur.y=m_rtStart.top;
		KillTimer(0);
	}
	SetWindowPos(NULL,m_ptCur.x,m_ptCur.y,0,0,SWP_NOSIZE);

	CDialogEx::OnTimer(nIDEvent);
}
