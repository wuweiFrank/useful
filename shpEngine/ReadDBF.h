#include "../stdafx.h"
#include <string.h>


#ifndef _READDBF_
#define _READDBF_

#define MAX_CHAR_LENGTH 256			//字符型字段的最大长度

class CDBF
{
public:
	FILE *m_fpInFile;				//输入文件
	unsigned int m_uiRecLength;		//文件记录的长度
	unsigned int m_uiHeadFileLength;//文件结构描述部分长度
	unsigned long m_ulRecCount;		//文件记录总个数
	unsigned int m_uiFieldCount;	//字段的个数 296 表示 263（后链信息）+ 1（头记录终止符）+ 32（第一个字段子记录），32 是字段子记录的长度
	char ***m_pCDBFInfo;			//文件信息头
	unsigned long m_ulValidRecCount;//文件有效记录总个数，不包括被打上删除标记的记录
	unsigned long m_ulCurRecLine;	//当前记录行，行号从零开始算起
	char ***m_pszCondition;			//条件数组
	unsigned int m_uiCond;			//条件个数
	char *m_delLabel;				//删除标志

public:
	CDBF();
	virtual ~CDBF();

	bool ReadField(char *pcFieldName,char *pcResult,unsigned long ulSize); 	//读出DBF中指定行、指定列的char型数据
	bool InitFieldInfo(char *pcFilePath);									//读出DBF中的字段信息
	bool SetGoLineNo(unsigned long ulGoLineNo);								//跳到所需要处理的数据行
	bool LogicDeleteCur();													//逻辑删除当前行
	bool PhysicalPackCur();													//物理删除当前行
	bool PhysicalPack();													//物理删除所有被打上删除标记的行
	bool ReplaceField(char *pcFieldName,char *pszContent,unsigned long ulSize);//写入dbf中指定行、指定列的char型数据
	bool AppendBlank();														//追加一空行
	bool AppendDbf(char *pszFileName);										//将另外一个dbf文件追加到本dbf文件中,两个表结构必须一致												
	
	//bLoca表示找到数据后，是否将当前m_ulCurRecLine变量指向这里，m_pszCondition使检索条件，例如：
	//有三个字段要查找，姓名=aa && 年龄>11 && 籍贯<bb
	//m_pszCondition[0][0]=姓名，m_pszCondition[0][1]=年龄，m_pszCondition[0][2]=籍贯
	//m_pszCondition[1][0]=aa，m_pszCondition[1][1]=11，m_pszCondition[1][2]=bb
	//m_pszCondition[2][0]==，m_pszCondition[2][1]=>，m_pszCondition[2][2]=<，暂时条件只实现完全相等
	bool Locate(bool bLoca);
	unsigned long Count();													//计算符合条件的记录个数
	bool CreateConditon(unsigned int uiCond);								//创建条件
	bool DestroyCondition();												//摧毁条件
	bool SetCondition(char *pszFieldName,char *pszContent,char *pszCondPattern,unsigned int uiSerial);//设置条件
	bool AllTrim(char *pszContent);
};

#endif