
#ifndef MapLayer_h
#define MapLayer_h 

#include "ILayer.h"

class MapLayer : public ILayer 
{

  public:

      MapLayer (LayerProperty* layerProperty);
      ~MapLayer();
      int GetLayerType ();
      const char* GetLayerName ();
      bool IsVisible ();
      LayerProperty& GetProperty ();
      IRender& GetRender ();

      void SetVisible (bool bVisible);
      void SetRender (IRender* renderObj);
      void GetBound (double& x, double& y, double& w, double& h);

  private:
      LayerProperty* m_pLayerProperty;
      IRender* m_pRender;
};
#endif
