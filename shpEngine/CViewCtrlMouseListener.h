

#ifndef CViewCtrlMouseListener_h
#define CViewCtrlMouseListener_h 

#include "IMouseListener.h"
class CViewCtrlMouseListener : public IMouseListener 
{

  public:
      CViewCtrlMouseListener();
      ~CViewCtrlMouseListener();

      //鼠标左键被按下。
      void OnLButtonDown (CMouseEvent* pMouseEvent);

      //鼠标左键被抬起。
      void OnLButtonUp (CMouseEvent* pMouseEvent);

      //鼠标左键被双击。
      void OnLButtonDBLClick (CMouseEvent* pMouseEvent);

      //鼠标右键被按下。
      void OnRButtonDown (CMouseEvent* pMouseEvent);

      //鼠标右键被抬起。
      void OnRButtonUp (CMouseEvent* pMouseEvent);

      //鼠标移动
      void OnMouseMove (CMouseEvent* pMouseEvent);

      //鼠标拖动
      void OnMouseDrag (CMouseEvent* pMouseEvent);

      //取消操作。
      void OnCancel ();

  private:
	  CPoint m_LButtonPoint ;
	  CPoint m_lastPoint ;

};
#endif
