
#include "Sort.h" // we include our header

void simpleInsertion( int* pTab, int nSize )
{
  for( int i = 1; i < nSize; i++ ) // start from the next element (1 not 0)
  {
    int j = i - 1; // new index j starts one number before 1 to not compare the same values
    int tmp = pTab[i]; // get element under index i ( i == j + 1 )

    while( j >= 0 && pTab[j] > tmp ) // check if we are still in array range, and that number before i is larger
      pTab[j + 1] = pTab[j--]; // then change number ahead to the one before

    pTab[j + 1] = tmp; // insert our value in correct index
  }
}

void simpleSelection( int* pTab, int nSize )
{
  for( int i = 0; i < nSize - 1; i++ ) // we don't need to check last element so we go to nSize - 1
  {
    int idx = i; // get current index
    int min = pTab[i]; // set current number as the smallest one

    for( int j = i + 1; j < nSize; j++ ) // start searching for smaller number from current index (i) + 1
      if( pTab[j] < min ) // if we find smaller number then min change to new min and new index of min
      {
        min = pTab[j];
        idx = j;
      }

    pTab[idx] = pTab[i]; // switch values to correct spot
    pTab[i] = min;
  }

}

void bubbleSort( int* pTab, int nSize )
{
  for( int i = 0; i < nSize - 1; i++ ) 
    for( int j = nSize - 1; j > i; j-- ) // do not check last element because it will be sorted
      if( pTab[j] < pTab[j - 1] ) // if element after is smaller then before switch
      {
        int tmp = pTab[j]; // temporary variable that helps with switching values
        pTab[j] = pTab[j - 1];
        pTab[j - 1] = tmp;
      }
}