
#ifndef GeoPolygon_h
#define GeoPolygon_h 


#include "Geometry.h"
#include "GeoPoints.h"

class GeoPolygon : public Geometry  
{

  public:
      GeoPolygon();

      ~GeoPolygon();
      int GetGeoType ();
      void SetPointsCount (int nCount);
      int GetPointsCount ();
      GeoPoints& GetPoints (int index);
  private:
      GeoPoints* arrayPoints;
      int nPointsCount;
};
#endif
