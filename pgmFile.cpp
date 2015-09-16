#include "stdafx.h"
#include "pgmFile.h"
#include <io.h>
#include <iostream>	
using namespace std;

#include "gdal//gdal_priv.h"              //using gdal lib to realize the transform to bmp file
#pragma comment(lib,"gdal_i.lib")

/*open pgm and get the head file*/
/*
	get file information of the pgm file
	the version of the pgm data, the width
	and height of the pgm image, the datatype 
	of the pgm image.
*/
PGMHeadInfo pgmFile::openFile(const char* path)
{
	PGMHeadInfo _pgmHeadInfo;
	memset(&_pgmHeadInfo,0,sizeof(PGMHeadInfo));
	m_readPGM.open(path,ios_base::in|ios_base::binary);
	if(!m_readPGM.is_open())
	{
		cerr<<"error file is not opened";
		return _pgmHeadInfo;
	}
	else
	{
		char temp[10];
		m_readPGM.getline(temp,10);
		_pgmHeadInfo.pgm_version[0]=temp[0];
		_pgmHeadInfo.pgm_version[1]=temp[1];
		if(!(strcmp(_pgmHeadInfo.pgm_version,"P5")||strcmp(_pgmHeadInfo.pgm_version,"P2")))
			cerr<<"error file is not the format of PGM";
		m_readPGM>>_pgmHeadInfo.pgm_width>>_pgmHeadInfo.pgm_height>>_pgmHeadInfo.pgm_max;
// 		m_readPGM.getline(temp,10);
//      sscanf_s(temp,"%d%d",&_pgmHeadInfo.pgm_width,&_pgmHeadInfo.pgm_height);
// 		m_readPGM.getline(temp,10);
		
		int type=_pgmHeadInfo.pgm_max;
		if(type<=255)
			_pgmHeadInfo.pgm_dataType=_256Level;
		else
			_pgmHeadInfo.pgm_dataType=_65536Level;

		return _pgmHeadInfo;
	}
}

/*close the opened pgm file*/
void pgmFile::closeFile()
{
	if(m_readPGM.is_open())
		m_readPGM.close();
	if(m_writePGM.is_open())
		m_writePGM.close();
}

/*get pgm data width and height*/
/*
	to get the private of the HeadInfo one
	should use these functions to get the info
*/
int pgmFile::getPGMWidth (PGMHeadInfo _pgmHeadInfo)
{
	int width=_pgmHeadInfo.pgm_width;
	return width;
}
int pgmFile::getPGMHeight(PGMHeadInfo _pgmHeadInfo)
{
	int height=_pgmHeadInfo.pgm_height;
	return height;
}
int pgmFile::getPGMMax(PGMHeadInfo _pgmHeadInfo)
{
	int maxnumber=_pgmHeadInfo.pgm_max;
	return maxnumber;
}
/*get the data type of the pgm file*/
PGMDATATYPE pgmFile::getPGMDataType(PGMHeadInfo _pgmHeadInfo)
{
	PGMDATATYPE _pgmDataType;
	_pgmDataType=_pgmHeadInfo.pgm_dataType;
	return _pgmDataType;
}

/*get image data from the file*/
/*
	if get the data successfully return 0
	else return other error value
*/
long pgmFile::readPGMData(PGMHeadInfo _pgmHeadInfo,void* pBuffer,PGMDATATYPE dataType)
{
	//check the validation import data
	if(_pgmHeadInfo.pgm_version==0x00000000||pBuffer==NULL)
	{
		cerr<<"error imput data please check the imput"<<endl;
		return -1;
	}
	if(_pgmHeadInfo.pgm_dataType!=dataType)
	{
		cerr<<"data type do not match please check the imput data type"<<endl;
		return -2;
	}
	//get image data
	int width =_pgmHeadInfo.pgm_width;
	int height=_pgmHeadInfo.pgm_height;
	
	//calculate the byte number according to the data type, width and height
	int byteCount=0;
	if(_pgmHeadInfo.pgm_dataType==_256Level)
		byteCount=width*height;
	else
		byteCount=width*height*2;
	
	m_readPGM.read(((char*)pBuffer),byteCount);
	m_readPGM.seekg(-byteCount,ios::cur);
	return 0;
}


/*save the image to file as the format of bmp*/
/*
 * first get the info and data of the pgm file
 * then  use gdal lib to save the data as the format
 * of bmp
*/
long pgmFile::tranPGMToBMP(PGMHeadInfo _pgmHeadInfo,void* data,const char* pathOut)
{
    //check the imput data
    if(pathOut==NULL)
    {
        cerr<<" error imput path name please check the imput"<<endl;
        return -1;
    }
    //get image data
    pgmFile   optPgmFile;
    int width =optPgmFile.getPGMWidth(_pgmHeadInfo);
    int height=optPgmFile.getPGMHeight(_pgmHeadInfo);
    PGMDATATYPE datatype=optPgmFile.getPGMDataType(_pgmHeadInfo);

    GDALAllRegister();
    GDALDatasetH dataset;
    if(datatype==_256Level)
    {
        dataset=GDALCreate(GDALGetDriverByName("BMP"),pathOut,width,height,1,GDT_Byte,0);
        GDALRasterIO(GDALGetRasterBand(dataset,1),GF_Write,0,0,width,height,data,width,height,GDT_Byte,0,0);
        GDALClose(dataset);
    }
    if(datatype==_65536Level)
    {
        dataset=GDALCreate(GDALGetDriverByName("BMP"),pathOut,width,height,1,GDT_Int16,0);
        GDALRasterIO(GDALGetRasterBand(dataset,1),GF_Write,0,0,width,height,data,width,height,GDT_Int16,0,0);
        GDALClose(dataset);
    }
    return 0;
}

/*trans pgm in path pathPgm to bmp in path pathBmp*/
long pgmFile::tranPGMToBMP(char* pathPgm,char* pathBmp)
{
	PGMHeadInfo pgm_headinfo=openFile(pathPgm);

	int xsize=getPGMWidth(pgm_headinfo);
	int ysize=getPGMHeight(pgm_headinfo);
	int maxnum=getPGMMax(pgm_headinfo);

	//获取PGM数据
	PGMDATATYPE pgm_datatype;
	pgm_datatype=getPGMDataType(pgm_headinfo);

	//PGM数据转换为bmp数据
	if(pgm_datatype==_256Level)
	{
		char *data=new char[xsize*ysize];
		readPGMData(pgm_headinfo,data,pgm_datatype);
		tranPGMToBMP(pgm_headinfo,data,pathBmp);
		delete []data;data=NULL;
	}
	if (pgm_datatype==_65536Level)
	{
		short *data=new short[xsize*ysize];
		readPGMData(pgm_headinfo,data,pgm_datatype);
		tranPGMToBMP(pgm_headinfo,data,pathBmp);
		delete []data;data=NULL;
	}
	closeFile();
	return 0;
}

/*save all image to file as bmp type*/
/*
 * translate all pgm file in dir to bmp
 */
long pgmFile::transDirPGMToBMP(char* pgmImageDir,char* bmpImageDir)
{
	char dirPath[280];
	char pgmPath[280];
	char bmpPath[280];
	sprintf(dirPath,"%s\\*.pgm",pgmImageDir);

	_finddata_t file;
	long lError;
	int total=1;
	if((lError=_findfirst(dirPath,&file))==-1)
	{
		printf("cannot find the file..\n");
		return lError;
	}
	else
	{
		//handle the first file 
		printf("\rtrans %d image...",total);
		sprintf(bmpPath,"%s\\%s%s",bmpImageDir,file.name,".bmp");
		sprintf(pgmPath,"%s\\%s",pgmImageDir,file.name);
		tranPGMToBMP(pgmPath,bmpPath);

		while(_findnext(lError,&file)==0)
		{
			total++;
			sprintf(bmpPath,"%s\\%s%s",bmpImageDir,file.name,".bmp");
			sprintf(pgmPath,"%s\\%s",pgmImageDir,file.name);
			printf("\rtrans %d image...",total);
			tranPGMToBMP(pgmPath,bmpPath);
		}
		printf("finished..\n");
		return lError;
	}
}

//test funtion 
void pgmFile::test_pgm_trans()
{

	char* pathPGM="pgm\\air-force.1.pgm";
	char* pathBMP="pgm\\air-force.1.bmp";

	printf("打开PGM文件：%s\n",pathPGM);
	PGMHeadInfo pgm_headinfo=openFile(pathPGM);

	int xsize=getPGMWidth(pgm_headinfo);
	int ysize=getPGMHeight(pgm_headinfo);
	int maxnum=getPGMMax(pgm_headinfo);
	printf("PGM影像数据大小为：%d/%d\n",xsize,ysize);
	printf("PGM影像最大值为：%d\n",maxnum);

	//获取PGM数据
	printf("获取PGM数据\n");
	PGMDATATYPE pgm_datatype;
	pgm_datatype=getPGMDataType(pgm_headinfo);

	//PGM数据转换为bmp数据
	printf("PGM数据转换为BMP\n");
	if(pgm_datatype==_256Level)
	{
		char *data=new char[xsize*ysize];
		readPGMData(pgm_headinfo,data,pgm_datatype);
		tranPGMToBMP(pgm_headinfo,data,pathBMP);
		delete []data;data=NULL;
	}
	if (pgm_datatype==_65536Level)
	{
		short *data=new short[xsize*ysize];
		readPGMData(pgm_headinfo,data,pgm_datatype);
		tranPGMToBMP(pgm_headinfo,data,pathBMP);
		delete []data;data=NULL;
	}
	closeFile();

	pathPGM="pgm\\altschul.1.pgm";
	pathBMP="pgm\\altschul.1.bmp";
	tranPGMToBMP(pathPGM,pathBMP);
	printf("转换完成!\n");

	pathPGM="pgm";
	pathBMP="bmp";
	transDirPGMToBMP(pathPGM,pathBMP);

}



















