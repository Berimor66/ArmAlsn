
// OscilloscopeView.h : ��������� ������ COscilloscopeView
//


#pragma once

void Error(const wchar_t *es);
class COscilloscopeView : public CView
{
protected: // ������� ������ �� ������������
	COscilloscopeView();
	DECLARE_DYNCREATE(COscilloscopeView)

// ��������
public:
	COscilloscopeDoc* GetDocument() const;
	CWnd *m_pOscilWnd1;
protected:
	//CBitmap specbmp;
	//HBITMAP specbmp;
	BYTE *specbuf;
	BITMAP pBitmapInfo; // = new BITMAP;
	// Bitmap Attributes
	HBITMAP m_specbmp;
	HBITMAP m_pOldBitmap;
	HDC specdcmem;
	HDC specdc;              // �������� ���������� DIB � ������
	HBITMAP specbmp;         // � ��� ������� ������
	CPalette Palette;
//	BITMAPINFOHEADER BIH;     // � ��� ��������� ������� DIB
	CDC specdc_i;
	CDC specdc_can2;
//	BYTE *specbuf_i;
	//BYTE *specbuf_canal1;
	BYTE *specbuf_can2;
	HBITMAP specbmp_i;
	HBITMAP specbmp_can2;
	HRECORD chan;   // recording channel
	BYTE *specbuf_ii;
	// Palette Attributes
	RGBQUAD m_rgbPalette[256];
	HPALETTE m_hPalette;
	HPALETTE m_pOldPalette;
	


// ��������
public:
	
// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���������� � ������ ��� ����� ������������
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����������
public:
	virtual ~COscilloscopeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT nIDEvent);
	// ������ �������� �����
	void UpdateSpectrum(void);
	COscilloscopeFrm ofrm;
	afx_msg void OnTest();
//	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};

#ifndef _DEBUG  // ���������� ������ � OscilloscopeView.cpp
inline COscilloscopeDoc* COscilloscopeView::GetDocument() const
   { return reinterpret_cast<COscilloscopeDoc*>(m_pDocument); }
#endif

