
#ifndef GeoPoint_h
#define GeoPoint_h 
#include "Geometry.h"

class GeoPoint : public Geometry  
{

  public:
      GeoPoint();
      GeoPoint (double X, double Y);
      ~GeoPoint();

      int GetGeoType ();
      double GetX ();
      double GetY ();
      void SetX (double X);

      void SetY (double Y);


  private: 
      double x;

      double y;
};

#endif
