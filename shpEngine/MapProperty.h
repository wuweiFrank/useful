
#ifndef MapProperty_h
#define MapProperty_h 
class MapControl;

class MapProperty 
{

  public:
      MapProperty (MapControl* mapCtrl);
      ~MapProperty();
      void ClientToWorld (double& x, double& y);
      void WorldToClient (double& x, double& y);
      void GetClipRect (int& x, int& y, int& w, int& h);
      void SetClipRect (int x, int y, int w, int h);
	  double GetViewScale();
	  void ClientToWorldEx (double& x, double& y);
      void WorldToClientEx (double& x, double& y);

	  // 基于屏幕坐标系旋转，参数必须为屏幕坐标
	  void RotateBaseOnClient(double& x, double& y, bool direction);
	  // 基于地理坐标系旋转，参数必须为地理坐标
	  void RotateBaseOnWorld(double& x, double& y, bool direction);

  private: 
      MapControl* m_pMapControl;
      int m_nClipX;
      int m_nClipY;
      int m_nClipWidth;
      int m_nClipHeight;
};
#endif
