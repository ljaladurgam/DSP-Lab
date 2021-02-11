/* Write a program to implement Tower of Hanoi without recursion.*/
#include<conio.h>
#include<stdio.h>
/* Non-Recursive Function*/
void hanoiNonRecursion(int num,char sndl,char indl,char dndl)
{
  char stkn[50],stksndl[50],stkindl[50],stkdndl[50],stkadd[50],temp;
  int top,add;
  top = NULL;
  one:
    if(num==1)
    {
      printf("\nMove top disk from Tower %c to Tower %c ",sndl,dndl);
      goto four;
    }
  two:
    top=top+1;
    stkn[top]=num;
    stksndl[top]=sndl;
    stkindl[top]=indl;
    stkdndl[top]=dndl;
    stkadd[top]=3;
    num=num-1;
    sndl=sndl;
    temp=indl;
    indl=dndl;
    dndl=temp;
    goto one;
  three:
    printf("\nMove top disk from Tower %c to Tower %c ",sndl,dndl);
    top=top+1;
    stkn[top]=num;
    stksndl[top]=sndl;
    stkindl[top]=indl;
    stkdndl[top]=dndl;
    stkadd[top]=5;
    num=num-1;
    temp=sndl;
    sndl=indl;
    indl=temp;
    dndl=dndl;
    goto one;
  four:
    if(top==NULL)
      return;
    num=stkn[top];
    sndl=stksndl[top];
    indl=stkindl[top];
    dndl=stkdndl[top];
    add=stkadd[top];
    top=top-1;
    if(add==3)
      goto three;
    else if(add==5)
      goto four;
}

void main()
{
  printf("\n*********Implement Tower of Hanoi without recursion*********");  
  printf("\n---------------------------------------------------------------------------\n");  
  int no; 
  printf("Enter the no. of disks to be transferred:");
  scanf("%d",&no);
  if(no>=1)
  {
     printf("Below are the movements(without recursion):");
     hanoiNonRecursion(no,'1','2','3'); 
  }
  else
  {
     printf("\nInvalid value.\n");
  }
}
