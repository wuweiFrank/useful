#include "StdAfx.h"
#include "FieldValue.h"
#include "string.h"
#include "malloc.h"


FieldValue::FieldValue()
      : m_pValue(0)
{
}


FieldValue::~FieldValue()
{
	if( m_pValue ) delete []m_pValue;
}



int FieldValue::GetInt ()
{
	if( m_pValue )
		return *( (int*) m_pValue );
	else
		return 0;
}

void FieldValue::SetInt (int value)
{
	if( m_pValue == 0 )
		m_pValue = (char*) malloc( sizeof( int ) );
	*( (int*) m_pValue ) = value;
}

double FieldValue::GetDouble ()
{
	if( !m_pValue )
		return *( (double*) m_pValue );
	else	
		return 0;
}

void FieldValue::SetDouble (double value)
{
	if( m_pValue == 0 )
		m_pValue = (char*)malloc( sizeof( double ) );
	*( (double*) m_pValue ) = value;
}

const char* FieldValue::GetString ()
{
	return m_pValue;
}

void FieldValue::SetString (const char* value)
{
	if( !m_pValue )
	{
		m_pValue = (char*) malloc( strlen( value ) + 1 );
		strcpy( m_pValue, value );
	}
	else
	{
		delete m_pValue;
		m_pValue = (char*)malloc( strlen( value ) + 1 );
		strcpy( m_pValue, value );
	}
}
