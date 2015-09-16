
#ifndef Fields_h
#define Fields_h 1

#include "Field.h"
#include <map>
#include <vector>
#include <string>
using namespace std;
typedef vector< Field * >				VECTOR_Field;
typedef map< string, Field* >			MAP_Field;

class Fields 
{

  public:
      Fields();
      ~Fields();

      void AddField (const char* szName, const char* szCaption, int nFieldType, int nLength = 0);
      int Size ();
      Field& GetField (int index);
      Field& GetField (const char* szFieldName);
      int GetIndex (const char* szFieldName);
      void SetFieldCount (int nCount);

  private:
      void ClearMember ();
  private: 
      MAP_Field m_mapField;
      VECTOR_Field m_vectorField;
};

#endif
