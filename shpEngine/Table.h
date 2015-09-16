
#ifndef Table_h
#define Table_h 

#include "DataSet.h"
#include "Fields.h"
#include "Row.h"

typedef map< int, Row* > MAP_Row;
typedef vector< Row* > VECTOR_Row;
class Table : public DataSet 
{
 public:
      Table (int id, int type, DataSource* pDataSource = 0, const char *strName = 0);
      ~Table();
      const char* GetTableName ();
      Fields& GetFields ();
      int Size ();
      Row* GetRow (int id);
      Row* GetFirst ();
      Row* GetNext ();
      void AddRow (Row* pRow);
  protected:
      MAP_Row m_mapRow;
      MAP_Row::iterator m_curRow;
  private: 
      char* m_strName;
      Fields* m_pFields;
};
#endif
