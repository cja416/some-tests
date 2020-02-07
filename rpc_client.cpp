#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "square.h"
using namespace std;

#define host = "127.0.0.1"

int main(){
	
	CLIENT *cl;
	square_in in;
	square_out *outp;
	
	long q = 100000;
	
	cl = clnt_create(host, SQUARE_PROG, SQUARE_VERS, "tcp");
	in.arg1 = q;
	
	if((outp = squareproc_1(&in,cl)) == NULL){
		err_quit("%s", slnt_sperror(cl,host));
	}
	
	cout<<"result is "<< outp->res1 << endl;
	return 0;
}
