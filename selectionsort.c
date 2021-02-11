/* Rollnumber: 20MCMB05 Name: LAKSHMINARAYANA JALADURGAM */ 

/* The #include directive tells the C preprocessor to include the
   contents of the file specified in the input stream to the 
   compiler and then continue with the rest of the original file.
   Declare stdio.h for using standard input and output functions*/
#include<stdio.h>

// Driver code: This is the first funciton which gets invoked and executed
int main(){
   int i, j, count, temp, number[25];

   //printf("Number of elements: ");
   scanf("%d",&count);

   //printf("\nEnter %d elements: ", count);
   // Loop to get the elements stored in array
   for(i=0;i<count;i++)
      scanf("%d",&number[i]);
      
   //printf("\nElements before sorting:\n");
   //for(i=0;i<count;i++)
      //printf(" %d",number[i]);
 
   // Logic of selection sort algorithm
   /* Here i & j for loop counters, temp for swapping,
    * count for total number of elements, number[] to
    * store the input numbers in array. You can increase
    * or decrease the size of number array as per requirement
    */
   for(i=0;i<count;i++){
      for(j=i+1;j<count;j++){
         if(number[i]>number[j]){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }
   }
   
   //printf("\nElements after sorting:\n ");
   for(i=0;i<count;i++)
      printf("%d ",number[i]);

   return 0;
}
