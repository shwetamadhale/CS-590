#include <cstdio>
#include <cstdlib>

#include "sort.h"


int ivector_length(int* v, int n)
{
  int sum;

  sum = 0;
  for (int i = 0; i < n; i++)
    sum += (v[i] < 0) ? -v[i] : v[i];

  return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
  int i;
  int* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

/*
*   TO IMPLEMENT: Improved Insertion Sort for problem 1.
*/
int* computeLength(int** A, int n, int l, int r){
    int vecSize = r - l + 1; 
    int* findLength =  new int[vecSize];

    for(int i = l; i <= r; i++){
        findLength[i] = ivector_length(A[i], n);
    }

    return findLength;
}


void insertion_sort_im(int** A, int n, int l, int r)
{ 
    int* compLength = computeLength(A, n, l, r);
    int i;
    int* key1, key2;

    for (int j = l+1; j <= r; j++){
        key1 = A[j];
        key2 = compLength[j-l];
        i = j - 1;

        while ((i >= l) && (key2 < compLength[i])){
            A[i+1] = A[i];
            compLength[i + 1] = compLength[i];
            i = i - 1;
        }
        A[i+1] = key1;
        compLength[i+1] = key2;
        }

}


/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/

void merge(int** A, int* compLength, int p, int q, int r){
    int mergedSize = r - p + 1;
    int mergePos = 0, leftPos = 0, rightPos = 0;
    int** mergedArray = new int*[mergedSize];
    leftPos = p;
    rightPos = q+1;

    while(leftPos <= q && rightPos <= r){
        if(compLength[leftPos] <= compLength[rightPos]){
            mergedArray[mergePos] = A[leftPos];
            ++leftPos;
        }else{
            mergedArray[mergePos] = A[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    while(leftPos <= q){
        mergedArray[mergePos] = A[leftPos];
        ++leftPos;
        ++mergePos;
    }

    while(rightPos <= r){
        mergedArray[mergePos] = A[rightPos];
        ++rightPos;
        ++mergePos;
    }

    for(mergePos = 0; mergePos < mergedSize; ++mergePos){
        A[p+mergePos] = mergedArray[mergePos];
    }

}

void sortMerge(int** A, int* compLength, int p, int r){
    int q = 0;
    if(p < r){
        q = p + r/2;
        sortMerge(A, compLength, p, q);
        sortMerge(A, compLength, q+1, r);

        merge(A, compLength, p, q, r);
    }
}
/*
*   TO IMPLEMENT: Improved Merge Sort for problem 2.
*/
void merge_sort(int** A, int n, int p, int r)
{
    int* compLength = computeLength(A, n, p, r);
    sortMerge(A, compLength, p, r);
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
  for (int i = l+1; i <= r; i++)
    if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
      return false;
  return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
  int** iv_array;

  iv_array = new int*[m];
  for (int i = 0; i < m; i++)
    iv_array[i] = new int[n];

  return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
  for (int i = 0; i < m; i++)
    delete[] iv_array[i];
  delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = (i+j)/n;

  return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      iv_array[i][j] = ((m-i)+j)/n;

  return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
  random_generator rg;
  int** iv_array;

  iv_array = create_ivector(n, m);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      {
	rg >> iv_array[i][j];
	if (small)
	  iv_array[i][j] %= 100;
	else
	  iv_array[i][j] %= 65536;
      }

  return iv_array;
}

