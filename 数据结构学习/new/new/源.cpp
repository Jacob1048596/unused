#define _CRT_SECURE_NO_WARNINGS 0
#define MAXN 25000
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <time.h>
using namespace std;

typedef struct Node {
	char sign1 = '+';//第一个大整数的符号
	char ctr1[MAXN] = { '\0' };//第一个大整数字符型(正序)
	int itr1[MAXN] = { 0 };//第一个大整数字符型转化为整数型(逆序)
	int Lenctr1;//第一个大整数的长度

	char sign2 = '+';//第二个大整数的符号
	char ctr2[MAXN] = { '\0' };//第二个大整数字符型(正序)
	int itr2[MAXN] = { 0 };//第二个大整数字符型转化为整数型(逆序)
	int Lenctr2;//第二个大整数的长度

	char signresult = '+';//第三个大整数的符号
	char cresult[MAXN] = { '\0' };//经过计算后得到的大整数结构字符型(正序)
	int iresult[MAXN] = { 0 };//结果的整数型(逆序)
	int Lencresult;//结果长度
}Node;

void page__title(char* menu_item) {
	printf("\n\t* * * * * * * * * 大整数运算 * * * * * * * * * *");
	printf("\n\n\t * *          -———-%s-———-          * *\n\n", menu_item);
	printf("\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	printf("* *请输入所需计算的数据：\n\n");
}
void page_title() {
	printf("\n\t* * * * * * * * * * 大整数运算 * * * * * * * * * *\n\n");
	cout << "\t   1.大数-加法-运算           2.大整-减法-运算" << endl << endl;
	cout << "\t   3.大数-乘法-运算                          " << endl;
	printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	cout << "* *请输入你想进行的运算序号：";
}

void Addition(Node& K) {//加法运算
	clock_t startTime, endTime;
	startTime = clock();
	if (K.Lenctr1 < K.Lenctr2) {
		swap(K.sign1, K.sign2);
		swap(K.ctr1, K.ctr2);
		swap(K.Lenctr1, K.Lenctr2);
	}
	else {
		if (strcmp(K.ctr1, K.ctr2) < 0 && K.Lenctr1 == K.Lenctr2) {
			swap(K.sign1, K.sign2);
			swap(K.ctr1, K.ctr2);
		}
	}
	for (int i = K.Lenctr1 - 1, j = 0;i >= 0;i--, j++) {//将ctr1字符型数组转化为整形数组
		K.itr1[j] = K.ctr1[i] - '0';
	}
	for (int i = K.Lenctr2 - 1, j = 0;i >= 0;i--, j++) {//将ctr2字符型数组转化为整形数组
		K.itr2[j] = K.ctr2[i] - '0';
	}
	K.Lencresult = K.Lenctr1;
	for (int i = 0;i < K.Lencresult;i++) {
		K.iresult[i] = K.itr1[i] + K.itr2[i];//进行加法运算
	}
	for (int i = 0;i < K.Lencresult;i++) {//判断是否进位
		if (K.iresult[i] >= 10) {
			K.iresult[i] %= 10;
			K.iresult[i + 1]++;
		}
	}
	int k = 0;//判断K.iresult最后一个数据元素不为0的下标
	for (int i = 0;i <= K.Lencresult;i++) {
		if (K.iresult[i] != 0) k = i;
	}
	for (int i = k, j = 0;i >= 0;i--) {//将整形数组转化为字符型数组
		K.cresult[j++] = K.iresult[i] + '0';
	}
	K.Lencresult = k + 1;
	K.signresult = K.sign1;
	cout << endl << "*计算后的结果为：" << endl << endl;
	cout << K.signresult;
	for (int i = 0;i <= k;i++) {//结果输出
		cout << K.cresult[i];
	}
	cout << endl << endl;
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl << endl;
}

void Subtraction(Node& K) {//大数减法
	clock_t startTime, endTime;
	startTime = clock();
	if (K.Lenctr1 < K.Lenctr2) {
		swap(K.sign1, K.sign2);
		swap(K.ctr1, K.ctr2);
		swap(K.Lenctr1, K.Lenctr2);
		if (K.sign1 == '-') K.sign1 = '+';
		else K.sign1 = '-';
	}
	else {
		if (strcmp(K.ctr1, K.ctr2) < 0 && K.Lenctr1 == K.Lenctr2) {
			swap(K.sign1, K.sign2);
			swap(K.ctr1, K.ctr2);
		}
	}
	for (int i = K.Lenctr1 - 1, j = 0;i >= 0;i--, j++) {//将ctr1字符型数组转化为整形数组
		K.itr1[j] = K.ctr1[i] - '0';
	}
	for (int i = K.Lenctr2 - 1, j = 0;i >= 0;i--, j++) {//将ctr2字符型数组转化为整形数组
		K.itr2[j] = K.ctr2[i] - '0';
	}
	K.Lencresult = K.Lenctr1;
	for (int i = 0;i < K.Lencresult;i++) {
		K.iresult[i] = K.itr1[i] - K.itr2[i];//进行减法运算
	}
	for (int i = 0;i < K.Lencresult;i++) {//判断是否退位
		if (K.iresult[i] < 0) {
			K.iresult[i] += 10;
			K.iresult[i + 1]--;
		}
	}
	int k = 0;//判断K.iresult最后一个数据元素不为0的下标
	for (int i = 0;i <= K.Lencresult;i++) {
		if (K.iresult[i] != 0) k = i;
	}
	for (int i = k, j = 0;i >= 0;i--) {//将整形数组转化为字符型数组
		K.cresult[j++] = K.iresult[i] + '0';
	}
	K.Lencresult = k + 1;
	if (k != 0) {
		if (K.Lenctr1 >= K.Lenctr2) {
			K.signresult = K.sign1;
		}
		else {
			K.signresult = K.sign2;
		}
	}
	else {
		K.signresult = '+';
	}
	cout << endl << "*计算后的结果为：" << endl << endl;
	cout << K.signresult;
	for (int i = 0;i <= k;i++) {//结果输出
		cout << K.cresult[i];
	}
	cout << endl << endl;
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl << endl;
}

void Multiple(Node& K) {//大数乘法
	clock_t startTime, endTime;
	startTime = clock();
	if (K.Lenctr1 < K.Lenctr2) {
		swap(K.sign1, K.sign2);
		swap(K.ctr1, K.ctr2);
		swap(K.Lenctr1, K.Lenctr2);
	}
	else {
		if (strcmp(K.ctr1, K.ctr2) < 0 && K.Lenctr1 == K.Lenctr2) {
			swap(K.sign1, K.sign2);
			swap(K.ctr1, K.ctr2);
		}
	}
	for (int i = K.Lenctr1 - 1, j = 0;i >= 0;i--, j++) {//将ctr1字符型数组转化为整形数组
		K.itr1[j] = K.ctr1[i] - '0';
	}
	for (int i = K.Lenctr2 - 1, j = 0;i >= 0;i--, j++) {//将ctr2字符型数组转化为整形数组
		K.itr2[j] = K.ctr2[i] - '0';
	}
	K.Lencresult = K.Lenctr1 * K.Lenctr1;
	for (int i = 0;i < K.Lenctr1;i++) {
		for (int j = 0;j < K.Lenctr2;j++) {
			K.iresult[i + j] += K.itr1[i] * K.itr2[j];
		}
	}
	for (int i = 0;i <= K.Lencresult;i++) {//判断是否进位
		if (K.iresult[i] >= 10) {//判断数据元素是否大于10
			K.iresult[i + 1] += K.iresult[i] / 10;//如果大于10，则除以10进位
			K.iresult[i] %= 10;
		}
	}
	int k = 0;//判断结果数组中最后一个不为0的数据元素的下标
	for (int i = 0;i <= K.Lencresult;i++) {
		if (K.iresult[i] != 0) k = i;
	}
	for (int i = k, j = 0;i >= 0;i--) {//将整形数组转化为字符型数组
		K.cresult[j++] = K.iresult[i] + '0';
	}
	K.Lencresult = k + 1;
	switch (K.sign1) {//判断最后输出的正负号
	case '-':
		if (K.sign2 == '-') K.signresult = '+';
		else K.signresult = '-';
		break;
	case '+':
		if (K.sign2 == '-') K.signresult = K.sign2;
		else K.signresult = K.sign1;
		break;
	default:
		if (K.sign2 == '-') K.signresult = K.sign2;
		else K.signresult = '+';
	}
	cout << endl << "*计算后的结果为：" << endl << endl;
	cout << K.signresult;
	for (int i = 0;i <= k;i++) {//结果输出
		cout << K.cresult[i];
	}
	cout << endl << endl;
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl << endl;
}

void Charscanf(Node& K) {//数据输入
	char str1[MAXN], str2[MAXN];
	scanf("%s %s", str1, str2);//将第一个数据赋给str1,将第二个数据赋给str2
	int Lenstr1 = strlen(str1), Lenstr2 = strlen(str2);
	if (str1[0] != '-' && str1[0] != '+') {
		strcpy(K.ctr1, str1);
	}
	else {
		K.sign1 = str1[0];
		for (int i = 1, j = 0;i < Lenstr1;i++) {
			K.ctr1[j++] = str1[i];
		}
	}
	if (str2[0] != '-' && str2[0] != '+') {
		strcpy(K.ctr2, str2);
	}
	else {
		K.sign2 = str2[0];
		for (int i = 1, j = 0;i < Lenstr2;i++) {
			K.ctr2[j++] = str2[i];
		}
	}
	K.Lenctr1 = strlen(K.ctr1), K.Lenctr2 = strlen(K.ctr2);
}

int main() {
	Node K;//创建一个结点
	system("color F0");
al:char ch;
	page_title();
	cin >> ch;
	switch (ch) {//选择何种算法
	case '1':system("cls");page__title("加法");Charscanf(K);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Addition(K);
			else Subtraction(K);
			break;
		case '+':
			if (K.sign2 == '-') Subtraction(K);
			else Addition(K);
			break;
		default:
			if (K.sign2 == '-') Subtraction(K);
			else Addition(K);
		}
		break;
	case '2':system("cls");page__title("减法");Charscanf(K);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Subtraction(K);
			else Addition(K);
			break;
		case '+':
			if (K.sign2 == '-') Addition(K);
			else Subtraction(K);
			break;
		default:
			if (K.sign2 == '-') Addition(K);
			else Subtraction(K);
		}
		break;
	case '3':system("cls");page__title("乘法");Charscanf(K);Multiple(K);break;
	default:
		cout << "\n***格式错误，请重新输入！！！\n" << endl;
		Sleep(1500);
		system("cls");
		goto al;
	}
	return 0;
}

