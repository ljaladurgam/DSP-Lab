/* Write a program to Convert an unsorted Array into Sorted Array. 
   Find the Starting and Ending position of a given Value in that 
   sorted Array. {You should Pass the array to the functions */ 

/* The #include directive tells the C preprocessor to include the
   contents of the file specified in the input stream to the 
   compiler and then continue with the rest of the original file.
   Declare stdio.h for using standard input and output functions*/   
#include <stdio.h>
 
/* Funtion to Get the starting position of the value in the array. 
   if value is present in arr[] then returns the index of Starting
   occurrence of x in arr[0..n-1], otherwise returns -1 */
int getStartPos(int arr[], int low, int high, int value, int n)
{
	int mid, first;
	
	//Search using Binary search technique 
    if (high >= low) {
        mid = low + (high - low) / 2;
        if ((mid == 0 || value > arr[mid - 1]) && arr[mid] == value)
        	//If the value is found at middle, Return it
            return mid;
        else if (value > arr[mid]){
        	//Search furhter on the Right side
        	first = getStartPos(arr, (mid + 1), high, value, n);
        	return first;
		}
        else{
        	//Search furhter on the Left side
        	first = getStartPos(arr, low, (mid - 1), value, n);
        	return first;
		}
    }
    return -1;
}

/* Funtion to Get the starting position of the value in the array. 
   if value is present in arr[] then returns the index of Ending occurence
   occurrence of x in arr[0..n-1], otherwise returns -1 */
int getEndPos(int arr[], int low, int high, int value, int n)
{
	int mid, last;
	
	//Search using Binary search technique
    if (high >= low) {
        int mid = low + (high - low) / 2;
        if ((mid == n - 1 || value < arr[mid + 1]) && arr[mid] == value)
        	//If the value is found at middle, Return it
            return mid;
        else if (value < arr[mid]){
        	//Search furhter on the Right side
        	last = getEndPos(arr, low, (mid - 1), value, n);
        	return last;        	
		}
        else{
        	//Search furhter on the Left side
        	last = getEndPos(arr, (mid + 1), high, value, n);
        	return last;        	
		}
    }
    return -1;
}

// Funtion to Sort the elements of the array 
void sortArray( int n, int arr[])	
{	
	int i, j, temp;
	
	// Loop each element in an array from starting position 
	for (i = 0; i < n; ++i) 	{ 
		// Loop each element in an array from next postion 
		for (j = i + 1; j < n; ++j) 		{   
			//Check if the value is bigger 
			if (arr[i] > arr[j]) 
			{   
				//Swap values 
				temp =  arr[i]; 
				arr[i] = arr[j];
				arr[j] = temp;
			}
		} 
	}
} 

// Funtion to display the elements of the Array
void displayArray( int n, int arr[])
{	
	int i;
	for (i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

// Driver code: This is the first funciton which gets invoked and executed
void main()
{ 
	//Declare local variables 
	int i, n, arr[30], value, first, last;
	
	//Prompt user to input the number of elements in the array
	printf("Enter the number of elements in array:");
	scanf("%d", &n);
	
	printf("Enter the array elements: \n");
	for (i = 0; i < n; ++i)	
		//Collect input for value of array elements from the user
		scanf("%d", &arr[i]);
			 
	//Call function to Sort the array elements 
	sortArray( n, arr);
	printf("Array elements after converting to sorted order:\n");
	
	//Call function to Display the array elements
	displayArray(n, arr);	
		
	//Take input value for whcih the Starting and ending position need to be found
	printf("\nEnter the Value in array to find the Starting and Ending Occurrence:");
	scanf("%d", &value);
	
	//Call function to find the Starting Occurrence of the value in array
	first = getStartPos(arr, 0, n - 1, value, n);
	//Call function to find the Ending Occurrence of the value in array
	last = getEndPos(arr, 0, n - 1, value, n);
	
    if (first != -1)
    {   
    	first++; last++;
    	//Show the Starting Occurrence of the value in array
        printf("\nStarting Occurrence: %d", first); 
    	//Show the Ending Occurrence of the value in array
        printf("\nEnding Occurrence: %d", last);
	} 
    else
    	//Show the message Value not found in array
        printf("\nValue not found in array");  
    
}
