#pragma once


// CDialog3D 对话框
#include "COpenGL/COpenGL.h"
#include <vector>
#include<fstream>
#include <algorithm>
using namespace std;

struct PNT3D 
{
	float DX;
	float DY;
	float DZ;
};

class CDialog3D : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3D)

public:
	CDialog3D(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog3D();

	//对话框数据
	enum { IDD = IDD_DIALOG1 };
	COpenGL			m_Histro_GLopt;

	vector<PNT3D>	m_vec_PNT3Ds;
	vector<PNT3D>	m_vec_colors;

	float			m_min_DX;
	float			m_min_DY;
	float			m_max_DX;
	float			m_max_DY;
	float			m_min_DZ;
	float			m_max_DZ;

	//绘制直方图
	void OnDraw();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnColor();
};
