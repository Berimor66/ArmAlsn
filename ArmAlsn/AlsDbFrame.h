#pragma once


// ����� CAlsDbFrame

class CAlsDbFrame : public CFrameWndEx
{
	DECLARE_DYNCREATE(CAlsDbFrame)
protected:
	CAlsDbFrame();           // ���������� �����������, ������������ ��� ������������ ��������
	virtual ~CAlsDbFrame();
	// ����������
public:
	//virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()
protected:  // ���������� ����� ������ ��������� ����������
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
//	COutputWnd        m_wndOutput;

	// ��������
protected:
	CSplitterWnd m_wndSplitter;
	// ���������������
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// ��������� ������� ����� ���������
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); //,CCreateContext* pContext);
};


