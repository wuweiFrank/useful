#include "StdAfx.h"
#include "Row.h"
#include "fields.h"
Row::Row (int id, Fields* pFields)
      : m_pFields(0),
        m_pArrayValue(0)
{
	int		num;
	m_nID		= id;
	m_pFields	= pFields;
	
	num = pFields->Size();
	if ( num > 0 )
		m_pArrayValue = new FieldValue[ num ];
}


Row::~Row()
{
	if( m_pArrayValue ) delete []m_pArrayValue;
}


int Row::GetID ()
{
	return m_nID;
}

Fields& Row::GetFields ()
{
	return *m_pFields;
}

FieldValue& Row::GetFieldValue (int index)
{
	return m_pArrayValue[ index ];
}

FieldValue& Row::GetFieldValue (const char* szFieldName)
{
	int index = m_pFields->GetIndex( szFieldName );
	if( index != -1 )	return m_pArrayValue[ index ];
}
