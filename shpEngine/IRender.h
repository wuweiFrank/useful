
#ifndef IRender_h
#define IRender_h 

class MapProperty;
class CDC ;

class IRender 
{
 
  public:

      virtual void Render (CDC *pDC, MapProperty* pMapProperty) = 0;

};

#endif
