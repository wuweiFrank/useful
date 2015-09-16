#include "StdAfx.h"
#include "GeoPolygon.h"

GeoPolygon::GeoPolygon()
      : nPointsCount(0)
{
}


GeoPolygon::~GeoPolygon()
{
	delete []arrayPoints;
}



int GeoPolygon::GetGeoType ()
{
	return GEO_POLYGON;		
}

void GeoPolygon::SetPointsCount (int nCount)
{
	if( nPointsCount == 0 )
	{
		nPointsCount = nCount;
		arrayPoints = new GeoPoints[ nCount ];
	}
	else
	{
		nPointsCount = nCount;
		delete []arrayPoints;
		arrayPoints = new GeoPoints[ nCount ];
	}
}

int GeoPolygon::GetPointsCount ()
{
	return nPointsCount;
}

GeoPoints& GeoPolygon::GetPoints (int index)
{
	return arrayPoints[ index ];
}