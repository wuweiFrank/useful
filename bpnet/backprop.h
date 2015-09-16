#pragma once
#ifndef _BACKPROP_H_
#define _BACKPROP_H_

#define BIGRND 0x7fff

/*** The neural network data structure.  The network is assumed to
     be a fully-connected feedforward three-layer network.
     Unit 0 in each layer of units is the threshold unit; this means
     that the remaining units are indexed from 1 to n, inclusive.
 ***/

typedef struct {
  int input_n;                  /* number of input units */
  int hidden_n;                 /* number of hidden units */
  int output_n;                 /* number of output units */

  double *input_units;          /* the input units */
  double *hidden_units;         /* the hidden units */
  double *output_units;         /* the output units */

  double *hidden_delta;         /* storage for hidden unit error */
  double *output_delta;         /* storage for output unit error */

  double *target;               /* storage for target vector */

  double **input_weights;       /* weights from input to hidden layer */
  double **hidden_weights;      /* weights from hidden to output layer */

                                /*** The next two are for momentum ***/
  double **input_prev_weights;  /* previous change on input to hidden wgt */
  double **hidden_prev_weights; /* previous change on hidden to output wgt */
} BPNN;


/*** User-level functions ***/
void bpnn_initialize(int seed);

BPNN *bpnn_create(int n_in, int n_hidden,int n_out);
void bpnn_free(BPNN *net);

void bpnn_train(BPNN *net,double eta,double momentum,double* eo,double* eh);
void bpnn_feedforward(BPNN *net);

void bpnn_save(BPNN *net, const char *filename);
BPNN *bpnn_read(const char *filename);

//class of 3level bp net work
class BPNet{
public:
	//construct and deconstruct function
	BPNet(){bp=NULL;}
	BPNet(int imput_n,int hidden_n,int output_n);
	BPNet(BPNN* _bp);
	~BPNet();

	//function of save to file 
	void bp_save(const char* path);
	//function of load from file
	void bp_load(const char* path);

	//interface funcion
	void bp_train()  ;
	void bp_predict();

public:
	BPNN* bp;
};

#endif


