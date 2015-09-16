

#ifndef DataSet_h
#define DataSet_h 

class DataSource;
enum DATASETTYPE
{
	POINTDATASET = 0,
	LINEDATASET = 1,
	POLYGONDATASET = 2,
	ANNOTATIONDATASET = 3
};

class DataSet 
{
public:
	DataSet (int id, int type, const char* strName, DataSource* pDataSource);
	~DataSet();
	int GetID ();
	DATASETTYPE GetType ();
	const char * GetName ();
	DataSource* GetOwnerDataSource ();

private: 
	int m_nID;
	DATASETTYPE m_nType;
	DataSource* m_pOwnerDataSource;
	char *m_szName;

};

#endif
