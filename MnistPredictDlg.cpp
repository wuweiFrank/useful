// MnistPredictDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "useful.h"
#include "MnistPredictDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include <fstream>
using namespace std;

// CMnistPredictDlg 对话框

IMPLEMENT_DYNAMIC(CMnistPredictDlg, CDialog)

CMnistPredictDlg::CMnistPredictDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMnistPredictDlg::IDD, pParent)
{

}

CMnistPredictDlg::~CMnistPredictDlg()
{
}

void CMnistPredictDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Train);
	DDX_Control(pDX, IDC_EDIT2, m_Label);
	DDX_Control(pDX, IDC_EDIT3, m_Test);
	DDX_Control(pDX, IDC_EDIT4, m_Predict);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(CMnistPredictDlg, CDialog)
	ON_BN_CLICKED(IDOK3, &CMnistPredictDlg::OnBPNetTrain)
	ON_BN_CLICKED(IDOK, &CMnistPredictDlg::OnBPNetPredict)
END_MESSAGE_MAP()


// CMnistPredictDlg 消息处理程序
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BPNetMnist::BP_Mnist_Swap(char* buf)
{
	char temp;
	temp=*(buf);
	*buf=*(buf+3);
	*(buf+3)=temp;
	temp=*(buf+1);
	*(buf+1)=*(buf+2);
	*(buf+2)=temp;
}
MNISTIMG BPNetMnist::BPNetMnist_Allocate(int rows,int cols)
{
	MNISTIMG img;
	img.mnist_col=cols;
	img.mnist_row=rows;
	img.mnist_data=new unsigned char[rows*cols];
	return img;
}
void BPNetMnist::BPNetMnist_Free(MNISTIMG img)
{
	if(img.mnist_data!=NULL)
		delete[]img.mnist_data;
	img.mnist_data=NULL;
}
void BPNetMnist::BP_Mnist_Train(const char* pathMnist,const char* pathLabel,const char* pathBPNet,CProgressCtrl* progress)
{
	ifstream ifs_label(pathLabel,ios_base::binary);
	ifstream ifs_mnist(pathMnist,ios_base::binary);

	if(!ifs_label.is_open()||!ifs_mnist.is_open())
		return ;
	char magicNum[4],ccount[4],crows[4],ccols[4];
	ifs_mnist.read(magicNum,4*sizeof(char));
	ifs_mnist.read(ccount,4*sizeof(char));
	ifs_mnist.read(crows,4*sizeof(char));
	ifs_mnist.read(ccols,4*sizeof(char));

	int count,rows,cols;
	this->BP_Mnist_Swap(ccount);
	this->BP_Mnist_Swap(crows);
	this->BP_Mnist_Swap(ccols);
	memcpy(&count,ccount,sizeof(ccount));
	memcpy(&rows,crows,sizeof(rows));
	memcpy(&cols,ccols,sizeof(cols));

	ifs_label.read(magicNum,sizeof(magicNum));
	ifs_label.read(ccount,sizeof(ccount));
	int intmagicNum,ccountint;
	this->BP_Mnist_Swap(magicNum);
	this->BP_Mnist_Swap(ccount);
	memcpy(&intmagicNum,magicNum,sizeof(intmagicNum));
	memcpy(&ccountint,ccount,sizeof(ccountint));

	MNISTIMG img;
	double   bpDatap[10];
	img=this->BPNetMnist_Allocate(rows,cols);
	bpnn_initialize(54);
	bp=bpnn_create(rows*cols,15,10);
	char label=0;
	progress->SetPos(0);
	progress->SetStep(1);
	progress->SetRange(0,count);
	for (int i=0;i<count;i++)
	{
		progress->StepIt();
		memset(bpDatap,0,10*sizeof(double));
		ifs_label.read(&label,1);
		bpDatap[label]=1.0;
		ifs_mnist.read((char*)img.mnist_data,rows*cols);
		for(int j=0;j<rows*cols;j++)
			bp->input_units[j]=(double)img.mnist_data[j]/255.0;
		for(int j=0;j<11;j++)
			bp->target[j]=bpDatap[j];
		double eh,eo;
		bpnn_train(bp,0.6,0.4,&eo,&eh);
	}
	this->bp_save(pathBPNet);
	this->BPNetMnist_Free(img);
	ifs_label.close();
	ifs_mnist.close();
}
void BPNetMnist::BP_Mnist_Predict(const char* pathBPNet,const char* pathMnist,int num,CDC* pDC,CEdit* m_edit)
{
	this->bp_load(pathBPNet);
	
	//打开mnist信息
	ifstream ifs_mnist(pathMnist,ios_base::binary);

	if(!ifs_mnist.is_open())
		return ;
	char magicNum[4],ccount[4],crows[4],ccols[4];
	ifs_mnist.read(magicNum,4*sizeof(char));
	ifs_mnist.read(ccount,4*sizeof(char));
	ifs_mnist.read(crows,4*sizeof(char));
	ifs_mnist.read(ccols,4*sizeof(char));

	int count,rows,cols;
	this->BP_Mnist_Swap(ccount);
	this->BP_Mnist_Swap(crows);
	this->BP_Mnist_Swap(ccols);
	memcpy(&count,ccount,sizeof(ccount));
	memcpy(&rows,crows,sizeof(rows));
	memcpy(&cols,ccols,sizeof(cols));

	MNISTIMG img;
	img=this->BPNetMnist_Allocate(rows,cols);
	CRect tempRect;
	m_edit->GetRect(&tempRect);
	for (int i=0;i<num;i++)
	{
		ifs_mnist.read((char*)img.mnist_data,rows*cols);
		for(int j=0;j<rows*cols;j++)
			bp->input_units[j]=(double)img.mnist_data[j]/255.0;
		for(int j=0;j<rows;j++)
			for (int k=0;k<cols;k++)
				pDC->SetPixel(j+50,k+50,img.mnist_data[k*rows+j]);
		bpnn_feedforward(this->bp);
		double maxdata=-1;
		int data=0;
		for(int j=0;j<10;j++)
		{
			if(maxdata<bp->output_units[j])
			{
				data=j;
				maxdata=bp->output_units[j];
			}
		}
		CString temp2;
		temp2.Format("%d",data);
		AfxMessageBox(temp2);
		//SendMessage(m_edit->GetSafeHwnd(),WM_SETTEXT,0,data);
		//m_edit->SetWindowText(temp2);
		//m_edit->Invalidate(TRUE);
		//Sleep(500);
	}
	this->BPNetMnist_Free(img);
	ifs_mnist.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMnistPredictDlg::OnBPNetTrain()
{
	// TODO: 在此添加控件通知处理程序代码
	const char* pathMnist="D:\\testdata\\mnist\\train-images-idx3-ubyte\\train-images.idx3-ubyte";
	const char* pathLabel="D:\\testdata\\mnist\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte";
	m_BPNetMnist_MFC_Dlg.BP_Mnist_Train(pathMnist,pathLabel,"bpnetTrain.txt",&m_progress);
	AfxMessageBox("手写数字训练完成！");
}
void CMnistPredictDlg::OnBPNetPredict()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	const char* pathMnist="D:\\testdata\\mnist\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte";
	//const char* pathLabel="D:\\测试数据集\\mnist\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte";
	CDC *pDC=GetDlgItem(IDC_STATIC)->GetDC();
	//m_Predict.SetWindowText("test");
	m_BPNetMnist_MFC_Dlg.BP_Mnist_Predict("bpnetTrain.txt",pathMnist,60,pDC,&m_Predict);
	
}
