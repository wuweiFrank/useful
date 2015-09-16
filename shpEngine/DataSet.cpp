#include "StdAfx.h"
#include "DataSet.h"
#include "string.h"

DataSet::DataSet (int id, int type, const char* strName, DataSource* pDataSource)
      : m_pOwnerDataSource(0)
{
	m_szName = 0;
	m_nID = id;
	m_nType = (DATASETTYPE)type;
	m_pOwnerDataSource = pDataSource;
	int len = strlen( strName );
	if( len != 0 )
	{
		m_szName = new char[ len + 1 ];
		strcpy( m_szName, strName );
	}
}

DataSet::~DataSet()
{
	if( m_szName != 0 )	delete []m_szName;
}

int DataSet::GetID ()
{
	return m_nID;
}

DATASETTYPE DataSet::GetType ()
{
	return m_nType;
}

const char * DataSet::GetName ()
{
	return m_szName;
}

DataSource* DataSet::GetOwnerDataSource ()
{
	return m_pOwnerDataSource;
}
