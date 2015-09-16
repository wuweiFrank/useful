#ifndef _PGM_FILE_OPERATION_
#define _PGM_FILE_OPERATION_

/*/////////////////////////////////////////////////////////////////////
	谷歌人脸识别影像读取
	并将人脸图像转换为bmp格式图像
	图像格式为pgm格式
	修改了不能将影像完全读入并转换的错误，添加了测试函数进行测试
	version：1.0
	copyright：w.ww.Frank
	添加了批处理函数，修改了影像打开后没有进行关闭的错误
	version：1.1
	copyright：w.ww.Frank
/////////////////////////////////////////////////////////////////////*/
//  [3/14/2015 wuwei just you]

#include<fstream>
using namespace std;


#define DXPORT			__declspec(dllexport)
#define EXT_CLASS_TYPE  __declspec(dllexport)

enum DXPORT PGMDATATYPE			//define the pgm data type
{
	_256Level,				//the max gray level is lower than 256
	_65536Level				//the max gray level is lager than 256
};

class pgmFile;				//declare the class pgmFile

typedef class EXT_CLASS_TYPE PGMHead   	//define the pgm file header
{
private:
	char		 pgm_version[2];     //file version
	int			 pgm_width;			 //image file width
	int			 pgm_height;		 //image file height
	int          pgm_max;			 //max number of pgm data
	PGMDATATYPE  pgm_dataType;		 //image data type
public:
	friend class pgmFile;
}PGMHeadInfo;

class EXT_CLASS_TYPE pgmFile			//define the operation of the pgm file
{
public:
    pgmFile(){}
    ~pgmFile(){
        if(m_readPGM.is_open())
            m_readPGM.close();
        if(m_writePGM.is_open())
            m_writePGM.close();
    }

	/*open pgm and get the head file*/
	PGMHeadInfo openFile(const char* path);
	/*close pgm file*/
	void        closeFile();

	/*get pgm data width and height*/
	int getPGMWidth (PGMHeadInfo _pgmHeadInfo);
	int getPGMHeight(PGMHeadInfo _pgmHeadInfo);
	int getPGMMax(PGMHeadInfo _pgmHeadInfo);

	/*get the data type of the pgm file*/
	PGMDATATYPE getPGMDataType(PGMHeadInfo _pgmHeadInfo);

	/*get image data from the file*/
	long readPGMData(PGMHeadInfo _pgmHeadInfo,void* pBuffer,PGMDATATYPE dataType);

	/*save the image to file as the format of bmp*/
	long tranPGMToBMP(PGMHeadInfo _pgmHeadInfo,void* data,const char* pathOut);
	/*trans pgm to bmp*/
	long tranPGMToBMP(char* pathPgm,char* pathBmp);
	/*save all image to file as format of bmp*/
	long transDirPGMToBMP(char* pgmImageDir,char* bmpImageDir);

	/*test pgm data trans*/
	void test_pgm_trans();

private:
	ifstream m_readPGM;				//read file stream to get data from the file
	ofstream m_writePGM;			//write image to file as the format of bmp
};

#endif
