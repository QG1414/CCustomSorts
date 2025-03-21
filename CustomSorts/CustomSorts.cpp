#include "Sort.h" // include our header for sort functions
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <memory.h>

typedef void (*pSortFuns)( int*, int ); // type for sort functions

void initTab( int* pTab, int nSize ); // function to initialize array with random values
void printTab( int* pTab, int nSize ); // function to print array
int createTab( int**, int ); // function to create array in memory dynamicly

#define DEBUG_PRINT // Defined value for conditional invoking used for debugging when commented arrays are not printed

#define MAXLINE 10 // max number in line before new line
#define PARAMNUM 2 // numbers of parameters that needs to be passed
#define MAXNUMPRINT 50 // max number of elements that can be printed if array is less then this then it will be printed to size of array

int main( int argc, char* argv[] )
{
  if( argc != PARAMNUM ) // check if we got correct number of parameters
  {
    printf( "Usage: %s <array_length>\n", argv[0] ); // number of params is not correct, then display how to use this script
    return 1;
  }

  int nSize = atoi( argv[1] ); // convert second parameter to int from const char*

  int* exTab = NULL; // create empty example tab
  if( !createTab( &exTab, nSize ) ) // allocate memory for it if not sucessful then end function
  {
    printf( "Memory allocation error exTab array can't be created\n" );
    return 2;
  }

  initTab( exTab, nSize ); // initialize array with random values

#ifdef DEBUG_PRINT // this lines are only invoking when DEBUG_PRINT is defined

  printf( "Unsorted array\n" );
  printTab( exTab, nSize );

#endif


  pSortFuns pSortTab[] = { simpleInsertion, simpleSelection, bubbleSort }; // create array of sort functions we will be invoking
  const char* sortNames[] = { "Insertion Sort", "Selection Sort", "Bubble Sort" }; // create name of sort methods for easier printing

  int pSortSize = sizeof( pSortTab ) / sizeof( pSortFuns ); // calculate size of array of sort functions because it can change if we add more


  int* desTab = NULL; // create array that will be a copy of example tab in which we will sort
  if( !createTab( &desTab, nSize ) ) // the same as example allocate memory for desTab
  {
    printf( "Memory allocation error desTab array can't be created\n" );
    return 3;
  }

  for( int i = 0; i < pSortSize; i++ )
  {
    memcpy( desTab, exTab, sizeof( int ) * nSize ); // copy elements from example array (exTab) to destination array (desTab)
    
    clock_t startTime = clock(); // get elapsed time before we start to sort

    pSortTab[i]( desTab, nSize ); // invoke sorting method

    printf( "Sorting with %s | time = %lf\n", sortNames[i], ( double )( clock() - startTime ) / CLOCKS_PER_SEC ); // print sorting method and time it took in seconds

#ifdef DEBUG_PRINT

    printf( "Sorted array %s\n", sortNames[i] );
    printTab( desTab, nSize );

#endif

  }

  free( exTab ); // free memory for example array
  free( desTab ); // free memory for destination array

  return 0;
}

void initTab( int* pTab, int nSize )
{
  srand( ( unsigned )time( NULL ) ); // initialize pseudo-random number generator
  for( int i = 0; i < nSize; i++ )
    *pTab++ = rand() % nSize; // assign random value in range of [0, nSize-1]
}

void printTab( int* pTab, int nSize )
{
  int print_size = ( nSize <= MAXNUMPRINT ) ? nSize : MAXNUMPRINT; // check if size of print array is lower then our max print and assign correct value
  
  for( int i = 0; i < print_size; i++ )
  {
    printf( "%d ", *pTab++ );

    if( !( ( i+1 ) % MAXLINE ) )
      printf( "\n" );
  }
}

int createTab( int** pTab, int nSize )
{
  *pTab = ( int* )malloc( nSize * sizeof( int ) ); // allocate memory for new array in size of type multiplied by number of elements

  if( !*pTab ) // check if memory was allocated correctly and *pTab is not NULL if it is return 0 that indicates failure(False)
    return 0;

  memset( *pTab, 0, nSize * sizeof( int ) ); // set all values in array to 0

  return 1; // return 1 that indicates sucess (True)
}
