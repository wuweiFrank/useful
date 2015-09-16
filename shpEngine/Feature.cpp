#include "StdAfx.h"
#include "Feature.h"
#include "GeoPoint.h"
#include "geopolyline.h"
#include "GeoPolygon.h"
Feature::Feature (int fid, int subType, Fields* pFields)
      : m_pGeometry(0)
		,Row( fid, pFields )
{
	m_nSubType = subType;
}


Feature::~Feature()
{
	if( m_pGeometry ) 
	{
		switch( m_pGeometry ->GetGeoType() )
		{
		case GEO_POINT:	delete (GeoPoint*)m_pGeometry; break;
		case GEO_POLYLINE: delete (GeoPolyline*)m_pGeometry; break;
		case GEO_POLYGON: delete (GeoPolygon*)m_pGeometry; break;
		}
	}
}

int Feature::GetFID ()
{
	return m_nID;
}

int Feature::GetSubType ()
{
	return m_nSubType;
}

void Feature::GetBound (double& minx, double& miny, double& w, double& h)
{
	minx	=	m_dMinx;
	miny	=	m_dMiny;
	w		=	m_dWidth;
	h		=	m_dHeight;
}

void Feature::SetBound (double minx, double miny, double w, double h)
{
	m_dMinx		= minx;
	m_dMiny		= miny;
	m_dWidth	= w;
	m_dHeight	= h;
}

Geometry& Feature::GetGeometry ()
{
	return *m_pGeometry;
}

void Feature::SetGeometry (Geometry* pGeometry)
{
	m_pGeometry = pGeometry;
}

