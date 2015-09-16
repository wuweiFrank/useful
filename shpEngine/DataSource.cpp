#include "StdAfx.h"
#include "DataSource.h"
#include "FeatureClass.h"

DataSource::DataSource()
{
}


DataSource::~DataSource()
{
	MAP_DataSet::iterator map_i;
	DataSet *pdataset;
	for( map_i = m_mapDataSet.begin(); map_i != m_mapDataSet.end(); map_i++)
	{
		pdataset = ( DataSet* )(*map_i).second;
		delete (FeatureClass*)pdataset;
		(*map_i).second = 0 ;
	}
	m_mapDataSet.clear();
}

DataSet& DataSource::CreateDataSet (int id, int type, const char* strName)
{
	DataSet *pdataset = new FeatureClass( id, type, strName, this );
	m_mapDataSet.insert( MAP_DataSet::value_type( id, pdataset ) );
	return *pdataset;
}

int DataSource::Size ()
{
	return m_mapDataSet.size();
}

DataSet& DataSource::GetDataSet (int id)
{
	DataSet *pdatasets;
	MAP_DataSet::iterator map_i = m_mapDataSet.find( id );
	if( map_i != m_mapDataSet.end() )
	{
		pdatasets = (DataSet*)(*map_i).second;
		return *pdatasets;
	}
}

DataSet* DataSource::GetFirstDataSet ()
{
	m_curIterator = m_mapDataSet.begin();
	if( m_curIterator != m_mapDataSet.end() )
	{
		return (DataSet*)(*m_curIterator).second;
	}
	else
	{
		return 0;
	}
}

DataSet* DataSource::GetNextDataSet ()
{
	if( m_curIterator != m_mapDataSet.end() )
	{
		m_curIterator++;
		if( m_curIterator != m_mapDataSet.end() )
		{
			return (DataSet*)(*m_curIterator).second;
		}
	}
	return 0;
}

int DataSource::GetUniqueID()
{
	return m_mapDataSet.size() + 1 ;
}
