

#ifndef ILayer_h
#define ILayer_h 

class LayerProperty ;
class IRender ;

class ILayer 
{
  public:

      virtual int GetLayerType () = 0;
      virtual const char* GetLayerName () = 0;

      virtual bool IsVisible () = 0;

      virtual LayerProperty& GetProperty () = 0;
      virtual IRender& GetRender () = 0;

      virtual void GetBound (double& x, double& y, double& w, double& h) = 0;

};
#endif
