#include "StdAfx.h"
#include "Field.h"
#include "string.h"

Field::Field (const char* szName, const char* szCaption, int nFieldType, int nLength)
 
{
	if ( sizeof (szCaption) > FIELDCAPTIONLEN )
	{
		strncpy(m_szFieldCaption, szCaption, FIELDCAPTIONLEN - 1) ;
		m_szFieldName[FIELDCAPTIONLEN - 1 ] = '\0' ;
	}
	else strcpy ( m_szFieldCaption, szCaption ) ;
	if ( sizeof (szName) > FIELDNAMELEN )
	{
		strncpy(m_szFieldName, szName, FIELDNAMELEN - 1) ;
		m_szFieldName[FIELDNAMELEN - 1 ] = '\0' ;
	}
	else strcpy ( m_szFieldName, szName ) ;

	m_nFieldType		=	(FIELDTYPE)nFieldType;
	m_nFieldLength		=	nLength;
}


Field::~Field()
{
  
}


const char* Field::GetFieldName ()
{
	return m_szFieldName;
}

const char* Field::GetFieldCaption ()
{
	return m_szFieldCaption;
}

void Field::SetFieldCaption (const char* szCaption)
{
	if ( strlen (szCaption) > FIELDCAPTIONLEN )
	{
		strncpy(m_szFieldCaption, szCaption, FIELDCAPTIONLEN - 1) ;
		m_szFieldName[FIELDCAPTIONLEN - 1 ] = '\0' ;
	}
	else strcpy ( m_szFieldCaption, szCaption ) ;
}

FIELDTYPE Field::GetFieldType ()
{
	return m_nFieldType;
}

int Field::GetFieldLength ()
{
	return m_nFieldLength;
}

FieldValue& Field::GetFieldValue ()
{
	return m_oFieldValue;
}

