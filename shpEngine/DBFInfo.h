#pragma once
#include "ReadDBF.h"
#include <vector>



//单个Field数据空间
class DBFField
{
public:
	char  m_FieldData[128];		//数据
	long  m_FieldIndex;			//记录标示
	char  m_IsDel;				//删除标志
public:
	DBFField()
	{
		memset(m_FieldData,0,sizeof(char)*128);
		m_IsDel=0;
	}
	void operator =(DBFField &filed);
};

typedef std::vector< DBFField >    DBFRecord;

//属性数据
class DBFFields
{
public:
	char			 m_FieldType;	  //数据类型
	char             m_FieldName[11]; //字段名称
	long			 m_RecordCounts;  //记录条数
	DBFRecord        m_Records;	      //每条记录	

public:
	DBFFields()
	{
		memset(m_FieldName,0,sizeof(char)*11);
	}
	void operator =(DBFFields &fields);
};

typedef std::vector < DBFFields >   DBFTable;

//获取一列数据
long DBFColFieldData(CDBF &dbfFile,DBFFields &dbfField,int pos);

//获取一行数据
long DBFFieldData(CDBF &dbfFile,DBFTable &dbfTable);

