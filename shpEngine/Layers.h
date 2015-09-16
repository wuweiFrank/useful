
#ifndef Layers_h
#define Layers_h 

#include "ILayer.h"
#include <vector>
using namespace std;
typedef vector< ILayer * > VECTORLayer;

class Layers 
{

  public:
      Layers();
      ~Layers();

      void Add (ILayer* layer);
      ILayer* GetLayer (int index);
      int Count ();
      int GetActive ();
      ILayer* GetActiveLayer ();
      void SetActive (int index);
      bool MoveTo (int fromIndex, int toIndex);
      bool MoveToBottom (int index);
      bool MoveToTop (int index);
      void Remove (int index);
      void Clear ();

  private: 
	  VECTORLayer m_vectorLayers;
      int m_nActiveIndex;
    
};

#endif
