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

square_out* squareproc_1_svc(square_in *inp, struct svc_req * rqstp){
	static square_out out;
	
	out.res1 = inp->arg1 * inp->arg1;
	return (&out);
}