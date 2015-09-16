#include "StdAfx.h"
#include "GeoPoint.h"
GeoPoint::GeoPoint()
      : x(0),
        y(0)
{
}

GeoPoint::GeoPoint (double X, double Y)
      : x(0),
        y(0)
{
	this->x = X;
	this->y = Y;
}


GeoPoint::~GeoPoint()
{
}



int GeoPoint::GetGeoType ()
{
	return GEO_POINT;
}

double GeoPoint::GetX ()
{
	return x;
}

double GeoPoint::GetY ()
{
	return y;
}

void GeoPoint::SetX (double X)
{
	this->x = X;
}

void GeoPoint::SetY (double Y)
{
	this->y = Y;
}

