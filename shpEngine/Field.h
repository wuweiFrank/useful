
#ifndef Field_h
#define Field_h 

#include "FieldValue.h"

enum FIELDTYPE
{
	FIELD_INT = 1,
    FIELD_DOUBLE = 2,
    FIELD_STRING = 3
};

//	《说明》：单个字段的描述信息。
//	包括：字段的名称、字段的类型、字段的长度和字段的值
class Field 
{
	enum { FIELDNAMELEN = 40, FIELDCAPTIONLEN = 40 };

  public:
      Field (const char* szName, const char* szCaption, int nFieldType, int nLength);
      ~Field();

      const char* GetFieldName ();

      const char* GetFieldCaption ();

      void SetFieldCaption (const char* szCaption);

      FIELDTYPE GetFieldType ();

      int GetFieldLength ();

      FieldValue& GetFieldValue ();

  private: 
      char m_szFieldName[FIELDNAMELEN];
      char m_szFieldCaption[FIELDCAPTIONLEN];
      FIELDTYPE m_nFieldType;
      int m_nFieldLength;
      FieldValue m_oFieldValue;
};
#endif
