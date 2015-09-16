
#ifndef Geometry_h
#define Geometry_h 

enum	_GEOTYPE
{
	GEO_POINT = 0,
	GEO_POLYLINE = 1, 
	GEO_POLYGON = 2,
	GEO_ANNOTATION	= 3
};


class Geometry 
{

public:
      virtual int GetGeoType () = 0;

};


#endif
