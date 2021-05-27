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
  int j;
  /* ========= FILL ======== */
  int k,wcount=0;
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
  if ( argc != 4 ) {
    //fprintf(stderr, "%d\n",argc);
    fprintf(stderr, "usage: %s hashtablesize infile outfile\n",argv[0]);
    exit(0);
  }
  else {
    htabsize = atoi(argv[1]);
    infile = argv[2];
    outfile = argv[3];
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
	/* ========= END OF FILL ======== */
      }
    }

    fclose(ifp);	// read done
    sort(hashtable);
    arr= hashToArray(hashtable);
    // check for output file
    if ( (ofp = fopen(outfile,"w")) == NULL ) {
      fprintf(stderr, "cannot open file for write %s\n",outfile);
      return -1;
    }
    else {
      /* ========= FILL ======== */
      fputs("hashtable %d buckets %d words\n",htabsize,hashtable->num_words);

      // 5. print the hash table to the output file (ofp)
      // 6. print the sorted list of all the words to the output file (ofp)
      /* ========= END OF FILL ======== */
      fclose(ofp);
    }
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
