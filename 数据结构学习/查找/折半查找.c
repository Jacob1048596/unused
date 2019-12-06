#include<stdio.h>
typedef struct{
  int key;
  int other;
}ElemType;
typedef struct{
  ElemType *R;
  int lengh;
}Stable;
int Half_search(Stable ST,int key)
{
  int low =1;
  int high=ST.lengh;
  while (low<=high)
  {
    int mid=(low+high)/2;
    if (key=ST.R[mid].key)   return mid;
     else if (key<ST.R[mid].key) high=mid-1;
     else low=mid+1;

  }
  return 0;
}

int main()
{
  ElementType a[10]={10,9,8,7,6,5,4,3,2,1};
  int x =10;
  a=Half_search(a,x)
  for (int i=0;i<10;i++)
   {
    printf("%d\t",a[i] );
   }
 return 0;
}
