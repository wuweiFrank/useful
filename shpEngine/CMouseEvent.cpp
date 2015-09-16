

// CMouseEvent
#include "stdafx.h"
#include "CMouseEvent.h"
CMouseEvent::CMouseEvent (void* pSource, CPoint point, int mouseFlag, int theTool)
{
	this->m_pSource = pSource ;
	this ->m_Point = point ;
	this ->m_MouseFlag = mouseFlag ;
	this ->m_tool = theTool ;
}


CMouseEvent::~CMouseEvent()
{
	m_pSource = 0 ;
}


CPoint CMouseEvent::GetPoint ()
{
	return m_Point ;
}

int CMouseEvent::GetMouseFlag ()
{
	return this ->m_MouseFlag ;
}

int CMouseEvent::GetTool ()
{
	return this ->m_tool ;
}

void* CMouseEvent::GetSource ()
{
	return m_pSource ;
}
