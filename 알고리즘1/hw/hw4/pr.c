/* ID: 2016111683
 * NAME: LEE SEUNGMIN
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

// HOMEWORK PROGRAMMING ASSIGNMENT 4-1
// HASH FUNCTION DESIGN FOR WORD COUNTING

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
  size = strlen(s)+1;	// including last null character
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

};

struct WORDNODE *create_wnode( const char w[] ) {
  struct WORDNODE *newnode;

  // create a new word node
  newnode = (struct WORDNODE*)malloc_c(sizeof(struct WORDNODE));
  newnode->word = strdup_c(w);
  newnode->count = 1;
  newnode->next = NULL;
  return newnode;
}

void free_wnodelist_recursive(struct WORDNODE *node) {
  if ( node ) {
    free_wnodelist_recursive(node->next);
    free(node->word);
    free(node);
  }
}

/* ========= FILL ======== */
// functions for handing struct WORDNODE
// changing the struct or
// defining any additional functions and structs are allowed
/* ========= END OF FILL ======== */


/////////////////////////////////////////////////////////////
// hash table for word counting
/////////////////////////////////////////////////////////////
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
  if ( htab ) {
    for (i=0; i<htab->size; i++)
      free_wnodelist_recursive(htab->wnode[i]);
    free(htab);
  }
}

/* ========= FILL ======== */
// functions for handing struct WORDHASHTABLE
// changing the struct or
// defining any additional functions and structs are allowed
/* ========= END OF FILL ======== */
int hashFunction(int key,int size){
    return key%size;
}


void insert(struct WORDHASHTABLE *hashtable,int key,char* value ){
    int hashIndex = hashFunction(key,hashtable->size);

    struct WORDNODE * newnode = create_wnode(value);
    struct WORDNODE * iterator;

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
    char **arr;
    struct WORDNODE * min;
    char* tmp;
    int ntmp;

    for(int i=0;i<hashtable->size;i++){

        index=hashtable->wnode[i];

        while(index!=NULL){
            iterator=index;
            min=index;

            while(iterator!=NULL && iterator->next!=NULL){

                if(strcmp(min->word,iterator->next->word)>0){

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
char** hashToArray(struct WORDHASHTABLE *hashtable){
    struct WORDNODE **arr;
    struct WORDNODE * iterator;
    struct WORDNODE * min;
    char *tmp;
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
            min=arr[i];
            for(int k=i+1;k<hashtable->num_words;k++){
                if(strcmp(min->word,arr[k]->word)>0){
                    min=arr[k];
                }
            }
            tmp=min->word;
            min->word=arr[i]->word;
            arr[i]->word=tmp;

            ntmp=min->count;
            min->count=arr[i]->count;
            arr[i]->count=ntmp;


    }


    return arr;

}

/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  struct WORDHASHTABLE *hashtable;
  int htabsize;
  char buffer[256];	// input string
  char *infile, *outfile;
  FILE *ifp, *ofp;
  int j,k;
  int wcount=0;

  struct WORDNODE *currentnode;
  struct WORDNODE **arr;

  /* ========= FILL ======== */
  // any additional variables can be defined here
  /* ========= END OF FILL ======== */

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
  start = clock();
#endif

    htabsize = 97;
    infile = "ihaveadream.txt";


  // create a hash table
  hashtable = create_word_hashtable(htabsize);


  if ( (ifp = fopen(infile,"r")) == NULL ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return -1;
  }
  else {
    // read word one by one to the end of file
    for (j=0; !feof(ifp); j++) {	// feof: end of file
      // 1. read word
      if ( fscanf(ifp, "%s", buffer) != 1 ) break;	// out of the loop
      else {
	/* ========= FILL ======== */
        k=strlen(buffer);

        for(int i=0;i<k;i++){
            wcount+=buffer[i];
        }
        insert(hashtable,wcount,buffer);


        wcount=0;

      }
	/* ========= END OF FILL ===sdasdasd===== */
    }



    fclose(ifp);	// read done


  }


   /*
    printf("hashtable %d buckets %d words\n",htabsize,hashtable->num_words);

    for(int i=0;i<htabsize;i++){
        printf("bucket %d",i);
        currentnode=hashtable->wnode[i];
        while(currentnode!=NULL){
            printf("(%s %d) ",currentnode->word,currentnode->count);
            currentnode=currentnode->next;
        }
        printf("\n");
    }
    printf("\n");

    printf("alphabet-sorted %d words\n",hashtable->num_words);
    for(int i=0;i<hashtable->num_words;i++){
        printf("(%s %d) ",arr[i]->word,arr[i]->count);
    }
    printf("\n");*/
    sort(hashtable);
    outfile="ihaveadream_result1.txt";
    ofp=fopen(outfile,"w");
    if ( !ofp ) {
        fprintf(stderr, "cannot open file %s for write\n",outfile);
    }
    else {
        fprintf(ofp,"hashtable %d buckets %d words\n",htabsize,hashtable->num_words);
        for(int i=0;i<htabsize;i++){
            fprintf(ofp,"bucket %d",i);
            currentnode=hashtable->wnode[i];
                while(currentnode!=NULL){
                    fprintf(ofp,"(%s %d) ",currentnode->word,currentnode->count);
                    currentnode=currentnode->next;
                }
            fprintf(ofp,"\n");
        }
        arr= hashToArray(hashtable);
        fprintf(ofp,"\n");
        arr= hashToArray(hashtable);
        fprintf(ofp,"alphabet-sorted %d words\n",hashtable->num_words);
        for(int i=0;i<hashtable->num_words;i++){
            fprintf(ofp,"(%s %d) ",arr[i]->word,arr[i]->count);
        }
    fprintf(ofp,"\n");
       /* n = fwrite(arr,1,Nbytes,fp);
        if ( n != Nbytes ) {
        fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);*/

    }
    //fprintf(stderr, "file %s, %ld/%ld bytes written\n",outfile,n,Nbytes);

    // close file
    fclose(ofp);

  free_hashtable(hashtable);
  return 0;
}
