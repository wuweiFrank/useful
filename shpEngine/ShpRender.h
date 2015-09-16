
#ifndef ShpRender_h
#define ShpRender_h 

#include "IRender.h"
class MapLayer ;
class ShpRender : public IRender  
{
  public:
      ShpRender (MapLayer* pLayer);
      ~ShpRender();

      void Render (CDC *pDC, MapProperty* pMapProperty);

  private: 
      MapLayer* m_pLayer;
};

#endif
