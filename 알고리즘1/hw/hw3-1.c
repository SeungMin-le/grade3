/* ID: COMP319		>>> REPLACE WITH YOUR ID
 * NAME: Algorithms 1	>>> REPLACE WITH YOUR NAME
 * OS: linux, Ubuntu 16.04
 * Compiler version: gcc 5.4.0 20160609
 */

// MEMORY
// Given (allowed): malloc_c(size_t) strdup_c(const char*)
// Allowed string functions: strcpy, strncpy, strlen, strcmp, strncmp
// Unallowed memory functions: memcpy, memccpy, memmove, wmemmove,
//    or other direct memory copy/move functions
//    these functions performs 'BLOCKED' operations so that
//    a large chunk of memory allocation or move operation are
//    efficiently implemented, so they break UNIT TIME assumption
//    in algorithm design
// Unallowed string functions: strdup

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS
// >>> LINE 1: REPLACE WITH YOUR ID (IF YOU HAVE NON-NUMERIC, IGNORE IT)
// >>> Line 2: REPLACE WITH YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS AND Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 3
// IMPLEMENTATION OF SORTING ALGORITHMS FOR CHAR ARRAY STRINGS

#include<stdio.h>
#include<stdlib.h>	// atoi, malloc, free
#include<string.h>	// string library
#include<stdint.h>	// fixed-width integers, since C99 --- 1999 ISO standards

#define MEASURE_TIME	// to measure execution time

#define MEASURE_MEMORY	// to measure required memory
// from GJANG: free is not considered
// just counts the amount of memory required by malloc_c

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// to compute used memory
// use malloc_c defined below, instead of malloc, calloc, realloc, etc.
// malloc_c accumulates the size of the dynamically allocated memory to
// global/static variable used_memory, so that we can measure the
// used amount of memory exactly.
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_MEMORY
static size_t used_memory = 0;
void *malloc_c(size_t size)
{
  if ( size > 0 ) {
    // increase the required memory count
    used_memory += size;
    return malloc(size);
  }
  else return NULL;
}

// create a duplicate word with counting bytes
char *strdup_c(const char *s) {
  int size;
  size = strlen(s)+1;   // including last null character
  used_memory += size;
  return strdup(s);
}
#else
void *malloc_c(size_t size) { return malloc(size); }
char *strdup_c(const char *s) { return strdup(s); }
#endif


/////////////////////////////////////////////////////////////
// read whole file into memory
/////////////////////////////////////////////////////////////
char* read_bytes( const char infile[], long *pNbytes )
  // returns an char array with its size stored in
  // the memory indicated by integer pointer variable pNbytes
  // the retured memory should freed by the caller
{
  char *B;
  long n;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL input file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for read\n",infile);
    return NULL;
  }
  else {
    // find the file size
    fseek(fp,0,SEEK_END);	// move to the end of file
    *pNbytes = ftell(fp);	// file size = end loc from the start
    if ( *pNbytes <= 0 ) return NULL;	// no element

    // to the beginning again
    rewind(fp);

    // allocate memory and read the file
    B = (char*)malloc_c(*pNbytes+1);
    n = fread(B,1,*pNbytes,fp);
    if ( n != *pNbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);
    }
    B[*pNbytes] = '\0';
    //fprintf(stderr, "file %s, %ld/%ld bytes read\n",infile,n,*pNbytes);

    // close file
    fclose(fp);
    return B;
  }
}

/////////////////////////////////////////////////////////////
// write memory to a text file
/////////////////////////////////////////////////////////////
void write_bytes( const char outfile[], const char B[], long Nbytes )
  // write the char array of size Nbytes
  // to file whose name given by outfile[]
{
  FILE *fp;
  long n;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL output file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s for write\n",outfile);
  }
  else {
    n = fwrite(B,1,Nbytes,fp);
    if ( n != Nbytes ) {
      fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);
    }
    //fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);

    // close file
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// FILL: YOUR AREA
// DEFINE YOUR OWN FUNCTIONS
/////////////////////////////////////////////////////////////
char ** bToArr(char *B,int numBytes,int count){
    char **arr;
    int k=0;


    arr=(char**)malloc_c(sizeof(char*)*(numBytes/count));
    for(int i=0;i<(numBytes/count);i++){
        arr[i]=(char*)malloc_c(sizeof(char)*count+1);
    }
    for(int i=0;i<(numBytes/count);i++){
        for(int j=0;j<count;j++){
            arr[i][j]=B[k++];
        }
        arr[i][count]='\0';

    }
    return arr;
}
void arrToB(char **arr,char*B,int numBytes,int count){

    int k=0;
    for(int i=0;i<(numBytes/count);i++){
        for(int j=0;j<count;j++){
            B[k++]=arr[i][j];
        }

    }
    B[numBytes-1]='\0';


}
///////////////////////////////////////////////////////////////
// merge sort
//source:COMP319 Algorithms 1, Spring 2021: Lecture 5 Merge and Quick Sort P.11
void merge_sort(char **arr,char**tmp,int left,int right){
    int mid;

    if(left<right){
        mid = (left+right)/2;
        merge_sort(arr,tmp,left,mid);
        merge_sort(arr,tmp,mid+1,right);

        merge(arr,tmp,left,mid,right);

    }
}
///////////////////////////////////////////////////////////////
// merge sort
//source:COMP319 Algorithms 1, Spring 2021: Lecture 5 Merge and Quick Sort P.11
void merge(char**arr,char**tmp,int left,int mid, int right){

    int i,j,k,l;


    i=left; j=mid+1; k=left;

    while(i<=mid && j<=right){
        if(strcmp(arr[i],arr[j])<=0){
            strcpy(tmp[k++] , arr[i++]);
        }
        else{
            strcpy(tmp[k++] , arr[j++]);
        }
    }
    if(i>mid){
        for(l=j; l<=right; l++){
            strcpy(tmp[k++] , arr[l]);
        }
    }
    else{
        for(l=i; l<=mid; l++){
            strcpy(tmp[k++] , arr[l]);
        }
    }

    for(l=left; l<=right; l++){
        strcpy(arr[l] , tmp[l]);
    }

}
///////////////////////////////////////////////////////
//quick Sort
//source: https://jaehee-developer.tistory.com/14
void quick_sort(char **arr,int start,int end, int count){
    if(start<end){
        int pivot = getPivot(arr,start,end,count);
        quick_sort(arr,start,pivot-1,count);
        quick_sort(arr,pivot+1,end,count);
    }
}
int getPivot(char **arr, int start, int end,int count){
    int i= start-1,j;
    char *pivot = (char*)malloc_c(sizeof(char)*count+1);
    char *temp = (char*)malloc_c(sizeof(char)*count+1);
    pivot=arr[end];
    for(j=start;j<end;j++){
        if(strcmp(arr[j],pivot)<=0){
            strcpy(temp,arr[++i]);
            strcpy(arr[i],arr[j]);
            strcpy(arr[j],temp);
        }
    }
    strcpy(temp,arr[i+1]);
    strcpy(arr[i+1],arr[end]);
    strcpy(arr[end],temp);
    return i+1;
}
/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  long numBytes;
  char *B;	// to store data to be sorted
  int method;	// which sorting method
  char **arr;
  int count=0;
  char **tmp;
#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
#endif

  if ( argc != 4 ) {
    fprintf(stderr, "usage: %s method infile outfile\n",argv[0]);
    fprintf(stderr, " method 1: mergesort, 2: quicksort\n");
    exit(0);
  }

  method = atoi(argv[1]);
  B = read_bytes(argv[2], &numBytes);

#ifdef MEASURE_TIME
  start = clock();
#endif
  for(int i=0;i<numBytes-1;i++){
        if(B[i]=='>'){
            count=i+1;
            break;
        }
  }
  arr=bToArr(B,numBytes,count);
  if ( B != NULL && numBytes > 0 ) {
    switch ( method ) {
      case 1:	// merge sort
          tmp=(char**)malloc_c(sizeof(char*)*(numBytes/count));
          for(int i=0;i<(numBytes/count);i++){
            tmp[i]=(char*)malloc_c(sizeof(char)*count+1);
          }

          merge_sort(arr,tmp,0,numBytes/count-1);

	break;
      case 2:
          quick_sort(arr,0,numBytes/count-1,count);

	break;
      default:
	fprintf(stderr, "unknown method: %d\n", method);
	break;
    }
    arrToB(arr,B,numBytes,count);

#ifdef MEASURE_TIME
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(stdout,"%.5f seconds\n",cpu_time_used);
#endif
#ifdef MEASURE_MEMORY
    fprintf(stdout,"%lu bytes ( %.3f x %ld )\n",
	used_memory,(double)used_memory/(double)numBytes,numBytes);
	//used_memory,(double)used_memory/(double)(numBytes-1),numBytes-1);
#endif

    // save results
    write_bytes(argv[3], B, numBytes);

    // once allocated, should be freed after use
    free(B);
    free(arr);
  }
  else {	// wrong file
    fprintf(stderr,"Wrong file format for %s\n",argv[2]);
  }
}
