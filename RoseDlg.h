#pragma once


// CRoseDlg 对话框

class CRoseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoseDlg)

public:
	CRoseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRoseDlg();
	bool m_bUp;
	int m_nTransparent;
	CImage m_imgRose;
	void SetImage(CImage& img)
	{
		if (img.GetBPP() == 32) //确认该图像包含Alpha通道
		{
			for (int i=0; i<img.GetWidth();i++)
			{
				for(int j=0; j<img.GetHeight(); j++)
				{
					byte*pByte = (byte*)img.GetPixelAddress(i, j);
					pByte[0]= pByte[0] * pByte[3]/ 255;
					pByte[1]= pByte[1] * pByte[3]/ 255;
					pByte[2]= pByte[2] * pByte[3]/ 255;
				}
			}
		}
	}
	void SetWindowImage(CImage& img,int nTransparent)
	{
		BLENDFUNCTION Blend;
		int nBakWidth , nBakHeight;

		Blend.BlendOp=0;
		Blend.BlendFlags=0;
		Blend.AlphaFormat=1;
		Blend.SourceConstantAlpha=nTransparent;

		nBakWidth  =img.GetWidth();
		nBakHeight =img.GetHeight();

		CDC* pDC=GetDC();
		CDC dcMem;
		HBITMAP hBitmap;
		dcMem.CreateCompatibleDC(pDC);
		hBitmap=CreateCompatibleBitmap(pDC->m_hDC,nBakWidth,nBakHeight);
		SelectObject(dcMem,hBitmap);
		img.AlphaBlend(dcMem,0,0);

 		SIZE sizeWindow={nBakWidth,nBakHeight};
 		POINT ptSrc={0,0};
 		SetWindowLong(m_hWnd,GWL_EXSTYLE,0x80000);
 
		RECT rect;
 		GetWindowRect(&rect);
 		POINT ptWinPos={rect.left,rect.top};
 		UpdateLayeredWindow(pDC,&ptWinPos,&sizeWindow,&dcMem,&ptSrc,0,&Blend,2);
 
	}

// 对话框数据
	enum { IDD = IDD_ROSE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
