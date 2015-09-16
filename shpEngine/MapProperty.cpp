#include "StdAfx.h"
#include "MapProperty.h"
#include "MapControl.h"


// Class MapProperty 

MapProperty::MapProperty (MapControl* mapCtrl)
{
	this ->m_pMapControl = mapCtrl ;
}


MapProperty::~MapProperty()
{
	m_pMapControl = 0 ;
}



void MapProperty::ClientToWorld (double& x, double& y)
{
	m_pMapControl ->ClientToWorld(x,y);
}

void MapProperty::WorldToClient (double& x, double& y)
{
	m_pMapControl->WorldToClient(x,y);
}

void MapProperty::GetClipRect (int& x, int& y, int& w, int& h)
{
	x = this ->m_nClipX ;
	y = this ->m_nClipY ;
	w = this ->m_nClipWidth ;
	h = this ->m_nClipHeight ;
}

void MapProperty::SetClipRect (int x, int y, int w, int h)
{
	this ->m_nClipX = x ; 
	this ->m_nClipY = y ;
	this ->m_nClipWidth = w ;
	this ->m_nClipHeight = h ;
}
