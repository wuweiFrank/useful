
#ifndef FeatureClass_h
#define FeatureClass_h 
#include "Table.h"
#include "Feature.h"
class FeatureClass : public Table  
{
  public:

      FeatureClass (int id, int type, const char *strName, DataSource* pDataSource = 0);
      ~FeatureClass();
      const char* GetName ();
      void GetBound (double& minx, double& miny, double& w, double& h);
      void CalculateBound ();
      int  GetFeatureSize ();
      Feature* GetFirstFeature ();
      Feature* GetNextFeature ();
      Feature* GetFeature (int fid);

  private: 
      double m_dMinx;
      double m_dMiny;
      double m_dWidth;
      double m_dHeight;

};
#endif
