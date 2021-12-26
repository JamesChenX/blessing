// RoseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Blessing.h"
#include "RoseDlg.h"
#include "afxdialogex.h"


// CRoseDlg �Ի���

IMPLEMENT_DYNAMIC(CRoseDlg, CDialogEx)

CRoseDlg::CRoseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoseDlg::IDD, pParent)
{
	m_nTransparent=1;
	m_bUp=true;
}

CRoseDlg::~CRoseDlg()
{
}

void CRoseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRoseDlg ��Ϣ�������


BOOL CRoseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MoveWindow(0,0,2000,2000);
	m_imgRose.Load(L"Textures\\Rose.png");	
	SetImage(m_imgRose);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CRoseDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

}


BOOL CRoseDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
}

void CRoseDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bUp)
		m_nTransparent+=5;
	else
		m_nTransparent-=5;
	if (m_nTransparent>=255)
	{
		m_bUp=false;
		m_nTransparent=255;
	}
	if (m_nTransparent<=0)
	{
		KillTimer(0);
		EndDialog(0);
	}
	SetWindowImage(m_imgRose,m_nTransparent);
	CenterWindow();

	CDialogEx::OnTimer(nIDEvent);
}
