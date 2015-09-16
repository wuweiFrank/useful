
#ifndef DataSource_h
#define DataSource_h 

#include "DataSet.h"
#include <map>
using namespace std;

typedef map< int, DataSet* > MAP_DataSet;

class DataSource
{

  public:
	  int GetUniqueID();
      DataSource();
      ~DataSource();
      DataSet& CreateDataSet (int id, int type, const char* strName);
      int Size ();
      DataSet& GetDataSet (int id);

      DataSet* GetFirstDataSet ();
      DataSet* GetNextDataSet ();


  private: 
      MAP_DataSet m_mapDataSet;
      MAP_DataSet::iterator m_curIterator;
};

#endif
