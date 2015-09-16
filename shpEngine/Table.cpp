#include "StdAfx.h"

#include "Table.h"


Table::Table (int id, int type, DataSource* pDataSource, const char *strName)
      : m_pFields(0)
  ,DataSet( id, type, strName, pDataSource ) 
{
	m_strName = new char[ strlen( strName ) + 1 ];
	strcpy( m_strName, strName );
	m_curRow=m_mapRow.begin();
}


Table::~Table()
{
	delete []m_strName;
	m_strName = 0 ;

	if( m_pFields != 0 ) 
	{
		delete m_pFields;
		m_pFields = 0 ;
	}

	Row * pRow;
	for( m_curRow = m_mapRow.begin(); m_curRow != m_mapRow.end(); m_curRow++ )
	{
		pRow = ( Row * )(*m_curRow).second;
		delete pRow;
		(*m_curRow).second = 0;
	}
	m_mapRow.clear();
}



const char* Table::GetTableName ()
{
	return m_strName;
}

Fields& Table::GetFields ()
{
	if( m_pFields == 0 )
	{
		m_pFields = new Fields();
	}
	return *m_pFields;
}

int Table::Size ()
{
	return m_mapRow.size();
}

Row* Table::GetRow (int id)
{
	return m_mapRow[ id ];
}

Row* Table::GetFirst ()
{
	m_curRow = m_mapRow.begin();

	if( m_curRow == m_mapRow.end() ) return 0;
	else
		return (Row*)(*m_curRow).second;
}

Row* Table::GetNext ()
{
	m_curRow++;
	if( m_curRow == m_mapRow.end() ) 
	{
		m_curRow--;
		return 0;
	}
	else	return (Row*)(*m_curRow).second;
}

void Table::AddRow (Row* pRow)
{
	m_mapRow.insert( MAP_Row::value_type( pRow->GetID(), pRow ) );
}

