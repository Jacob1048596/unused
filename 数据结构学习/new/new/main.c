#include<stdio.h>
void InsertSort(int* a, int len) 
{
	int begin = 1;   
	int i = 0;    
	while (begin < len) 
	{
		int key = a[begin]; 
		for (i = begin - 1;i >= 0;i--)
		{
			if (a[i] <= key)    //稳定的 
			{    
				a[i+1] = key;
				break;            
			}            
			a[i+1] = a[i];
		}      
		if(i<0)   
			a[0] = key;//说明找完了整个有序子序列都没找到     
		begin++; 
	}
}
void ShellSort(int* a, int len)
{
	int gap = len;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = gap;i < len;i++)
		{
			int key = a[i];
			int start = i - gap;
			while (start >= 0 && key <= a[start])//对当前key进行一趟直接插入排序
			{
				a[start+gap] = a[start];
				start -= gap;
			}               
			a[start + gap] = key;
		}       
	}  
}
void SelectSort(int* a, size_t len)
{
	int begin = 0;
	int end = len - 1;
	int max = 0;
	int min = 0;
	while (begin < end)
	{
		max = begin, min = begin;
		for (int i = begin;i <= end;i++)
		{
			if (a[i] >= a[max])  //有相同元素时，最大的要找位置相对最后的一个最大的
			{  
				max = i;
			}          
			if(a[i]<a[min])  //最小的要找位置相对最前的一个最小的，这样可以使选择排序算法稳定 
			{              
				min = i;     
			}      
		}      
		if(max == begin && min == end)   
		{          
			swap(a[max],a[end]);  
			continue;       
		}       
		if(max == begin)   
		{         
			swap(a[max],a[end]);
			swap(a[min],a[begin]);  
			continue;     
		}      
		if(min == end)  
		{         
			swap(a[min],a[begin]);  
			swap(a[max],a[end]);  
			continue;      
		}       
		swap(a[min],a[begin]);
		swap(a[max],a[end]); 
		begin++;    
		end--;  
	} 
}
void BubbleSort(int* a, size_t len)
{ 
	int end = len - 1;
	while (end > 0)
	{ 
		bool exchange = false; 
		for (int i = 0;i < end;i++)
		{ 
			if (a[i] > a[i + 1])
			{ 
				swap(a[i], a[i + 1]);
				exchange = true; 
			} 
		}    
		if (exchange == false)  
			return;   
		else    
			exchange = false;    
		end--; 
	} 
}
int QuickSort(int* a, int low, int high) //快速排序
{
	a[0] = a[low];  
	int pivokey = a[low];
	int tlow = low, thigh = high;  // 记录区间  
	while(low<high)
	{      
		while(low<high&&a[high]>=pivokey)
			--high;  
		a[low]=a[high]; 
		while(low<high&&a[low]<=pivokey) 
			++low;     
		a[high]=a[low];  
	}   
	a[low]=a[0]; 
	if(tlow<thigh)
	{   //长度大于1 
		QuickSort(a,tlow,low-1);// 递归对枢轴左边的元素进行快排 
		QuickSort(a,low+1,thigh);  //递归对枢轴右边的位置进行快排
	}	
	return 0;
}    			
int main()
{

	return 0;
}