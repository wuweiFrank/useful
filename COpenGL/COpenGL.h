/************************************************************************/
/*                        北京博维恒信公司                              */
/*                           COpenGL.h                                  */
/*                        编写人：李瑞                                  */
/*                        日期：  二○○五年三月十五日                  */
/*                        用途：  封装OpenGL有关参数设置用于MFC         */                                                       
/************************************************************************/
/**/
#ifndef   __COPENGL_H__
#define   __COPENGL_H__
 
#include "MyClass.h"  //三维点、向量、四维点、颜色、二维纹理坐标
                      //矩阵计算    加 乘 逆 转 特征值 特征向量
                      //变换矩阵    平移  绕X\Y\Z任意一轴旋转 
                      //            点绕任意轴旋转
                      //            向量旋转到Z轴平行方向
////////////////////////////////////////////////////////////////////////////
#include <wingdi.h>//win32 API 画图程序库
#pragma comment(lib,"gdi32.lib")//
#pragma comment(lib,"COpenGL.lib")
////////////////////////////////////////////////////////////////////////////


class __declspec(dllexport) COpenGL        //Set OpenGL Condition in CView 
{
public:
////////////////////////////////////////////////////////////////////////////////
	//鼠标视图操作mouse view operator   
	//鼠标键     左 中 右 滚轮button - left middle right wheel   
	//鼠标操作   单击 放开 双击 移动 转动 operator - down  up  d-down  move  
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonDblClk(UINT nFlags, CPoint point);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnMButtonUp(UINT nFlags, CPoint point);
	void OnMButtonDown(UINT nFlags, CPoint point);
	void OnMButtonDblClk(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);	

////////////////////////////////////////////////////////////////////////////////////////////////////////
//  char ch  = 
	//  'l' or 'L' - Left View    
	//  'r' or 'R'  - Right View  
	//   other  -  one view
	void GetViewModelProjectMatrix(char  ch , GLint  Viewport[4], GLdouble Modelmatrix[16] , GLdouble Projmatrix[16]);//view model project matrix
	//获取 Viewport  － 视图矩阵   Modelmatrix  － 模型矩阵   Projmatrix  － 投影矩阵
	void GetRotate(char ch , GLdouble  Matrix[4][4]);//旋转矩阵
	void SetRotate(char ch , GLdouble  Matrix[4][4]);//rotate matrix
	tagCVector GetScaling(char ch);//缩放比例
	void SetScaling(char ch , tagCVector&  fScaling);//scaling
	tagCVector GetTranslate(char ch);//平移量
	void SetTranslate(char  ch , tagCVector&  fTranslate);//translate
	tagCVector GetRotateCenter(char ch);//旋转中心
	void SetRotateCenter(char  ch , tagCVector&  fRotateCenter);// rotate center
//  char ch
////////////////////////////////////////////////////////////////////////////////////////////////////////	

////////////////////////////////////////////////////////////////////////////////////////////////////////
	void GetLookAtData(tagCVector& fEyePos, tagCVector& fAspectPos, tagCVector& fUpAspect);
	//视点设置 look view point    
	// fEyePos -视点 viewpiont    fAspectPos - 视区中心viewbox center     fUpAspect -相机方向 camera up aspect
	void SetLookAtData(tagCVector&  fEyePos , tagCVector&  fAspectPos , tagCVector&  fUpAspect);
	tagCVector GetPerspectiveProjectionData();
	//三维透视投影参数
      //m_fPerspective.x - 角度 angle  
	  //m_fPerspective.y - 距离视点最近距离near position     Frustum 3D
	  //m_fPerspective.z - 距离视点最远距离far position      Frustum 3D
	void SetPerspectiveProjectionData(tagCVector&  fPerspective);//3D Perspective 
	                          //m_fPerspective;//3D Perspective Projection 
	                          //m_fPerspective.x - angle  
	                          //m_fPerspective.y - near position Frustum 3D
	                          //m_fPerspective.z - far position  Frustum 3D
	GLdouble GetOrthoScaleZAxis();//正交投影  Z方向与Y方向比例
	void SetOrthoScaleZAxis(GLdouble& dOrthScale_Z);//3D Ortho   z axis  scale
	bool IsTwoView();//判定是否切分窗口  CView::OnDraw(CDC *pDC) is or not two view	
	void SetTwoView(bool bBTwoView);//设置切分窗口与否 set two view or not
	void GetBox(tagCVector&   fBoxCenter, tagCVector& fBoxSize);//数据包围盒 中心 半边长box   fBoxCenter  -  center point   fBoxSize  -  box size
	void SetBox(tagCVector&   fBoxCenter, tagCVector& fBoxSize);
	tagColor GetBfColor();//前景颜色
	void SetBfColor(tagColor& fBfColor);//before color
	tagColor GetBkColor();//背景颜色
	void SetBkColor(tagColor& fBkColor);//back color
	BYTE GetProjectionMode();//投影模式
	void SetProjectionMode(BYTE bProjectionMode);//投影模式
	                             //0 - Orthographic 2D Projection  
	                             //1 - Orthographic 3D Projection  default 
	                             //2 - 3D Perspective Projection  
	                             //3 - Frustum 3D Perspective Projection
///////////////////////////////////////////////////////////////////////////////////////////////////
	void OnDrawRight();//切分窗口 右窗口设置  CView::OnDraw(CDC *pDC) set right view projection data 
	void OnInitRenderOpenGL();//初始化窗口设置  包括切分左窗口 CView::OnDraw(CDC *pDC)  one view and left view
	void OnInitUpdateData();//初始化COpenGL内部参数  CView::CView()
	void OnInitUpdatePartData();//初始化COpenGL内部部分参数  update part data
	void SwapBufferOpenGL();//双缓存 CView::OnDraw(CDC *pDC)
	void OnSizeOpenGL(UINT nType, int cx, int cy);//设置窗口大小  set view size CView::OnSize(UINT nType, int cx, int cy)
	bool OnDestroyOpenGL();//释放OpenGL资源 destroy opengl rc	//CView::OnDestroy() 	//
	bool OnInitOpenGL(HWND hWnd);//获取Windows手柄 初始化环境参数 get windows handle int  CView::OnCreate(LPCREATESTRUCT lpCreateStruct)  OnInitOpenGL(GetSafeHwnd())
	COpenGL();
    ~COpenGL();

protected:

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnMouseScalePart(CPoint point , CRect& pRect , tagCVector& fScaling , tagCVector& fTranslate);
	//鼠标操作局部放大
	//scale part by select in rectangle  return fscaling  and fTranslate
	void OnMouseRotateZAxis(CPoint point,tagCVector& fRotateCenter, GLint  Viewport[4], GLdouble Modelmatrix[16] , GLdouble Projmatrix[16], GLdouble Matrix[][4]);
	//鼠标操作绕垂直于屏幕方向旋转	
	//rotate around fRotateCenter in screen  return  Matrix
	void OnMouseRotate(CPoint point,GLdouble Matrix[4][4]);
	//鼠标操作任意旋转	
	//rotate by mouse move     
	void OnMouseTranslate(CPoint point,CSize& nSize,tagCVector& fScaling ,tagCVector& fTranslate);
	//鼠标操平移    
	//translate view - size is nSize by mouse move  return fTranslate
	void OnMouseMoveTransform(UINT  nFlags , CPoint point);
	//鼠标中键操作进行变换	
	//transform by mouse middle
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void OnComputeProjectionParameter();//计算投影参数 compute project parameter (y,z) int m_fPerspective and m_fEyePos
	void OnMouseDownRect(CPoint point);//如果切分窗口  判定鼠标单击在左还是右窗口if view divide into parts  ,it jugdes mouse down in which view
	void OnDrawMiddle();//画切分条 view divide into two  , draw middle rectangle
	void OnTransformOpenGL(char ch);//变换矩阵  transform matrix translate rotate  get matrix
	void OnProjectionCOpenGL(GLint xGL, GLint yGL, GLsizei xGLWidth, GLsizei yGLHeight);
	//投影设置  (xGL , yGL) - 左上角视点    (xGLWidth , yGLHeight) - 视图区域横纵向大小
	//opengl projection set
	//(xGL , yGL) - view leftup point     (xGLWidth , yGLHeight) - view size
	void PrintString(const char *str);//绘制三维字体 print 3d string
	void RasterFont();//初始化字体string raster
	bool CreateCViewCOpenGLContext();//创建OpenGL设备文  create CView COpenGL Context
	bool SetWindowPixelFormat();//设置Windows像素设置  set windows pixel format

protected:
///////////////////////////////////////////////////////////////////////////////////////////
/////COpenGL Data 
	HWND       m_hWnd;//windows handle  active
	HDC        m_hDC;//dc handle  about windows
	HGLRC      m_hRC;//rc handle

    CSize      m_nSize;//windows view size
    GLuint     m_nFont;// 3d font
	BYTE       m_bProjectionMode;//0 - Orthographic 2D Projection  
	                             //1 - Orthographic 3D Projection  
	                             //2 - 3D Perspective Projection  
	                             //3 - Frustum 3D Perspective Projection
    tagColor   m_fBkColor;// set opengl back color
	tagColor   m_fBfColor;// set opengl before color
	tagCVector m_fBoxSize;// box size half (length width height) x y z
	tagCVector m_fBoxCenter;// box center vertex
	GLdouble   m_dBoxMaxSize;// half length of max edge of Box
	bool       m_bBTwoView;//is or not two view   left and right  
	BYTE       m_bMouseLeftRight;//Left Button Down in Left View or Right View
                                 //0-no  1-Left View  2-Right View
///////////////////////////////////////////////////////////////////////////////////////
///projection data
	GLdouble   m_dOrthScale_Z;//Orthographic 3D Projection  z axis ratio    
	tagCVector m_fPerspective;//3D Perspective Projection 
	                          //m_fPerspective.x - angle  
	                          //m_fPerspective.y - near position Frustum 3D
	                          //m_fPerspective.z - far position  Frustum 3D
	
	tagCVector m_fEyePos;//3D Perspective Projection  Eye position
	tagCVector m_fAspectPos;////3D Perspective Projection  eye aspect position
	tagCVector m_fUpAspect;//3D Perspective Projection up aspect
/////////////////////////////////////////////////////////////////////////////////////////
////one view data
	tagCVector m_fRotateCenter;//set opengl rotate center 
	tagCVector m_fTranslate;//set opengl translate dxyz
	tagCVector m_fScaling;//m_fScaling (x,y,z)   on x y z axis scaling
    GLint      viewport[4];//view matrix
    GLdouble   modelmatrix[16],projmatrix[16];//model projection matrix
    GLdouble   matrix[4][4];//i - clos  j - rows 
	                        //rotate matrix all -left hand criterion	
/////////////////////////////////////////////////////////////////////////////////////////
////left view data
	tagCVector m_fLRotateCenter;//set left view opengl rotate center 
	tagCVector m_fLTranslate;//set left view opengl translate dxyz
	tagCVector m_fLScaling;//m_fLScaling (x,y,z)   on  left view x y z axis scaling
    GLint      lviewport[4];// left view matrix
    GLdouble   lmodelmatrix[16],lprojmatrix[16];// left view model projection matrix
    GLdouble   lmatrix[4][4];//i - clos  j - rows 
	                        //rotate matrix  left view -left hand criterion	
/////////////////////////////////////////////////////////////////////////////////////////
////right view data
	tagCVector m_fRRotateCenter;//set right view opengl rotate center 
	tagCVector m_fRTranslate;//set right view opengl translate dxyz
	tagCVector m_fRScaling;//m_fRScaling (x,y,z)   on  right view x y z axis scaling
    GLint      rviewport[4];// right view matrix
    GLdouble   rmodelmatrix[16],rprojmatrix[16];// right view model projection matrix
    GLdouble   rmatrix[4][4];//i - clos  j - rows 
	                        //rotate matrix  right view -left hand criterion
///////////////////////////////////////////////////////////////////////////////////
	CPoint     m_nMouseMovePos;// mouse move position
	CPoint     m_nMouseDownPos;// mouse down position
	
};

#endif