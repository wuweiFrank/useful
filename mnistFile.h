#ifndef _MNIST_FILE_OPERATION_
#define _MNIST_FILE_OPERATION_

#define DXPORT			__declspec(dllexport)
#define EXT_CLASS_TYPE  __declspec(dllexport)

/*/////////////////////////////////////////////////////////////////////
	mnist数字识别影像库
	手写数字影像格式图像转换为bmp格式图像
	version：1.0
	copyright：w.ww.Frank
/////////////////////////////////////////////////////////////////////*/
//  [3/14/2015 wuwei just you]

#pragma once


class EXT_CLASS_TYPE mnistFile
{
public:
	//trans the image buffer from high level to low level
	//only deal with 4 BYTEs data
	void swapBuffer(char* buf);

	//trans mnist file to bmp file in dir of bmpDir
	//get the link of label with the image
	//so that in train process the image can be distinguished
	long MnistToBmp(char* mnistPath,char* bmpDir,char* labelPath,char* link,int num=0);

	//test function
	void mnist_func_test();

};

#endif