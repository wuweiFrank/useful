#include "StdAfx.h"
#include "LayerProperty.h"
#include "string.h"

LayerProperty::LayerProperty (int layerID, const char* name )
      : m_nLayerID(-1),
        m_isVisible(true),
        m_dMinVisual(0.0),
        m_dMaxVisual(3.6e11)
{
	m_nLayerID = layerID;
	strcpy( m_szName, name );
}


LayerProperty::~LayerProperty()
{
}



int LayerProperty::GetLayerID ()
{
	return m_nLayerID;
}

const char* LayerProperty::GetLayerName ()
{
	return m_szName;
}

int LayerProperty::GetLayerIndex ()
{
	return m_nLayerIndex;
}

bool LayerProperty::IsVisible ()
{
	return m_isVisible;
}

double LayerProperty::GetMinVisual ()
{
	return m_dMinVisual;
}

double LayerProperty::GetMaxVisual ()
{
	return m_dMaxVisual;
}

void LayerProperty::SetMinVisual (double visual)
{
	m_dMinVisual = visual;
}

void LayerProperty::SetMaxVisual (double visual)
{
	m_dMaxVisual = visual;
}

void LayerProperty::SetRelateDataSet (DataSet* pDataset)
{
	this->m_pDataSet = pDataset ;
}

DataSet& LayerProperty::GetRelateDataSet ( )
{
	//获取与图层相关数据集
	return *m_pDataSet ;
}

void LayerProperty::SetLayerIndex (int layerIndex)
{
	m_nLayerIndex = layerIndex;
}

void LayerProperty::SetVisible (bool visible)
{
	m_isVisible = visible;
}
