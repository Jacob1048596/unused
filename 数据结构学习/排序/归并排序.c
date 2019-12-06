// #include<stdio.h>
// #include<stdlib.h>
// typedef int ElementType;
// void Merge(ElementType A[],ElementType tempA[],int low, int mid, int high)
// {
//   int i=low;
//   int j=mid+1;
//   int k=low;
//   while (i<=mid&&j<=high)
//   {
//     if (A[i]<A[j]) tempA[k++]=A[i++];
//     else tempA[k++]=A[j++];
//   }
//   while(i<=mid) tempA[k++]=A[i++];
//   while(j<=high) tempA[k++]=A[j++];
// }
// void Msort(ElementType A[],ElementType tempA[],int L, int Right)
// {
//   int Center;
//   if (L<Right)
//    {
//     Center=(L+Right)/2;
//     Msort(A,tempA,L,Center);
//     Msort(A,tempA,Center+1,Right);
//     Merge(A,tempA,L,Center+1,Right);
//   }
// }
// void Merge_Sort(ElementType A[],int N)
// {
//   ElementType *tempA;
//   tempA=(int*)malloc(N*(sizeof(ElementType*)));
//   if (tempA!=NULL)
//    {
//     Msort(A,tempA,0,N-1);
//     free(tempA);
//   }
// }
// int main()
// {
//   ElementType a[10]={10,9,8,7,6,5,4,3,2,1};
//   int x =10;
//   Merge_Sort(a,x);
//   for (int i=0;i<10;i++)
//    {
//     printf("%d\t",a[i] );
//    }
//  return 0;
// }
#include <stdlib.h>
#include <stdio.h>

void Merge(int sourceArr[],int tempArr[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j=midIndex+1, k = startIndex;
    while(i!=midIndex+1 && j!=endIndex+1)
    {
        if(sourceArr[i] > sourceArr[j])
            tempArr[k++] = sourceArr[j++];
        else
            tempArr[k++] = sourceArr[i++];
    }
    while(i != midIndex+1)
        tempArr[k++] = sourceArr[i++];
    while(j != endIndex+1)
        tempArr[k++] = sourceArr[j++];
    for(i=startIndex; i<=endIndex; i++)
        sourceArr[i] = tempArr[i];
}

//内部使用递归
void MergeSort(int sourceArr[], int tempArr[], int startIndex, int endIndex)
{
    int midIndex;
    if(startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex-startIndex) / 2;//避免溢出int
        MergeSort(sourceArr, tempArr, startIndex, midIndex);
        MergeSort(sourceArr, tempArr, midIndex+1, endIndex);
        Merge(sourceArr, tempArr, startIndex, midIndex, endIndex);
    }
}

int main(int argc, char * argv[])
{
    int a[8] = {50, 10, 20, 30, 70, 40, 80, 60};
    int i, b[8];
    MergeSort(a, b, 0, 7);
    for(i=0; i<8; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
