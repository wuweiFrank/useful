
#include "StdAfx.h"
#include "MapLayer.h"
#include "LayerProperty.h"
#include "FeatureClass.h"


MapLayer::MapLayer (LayerProperty* layerProperty)
      : m_pRender(0)
{
	m_pLayerProperty = layerProperty;
}


MapLayer::~MapLayer()
{
	if ( m_pLayerProperty != 0 )
	{
		delete m_pLayerProperty;
		m_pLayerProperty = 0 ;
	}

	if ( m_pRender != 0 )
	{
		delete m_pRender ;
		m_pRender = 0 ;
	}
}



int MapLayer::GetLayerType ()
{
	return 1;
}

const char* MapLayer::GetLayerName ()
{
	return m_pLayerProperty->GetLayerName();
}

bool MapLayer::IsVisible ()
{
	return m_pLayerProperty->IsVisible();
}

LayerProperty& MapLayer::GetProperty ()
{
	return *m_pLayerProperty;
}

IRender& MapLayer::GetRender ()
{
	return *m_pRender;
}

void MapLayer::SetVisible (bool bVisible)
{
	m_pLayerProperty->SetVisible( bVisible );
}

void MapLayer::SetRender (IRender* renderObj)
{
	if ( m_pRender != 0 )
	{
		delete m_pRender ;
		m_pRender = 0 ;
	}
	m_pRender = renderObj;
}

void MapLayer::GetBound (double& x, double& y, double& w, double& h)
{
	double minx, miny, width, height;

	FeatureClass& dataset = (FeatureClass&)m_pLayerProperty->GetRelateDataSet();
	dataset.GetBound( minx, miny, width, height );
	x = minx;
	y = miny;
	w = width;
	h = height;
}

