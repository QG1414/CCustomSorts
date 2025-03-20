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

int main( int argc, char* argv[] )
{
  //sprawdzic parametry
  
  if( argc != 2 )
  {
    printf( "Usage: %s <array_length> ", argv[0] );
    return 1;
  }

  int nSize = atoi( argv[1] );
  //obliczyc rozmiar tablicy

  int* exTab = NULL;
  if( !createTab( &exTab, nSize ) )
  {
    printf( "Memory allocation error exTab can't be created\n" );
    return 2;
  }

  initTab( exTab, nSize );
  //alokacja tablicy wzorcowej i jej zainicjowanie (funkje)

  #ifdef DEBUG_PRINT

  printTab( exTab, nSize );
  // wydruk na warunkowej kompil

  #endif

  //----------odczytac czasy poszczegolnych sortowan



  // alokacja pamieci na tabl do sortow
  pSortFuns pSortTab[] = { simpleInsertion, simpleSelection, bubbleSort };
  const char* sortNames[] = { "wstawianie", "wybieranie", "babelkowe" };

  // obliczyc rozmiar tablicy adresoww funkcji
  int pSortSize = sizeof( pSortTab ) / sizeof( pSortFuns );


  //TO W PETLI for
  int* desTab = NULL;
  createTab( &desTab, nSize );
  for( int i=0; i<pSortSize; i++ )
  {
    memcpy( desTab, exTab, sizeof( int ) * nSize );
    
    double startTime = clock();

    pSortTab[i]( desTab, nSize );

    printf( "%s time = %lf\n", sortNames[i], ( clock() - startTime ) / CLOCKS_PER_SEC );

    #ifdef DEBUG_PRINT

    printTab( desTab, nSize );

    #endif

  }
  // wkopiowanie do niej tabl wzorcowej

  // -- odczytac czas  clock()
  // -- posortowac
  // -- odczytac czas i wypisac czas sortowania (wzor w helpach), wypisac nazwe srtowania
  // -- na warunkowej kompilacji wydruk posortowanej

  // zwolnic pamiec

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

  if( !pTab ) return 0;

  memset( *pTab, 0, nSize * sizeof( int ) );

  return 1;
}
