/* ID: 2016111683
 * NAME: Lee SeungMin
 * OS: linux, Ubuntu 16.04
 * Compiler version: gcc 5.4.0 20160609
 */

// NOTE: IN GENERAL, COMMENTED STATEMENTS FOLLOWED BY
// ">>>" WRITTEN IN CAPITAL LETTERS ARE DIRECTIONS

// >>> (10/100) pts
// >>> IN THE TOP 4-LINES COMMENTS
// >>> LINE 1: WRITE YOUR ID (NON-NUMERIC LETTERS ARE FINE)
// >>> Line 2: WRITE YOUR NAME (NO HANGUL)
// >>> DO NOT CHANGE OS OR Compiler
// >>> COMPILE AND RUN YOUR CODE ON THE LINUX MACHINE

// HOMEWORK PROGRAMMING ASSIGNMENT 4-2
// HASH FUNCTION DESIGN FOR WORD COUNTING SORTED BY NUMBER OF APPEARANCES

#include<stdio.h>
#include<stdlib.h>	// atoi
#include<string.h>	// string library

#define MEASURE_TIME	// to measure execution time

#define MEASURE_MEMORY	// to measure required memory

#ifdef MEASURE_TIME
/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#include<time.h>
#endif

#ifdef MEASURE_MEMORY
/////////////////////////////////////////////////////////////////////
// to compute used memory
/////////////////////////////////////////////////////////////////////
static size_t used_memory = 0;

// allocate memory with counting bytes
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
// linked list for word counting
/////////////////////////////////////////////////////////////
struct WORDNODE {
  char *word;	// content
  int count;	// number of appearances
  struct WORDNODE *next;
  int code;	// code, in the descending order of counts
};

struct WORDNODE *create_wnode( const char w[] ) {
  struct WORDNODE *newnode;

  // create a new word node
  newnode = (struct WORDNODE*)malloc_c(sizeof(struct WORDNODE));
  newnode->word = strdup_c(w);
  newnode->count = 1;
  newnode->next = NULL;
  newnode->code = -1;	// initially not set
  return newnode;
}

void free_wnodelist_recursive(struct WORDNODE *node) {
  if ( node ) {
    free_wnodelist_recursive(node->next);
    free(node->word);
    free(node);
  }
}
struct WORDHASHTABLE {
  struct WORDNODE **wnode;	// hash table, array of word node lists
  int size;	// size of the hash table
  int num_words;	// count unique number of words, same as the length of the list
};

struct WORDHASHTABLE *create_word_hashtable( int hashtabsize )
{
  int i;
  struct WORDHASHTABLE *htab;

  htab = (struct WORDHASHTABLE*)malloc_c(sizeof(struct WORDHASHTABLE));
  htab->wnode = (struct WORDNODE**)malloc_c(sizeof(struct WORDNODE*)*hashtabsize);
  for (i=0; i<hashtabsize; i++) htab->wnode[i] = NULL;
  htab->size = hashtabsize;
  htab->num_words = 0;
  return htab;
}

void free_hashtable(struct WORDHASHTABLE *htab) {
  int i;
  for (i=0; i<htab->size; i++)
    free_wnodelist_recursive(htab->wnode[i]);
  free(htab);
}

/* ========= FILL ======== */
int hashFunction(int key,int size){
    return key%size;
}


void insert(struct WORDHASHTABLE *hashtable,int key,char* value ){
    int hashIndex = hashFunction(key,hashtable->size);


    struct WORDNODE * iterator;
    struct WORDNODE * newnode= create_wnode(value);


    //hashIndex에 아무것도 없는 경우
    if(hashtable->wnode[hashIndex]==NULL){
        hashtable->wnode[hashIndex]=newnode;
        hashtable->num_words++;

    }
    else{
        iterator=hashtable->wnode[hashIndex];

        while(iterator!=NULL){
            if(strcmp(iterator->word,newnode->word)==0){
                iterator->count++;
                return;
            }

            iterator=iterator->next;

        }

        newnode->next=hashtable->wnode[hashIndex];
        hashtable->wnode[hashIndex]=newnode;
        hashtable->num_words++;


    }
}
void sort(struct WORDHASHTABLE *hashtable){
    struct WORDNODE * iterator;
    struct WORDNODE * index;
    struct WORDNODE * min;
    char* tmp;
    int ntmp;

    for(int i=0;i<hashtable->size;i++){

        index=hashtable->wnode[i];

        while(index!=NULL){
            iterator=index;
            min=index;

            while(iterator!=NULL && iterator->next!=NULL){

                if(min->count < iterator->next->count){


                    min = iterator->next;

                }
                else if(min->count == iterator->next->count && strcmp(min->word,iterator->next->word)>0){
                        min = iterator->next;

                }

                iterator=iterator->next;
            }


            tmp=min->word;
            min->word=index->word;
            index->word=tmp;


            ntmp=min->count;
            min->count=index->count;
            index->count=ntmp;

            index=index->next;
        }

    }
}
struct WORDNODE ** hashToArray(struct WORDHASHTABLE *hashtable){
    struct WORDNODE **arr;
    struct WORDNODE * iterator;
    struct WORDNODE * max;
    struct WORDNODE *tmp;
    int ntmp;
    int j=0;


    arr = (struct WORDNODE **)malloc_c(sizeof(struct WORDNODE *)*hashtable->num_words);

    for(int i=0;i<hashtable->size;i++){

        iterator=hashtable->wnode[i];

        while(iterator!=NULL){

            arr[j]=iterator;

            iterator=iterator->next;

            j++;

        }
    }
    for(int i=0;i<hashtable->num_words-1;i++){

            max=arr[i];

            for(int k=i+1;k<hashtable->num_words;k++){


                if(max->count < arr[k]->count){


                    max=arr[k];
                }
                else if(max->count == arr[k]->count && strcmp(max->word,arr[k]->word)>0){

                        max=arr[k];

                    }

            }
            if(max->word!=arr[i]->word){

                tmp=max->word;
                max->word=arr[i]->word;
                arr[i]->word=tmp;

                ntmp=max->count;
                max->count=arr[i]->count;
                arr[i]->count=ntmp;
            }

    }
    for(int i=0;i<hashtable->num_words;i++){
        arr[i]->code=i;
    }


    return arr;

}
struct WORDHASHTABLE * cpyHashtable(struct WORDHASHTABLE *hashtable){

    struct WORDHASHTABLE *htable;
    int wcount;
    struct WORDNODE* h1node;
    struct WORDNODE* h2node;
    htable=create_word_hashtable(hashtable->size);

    htable->size=hashtable->size;

    for(int i=0;i<htable->size;i++){
        h1node=hashtable->wnode[i];
        while(h1node!=NULL){
            wcount=0;
            for(int j=0;j<strlen(h1node->word);j++){
                wcount+=h1node->word[j];
            }
            insert(htable,wcount,h1node->word);
            h1node=h1node->next;

        }
    }

    for(int i=0;i<htable->size;i++){
        h1node=hashtable->wnode[i];
        h2node=htable->wnode[i];
        while(h1node!=NULL){
            h2node->word=h1node->word;
            h2node->count=h1node->count;
            h1node=h1node->next;
            h2node=h2node->next;
        }
    }



    return htable;
}
void cpyCode(struct WORDNODE **arr,struct WORDHASHTABLE *h2){
    struct WORDNODE *iterator;
    for(int j=0;j<h2->size;j++){
        iterator=h2->wnode[j];

        while(iterator!=NULL){

            for(int i=0;i<h2->num_words;i++){

                if(strcmp(iterator->word,arr[i]->word)==0){

                    iterator->code=arr[i]->code;
                }
            }
            iterator=iterator->next;
        }
    }

}
/* ========= END OF FILL ======== */


/////////////////////////////////////////////////////////////
// hash table for word counting
/////////////////////////////////////////////////////////////


/* ========= FILL ======== */
// functions for handing struct WORDHASHTABLE
// changing the struct or
// defining any additional functions and structs are allowed
/* ========= END OF FILL ======== */


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  struct WORDHASHTABLE *hashtable;
  int htabsize;
  char buffer[256];	// input string
  char *infile, *outfile1, *outfile2;
  FILE *ifp, *ofp;
  int j;
  /* ========= FILL ======== */
  int hashIndex;
  int wcount=0,k;
  struct WORDHASHTABLE * htable;
  struct WORDNODE *currentnode;
  struct WORDNODE **arr;
  /* ========= END OF FILL ======== */

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
  start = clock();
#endif

  // INPUT ARGUMENTS
  if ( argc != 5 ) {
    fprintf(stderr, "usage: %s hashtablesize infile outfile1 outfile2\n",argv[0]);
    exit(0);
  }
  else {
    htabsize = atoi(argv[1]);
    infile = argv[2];
    outfile1 = argv[3];
    outfile2 = argv[4];
  }

  // create a hash table
  hashtable = create_word_hashtable(htabsize);




  // check for input file existence
  if ( (ifp = fopen(infile,"r")) == NULL ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return -1;
  }
  else {
    // read word one by one to the end of file
    for (j=0; !feof(ifp); j++) {	// feof: end of file
      if ( fscanf(ifp, "%s", buffer) != 1 ) break;	// out of the loop
      else {
	/* ========= FILL ======== */
         k=strlen(buffer);

        for(int i=0;i<k;i++){
            wcount+=buffer[i];
        }
        insert(hashtable,wcount,buffer);


        wcount=0;

	/* ========= END OF FILL ======== */
      }
    }
    rewind(ifp);	// move to the beginning of the file, for the read in ENCODING

    /* ========= FILL ======== */
    sort(hashtable);
    htable=cpyHashtable(hashtable);
    ofp=fopen(outfile1,"w");
    if ( !ofp ) {
        fprintf(stderr, "cannot open file %s for write\n",outfile1);
    }
    else {
        fprintf(ofp,"hashtable %d buckets %d words\n",htabsize,hashtable->num_words);
        for(int i=0;i<htabsize;i++){
            fprintf(ofp,"bucket %d ",i);
            currentnode=hashtable->wnode[i];
        while(currentnode!=NULL){
            fprintf(ofp,"(%s %d %d) ",currentnode->word,currentnode->count,currentnode->code);
            currentnode=currentnode->next;
        }
        fprintf(ofp,"\n");
    }
    fprintf(ofp,"\n");
    arr=hashToArray(hashtable);
    fprintf(ofp,"count-alphabet-sorted %d words\n",htable->num_words);
   for(int i=0;i<hashtable->num_words;i++){
        fprintf(ofp,"(%s %d %d) ",arr[i]->word,arr[i]->count,arr[i]->code);
    }
    fprintf(ofp,"\n");
     fprintf(ofp,"\n");

    cpyCode(arr,htable);
    for(int i=0;i<htabsize;i++){
        fprintf(ofp,"bucket %d ",i);
        currentnode=htable->wnode[i];
        while(currentnode!=NULL){
            fprintf(ofp,"(%s %d %d) ",currentnode->word,currentnode->count,currentnode->code);
            currentnode=currentnode->next;
        }
        fprintf(ofp,"\n");
    }
    fprintf(ofp,"\n");
    }
    fclose(ofp);
    ofp=fopen(outfile2,"w");
    if ( !ofp ) {
        fprintf(stderr, "cannot open file %s for write\n",outfile2);
    }
    else {
    for (j=0; !feof(ifp); j++) {	// feof: end of file
      if ( fscanf(ifp, "%s", buffer) != 1 ) break;	// out of the loop
      else {

        k=strlen(buffer);
        wcount=0;
        for(int i=0;i<k;i++){
            wcount+=buffer[i];
        }


      hashIndex=hashFunction(wcount,htable->size);

      currentnode=htable->wnode[hashIndex];
      while(currentnode!=NULL){
            if(strcmp(buffer,currentnode->word)==0){
                fprintf(ofp,"%d ",currentnode->code);

            }
        currentnode=currentnode->next;
      }


      }
    }
    }
    /* ========= END OF FILL ======== */

    fclose(ifp);
  }

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"%.5f seconds\n",cpu_time_used);
#endif
#ifdef MEASURE_MEMORY
  fprintf(stdout,"%lu bytes ( %.3f x %d )\n",
      used_memory,(double)used_memory/(double)hashtable->num_words,hashtable->num_words);
#endif
  free_hashtable(hashtable);
  return 0;
}
