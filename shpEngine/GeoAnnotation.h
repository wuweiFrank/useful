
#ifndef GeoAnnotation_h
#define GeoAnnotation_h 
#include "Geometry.h"

class GeoAnnotation : public Geometry  
{

  public:
      GeoAnnotation();
      GeoAnnotation (double X, double Y, const char *string = 0);
      ~GeoAnnotation();

      int GetGeoType ();

      double GetX ();

      double GetY ();

      const char * GetString ();

      void SetString (const char *string);

      void SetX (double X);

      void SetY (double Y);


  private: 
      char* pString;
      double x;
      double y;
};
#endif
