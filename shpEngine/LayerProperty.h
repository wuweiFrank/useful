
#ifndef LayerProperty_h
#define LayerProperty_h 
#include "dataset.h"

class LayerProperty 
{
  public:
      LayerProperty (int layerID, const char* name );
      ~LayerProperty();
      int GetLayerID ();

      const char* GetLayerName ();
      int GetLayerIndex ();

      bool IsVisible ();
      double GetMinVisual ();
      double GetMaxVisual ();
      void SetMinVisual (double visual);
      void SetMaxVisual (double visual);
      void SetRelateDataSet (DataSet* pDataset);

      DataSet& GetRelateDataSet ( );

      void SetLayerIndex (int layerIndex);

      void SetVisible (bool visible);

  private: 
      int m_nLayerID;
      char m_szName[40];
      int m_nLayerIndex;
      bool m_isVisible;
      double m_dMinVisual;
      double m_dMaxVisual;
      DataSet *m_pDataSet;

};

#endif
