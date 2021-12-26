#pragma once


// CTextDlg 对话框

class CTextDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // 标准构造函数
	CString m_strText;
	CFont m_font;
	CPoint m_ptPre;
	CPoint m_ptCur;
	bool m_bUp;
	CBrush m_brush;
	CRect m_rtStart;
	int m_nVy;
	int m_X;
	COLORREF m_color;
	virtual ~CTextDlg();
	void SetPoint(CPoint pt,bool bIsLeft)
	{
		if (bIsLeft)
			m_X=-4;
		else
			m_X=4;
		m_ptPre=pt;
		m_ptCur=pt;
	}
	void Start()
	{
		SetTimer(0,1000/50,NULL);
		srand(time(NULL));
		int color[3];
		color[0]=rand()%256;
		color[1]=rand()%256;
		color[2]=rand()%256;
		m_color=RGB(color[0],color[1],color[2]);
	}
	void SetWindowText(CString strText,int nTransparent)
	{
		BLENDFUNCTION Blend;

		Blend.BlendOp=0;
		Blend.BlendFlags=0;
		Blend.AlphaFormat=1;
		Blend.SourceConstantAlpha=nTransparent;

		CDC* pDC=GetDC();
		SIZE size;
		CDC dcMem;
		HBITMAP hBitmap;
		dcMem.CreateCompatibleDC(pDC);
		CFont font;
		font.CreateFont(25,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,L"宋体");
		dcMem.SelectObject(&font);
		GetTextExtentPoint32(dcMem.m_hDC,strText,strText.GetLength(),&size);
		hBitmap=CreateCompatibleBitmap(pDC->m_hDC,size.cx,size.cy);
		dcMem.SelectObject(hBitmap);

		dcMem.SetTextColor(m_color);
		dcMem.TextOut(0,0,strText,strText.GetLength());

		SetWindowLong(m_hWnd,GWL_EXSTYLE,0x80000);
		RECT rect;
		GetWindowRect(&rect);

		UpdateLayeredWindow(pDC,&CPoint(rect.left,rect.top),&size,&dcMem,&CPoint(0,0),RGB(255,255,255),&Blend,ULW_COLORKEY);
	}
	void SetText(CString strText,int nTransparent)
	{
		m_strText=strText;
		SetWindowText(strText,nTransparent);
	}
// 对话框数据
	enum { IDD = IDD_TEXT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
