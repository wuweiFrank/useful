#include "StdAfx.h"
#include "GeoAnnotation.h"
#include <string>
GeoAnnotation::GeoAnnotation()
      : pString(0)
{
}

GeoAnnotation::GeoAnnotation (double X, double Y, const char *string)
      : pString(0)
{
	x = X;
	y = Y;
	if( pString != 0 ) 
	{
		delete []pString;
		pString = 0;
	}
	int len = strlen( string );
	pString = (char*)malloc( len + 1 );
	strcpy( pString, string );
}


GeoAnnotation::~GeoAnnotation()
{
	if( pString )
	{
		delete []pString;
	}
}



int GeoAnnotation::GetGeoType ()
{
	return GEO_ANNOTATION;
}

double GeoAnnotation::GetX ()
{
	return x;
}

double GeoAnnotation::GetY ()
{
	return y;
}

const char * GeoAnnotation::GetString ()
{
	return pString;
}

void GeoAnnotation::SetString (const char *string)
{
	if( pString )
	{
		delete []pString;
		pString = 0;
	}
	int len = strlen( string );
	pString = ( char * )malloc( len );
	strcpy( pString, string );
}

void GeoAnnotation::SetX (double X)
{
	x = X;
}

void GeoAnnotation::SetY (double Y)
{
	y = Y;
}
