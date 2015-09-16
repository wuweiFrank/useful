#include "StdAfx.h"
#include "GeoPoints.h"


GeoPoints::GeoPoints()
      : pArrayX(0),
        pArrayY(0),
        nPtCount(0)
{
}


GeoPoints::~GeoPoints()
{
	delete []pArrayX;
	delete []pArrayY;
}



GeoPoint GeoPoints::GetPoint (int index)
{
	return GeoPoint( pArrayX[ index], pArrayY[ index ] );
}

void GeoPoints::GetPoint (int index, double& x, double& y)
{
	x = pArrayX[ index ];
	y = pArrayY[ index ];
}

int GeoPoints::GetPtCount ()
{
	return nPtCount;
}

void GeoPoints::SetPointCount (int nPtCount)
{
	if( pArrayX == 0 && pArrayY == 0 )
	{
		pArrayX = new double[ nPtCount ];
		pArrayY = new double[ nPtCount ];
		this->nPtCount = nPtCount;
		return;
	}
	else
	{
	}
}

void GeoPoints::SetPoint (int index, double x, double y)
{
	pArrayX[ index ] = x;
	pArrayY[ index ] = y;
}

void GeoPoints::SetPoint (int index, GeoPoint point)
{
	pArrayX[ index ] = point.GetX();
	pArrayY[ index ] = point.GetY();
}
