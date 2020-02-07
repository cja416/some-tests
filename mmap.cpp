#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/mman.h>
 
using namespace std;
#define MAX 1
 
int main()
{
	int i=0;
	int count=0, fd=0;
	struct timeval tv1, tv2;
	int *array = (int *)malloc( sizeof(int)*MAX );
	 
	/*read*/
	 
	gettimeofday( &tv1, NULL );
	fd = open( "mmap_test.txt", O_RDWR );
	int num = read( fd, (void *)array, sizeof(int)*MAX );
	if( sizeof(int)*MAX != num )
	{
		cout<< "Reading data failed..." << endl;
		return -1;
	}
	for( i=0; i<MAX; ++i )
		++array[i];
	num = write( fd, (void *)array, sizeof(int)*MAX );
	if( sizeof(int)*MAX != num )
	{
	 	cout << "Writing data failed..." << endl;
		return -1;
	}
	free( array );
	close( fd );
	gettimeofday( &tv2, NULL );
	cout<< "Time of read/write: " << tv2.tv_usec-tv1.tv_usec<<endl;
	 
	/*mmap*/
	 
	gettimeofday( &tv1, NULL );
	fd = open( "mmap_test.txt", O_RDWR );
	array = (int *)mmap( NULL, sizeof(int)*MAX, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
	for( i=0; i<MAX; ++i )
		++array[i];
	munmap( array, sizeof(int)*MAX );
	msync( array, sizeof(int)*MAX, MS_SYNC );
	//free( array );
	close( fd );
	gettimeofday( &tv2, NULL );
	cout<< "Time of mmap: " <<  tv2.tv_usec-tv1.tv_usec<<endl;
	 
	return 0;
}
