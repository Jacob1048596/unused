#include<stdio.h>
typedef int ElementType;
void Insert_Sort(ElementType A[], int N)
{
  int i,p,temp;
  for( p=1;p<N;p++)
  {
     temp=A[p];                         //其中的原理需要知晓；扑克牌插牌；
    for(i=p;i>0&&A[i-1]>temp;i--)
    {
      A[i]=A[i-1];
    }
    A[i]=temp;
  }
}
int main()
{
  ElementType a[10]={10,9,8,7,6,5,4,3,2,1};
  int x =10;
  Insert_Sort(a, x);
  for (int i=0;i<10;i++)
   {
    printf("%d\t",a[i] );
   }
 return 0;
}
