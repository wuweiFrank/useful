
#ifndef MapControl_h
#define MapControl_h 
#include "..//stdafx.h"
#include "Layers.h"
#include "CMouseListeners.h"
class CBitmap;
class CView;
class CDC;
class CPoint;

class MapControl
{

  public:
      MapControl();
      ~MapControl();


      void GetDataBound (double& x, double& y, double& w, double& h);
      void GetWorldBound (double& x, double& y, double& w, double& h);

      Layers& GetLayers ();
      void ClientToWorld (double& x, double& y);
      void WorldToClient (double& x, double& y);
      void SetWorldBound (double x, double y, double w, double h);
      void Reset ();
      void ReDraw (int x, int y, int w, int h);
      void DrawMap ();
      void Refresh ();
      void ZoomIn (int x, int y, int w, int h);
      void ZoomOut (int x, int y, int w, int h);
      void Scroll (int dx, int dy);
	  void ClearBuffer( CDC *pDC, int x, int y, int w, int h );
	  void SetViewBound ( int x, int y, int w, int h );
	  void GetViewBound ( int& x, int& y, int& w, int& h );
      void SetOwnerView (CView* pView);
      CView* GetOwnerView ();
	  CPoint* GetOwnerWindowDrawingPos();
	  CMouseListeners& GetMouseListeners();

  private:

	  CPoint *m_pOwnerWindowDrawingPos;
	  CMouseListeners *m_pMouseListeners;

  private: 

	  double dataX;
      double dataY;
      double dataWidth;
      double dataHeight;
      int clientWidth;
      int clientHeight;
      double worldX;
      double worldY;
      double worldWidth;
      double worldHeight;
      CBitmap *m_pMapBuffer;
      CBitmap *m_pPaintBuffer;
      Layers* layers;
	  CView *m_pOwnerView;
};

#endif
