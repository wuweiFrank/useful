
// usefulView.cpp : CusefulView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "useful.h"
#endif

#include "usefulDoc.h"
#include "usefulView.h"
#include "shpEngine/CMouseEvent.h"
#include "shpEngine/LayerProperty.h"
#include "shpEngine/MapLayer.h"
#include "shpEngine/ShpRender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CusefulView

IMPLEMENT_DYNCREATE(CusefulView, CView)

BEGIN_MESSAGE_MAP(CusefulView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CusefulView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHP32775, &CusefulView::OnShpFileOpen)
END_MESSAGE_MAP()

// CusefulView 构造/析构

CusefulView::CusefulView()
{
	// TODO: 在此处添加构造代码
	m_is_show_SHP=FALSE;
	m_pMapControl = new MapControl ;
}

CusefulView::~CusefulView()
{
	if ( m_pMapControl != 0 )
	{
		delete m_pMapControl ;
		m_pMapControl = 0 ;
	}
}

BOOL CusefulView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CusefulView 绘制

void CusefulView::OnDraw(CDC* pDC)
{
	CusefulDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->m_triShow)
		draw_triangle(pDoc->m_tinNet,pDoc->m_triVex,pDC);
	if(pDoc->m_gridShow)
		draw_grid(pDoc->m_grid,pDC);
	if(pDoc->m_shp_Show)
	{
		CRect clientRect;
		this->GetClientRect( &clientRect );
		if ( m_pMapControl == 0 ) return ;
		m_pMapControl->SetViewBound( clientRect.left,clientRect.top,clientRect.Width(), clientRect.Height() );
		m_pMapControl->DrawMap();
	}

	// TODO: 在此处为本机数据添加绘制代码
}

// CusefulView 打印


void CusefulView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CusefulView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CusefulView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CusefulView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CusefulView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CusefulView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CusefulView 诊断

#ifdef _DEBUG
void CusefulView::AssertValid() const
{
	CView::AssertValid();
}

void CusefulView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CusefulDoc* CusefulView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CusefulDoc)));
	return (CusefulDoc*)m_pDocument;
}
#endif //_DEBUG


// CusefulView 消息处理程序

void CusefulView::draw_triangle(tagTIN tinNet,tagVEX triVex,CDC* pDC)
{
	//获取区域的最大最小值
	double maxx=triVex[0].padivertixX,
		   maxy=triVex[0].padivertixY,
		   minx=triVex[0].padivertixX,
		   miny=triVex[0].padivertixY;
	for(int i=0;i<(int)triVex.size();i++)
	{
		maxx=max(maxx,triVex[i].padivertixX);
		minx=min(minx,triVex[i].padivertixX);
		maxy=max(maxy,triVex[i].padivertixY);
		miny=min(miny,triVex[i].padivertixY);
	}
	double scalex=1000/abs(maxx-minx);
	double scaley=600/abs(maxy-miny);
	for (int i=0;i<tinNet.size();i++)
	{
		pDC->MoveTo(int(triVex[tinNet[i].paivertix[0]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[0]].padivertixY-miny+10)*scaley);
		pDC->LineTo(int(triVex[tinNet[i].paivertix[1]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[1]].padivertixY-miny+10)*scaley);

		pDC->MoveTo(int(triVex[tinNet[i].paivertix[1]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[1]].padivertixY-miny+10)*scaley);
		pDC->LineTo(int(triVex[tinNet[i].paivertix[2]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[2]].padivertixY-miny+10)*scaley);

		pDC->MoveTo(int(triVex[tinNet[i].paivertix[2]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[2]].padivertixY-miny+10)*scaley);
		pDC->LineTo(int(triVex[tinNet[i].paivertix[0]].padivertixX-minx+10)*scalex,int(triVex[tinNet[i].paivertix[0]].padivertixY-miny+10)*scaley);
	}
}

void CusefulView::draw_grid(tagGRID grid,CDC *pDC)
{
	//获取区域的最大最小值
	double maxx=grid[0].grid_x,
		   maxy=grid[0].grid_y,
		   minx=grid[0].grid_x,
		   miny=grid[0].grid_y;

	for(int i=0;i<(int)grid.size();i++)
	{
		maxx=max(maxx,grid[i].grid_x);
		minx=min(minx,grid[i].grid_x);
		maxy=max(maxy,grid[i].grid_y);
		miny=min(miny,grid[i].grid_y);
	}

	double scalex=1000/abs(maxx-minx);
	double scaley=600/abs(maxy-miny);

	for (int i=0;i<grid.size();i++)
		pDC->Ellipse(scalex*(grid[i].grid_x-minx+10)-2,scaley*(grid[i].grid_y-miny+10)-2,scalex*(grid[i].grid_x-minx+10)+2,scaley*(grid[i].grid_y-miny+10)+2);
}

MapControl& CusefulView::GetMapControl()
{
	return *m_pMapControl ;
}


void CusefulView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CusefulDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->m_shp_Show)
	{
		this->SetCapture();
		CMouseListeners& mouselisteners = this->m_pMapControl->GetMouseListeners();
		IMouseListener *pMouseListener = mouselisteners.GetCurrentMouseListener();
		if ( pMouseListener != 0 )
		{
			CMouseEvent event( this->m_pMapControl, point, nFlags, mouselisteners.GetCurrentSubMouseListenerKey() );
			pMouseListener->OnLButtonDown( & event );
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CusefulView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CusefulDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CView::OnMouseMove(nFlags, point);
}

void CusefulView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CusefulDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CView::OnLButtonUp(nFlags, point);
}

void CusefulView::OnShpFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CusefulDoc *pDoc = this->GetDocument();
	FeatureClass *pFeatureClass = pDoc->load_shapefile_file();
	if ( pFeatureClass == 0 ) return ;

	Layers& layers = m_pMapControl->GetLayers();
	LayerProperty *pLayerProperty = new LayerProperty(layers.Count()+1,pFeatureClass->GetName());
	pLayerProperty->SetRelateDataSet( pFeatureClass);
	MapLayer *pMapLayer = new MapLayer( pLayerProperty );
	pMapLayer->SetRender( new ShpRender( pMapLayer) );
	layers.Add( pMapLayer );

	this->m_pMapControl->Reset();
	CRect clientRect;
	this->GetClientRect(&clientRect);
	this->m_pMapControl->ReDraw(clientRect.left,clientRect.top,clientRect.Width(),clientRect.Height());
	this->Invalidate(false);
}


void CusefulView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	if ( m_pMapControl == 0 ) return ;
	m_pMapControl->SetOwnerView( this );
}
