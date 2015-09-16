
#ifndef Feature_h
#define Feature_h 
#include "Row.h"
class Geometry;

class Feature : public Row  
{
  public:
      Feature (int fid, int subType, Fields* pFields);
      ~Feature();


      int GetFID ();
      int GetSubType ();
      void GetBound (double& minx, double& miny, double& w, double& h);
      void SetBound (double minx, double miny, double w, double h);
      Geometry& GetGeometry ();
      void SetGeometry (Geometry* pGeometry);

  private:
      int m_nSubType;
      double m_dMinx;
      double m_dMiny;
      double m_dWidth;
      double m_dHeight;
      Geometry* m_pGeometry;
};
#endif
