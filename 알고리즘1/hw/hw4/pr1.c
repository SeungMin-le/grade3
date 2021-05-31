
/* ID:
 * NAME:
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
  for (i=0; i<htab->size; i++)
    free_wnodelist_recursive(htab->wnode[i]);
  free(htab);
}
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

                if(min->count < iterator->next->count){

                    min = iterator->next;

                }
                else if(strcmp(min->word,iterator->next->word)>0){
                    min=iterator->next;
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
  int wcount=0,k;
  struct WORDNODE *currentnode;
  struct WORDNODE **arr;
  // any additional variables can be defined here
  /* ========= END OF FILL ======== */

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;
  start = clock();
#endif

  // INPUT ARGUMENTS


    htabsize = 3;
    infile = "i31.txt";
  //  outfile1 = "h2_i31_3.txt;
    //outfile2 = "encode_i31.txt";

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

      }
	/* ========= END OF FILL ===sdasdasd===== */
    }


    rewind(ifp);	// move to the beginning of the file, for the read in ENCODING

    /* ========= FILL ======== */
    // B. outfile1
    //   5. print the hash table to file "outfile1"
    //      the member variable "code" is all -1, because they can be decided
    //      after the next step
    //   6. print the sorted (count-then-alphabetic) list of all the words
    //      while sorting, update the member variable "code" of each WORDNODE instances
    //      by the order of "count"
    //   7. print the sorted list of all the words with updatd code
    // C. outfile2
    //   8. ENCODING: now we have the codes of all words by the "count" order,
    //      input file can be encoded by replacing each word with its code
    //      open file "infile" again for read, and open file "outfile2" for write,
    //      and store the encoding results (numbers only) to "outfile2"
    //      whitespaces differences (space/linebreak/tab) are accepted
    //
    /* ========= END OF FILL ======== */

    fclose(ifp);
  }
  sort(hashtable);
  printf("hashtable %d buckets %d words\n",htabsize,hashtable->num_words);

    for(int i=0;i<htabsize;i++){
        printf("bucket %d ",i);
        currentnode=hashtable->wnode[i];
        while(currentnode!=NULL){
            printf("(%s %d %d) ",currentnode->word,currentnode->count,currentnode->code);
            currentnode=currentnode->next;
        }
        printf("\n");
    }
    printf("\n");

  /*  printf("alphabet-sorted %d words\n",hashtable->num_words);
    for(int i=0;i<hashtable->num_words;i++){
        printf("(%s %d) ",arr[i]->word,arr[i]->count);
    }
    printf("\n");*/

  free_hashtable(hashtable);
  return 0;
}
