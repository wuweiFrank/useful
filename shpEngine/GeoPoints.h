
#ifndef GeoPoints_h
#define GeoPoints_h 
#include "geopoint.h"

class GeoPoints 
{

  public:
      GeoPoints();
      ~GeoPoints();
      GeoPoint GetPoint (int index);
      void GetPoint (int index, double& x, double& y);
      int GetPtCount ();
      void SetPointCount (int nPtCount);
      void SetPoint (int index, double x, double y);
      void SetPoint (int index, GeoPoint point);

  private: 
      double* pArrayX;
      double* pArrayY;
      int nPtCount;
};
#endif
