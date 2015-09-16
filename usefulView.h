
// usefulView.h : CusefulView 类的接口
//

#pragma once

#include "shpEngine/MapControl.h"
#include "shpEngine/DataSet.h"

#include <vector>
using namespace std;

struct TRIANGLE
{
	int paivertix[3];
	int piffacest[3];
};
struct TriVERTIX
{
	double padivertixX;
	double padivertixY;
};
struct GridVERTIX 
{
	double grid_x;
	double grid_y;
	double grid_value;
};
typedef vector<TRIANGLE>	tagTIN;
typedef vector<TriVERTIX>	tagVEX;
typedef vector<GridVERTIX>	tagGRID;

class CusefulDoc;
class CusefulView : public CView
{
protected: // 仅从序列化创建
	CusefulView();
	DECLARE_DYNCREATE(CusefulView)

// 特性
public:
	CusefulDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	//从文件中导入三角形，绘制三角形代码
	void draw_triangle(tagTIN tinNet,tagVEX triVex,CDC* pDC);
	void draw_grid(tagGRID grid,CDC *pDC);

	MapControl *m_pMapControl;
	BOOL        m_is_show_SHP;
	MapControl& CusefulView::GetMapControl();

// 实现
public:
	virtual ~CusefulView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShpFileOpen();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // usefulView.cpp 中的调试版本
inline CusefulDoc* CusefulView::GetDocument() const
   { return reinterpret_cast<CusefulDoc*>(m_pDocument); }
#endif

