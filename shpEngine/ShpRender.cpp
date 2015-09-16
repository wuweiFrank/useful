#include "stdafx.h"
#include "ShpRender.h"
#include "math.h"
#include "MapLayer.h"
#include "MapProperty.h"
#include "LayerProperty.h"
#include "featureclass.h"
#include "feature.h"
#include "geopolyline.h"
#include "geopolygon.h"

ShpRender::ShpRender (MapLayer* pLayer)
{
	this ->m_pLayer = pLayer ;
}


ShpRender::~ShpRender()
{
	this ->m_pLayer = 0 ;
}


void ShpRender::Render (CDC *pDC, MapProperty* pMapProperty)
{
	if (m_pLayer->IsVisible())
	{
		int i, x, y, w, h ;
		double x0, y0, x1, y1;
		double clipL, clipT, clipR, clipB ; // 地理坐标
		double intersectL, intersectT, intersectR, intersectB ; // 相交的矩形
		double xs[4], ys[4];

		//CPoint pointarray[ 500 ];
		pMapProperty->GetClipRect(x,y,w,h);	
		xs[0] = x ; ys[0] = y ;
		xs[1] = x ; ys[1] = y+h ;
		xs[2] = x+w ; ys[2] = y ;
		xs[3] = x+w ; ys[3] = y+h ;
		// (地理坐标系)
		for ( i = 0; i < 4; i ++ )
			pMapProperty->ClientToWorld(xs[i],ys[i]);

		clipL = clipR = xs[0];
		clipB = clipT = ys[0];
		for ( i = 1; i < 4; i ++ )
		{
			if ( clipL > xs[i] ) clipL = xs[i];
			if ( clipR < xs[i] ) clipR = xs[i];
			if ( clipB > ys[i] ) clipB = ys[i];
			if ( clipT < ys[i] ) clipT = ys[i];
		}

		Feature			*pfeature;
		int	pointscount, pointcount, index ;
		LayerProperty &layerproperty = m_pLayer ->GetProperty();
		FeatureClass &featureClass = (FeatureClass&)layerproperty.GetRelateDataSet();
		if ( featureClass.GetType() == POINTDATASET )
		{
			for( pfeature = featureClass.GetFirstFeature(); pfeature != NULL; pfeature = featureClass.GetNextFeature() )
			{
				pfeature ->GetBound(x0, y0, x1, y1);

				// 增加判断以提高显示速度
				intersectL = max(clipL,x0);
				intersectR = min(clipR,x0+x1);
				intersectB = max(clipB,y0);
				intersectT = min(clipT,y0+y1);
				if ( intersectL - intersectR >= 1e-8 || intersectB - intersectT >= 1e-8 )
					continue ;

				GeoPoint &point = (GeoPoint&)pfeature ->GetGeometry();
				x0 = point.GetX();
				y0 = point.GetY();
				pMapProperty->WorldToClient(x0,y0);
				pDC->Ellipse(x0-2,y0-2,x0+2,y0+2);
			}
		}
		else if ( featureClass.GetType() == LINEDATASET )
		{
			CPen newPen, *pPrePen;
			newPen.CreatePen(0,1,RGB(0,0,200) );
			pPrePen = pDC->SelectObject( &newPen );
			for( pfeature = featureClass.GetFirstFeature(); pfeature != NULL; pfeature = featureClass.GetNextFeature() )
			{
				pfeature ->GetBound(x0, y0, x1, y1);

				// 增加判断以提高显示速度
				intersectL = max(clipL,x0);
				intersectR = min(clipR,x0+x1);
				intersectB = max(clipB,y0);
				intersectT = min(clipT,y0+y1);
				if ( intersectL > intersectR || intersectB > intersectT )
					continue ;

				GeoPolyline &polyline = (GeoPolyline&)pfeature ->GetGeometry();
				pointscount = polyline.GetPointsCount();
				for ( index = 0; index < pointscount; index ++ )
				{
					GeoPoints &points = polyline.GetPoints(index);
					pointcount = points.GetPtCount();
					for ( i = 0; i < pointcount - 1; i ++ )
					{
						points.GetPoint(i,x0,y0);
						points.GetPoint(i+1,x1,y1);
						pMapProperty->WorldToClient(x0,y0);
						pMapProperty->WorldToClient(x1,y1);
						pDC->MoveTo( x0, y0 );
						pDC->LineTo( x1, y1 );
					}
				}
			}
			pDC->SelectObject(pPrePen);
			newPen.DeleteObject();
			pPrePen = 0 ;
		}
		else if ( featureClass.GetType() == POLYGONDATASET )
		{
			CPen newPen, *pPrePen;
			newPen.CreatePen(0,1,RGB(0,200,0) );
			pPrePen = pDC->SelectObject( &newPen );
			for( pfeature = featureClass.GetFirstFeature(); pfeature != NULL; pfeature = featureClass.GetNextFeature() )
			{
				pfeature ->GetBound(x0, y0, x1, y1);

				// 增加判断以提高显示速度
				intersectL = max(clipL,x0);
				intersectR = min(clipR,x0+x1);
				intersectB = max(clipB,y0);
				intersectT = min(clipT,y0+y1);
				if ( intersectL > intersectR || intersectB > intersectT )
					continue ;

				GeoPolygon &polygon = (GeoPolygon&)pfeature ->GetGeometry();
				pointscount = polygon.GetPointsCount();
				for ( index = 0; index < pointscount; index ++ )
				{
					GeoPoints &points = polygon.GetPoints(index);
					pointcount = points.GetPtCount();
					for ( i = 0; i < pointcount-1; i ++ )
					{
						points.GetPoint(i,x0,y0);
						points.GetPoint(i+1,x1,y1);
						pMapProperty->WorldToClient(x0,y0);
						pMapProperty->WorldToClient(x1,y1);
						pDC->MoveTo( x0, y0 );
						pDC->LineTo( x1, y1 );
					}
				}
			}
			pDC->SelectObject(pPrePen);
			newPen.DeleteObject();
			pPrePen = 0 ;
		}
	}
}