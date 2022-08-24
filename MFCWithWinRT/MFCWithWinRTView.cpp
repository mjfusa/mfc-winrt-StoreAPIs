
// MFCWithWinRTView.cpp : implementation of the CMFCWithWinRTView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCWithWinRT.h"
#endif

#include "MFCWithWinRTDoc.h"
#include "MFCWithWinRTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCWithWinRTView

IMPLEMENT_DYNCREATE(CMFCWithWinRTView, CView)

BEGIN_MESSAGE_MAP(CMFCWithWinRTView, CView)
END_MESSAGE_MAP()

// CMFCWithWinRTView construction/destruction

CMFCWithWinRTView::CMFCWithWinRTView() noexcept
{
	// TODO: add construction code here

}

CMFCWithWinRTView::~CMFCWithWinRTView()
{
}

BOOL CMFCWithWinRTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCWithWinRTView drawing

void CMFCWithWinRTView::OnDraw(CDC* /*pDC*/)
{
	CMFCWithWinRTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCWithWinRTView diagnostics

#ifdef _DEBUG
void CMFCWithWinRTView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCWithWinRTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCWithWinRTDoc* CMFCWithWinRTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWithWinRTDoc)));
	return (CMFCWithWinRTDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCWithWinRTView message handlers
