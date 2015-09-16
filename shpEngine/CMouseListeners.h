
#ifndef CMouseListeners_h
#define CMouseListeners_h 
// IMouseListener
#include "IMouseListener.h"
#include <map>
using namespace std;
class CMouseListeners
{
  public:

	  CMouseListeners();
	  ~CMouseListeners();
      void AddMouseListener (int theKey, IMouseListener* pMouseListener);

      int GetCurrentMouseListenerKey ();
      int GetCurrentSubMouseListenerKey ();
      int SetCurrentMouseListenerKey (int theKey, int theSubKey);
      IMouseListener* GetCurrentMouseListener ();
      IMouseListener* Find (int theKey);
      void RemoveMouseListener (IMouseListener* pMouseListener);
      void RemoveMouseListener (int theKey);
      void RemoveAllMouseListener ();
  protected:
      int m_nCurrentMouseListenerKey;
      int m_nCurrentSubMouseListenerKey;
  private:
      map<int,IMouseListener*> m_MouselistenerContainer;

};
#endif
