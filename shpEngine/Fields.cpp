#include "StdAfx.h"
#include "Fields.h"

Fields::Fields()
{

}


Fields::~Fields()
{
	int i;
	Field	*pfield;
	for( i = 0; i < m_vectorField.size(); i++ )
	{
		pfield = m_vectorField[ i ];
		delete pfield;
	}
	m_vectorField.clear();
	m_mapField.clear();
}



void Fields::AddField (const char* szName, const char* szCaption, int nFieldType, int nLength)
{
	Field *pfield = new Field( szName, szCaption, nFieldType, nLength );
	m_vectorField.push_back( pfield );
	m_mapField.insert( MAP_Field::value_type( pfield->GetFieldName(), pfield ) );
}

int Fields::Size ()
{
	return m_vectorField.size();
}

Field& Fields::GetField (int index)
{
	Field *pfield = m_vectorField[ index ];
	return *pfield;
}

Field& Fields::GetField (const char* szFieldName)
{
	Field *pfield = m_mapField[ szFieldName ];
	return *pfield;
}

int Fields::GetIndex (const char* szFieldName)
{
	int		i;
	for( i = 0; i < m_vectorField.size(); i++ )
	{
		if( strcmp( m_vectorField[ i ]->GetFieldName(), szFieldName ) == 0 )	return i;
	}
	return -1;
}

void Fields::SetFieldCount (int nCount)
{
	if( nCount >= m_vectorField.size() )
	{
		m_vectorField.reserve( nCount );
	}
}

void Fields::ClearMember ()
{
	int		i;
	Field	*pfield;
	for( i = 0; i < m_vectorField.size(); i++ )
	{
		pfield = m_vectorField[ i ];
		delete pfield;
	}
	m_vectorField.clear();
	m_mapField.clear();
}

