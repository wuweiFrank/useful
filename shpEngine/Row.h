
#ifndef Row_h
#define Row_h 1

#include "FieldValue.h"
class Fields;

class Row 
{

  public:
      Row (int id, Fields* pFields);

      ~Row();

      int GetID ();

      Fields& GetFields ();

      FieldValue& GetFieldValue (int index);

      FieldValue& GetFieldValue (const char* szFieldName);

  protected:
      int m_nID;
  private:
      Fields* m_pFields;
      FieldValue* m_pArrayValue;
};

#endif
