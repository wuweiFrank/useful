// ttt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "readdbf.h"

bool CDBF::AllTrim(char *pszContent)
{
	char *pDest;
	pDest=strchr(pszContent,' ');
	while (pDest && pDest==pszContent)
	{
		strcpy(pszContent,pDest+1);
		pDest=strchr(pszContent,' ');
	}
	pDest=strrchr(pszContent,' ');
	while (pDest)
	{
		*pDest=0;
		pDest=strrchr(pszContent,' ');
	}
	return true;
}
bool CDBF::SetCondition(char *pszFieldName,char *pszContent,char *pszCondPattern,unsigned int uiSerial)
{
	sprintf(m_pszCondition[uiSerial][0],"%s",pszFieldName);//第一组条件，字段名
	sprintf(m_pszCondition[uiSerial][1],"%s",pszContent);//第一组条件，匹配的字段内容
	sprintf(m_pszCondition[uiSerial][2],"%s",pszCondPattern);//暂时不用
	return true;
}
bool CDBF::DestroyCondition()
{
	if (m_uiCond==0)
		return false;
	
	unsigned int i,j;
	for (i=0;i<m_uiCond;i++)
	{
		for (j=0;j<3;j++)
		{
			delete []m_pszCondition[i][j];
		}
		delete []m_pszCondition[i];
	}
	delete []m_pszCondition;
	m_uiCond=0;
	return true;
}
bool CDBF::CreateConditon(unsigned int uiCond)
{

	if (m_uiCond!=0)
		return false;
	m_uiCond=uiCond;//uiCond条件数目
	unsigned int i;
	m_pszCondition=new char**[uiCond];
	for (i=0;i<uiCond;i++)
	{
		m_pszCondition[i]=new char*[3];
		m_pszCondition[i][0]=new char[MAX_CHAR_LENGTH+1];
		memset(m_pszCondition[i][0],0,MAX_CHAR_LENGTH+1);
		m_pszCondition[i][1]=new char[MAX_CHAR_LENGTH+1];
		memset(m_pszCondition[i][1],0,MAX_CHAR_LENGTH+1);
		m_pszCondition[i][2]=new char[MAX_CHAR_LENGTH+1];
		memset(m_pszCondition[i][2],0,MAX_CHAR_LENGTH+1);
	}
	return true;
}
unsigned long CDBF::Count()
{
	unsigned int i,j;
	unsigned long ulPrevious=m_ulCurRecLine;
	unsigned long ulCount=0;
	char cResult[MAX_CHAR_LENGTH+1];
	memset(cResult,0,MAX_CHAR_LENGTH+1);
	for (i=0;i<m_ulRecCount;i++)
	{
		m_ulCurRecLine=i;
		for (j=0;j<m_uiCond;j++)
		{
			ReadField(m_pszCondition[j][0],cResult,MAX_CHAR_LENGTH);
			AllTrim(cResult);
			if (strnicmp(cResult,m_pszCondition[j][1],0)==0)
			{
				ulCount++;
			}
		}
	}
	m_ulCurRecLine=ulPrevious;
	return ulCount;
}
bool CDBF::Locate(bool bLoca)
{	
	unsigned int uiHave,i,j;
	unsigned long ulPrevious=m_ulCurRecLine;
	char cResult[MAX_CHAR_LENGTH+1];
	memset(cResult,0,MAX_CHAR_LENGTH+1);
	for (i=0;i<m_ulRecCount;i++)
	{
		uiHave=0;
		m_ulCurRecLine=i;
		for (j=0;j<m_uiCond;j++)
		{
			ReadField(m_pszCondition[j][0],cResult,MAX_CHAR_LENGTH);
			AllTrim(cResult);
			if (strnicmp(cResult,m_pszCondition[j][1],MAX_CHAR_LENGTH)==0)
			{
				uiHave++;
			}
		}
		if (uiHave==m_uiCond)
		{
			if (bLoca)
				m_ulCurRecLine=i;
			else
				m_ulCurRecLine=ulPrevious;
			return true;
		}
	}
	m_ulCurRecLine=ulPrevious;
	return false;
}
bool CDBF::AppendDbf(char *pszFileName)
{
	CDBF csDbfOther;
	csDbfOther.InitFieldInfo(pszFileName);
	if (csDbfOther.m_uiFieldCount!=m_uiFieldCount && csDbfOther.m_uiRecLength!=m_uiRecLength)
		return false;
	char cTemp[1];
	cTemp[0]=0x1A;
	unsigned long ulOffset;
	ulOffset=m_uiHeadFileLength+m_ulRecCount*m_uiRecLength;
	fseek(m_fpInFile,ulOffset,0);
	unsigned long i;
	char *pszTemp;
	pszTemp=new char[m_uiRecLength+1];

	ulOffset=m_uiHeadFileLength;
	fseek(csDbfOther.m_fpInFile,ulOffset,0);
	for (i=0;i<csDbfOther.m_ulRecCount;i++)
	{
		memset(pszTemp,0,m_uiRecLength+1);
		fread(pszTemp,m_uiRecLength,1,csDbfOther.m_fpInFile);
		fwrite(pszTemp,m_uiRecLength,1,m_fpInFile);
		m_ulRecCount++;
	}
	fwrite(cTemp,sizeof(char),1,m_fpInFile);
	m_ulCurRecLine=m_ulRecCount-1;
	
	fseek(m_fpInFile,4,0);
	fwrite(&m_ulRecCount,sizeof(long),1,m_fpInFile);
	delete []pszTemp;
	return true;
}
bool CDBF::ReplaceField(char *pcFieldName,char *pszContent,unsigned long ulSize)
{
	
	unsigned int i,j;
	bool bHave=false;
	for (i=0;i<m_uiFieldCount;i++)
	{
		if (strnicmp(m_pCDBFInfo[i][0],pcFieldName,MAX_CHAR_LENGTH)==0)
		{
			bHave=true;
			break;
		}
	}
	if (!bHave)
		return false;
	if (strlen(pszContent)>(unsigned char)m_pCDBFInfo[i][3][0])
		return false;
	if ((unsigned char)m_pCDBFInfo[i][3][0]>=ulSize)
		return false;
	char *pszTemp=new char[(unsigned char)m_pCDBFInfo[i][3][0]+1];
	memset(pszTemp,0x20,(unsigned char)m_pCDBFInfo[i][3][0]);
	pszTemp[(unsigned char)m_pCDBFInfo[i][3][0]]=0;
	for (j=0;j<strlen(pszContent);j++)
	{
		pszTemp[j]=pszContent[j];
	}
	unsigned long ulOffset=m_uiHeadFileLength+(unsigned char)m_pCDBFInfo[i][2][0]+((unsigned char)m_pCDBFInfo[i][2][1])*256+m_ulCurRecLine*m_uiRecLength;
	fseek(m_fpInFile,ulOffset,0);
	fwrite(pszTemp,(unsigned char)m_pCDBFInfo[i][3][0],1,m_fpInFile);
	delete []pszTemp;
	return true;
}
bool CDBF::AppendBlank()
{
	unsigned long ulOffset;
	char cTemp[1];
	cTemp[0]=0x1A;

	ulOffset=m_uiHeadFileLength+m_ulRecCount*m_uiRecLength;
	fseek(m_fpInFile,ulOffset,0);
	char *pszTemp=new char[m_uiRecLength+1];
	memset(pszTemp,0x20,m_uiRecLength);
	pszTemp[m_uiRecLength]=0;
	
	fwrite(pszTemp,m_uiRecLength,1,m_fpInFile);
	fwrite(cTemp,sizeof(char),1,m_fpInFile);
	m_ulCurRecLine=m_ulRecCount;
	m_ulRecCount++;
	fseek(m_fpInFile,4,0);
	fwrite(&m_ulRecCount,sizeof(long),1,m_fpInFile);
	delete []pszTemp;
	return true;
	
}
bool CDBF::SetGoLineNo(unsigned long ulGoLineNo)
{
	m_ulCurRecLine=ulGoLineNo;
	return true;
}
bool CDBF::InitFieldInfo(char *pcFilePath)
{
	if ((m_fpInFile=fopen(pcFilePath,"r+b"))==NULL)
	{
		return 0;
	}
	unsigned int i;
	unsigned char cHead[4];
	//文件记录总个数
	//fseek(m_fpInFile,4,0);
	//fread(cHead,4,1,m_fpInFile);
	//m_ulRecCount=cHead[0]+cHead[1]*0x100+(cHead[2]+cHead[3]*0x100)*256*256;
	//第一个字节为文件类型
	//第2-4字节为最近一次更新日期
	//4-7字节为记录数目
	fseek(m_fpInFile,4,0);
	fread(&m_ulRecCount,4,1,m_fpInFile);

	//文件结构描述部分长度
	//fseek(m_fpInFile,8,0);

	fscanf(m_fpInFile,"%c%c",&cHead[0],&cHead[1]);
	m_uiHeadFileLength=cHead[0]+cHead[1]*0x100;

	//文件记录的长度
	//fseek(m_fpInFile,10,0);	
	fscanf(m_fpInFile,"%c%c",&cHead[0],&cHead[1]);
	m_uiRecLength=cHead[0]+cHead[1]*0x100;

	//字段的个数 296 表示 263（后链信息）+ 1（头记录终止符）+ 32（第一个字段子记录），32 是字段子记录的长度
	m_uiFieldCount=(m_uiHeadFileLength-33)/32;
	
	m_delLabel=new char[m_ulRecCount];
	//将文件信息头存入数组
	m_pCDBFInfo=new char**[m_uiFieldCount];
	for (i=0;i<m_uiFieldCount;i++)
	{
		m_pCDBFInfo[i]=new char*[5];
		m_pCDBFInfo[i][0]=new char[11];//字段名
		m_pCDBFInfo[i][1]=new char[1]; //字段类型标志
		m_pCDBFInfo[i][2]=new char[4]; //首记录中该字段对应内容的偏移量
		m_pCDBFInfo[i][3]=new char[1]; //该字段的长度

		fseek(m_fpInFile,32+i*32,0);
		fread(m_pCDBFInfo[i][0],11,1,m_fpInFile);
		fseek(m_fpInFile,32+i*32+11,0);
		fread(m_pCDBFInfo[i][1],1,1,m_fpInFile) ;
		fseek(m_fpInFile,32+i*32+13,0);
		fread(m_pCDBFInfo[i][2],4,1,m_fpInFile) ;//偏移地址+段地址
		fseek(m_fpInFile,32+i*32+16,0);
		fread(m_pCDBFInfo[i][3],1,1,m_fpInFile) ;
	}
	return true;
}
bool CDBF::PhysicalPackCur()
{
	//当前行删除后，如果删除的是最后一条记录，当前行变量减一，否则当前行变量不变
	unsigned long i;
	if (m_ulCurRecLine>m_ulRecCount)
	{
		return false;
	}
	unsigned long ulOffset;
	char cTemp[1];
	cTemp[0]=0x1A;
	if (m_ulCurRecLine+1==m_ulRecCount)
	{
		ulOffset=m_uiHeadFileLength+m_ulCurRecLine*m_uiRecLength;
		fseek(m_fpInFile,ulOffset,0);
		
		fwrite(cTemp,sizeof(char),1,m_fpInFile);
		m_ulCurRecLine--;
		m_ulRecCount--;
		fseek(m_fpInFile,4,0);
		fwrite(&m_ulRecCount,sizeof(long),1,m_fpInFile);
		return true;
	}
	
	char *pszTemp=new char[m_uiRecLength+1];
	for (i=m_ulCurRecLine+1;i<m_ulRecCount;i++)
	{
		ulOffset=m_uiHeadFileLength+i*m_uiRecLength;
		fseek(m_fpInFile,ulOffset,0);
		memset(pszTemp,0,m_uiRecLength+1);
		fread(pszTemp,m_uiRecLength,1,m_fpInFile);

		ulOffset=m_uiHeadFileLength+(i-1)*m_uiRecLength;
		fseek(m_fpInFile,ulOffset,0);
		fwrite(pszTemp,m_uiRecLength,1,m_fpInFile);
	}
	fwrite(cTemp,sizeof(char),1,m_fpInFile);

	delete []pszTemp;
	m_ulRecCount--;
	fseek(m_fpInFile,4,0);
	fwrite(&m_ulRecCount,sizeof(long),1,m_fpInFile);
	return true;
}
bool CDBF::ReadField(char *pcFieldName,char *pcResult,unsigned long ulSize)
{
	unsigned int i;
	bool bHave=false;
	int  indexpos=1;
	for (i=0;i<m_uiFieldCount;i++)
	{
		if (strnicmp(m_pCDBFInfo[i][0],pcFieldName,MAX_CHAR_LENGTH)==0)
		{
			bHave=true;
			break;
		}
		indexpos=indexpos+m_pCDBFInfo[i][3][0];
	}
	if (!bHave)
		return false;
	if ((unsigned char)m_pCDBFInfo[i][3][0]>ulSize)
		return false;

	unsigned long ulOffset=m_uiHeadFileLength+(unsigned char)(m_pCDBFInfo[i][2][0])+((unsigned char)m_pCDBFInfo[i][2][1])*256+m_ulCurRecLine*m_uiRecLength+indexpos;

	fseek(m_fpInFile,ulOffset,0);
	fread(pcResult,(unsigned char)m_pCDBFInfo[i][3][0],1,m_fpInFile);
	m_ulCurRecLine++;
	return true;
}

CDBF::CDBF()
{
	m_uiCond=0;
	m_ulCurRecLine=0;
}
CDBF::~CDBF()
{
	unsigned int i,j;
	fclose(m_fpInFile);
	for (i=0;i<m_uiFieldCount;i++)
	{
		for (j=0;j<4;j++)
		{
			delete []m_pCDBFInfo[i][j];
		}
		delete []m_pCDBFInfo[i];
	}
	delete []m_pCDBFInfo;
}
