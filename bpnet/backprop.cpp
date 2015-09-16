#include "StdAfx.h"
#include "backprop.h"

#include <stdio.h>
#include<stdlib.h>
#include <cmath>
#include<fstream>
#include<iomanip>

using namespace std;
#define ABS(x)          (((x) > 0.0) ? (x) : (-(x)))

//using register to acclerrate the speed
#define fastcopy(to,from,len)\
{\
	register char *_to,*_from;\
	register int _i,_l;\
	_to = (char *)(to);\
	_from = (char *)(from);\
	_l = (len);\
	for (_i = 0; _i < _l; _i++) *_to++ = *_from++;\
}

/*** Return random number between 0.0 and 1.0 ***/
double drnd()
{
	return ((double) rand() / (double) BIGRND);
}

/*** Return random number between -1.0 and 1.0 ***/
double dpn1()
{
	return ((drnd() * 2.0) - 1.0);
}

/*** The squashing function.  Currently, it's a sigmoid. ***/
double squash(double x)
{
	return (1.0 / (1.0 + exp(-x)));
}

/*** Allocate 1d array of doubles ***/
double *alloc_1d_dbl(int n)
{
	double *data;

	data=new double[n];
	//data = (double *) malloc ((unsigned) (n * sizeof (double)));
	if (data == NULL) {
		printf("ALLOC_1D_DBL: Couldn't allocate array of doubles\n");
		return (NULL);
	}
	memset(data,0,sizeof(double)*n);
	return (data);
}

/*** Allocate 2d array of doubles ***/
double **alloc_2d_dbl(int m,int  n)
{
	int i;
	double **data;
	data=new double*[m];
	//data = (double **) malloc ((unsigned) (m * sizeof (double *)));
	if (data == NULL) {
		printf("ALLOC_2D_DBL: Couldn't allocate array of dbl ptrs\n");
		return (NULL);
	}

	for (i = 0; i < m; i++) {
		data[i] = alloc_1d_dbl(n);
	}

	return (data);
}


void bpnn_randomize_weights(double **w,int m,int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j <n; j++) {
			w[i][j] = dpn1();
		}
	}
}
void bpnn_zero_weights(double **w,int m,int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			w[i][j] = 0.0;
		}
	}
}


void bpnn_initialize(int seed)
{
	printf("Random number generator seed: %d\n", seed);
	srand(seed);rand();
}
BPNN *bpnn_internal_create(int n_in, int n_hidden,int n_out)
{
	BPNN *newnet;

	newnet = (BPNN *) malloc (sizeof (BPNN));
	if (newnet == NULL) {
		printf("BPNN_CREATE: Couldn't allocate neural network\n");
		return (NULL);
	}

	newnet->input_n = n_in;
	newnet->hidden_n = n_hidden;
	newnet->output_n = n_out;
	newnet->input_units = alloc_1d_dbl(n_in);
	newnet->hidden_units = alloc_1d_dbl(n_hidden);
	newnet->output_units = alloc_1d_dbl(n_out);

	newnet->hidden_delta = alloc_1d_dbl(n_hidden);
	newnet->output_delta = alloc_1d_dbl(n_out);
	newnet->target = alloc_1d_dbl(n_out);

	newnet->input_weights = alloc_2d_dbl(n_in, n_hidden);
	newnet->hidden_weights = alloc_2d_dbl(n_hidden, n_out);

	newnet->input_prev_weights = alloc_2d_dbl(n_in, n_hidden);
	newnet->hidden_prev_weights = alloc_2d_dbl(n_hidden, n_out);

	return (newnet);
}


void bpnn_free(BPNN *net)
{
	int n1, n2, i;

	n1 = net->input_n;
	n2 = net->hidden_n;

	free((char *) net->input_units);
	free((char *) net->hidden_units);
	free((char *) net->output_units);

	free((char *) net->hidden_delta);
	free((char *) net->output_delta);
	free((char *) net->target);

	for (i = 0; i < n1; i++) {
		free((char *) net->input_weights[i]);
		free((char *) net->input_prev_weights[i]);
	}
	free((char *) net->input_weights);
	free((char *) net->input_prev_weights);

	for (i = 0; i <n2; i++) {
		free((char *) net->hidden_weights[i]);
		free((char *) net->hidden_prev_weights[i]);
	}
	free((char *) net->hidden_weights);
	free((char *) net->hidden_prev_weights);

	free((char *) net);
}


/*** Creates a new fully-connected network from scratch,
with the given numbers of input, hidden, and output units.
Threshold units are automatically included.  All weights are
randomly initialized.

Space is also allocated for temporary storage (momentum weights,
error computations, etc).
***/

BPNN *bpnn_create(int n_in, int n_hidden,int n_out)
{

	BPNN *newnet;

	newnet = bpnn_internal_create(n_in, n_hidden, n_out);

#ifdef INITZERO
	bpnn_zero_weights(newnet->input_weights, n_in, n_hidden);
#else
	bpnn_randomize_weights(newnet->input_weights, n_in, n_hidden);
#endif
	bpnn_randomize_weights(newnet->hidden_weights, n_hidden, n_out);
	bpnn_zero_weights(newnet->input_prev_weights, n_in, n_hidden);
	bpnn_zero_weights(newnet->hidden_prev_weights, n_hidden, n_out);

	return (newnet);
}


void bpnn_layerforward(double *l1,double *l2,double **conn,int n1,int n2)
{
	double sum;
	int j, k;

	/*** Set up thresholding unit ***/
	l1[0] = 1.0;

	/*** For each unit in second layer ***/
	for (j = 0; j < n2; j++) {
		/*** Compute weighted sum of its inputs ***/
		sum = 0.0;
		for (k = 0; k < n1; k++) {
			sum += conn[k][j] * l1[k];
		}
		l2[j] = squash(sum);
	}
}

void bpnn_output_error(double *delta, double *target, double *output, int nj, double *err)
{
	int j;
	double o, t, errsum;

	errsum = 0.0;
	for (j =00; j < nj; j++) {
		o = output[j];
		t = target[j];
		delta[j] = o * (1.0 - o) * (t - o);
		errsum += ABS(delta[j]);
	}
	*err = errsum;
}
void bpnn_hidden_error(double*delta_h,int nh, double*delta_o,int no, double**who, double*hidden, double*err)
{
	int j, k;
	double h, sum, errsum;

	errsum = 0.0;
	for (j = 0; j < nh; j++) {
		h = hidden[j];
		sum = 0.0;
		for (k = 0; k < no; k++) {
			sum += delta_o[k] * who[j][k];
		}
		delta_h[j] = h * (1.0 - h) * sum;
		errsum += ABS(delta_h[j]);
	}
	*err = errsum;
}
void bpnn_adjust_weights(double *delta,int ndelta, double *ly,int nly, double **w, double **oldw,double eta,double momentum)
{
	double new_dw;
	int k, j;

	ly[0] = 1.0;
	for (j = 0; j < ndelta; j++) {
		for (k = 0; k < nly; k++) {
			new_dw = ((eta * delta[j] * ly[k]) + (momentum * oldw[k][j]));
			w[k][j] += new_dw;
			oldw[k][j] = new_dw;
		}
	}
}
void bpnn_feedforward(BPNN *net)
{
	int in, hid, out;

	in = net->input_n;
	hid = net->hidden_n;
	out = net->output_n;

	/*** Feed forward input activations. ***/
	bpnn_layerforward(net->input_units, net->hidden_units,
		net->input_weights, in, hid);
	bpnn_layerforward(net->hidden_units, net->output_units,
		net->hidden_weights, hid, out);

}

void bpnn_train(BPNN *net,double eta,double momentum,double* eo,double* eh)
{
	int in, hid, out;
	double out_err, hid_err;

	in = net->input_n;
	hid = net->hidden_n;
	out = net->output_n;

	/*** Feed forward input activations. ***/
	bpnn_layerforward(net->input_units, net->hidden_units,
		net->input_weights, in, hid);
	bpnn_layerforward(net->hidden_units, net->output_units,
		net->hidden_weights, hid, out);

	/*** Compute error on output and hidden units. ***/
	bpnn_output_error(net->output_delta, net->target, net->output_units,
		out, &out_err);
	bpnn_hidden_error(net->hidden_delta, hid, net->output_delta, out,
		net->hidden_weights, net->hidden_units, &hid_err);
	*eo = out_err;
	*eh = hid_err;

	/*** Adjust input and hidden weights. ***/
	bpnn_adjust_weights(net->output_delta, out, net->hidden_units, hid,
		net->hidden_weights, net->hidden_prev_weights, eta, momentum);
	bpnn_adjust_weights(net->hidden_delta, hid, net->input_units, in,
		net->input_weights, net->input_prev_weights, eta, momentum);
}

void bpnn_save(BPNN *net, const char *filename)
{
	int n1, n2, n3;
	ofstream fd;
	fd.open(filename,ios_base::out);
	if (!fd.is_open()) {
		printf("BPNN_SAVE: Cannot create '%s'\n", filename);
		return;
	}

	n1 = net->input_n;  n2 = net->hidden_n;  n3 = net->output_n;
	printf("Saving %dx%dx%d network to '%s'\n", n1, n2, n3, filename);
	fflush(stdout);
	
	//data output as the format 
	fd<<"3 level BP net output:\n";
	fd<<n1<<" "<<n2<<" "<<n3<<endl;
	
	fd<<"imput level weight:\n";
	for(int i=0;i<n1;i++)
	{
		for(int j=0;j<n2;j++)
			fd<<net->input_weights[i][j]<<" ";
		fd<<endl;
	}
	fd<<"hidden level weight:\n";
	for(int i=0;i<n2;i++)
	{
		for(int j=0;j<n3;j++)
			fd<<net->hidden_weights[i][j]<<" ";
		fd<<endl;
	}
	fd.close();
	return;
}
BPNN *bpnn_read(const char *filename)
{
	BPNN *net;
	int  n1, n2, n3;
	char tmpchr[2048];
	ifstream fd;
	fd.open(filename,ios_base::in);
	if (!fd.is_open()) {
		return (NULL);
	}

	printf("Reading '%s'\n", filename);  fflush(stdout);
	fd.getline(tmpchr,2048);
	fd>>n1>>n2>>n3;
	net = bpnn_internal_create(n1, n2, n3);

	printf("'%s' contains a %dx%dx%d network\n", filename, n1, n2, n3);
	printf("Reading input weights...");  fflush(stdout);
	fd.getline(tmpchr,2048);
	fd.getline(tmpchr,2048);
	for(int i=0;i<n1;i++)
		for(int j=0;j<n2;j++)
			fd>>net->input_weights[i][j];
	printf("Reading hidden weights...");  fflush(stdout);
	fd.getline(tmpchr,2048);
	fd.getline(tmpchr,2048);
	for(int i=0;i<n2;i++)
		for(int j=0;j<n3;j++)
			fd>>net->hidden_weights[i][j];
	fd.close();

	printf("Done\n");  fflush(stdout);

	bpnn_zero_weights(net->input_prev_weights, n1, n2);
	bpnn_zero_weights(net->hidden_prev_weights, n2, n3);

	return (net);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//base class of 3 level BP net
//construct and deconstruct function
BPNet::BPNet(int imput_n,int hidden_n,int output_n)
{
	// rand time
	bpnn_initialize(int(time_t()));
	bp=bpnn_create(imput_n,hidden_n,output_n);
}
BPNet::BPNet(BPNN* _bp)
{
	bp=_bp;
}
BPNet::~BPNet()
{
	bpnn_free(this->bp);
}

//function of save to file
void BPNet::bp_save(const char* path)
{
	bpnn_save(this->bp,path);
}
//function of load from file
void BPNet::bp_load(const char* path)
{
	this->bp=bpnn_read(path);
}

