
#ifndef GeoPolyline_h
#define GeoPolyline_h 

#include "Geometry.h"
#include "GeoPoints.h"

class GeoPolyline : public Geometry 
{

  public:
      GeoPolyline();

      ~GeoPolyline();

      int GetGeoType ();
      void SetPointsCount (int nCount);

      int GetPointsCount ();
      GeoPoints& GetPoints (int index);

  private:
      GeoPoints* arrayPoints;
      int nPointsCount;
};
#endif
