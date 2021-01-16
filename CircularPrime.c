/* Rollnumber: 20MCMB05 Name: LAKSHMINARAYANA JALADURGAM
A number is circular prime if the number and all its cyclic permutations are prime.
For example: The number 3779 is circular prime because all the cyclic permutations
3779, 9377, 7937, 7793 are prime numbers.
Where as the number 3877 is not circular prime because one of its cyclic permutation 
7738 is not a prime number.
Input/Output Specification:
 - Any input <= 0 to be treated as invalid input. Any input > 0 to be treated as valid input
 - If the number <= 0, your program should print -1
 - If the number is circular prime, your program should print 1
 - If the number is not circular prime, your program should print 0
 
Sample Input/Output:
Input: -100
Output: -1
Input: 0
Output: -1
Input: 3779
Output: 1
Input: 3877
Output: 0 */ 

/* The #include directive tells the C preprocessor to include the
   contents of the file specified in the input stream to the 
   compiler and then continue with the rest of the original file.
   Declare stdio.h for using standard input and output functions*/
#include<stdio.h>

// Funtion to find whether the number is Prime or not
int isPrime(int k)
{
   int n=k/2,i,flag=1;
   for (i=2;i<=n;i++)
   {
      if (k%i==0){flag=0;break;} 
   }
   if (flag==1){return 1;}
   else {return 0;}
}

// Driver code: This is the first funciton which gets invoked and executed
int main()
{
    int x,j,i,h=0,result=1,arr[50],a[50],temp=0,z=0,flag=0;
    printf("Input\n:");
    scanf("%d",&x);
    
    if (x<=0){
    	result = -1;
		printf("Output:\n%d",result);
		return 0;
	}    
	
    if (x==1){
        //1 is not a prime nuber
    	result = 0;
		printf("Output:\n%d",result);
		return 0;
	}   
    
    for (i=x;i!=0;i=i/10)
    {
        arr[h]=i%10;h++;
    }
    arr[h]='\0';int C[h*h],l=h-1;
    for (i=0;i<h;i++)
    {
        a[i]=arr[l];l--;
    }
    a[i]='\0';
    i=0;
    for (j=0;j<h*h;j++)
    {   if (i==h){i=0;}
        C[j]=a[i];i++;
    }
    for (j=0;j<h;)
    {
        flag=flag*10+C[z];z++;temp++;
        if ((temp)%h==0)
        {
            if (isPrime(flag)!=1){result=0;break;}
            flag=0;j++;z=j;
        }
    }
    
    //Display the final result
    //if (result==0)
	//	printf("Output: %d",result);   
	//else printf("Output: %d",result);
	printf("Output:\n%d", result);   
}