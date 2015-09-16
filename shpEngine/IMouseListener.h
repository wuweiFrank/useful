
#ifndef IMouseListener_h
#define IMouseListener_h 1


//工具类型
enum 
{
	EMAP_TOOL_NULL	= 0,					// 缺省状态下的工具状态

	EMAP_TOOL_MAPVIEW_CONTROLLER = 10,		// 视图的控制工具。  其子工具包括：
									
		EMAP_TOOL_ZOOMIN = 11,				// 缩小
		EMAP_TOOL_ZOOMOUT = 12,				// 放大
		EMAP_TOOL_PAN = 13					// 抓取滚动屏幕
};

class CMouseEvent;

class IMouseListener
{

  public:

      //	鼠标左键被按下。
      virtual void OnLButtonDown (CMouseEvent* pMouseEvent) = 0;

      //	鼠标左键被抬起。
      virtual void OnLButtonUp (CMouseEvent* pMouseEvent) = 0;

      //	鼠标左键被双击。
      virtual void OnLButtonDBLClick (CMouseEvent* pMouseEvent) = 0;

      //	鼠标右键被按下。
      virtual void OnRButtonDown (CMouseEvent* pMouseEvent) = 0;

      //	鼠标右键被抬起。
      virtual void OnRButtonUp (CMouseEvent* pMouseEvent) = 0;

      //	鼠标移动
      virtual void OnMouseMove (CMouseEvent* pMouseEvent) = 0;

      //	鼠标拖动
      virtual void OnMouseDrag (CMouseEvent* pMouseEvent) = 0;

      //	取消操作。
      virtual void OnCancel () = 0;

};

#endif
