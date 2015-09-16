
// CViewCtrlMouseListener
#include "stdafx.h"
#include "CViewCtrlMouseListener.h"
#include "MapControl.h"
#include "CMouseEvent.h"
// Class CViewCtrlMouseListener 

CViewCtrlMouseListener::CViewCtrlMouseListener()
{
}


CViewCtrlMouseListener::~CViewCtrlMouseListener()
{
}



void CViewCtrlMouseListener::OnLButtonDown (CMouseEvent* pMouseEvent)
{
	MapControl *pMapControl = (MapControl *)pMouseEvent ->GetSource() ;

	if ( !pMapControl ) return ;

	m_lastPoint = m_LButtonPoint = pMouseEvent ->GetPoint () ;
}

void CViewCtrlMouseListener::OnLButtonUp (CMouseEvent* pMouseEvent)
{
	MapControl *pMapControl = (MapControl *)pMouseEvent ->GetSource() ;

	if ( !pMapControl ) return ;

	int tool = pMouseEvent ->GetTool () ;

	CPoint point = pMouseEvent ->GetPoint () ;

	int dx = point.x - m_LButtonPoint.x ;
	int dy = point.y - m_LButtonPoint.y ;

	CRect rect ;
	rect.SetRect( m_LButtonPoint.x, m_LButtonPoint.y, point.x, point.y ) ;
	rect.NormalizeRect () ;


	switch ( tool )
	{
	case EMAP_TOOL_ZOOMIN :
		{
			pMapControl->ZoomIn ( rect.left, rect.top, rect.Width(), rect.Height() ) ;
			pMapControl->Refresh();
		}
		break ;
	case EMAP_TOOL_ZOOMOUT :
		{
			pMapControl->ZoomOut ( rect.left, rect.top, rect.Width(), rect.Height() ) ;
			pMapControl->Refresh();
		}
		break ;
	case EMAP_TOOL_PAN:
		{
			CPoint *pViewDrawingPos = pMapControl->GetOwnerWindowDrawingPos();
			pViewDrawingPos->x = 0;
			pViewDrawingPos->y = 0;
			pMapControl->Scroll ( dx, dy ) ;
			pMapControl->Refresh();
		}
		break ;
	default:
		break ;
	}
}

void CViewCtrlMouseListener::OnLButtonDBLClick (CMouseEvent* pMouseEvent)
{
}

void CViewCtrlMouseListener::OnRButtonDown (CMouseEvent* pMouseEvent)
{
}

void CViewCtrlMouseListener::OnRButtonUp (CMouseEvent* pMouseEvent)
{
}

void CViewCtrlMouseListener::OnMouseMove (CMouseEvent* pMouseEvent)
{
}

void CViewCtrlMouseListener::OnMouseDrag (CMouseEvent* pMouseEvent)
{
	MapControl *pMapControl = (MapControl *)pMouseEvent ->GetSource() ;

	if ( !pMapControl ) return ;

	int tool = pMouseEvent ->GetTool () ;

	CPoint point = pMouseEvent ->GetPoint () ;

	switch ( tool )
	{
	case EMAP_TOOL_ZOOMIN :		
	case EMAP_TOOL_ZOOMOUT :
		{
			CView *pView = pMapControl ->GetOwnerView () ;

			pMapControl ->Refresh ();
			
			CDC *pDC = pView->GetDC();
			CPen pen, *pOldPen ;
			pen.CreatePen ( 0, 1, 255 ) ;
			pOldPen = ( CPen*)pDC ->SelectObject ( &pen );
			CBrush *pOldBrush = (CBrush*)pDC ->SelectStockObject ( NULL_BRUSH );
			pDC ->Rectangle ( m_LButtonPoint.x, m_LButtonPoint.y, point.x, point.y ) ;
			pDC ->SelectObject ( pOldBrush );
			pDC ->SelectObject ( pOldPen );
			pen.DeleteObject () ;
			pView->ReleaseDC(pDC);
			pOldPen = 0;
			pOldBrush = 0;
			pDC = 0;
		}
		break ;
	case EMAP_TOOL_PAN:
		{
			int dx = point.x - m_lastPoint.x ;
			int dy = point.y - m_lastPoint.y ;
			CView *pView = pMapControl ->GetOwnerView () ;
			CPoint *pViewDrawingPos = pMapControl->GetOwnerWindowDrawingPos();
			pViewDrawingPos->x = point.x-m_LButtonPoint.x;
			pViewDrawingPos->y = point.y-m_LButtonPoint.y;
			pView ->ScrollWindow(dx,dy);
			m_lastPoint = point ;
		}
		break ;
	default:
		break ;
	}

}

void CViewCtrlMouseListener::OnCancel ()
{
}
