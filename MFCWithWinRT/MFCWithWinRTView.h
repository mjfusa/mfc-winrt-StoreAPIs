
// MFCWithWinRTView.h : interface of the CMFCWithWinRTView class
//

#pragma once


class CMFCWithWinRTView : public CView
{
protected: // create from serialization only
	CMFCWithWinRTView() noexcept;
	DECLARE_DYNCREATE(CMFCWithWinRTView)

// Attributes
public:
	CMFCWithWinRTDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCWithWinRTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCWithWinRTView.cpp
inline CMFCWithWinRTDoc* CMFCWithWinRTView::GetDocument() const
   { return reinterpret_cast<CMFCWithWinRTDoc*>(m_pDocument); }
#endif

