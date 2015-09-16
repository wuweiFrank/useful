
#ifndef CMouseEvent_h
#define CMouseEvent_h 

//	CMouseEvent类：鼠标事件类。
class CMouseEvent
{
  public:
      //	构造函数。
      //	在构造该对象时，初始化各成员变量。
      CMouseEvent (void* pSource, CPoint point, int mouseFlag, int theTool = -1);
      ~CMouseEvent();


      //	获取当前鼠标所在点的坐标。该坐标为设备坐标。
      CPoint GetPoint ();

      //	获取当前鼠标控制键的状态。
      int GetMouseFlag ();

      //	获取当前交互工具的子工具类型。
      int GetTool ();

	  void* GetSource ();

  private:
      //	当前鼠标所在点的坐标。该坐标为设备坐标。
      CPoint m_Point;
      //	表明当前是否有控制键被按下。详见EGIS_MouseFlag的说明。
      int m_MouseFlag;
      //	当前交互工具的子工具类型。
      int m_tool;
	  void* m_pSource;
};

#endif
