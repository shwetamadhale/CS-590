//Shweta Madhale
//CWID : 20015921
#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2){ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else{
      if (s1[i] < s2[i])
	      return -1;
      else
	      return 1;
  }
} /*>>>*/

//Insertion sort
void insertion_sort(char** A, int l, int r){ 
  int i;
  char* key;

  for (int j = l + 1; j <= r; j++){
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0)){
        A[i + 1] = A[i];
        i = i - 1;
	    }

      A[i + 1] = key;
  }
}

//Insertion sort according to position d
void insertion_sort_digit(char** A, int* A_len, int l, int r, int d){
  int i;   
  char* key;            
    
  for(int j = l + 1; j <= r; j++){ 
    //Starting j from 1 index ahead of i    
    key = A[j];     
    i = j - 1;    
    int Alen = A_len[i];
    //Holds character at dth position
    char AVal = A[i][d];
    int keylen = A_len[j]; 
    //Holds character at dth position
    char keyVal = key[d];

    //Sorting is done according to position d, checking if charcter at d exists else its 0
    if(d > Alen){
      AVal = 0;
    } 
         
    if(d > keylen){
      keyVal = 0;
    }


    //Comparing characters in A and key with respect to position d   
    while((i >= l) && (AVal > keyVal)){  

        A[i + 1] = A[i];       
        A_len[i + 1] = A_len[i];        
        i = i - 1;
      

      //Update new values        
      if(i >= l){   
        AVal = A[i][d];  
        if(d > Alen){
          AVal = 0;
        }   
      }                    
    }  

    //Update new values for array and corresponding lengths
    A[i + 1] = key; 
    A_len[i + 1] = A_len[j];      
  }  

}


//Implementing radix sort using insertion sort
void radix_sort_is(char** A, int* A_len, int n, int m){ 
  
  for (int s = m - 1; s >= 0; s--){     
    insertion_sort_digit(A, A_len, 0, n-1, s);    
  } 

}


//Counting sort 
void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d){
  
  //Stores counters for each char
  int C[256];   

  //Initializes the array C to all zeros
  for(int s = 0; s <= 255; s++){       
    C[s] = 0;   
  }      
    
  //Check if d exists and accordingly update counters in C. Here instead of A[j] it'll be A[j][d] beacuse of dependence on d
  for(int s = 0; s < n; s++){     
    if(A_len[s] >= d + 1){       
      C[A[s][d]] = C[A[s][d]] + 1;     
    }else{       
      C[0] = C[0] + 1;     
    }    
  }
  //C[s] has number of elements equal to s   
  //Change counters so each index corresponds to its specific count
    
  //Getting how many input elements are less than or equal to s by keeping running sum
  for(int s = 1; s <= 254; s++){     
    C[s] = C[s] + C[s - 1];   
  }    
  //C[s] holds number of elements <= s 
    
  //Place each element of A[s] into its correct sorted position in B
  //Update B(holds sorted output) and C according to comparison of the lengths with d
  for(int s = n - 1; s >= 0; s--){     
    if(A_len[s] >= d + 1){   
      //Update sorted values in B, item at A[i] is at B[C[A[i]]]
      B[C[A[s][d]] - 1] = A[s];   
      //Update lenghts corresponding the updated value      
      B_len[C[A[s][d]] - 1] = A_len[s];  
      //Decrement counter       
      C[A[s][d]] = C[A[s][d]] - 1;     
    }else{     
      //Update sorted values in B, item at A[i] is at B[C[A[i]]]  
      B[C[0] - 1] = A[s]; 
      //Update lenghts corresponding the updated value       
      B_len[C[0] - 1] = A_len[s];   
      //Decrement counter    
      C[0] = C[0] - 1;    
    }   
  }   
    
  //Update A with sorted values
  for(int s = 0; s < n; s++){     
    A[s] = B[s];     
    A_len[s] = B_len[s];   
  }       

}



void radix_sort_cs(char** A, int* A_len, int n, int m){ 
    //These two will be used for temporary changes, B holds sorted output
    char** B = new char* [n];   
    int* B_len = new int[n];   
    
    for (int i = m - 1; i >= 0; i--){     
        counting_sort_digit(A, A_len, B, B_len, n - 1, i);   
    } 
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r){
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
