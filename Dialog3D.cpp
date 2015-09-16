// Dialog3D.cpp : 实现文件
//

#include "stdafx.h"
#include "useful.h"
#include "Dialog3D.h"
#include "afxdialogex.h"
#include "gdal//gdal_priv.h"
#pragma comment(lib,"gdal_i.lib")

// CDialog3D 对话框

IMPLEMENT_DYNAMIC(CDialog3D, CDialogEx)

CDialog3D::CDialog3D(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog3D::IDD, pParent)
{
	m_Histro_GLopt.SetProjectionMode(0);
	m_Histro_GLopt.SetTwoView(false);
	m_vec_PNT3Ds.clear();
	m_vec_colors.clear();
}
CDialog3D::~CDialog3D()
{
	m_vec_PNT3Ds.clear();
	m_vec_colors.clear();
}
void CDialog3D::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialog3D, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CDialog3D::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_COLOR, &CDialog3D::OnBnClickedBtnColor)
END_MESSAGE_MAP()


// CDialog3D 消息处理程序
int CDialog3D::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_Histro_GLopt.OnInitOpenGL(GetSafeHwnd());
	return 0;
}
void CDialog3D::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_Histro_GLopt.OnDestroyOpenGL();
}
BOOL CDialog3D::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialogEx::OnEraseBkgnd(pDC);
	return TRUE;
}
void CDialog3D::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnLButtonDown(nFlags,point);
	CDialogEx::OnLButtonDown(nFlags, point);
}
void CDialog3D::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnLButtonUp(nFlags,point);
	InvalidateRect(NULL,FALSE);
	CDialogEx::OnLButtonUp(nFlags, point);
}
void CDialog3D::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnMButtonDown(nFlags,point);
	CDialogEx::OnMButtonDown(nFlags, point);
}
void CDialog3D::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnMButtonUp(nFlags,point);
	InvalidateRect(NULL,FALSE);
	CDialogEx::OnMButtonUp(nFlags, point);
}
void CDialog3D::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnMouseHWheel(nFlags, zDelta, pt);
}
void CDialog3D::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnMouseMove(nFlags,point);
	InvalidateRect(NULL,FALSE);
	CDialogEx::OnMouseMove(nFlags, point);
}
void CDialog3D::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnRButtonDown(nFlags,point);
	CDialogEx::OnRButtonDown(nFlags, point);
}
void CDialog3D::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnRButtonDown(nFlags,point);
	InvalidateRect(NULL,FALSE);
	CDialogEx::OnRButtonUp(nFlags, point);
}
BOOL CDialog3D::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Histro_GLopt.OnMouseWheel(nFlags,zDelta,pt);
	InvalidateRect(NULL,FALSE);
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
void CDialog3D::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_Histro_GLopt.OnSizeOpenGL(nType,cx,cy);
}
void CDialog3D::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	m_Histro_GLopt.OnInitRenderOpenGL();
	OnDraw();
	m_Histro_GLopt.SwapBufferOpenGL();
}
void CDialog3D::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}

void CDialog3D::OnDraw()
{
	if (m_vec_PNT3Ds.empty())
		return;
	float scalex=10.0f/(m_max_DX-m_min_DX);
	float scaley=10.0f/(m_max_DY-m_min_DY);
	float scalez=10.0f/(m_max_DZ-m_min_DZ);
	//float scalex=1;
	//float scaley=1;
	//float scalez=1;
	if(m_vec_colors.empty())
	{
		glColor3f(1.0f,1.0f,1.0f);
		glBegin(GL_POINTS);
		for (int i=0;i<m_vec_PNT3Ds.size();i++)
		{
			glColor3f(m_vec_PNT3Ds[i].DZ/m_max_DZ,1-m_vec_PNT3Ds[i].DZ/m_max_DZ,0.0f);
			float x=(m_vec_PNT3Ds[i].DX-m_min_DX)*scalex,y=(m_vec_PNT3Ds[i].DY-m_min_DY)*scaley,z=m_vec_PNT3Ds[i].DZ*scalez;
			glVertex3f(x,y,z);
		}
		glEnd();
	}
	else
	{
		glBegin(GL_POINTS);
		for (int i=0;i<m_vec_colors.size();i++)
		{
			glColor3f(m_vec_colors[i].DX,m_vec_colors[i].DY,m_vec_colors[i].DZ);
			float x=(m_vec_PNT3Ds[i].DX-m_min_DX)*scalex-5,y=(m_vec_PNT3Ds[i].DY-m_min_DY)*scaley-4,z=m_vec_PNT3Ds[i].DZ*scalez;
			glVertex3f(x,y,z);
		}
		glEnd();
	}
}
void CDialog3D::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal()!=IDOK)
		return;
	CString strExt	   =fileDlg.GetFileExt();
	CString strPathName=fileDlg.GetPathName();
	if(strExt=="txt")
	{
		ifstream ifs(strPathName,ios_base::in);
		char tmpchr[2048];
		ifs.getline(tmpchr,2048);
		do 
		{
			PNT3D tmpPnt;
			ifs.getline(tmpchr,2048);
			sscanf(tmpchr,"%f,%f,%f",&tmpPnt.DX,&tmpPnt.DY,&tmpPnt.DZ);
			m_vec_PNT3Ds.push_back(tmpPnt);
		} while (!ifs.eof());
		ifs.close();
	}
	if(strExt=="BMP"||strExt=="bmp"||strExt=="JPG"||strExt=="jpg"||strExt=="TIF"||strExt=="tif")
	{
		GDALAllRegister();
		GDALDatasetH hSrcDS=GDALOpen(strPathName,GA_ReadOnly);
		double adfGeoTrans[6];
		double scalex=1,scaley=1;
		GDALGetGeoTransform(hSrcDS,adfGeoTrans);
		int xsize=GDALGetRasterXSize(hSrcDS);
		int ysize=GDALGetRasterYSize(hSrcDS);
		int tmpxsize=xsize,tmpysize=ysize;
		if(xsize>800)
		{
			tmpxsize=800;
			scalex=xsize/tmpxsize;
		}
		if(ysize>600)
		{
			tmpysize=600;
			scaley=ysize/tmpysize;
		}
		float *dataIn=new float[tmpxsize*tmpysize];
		GDALRasterIO(GDALGetRasterBand(hSrcDS,1),GF_Read,0,0,xsize,ysize,dataIn,tmpxsize,tmpysize,GDT_Float32,0,0);
		for(int i=0;i<tmpxsize;i++)
		{
			for (int j=0;j<tmpysize;j++)
			{
				PNT3D tmpPnt;
				tmpPnt.DX=adfGeoTrans[0]+adfGeoTrans[1]*i*scalex+adfGeoTrans[2]*j*scaley;
				tmpPnt.DY=adfGeoTrans[3]+adfGeoTrans[4]*i*scalex+adfGeoTrans[5]*j*scaley;
				//tmpPnt.DX=i;
				//tmpPnt.DY=j;
				tmpPnt.DZ=dataIn[j*tmpxsize+i];
				m_vec_PNT3Ds.push_back(tmpPnt);
			}
		}
		delete[]dataIn;
		GDALClose(hSrcDS);
	}
	if(!m_vec_PNT3Ds.empty())
	{
		m_min_DX=m_max_DX=m_vec_PNT3Ds[0].DX;
		m_min_DY=m_max_DY=m_vec_PNT3Ds[0].DY;
		m_min_DZ=m_max_DZ=m_vec_PNT3Ds[0].DZ;
		for (int i=0;i<m_vec_PNT3Ds.size();i++)
		{
			m_max_DX=max(m_vec_PNT3Ds[i].DX,m_max_DX);
			m_min_DX=min(m_vec_PNT3Ds[i].DX,m_min_DX);
			m_max_DY=max(m_vec_PNT3Ds[i].DY,m_max_DY);
			m_min_DY=min(m_vec_PNT3Ds[i].DY,m_min_DY);
			m_max_DZ=max(m_vec_PNT3Ds[i].DZ,m_max_DZ);
			m_min_DZ=min(m_vec_PNT3Ds[i].DZ,m_min_DZ);
		}
		AfxMessageBox("数据读取成功!\n");
		InvalidateRect(NULL,FALSE);
	}
}
void CDialog3D::OnBnClickedBtnColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal()!=IDOK)
		return;
	CString strExt	   =fileDlg.GetFileExt();
	CString strPathName=fileDlg.GetPathName();
	if(strExt=="BMP"||strExt=="bmp"||strExt=="JPG"||strExt=="jpg"||strExt=="TIF"||strExt=="tif"||strExt=="png"||strExt=="PNG")
	{
		GDALAllRegister();
		GDALDatasetH hSrcDS=GDALOpen(strPathName,GA_ReadOnly);
		double adfGeoTrans[6];
		double scalex=1,scaley=1;
		GDALGetGeoTransform(hSrcDS,adfGeoTrans);
		int xsize=GDALGetRasterXSize(hSrcDS);
		int ysize=GDALGetRasterYSize(hSrcDS);
		int tmpxsize=xsize,tmpysize=ysize;
		if(xsize>800)
		{
			tmpxsize=800;
			scalex=xsize/tmpxsize;
		}
		if(ysize>600)
		{
			tmpysize=600;
			scaley=ysize/tmpysize;
		}
		float *dataIn1=new float[tmpxsize*tmpysize];
		float *dataIn2=new float[tmpxsize*tmpysize];
		float *dataIn3=new float[tmpxsize*tmpysize];

		GDALRasterIO(GDALGetRasterBand(hSrcDS,1),GF_Read,0,0,xsize,ysize,dataIn1,tmpxsize,tmpysize,GDT_Float32,0,0);
		GDALRasterIO(GDALGetRasterBand(hSrcDS,2),GF_Read,0,0,xsize,ysize,dataIn2,tmpxsize,tmpysize,GDT_Float32,0,0);
		GDALRasterIO(GDALGetRasterBand(hSrcDS,3),GF_Read,0,0,xsize,ysize,dataIn3,tmpxsize,tmpysize,GDT_Float32,0,0);
		
		for(int i=0;i<tmpxsize;i++)
		{
			for (int j=0;j<tmpysize;j++)
			{
				PNT3D tmpPnt;
				tmpPnt.DX=dataIn1[j*tmpxsize+i]/255;
				tmpPnt.DY=dataIn2[j*tmpxsize+i]/255;
				tmpPnt.DZ=dataIn3[j*tmpxsize+i]/255;
				m_vec_colors.push_back(tmpPnt);
			}
		}
		delete[]dataIn1;
		delete[]dataIn2;
		delete[]dataIn3;
		GDALClose(hSrcDS);
	}
}
