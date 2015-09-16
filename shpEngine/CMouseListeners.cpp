
// CMouseListeners
#include "StdAfx.h"
#include "CMouseListeners.h"

CMouseListeners::CMouseListeners()
{
	this->m_nCurrentMouseListenerKey = EMAP_TOOL_NULL;
	this->m_nCurrentSubMouseListenerKey = EMAP_TOOL_NULL;
}

CMouseListeners::~CMouseListeners()
{
	this->RemoveAllMouseListener();
	this->m_nCurrentMouseListenerKey = EMAP_TOOL_NULL;
	this->m_nCurrentSubMouseListenerKey = EMAP_TOOL_NULL;
}

void CMouseListeners::AddMouseListener (int theKey, IMouseListener* pMouseListener)
{
	if ( pMouseListener == 0 )	return ;
	m_MouselistenerContainer.insert(map<int,IMouseListener*>::value_type(theKey,pMouseListener) ) ;
}

int CMouseListeners::GetCurrentMouseListenerKey ()
{
	return m_nCurrentMouseListenerKey ;
}

int CMouseListeners::GetCurrentSubMouseListenerKey ()
{
	return m_nCurrentSubMouseListenerKey ;
}

int CMouseListeners::SetCurrentMouseListenerKey (int theKey, int theSubKey)
{
	int oldKey = m_nCurrentMouseListenerKey ;
	this ->m_nCurrentMouseListenerKey = theKey ;
	this ->m_nCurrentSubMouseListenerKey = theSubKey ;
	return oldKey ;
}

IMouseListener* CMouseListeners::GetCurrentMouseListener ()
{
	return m_MouselistenerContainer[m_nCurrentMouseListenerKey] ;
}

IMouseListener* CMouseListeners::Find (int theKey)
{
	return m_MouselistenerContainer[theKey];
}

void CMouseListeners::RemoveMouseListener (IMouseListener* pMouseListener)
{
	map<int,IMouseListener*>::iterator iterator ;
	for ( iterator = m_MouselistenerContainer.begin(); iterator != m_MouselistenerContainer.end() ; iterator ++ )
	{
		if ( (*iterator).second == pMouseListener )
			break ;
	}

	IMouseListener *tobedeleteMouseListener = (*iterator).second ;
	delete tobedeleteMouseListener ;
	tobedeleteMouseListener = 0 ;
	(*iterator).second = 0 ;
	pMouseListener = 0 ;

	m_MouselistenerContainer.erase ( iterator ) ;
}

void CMouseListeners::RemoveMouseListener (int theKey)
{
	map<int,IMouseListener*>::iterator iterator ;
	iterator = m_MouselistenerContainer.find( theKey );
	if ( iterator != m_MouselistenerContainer.end() )
	{
		IMouseListener *tobedeleteMouseListener = (*iterator).second ;
		if ( tobedeleteMouseListener )
			delete tobedeleteMouseListener ;
		tobedeleteMouseListener = 0 ;
		(*iterator).second = 0 ;
	}
	m_MouselistenerContainer.erase ( iterator ) ;
}

void CMouseListeners::RemoveAllMouseListener ()
{
	map<int,IMouseListener*>::iterator iterator ;
	for ( iterator = m_MouselistenerContainer.begin(); iterator != m_MouselistenerContainer.end() ; iterator ++ )
	{
		IMouseListener *pMouseListener = (*iterator).second ;
		if ( pMouseListener )
		{
			delete pMouseListener;
			pMouseListener = 0 ;
			(*iterator).second = 0;
		}
	}
	m_MouselistenerContainer.clear () ;
}
