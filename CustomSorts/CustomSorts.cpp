#include "Sort.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <memory.h>

typedef void (*pSortFuns)( int*, int );

void initTab( int* pTab, int nSize );
void printTab( int* pTab, int nSize );
int createTab( int**, int );

#define DEBUG_PRINT

#define MAXLINE 10
#define PARAMNUM 2

int main( int argc, char* argv[] )
{
  if( argc != PARAMNUM )
  {
    printf( "Usage: %s <array_length>\n", argv[0] );
    return 1;
  }

  int nSize = atoi( argv[1] );

  int* exTab = NULL;
  if( !createTab( &exTab, nSize ) )
  {
    printf( "Memory allocation error exTab can't be created\n" );
    return 2;
  }

  initTab( exTab, nSize );

#ifdef DEBUG_PRINT

  printf( "Tablica nieposortowana\n" );
  printTab( exTab, nSize );

#endif


  pSortFuns pSortTab[] = { simpleInsertion, simpleSelection, bubbleSort };
  const char* sortNames[] = { "wstawianie", "wybieranie", "babelkowe" };

  int pSortSize = sizeof( pSortTab ) / sizeof( pSortFuns );


  int* desTab = NULL;
  if( !createTab( &desTab, nSize ) )
  {
    printf( "Memory allocation error desTab can't be created\n" );
    return 3;
  }

  for( int i=0; i<pSortSize; i++ )
  {
    memcpy( desTab, exTab, sizeof( int ) * nSize );
    
    double startTime = clock();

    pSortTab[i]( desTab, nSize );

    printf( "sortowanie przy pomocy %s | czas = %lf\n", sortNames[i], (double)( clock() - startTime ) / CLOCKS_PER_SEC );

#ifdef DEBUG_PRINT

    printf( "Tablica posortowana %s\n", sortNames[i] );
    printTab( desTab, nSize );

#endif

  }

#ifdef DEBUG_PRINT

  printf( "Tablica nieposortowana\n" );
  printTab( exTab, nSize );

#endif

  free( exTab );
  free( desTab );

  return 0;
}

void initTab( int* pTab, int nSize )
{
  srand( (unsigned)time( NULL ) );
  for( int i=0; i<nSize; i++ )
    *pTab++ = rand() % nSize;
}

void printTab( int* pTab, int nSize )
{
  for( int i=0; i<nSize; i++ )
  {
    printf( "%d ", *pTab++ );

    if( !( ( i+1 ) % MAXLINE ) )
      printf( "\n" );
  }
}

int createTab( int** pTab, int nSize )
{
  *pTab = (int*)malloc( nSize * sizeof( int ) );

  if( !*pTab ) return 0;

  memset( *pTab, 0, nSize * sizeof( int ) );

  return 1;
}
