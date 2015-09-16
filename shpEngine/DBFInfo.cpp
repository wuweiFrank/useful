#include "StdAfx.h"
#include "DBFInfo.h"


//重载赋值操作符
void DBFField::operator =(DBFField &filed)
{
	memmove(m_FieldData,filed.m_FieldData,sizeof(char)*32);
	m_FieldIndex=filed.m_FieldIndex;
}


void DBFFields::operator=(DBFFields &fields)
{
	memmove(m_FieldName,fields.m_FieldName,sizeof(char)*256);
	m_FieldType=fields.m_FieldType;
	m_RecordCounts=fields.m_RecordCounts;
	m_Records=fields.m_Records;
}


//获取一列数据
long DBFColFieldData(CDBF &dbfFile,DBFFields &dbfField,int pos)
{
	if(int(dbfFile.m_uiFieldCount)<pos||pos<1||int(dbfFile.m_uiFieldCount)==0)
		return -1;
	char colName[11];
	memcpy(colName,dbfFile.m_pCDBFInfo[pos-1][0],sizeof(char)*11);
	memcpy(dbfField.m_FieldName,colName,sizeof(char)*11);
	dbfField.m_FieldType=dbfFile.m_pCDBFInfo[pos-1][1][0];
	dbfField.m_RecordCounts=dbfFile.m_ulRecCount;
	for (int i=0;i<dbfFile.m_ulRecCount;i++)
	{
		DBFField tempField;
		dbfFile.ReadField(colName,tempField.m_FieldData,128);
		tempField.m_FieldIndex=i;
		dbfField.m_Records.push_back(tempField);
	}
	dbfFile.m_ulCurRecLine=0;
	return 0;
}


//获取所有数据
long DBFFieldData(CDBF &dbfFile,DBFTable &dbfTable)
{
	if(int(dbfFile.m_uiFieldCount)==0||int(dbfFile.m_ulRecCount)==0)
		return -1;
	for (int i=0;i<int(dbfFile.m_uiFieldCount);i++)
	{
		DBFFields tempfields;
		DBFColFieldData(dbfFile,tempfields,i+1);
		dbfTable.push_back(tempfields);
	}
	return 0;
}