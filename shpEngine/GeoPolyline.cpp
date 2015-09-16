#include "StdAfx.h"
#include "GeoPolyline.h"




GeoPolyline::GeoPolyline()
      : nPointsCount(0)
  
{
 
}


GeoPolyline::~GeoPolyline()
{
 
}




int GeoPolyline::GetGeoType ()
{
	return GEO_POLYLINE;
}

void GeoPolyline::SetPointsCount (int nCount)
{
	if( nPointsCount == 0 )
	{
		nPointsCount = nCount;
		arrayPoints = new GeoPoints[ nCount ];
	}
	else
	{
		delete []arrayPoints;
		nPointsCount = nCount;
		arrayPoints = new GeoPoints[ nCount ];
	}
}

int GeoPolyline::GetPointsCount ()
{
	return nPointsCount;
}

GeoPoints& GeoPolyline::GetPoints (int index)
{
	return arrayPoints[ index ];
}
