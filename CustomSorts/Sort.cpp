
void simpleInsertion( int* pTab, int nSize )
{
  for( int i=1; i<nSize; i++ )
  {
    int j = i-1;
    int element = pTab[i];

    while( j >= 0 && pTab[j] > element )
      pTab[j+1] = pTab[j--];

    pTab[j+1] = element;
  }
}

void simpleSelection( int* pTab, int nSize )
{
  for( int i=0; i<nSize; i++ )
  {
    int idx = i;
    int min = pTab[i];

    for( int j = i+1; j < nSize; j++ )
      if( pTab[j] < min )
      {
        min = pTab[j];
        idx = j;
      }

    pTab[idx] = pTab[i];
    pTab[i] = min;
  }

}

void bubbleSort( int* pTab, int nSize )
{
  for( int i=0; i<nSize; i++ )
    for( int j=0; j<nSize-1; j++ )
      if( pTab[j] > pTab[j+1] )
      {
        int tmp = pTab[j];
        pTab[j] = pTab[j+1];
        pTab[j+1] = tmp;
      }
}