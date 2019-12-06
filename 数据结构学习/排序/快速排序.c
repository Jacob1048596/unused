#include<stdio.h>
typedef int ElementType;
int partition(ElementType A[],int low,int high)
{
  A[0]=A[low];
  int p=A[low];
  while (low<high) {
    while(low<high&&A[high]>=p) --high;
    A[low]=A[high];
    while (low<high&&A[low]<=p) ++low;
    A[high]=A[low];
  }
  A[low]=A[0];
  return low;
}
void Qsort(ElementType A[],int low ,int high)
{
  if (low<high) {
    int p=partition(A,low,high);
    Qsort(A,low,p-1);
    Qsort(A,p+1,high);
  }
}
void Quick_Sort(ElementType A[], int N)
{
  Qsort(A,1,N);
}
int main()
{
  ElementType a[10]={1,5,9,3,7,2,8,4,6,10};
  int x =10;
  Quick_Sort(a, x);
  for (int i=0;i<10;i++)
   {
    printf("%d\t",a[i] );
   }
 return 0;
}
