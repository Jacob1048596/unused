typedef int status;
typedef char Elem;
#define OK 0
#define ERROR -1
#define MAXN 25000

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
using namespace std;

typedef struct StackNode {
	Elem data;
	struct StackNode* next;
}StackNode, * LinkStack;

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

void InitNode(Node& K) {//结点初始化
	K.sign1 = '+';
	memset(K.ctr1, '\0', sizeof(K.ctr1));
	memset(K.itr1, 0, sizeof(K.itr1));
	K.Lenctr1 = 0;

	K.sign2 = '+';
	memset(K.ctr2, '\0', sizeof(K.ctr2));
	memset(K.itr2, 0, sizeof(K.itr2));
	K.Lenctr2 = 0;

	K.signresult = '+';
	memset(K.cresult, '\0', sizeof(K.cresult));
	memset(K.iresult, 0, sizeof(K.iresult));
	K.Lencresult = 0;
}

void page__title(char* menu_item) {
	printf("\n\t* * * * * * * * * 大整数运算 * * * * * * * * * *");
	printf("\n\n\t * *          -———-%s-———-          * *\n\n", menu_item);
	printf("\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	printf("* *请输入所需计算的数据：\n\n");
}
void page_title() {
	printf("\n\t* * * * * * * * * * 大整数运算 * * * * * * * * * *\n\n");
	cout << "\t   1.大数-加法-运算           2.大整-减法-运算" << endl << endl;
	cout << "\t   3.大数-乘法-运算           4.大整-除法-运算" << endl << endl;
	cout << "\t   5.大数表达式运算           6.大数-进制转化-" << endl << endl;
	cout << "\t   7.大数-阶乘-运算                          " << endl;
	printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	cout << "* *请输入你想进行的运算序号：";
}

status InitStack(LinkStack& S) {//链栈的初始化
	S = NULL;
	return OK;
}

status Push(LinkStack& S, Elem  e) {//链栈的入栈
	LinkStack p = (LinkStack)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}

status Pop(LinkStack& S, Elem& e) {//链栈的出栈
	LinkStack p;
	if (S == NULL) return ERROR;
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return OK;
}

char GetTop(LinkStack S) {//取栈顶元素
	if (S != NULL) return S->data;
}

status StackEmpty(LinkStack S)
{
	if (S == NULL) return 1;
	else return 0;
}

void DestroyStack(LinkStack& S) {//销毁链栈
	LinkStack p = S->next, q = S;
	while (p != NULL) {
		free(q);
		q = p;
		p = p->next;
	}
	free(p);
}

void TraverStack(LinkStack S) {//链栈的递归遍历显示
	if (S) {
		cout << S->data;
		TraverStack(S->next);
	}
}

int In(char ch) {//判断ch是否为运算符，是的话返回1不是返回0
	switch (ch) {
	case '-':return 1;
	case '+':return 1;
	case '*':return 1;
	case '/':return 1;
	case '(':return 1;
	case ')':return 1;
	case '#':return 1;
	default:return 0;
	}
}

char Precede(char ch1, char ch2) {//优先级比较
	int a1 = ch1 - '#', a2 = ch2 - '#';
	char sign[13][13] = {
	  {'=',' ',' ',' ',' ','<','<','<','<',' ','<',' ','<'},
	  {},
	  {},
	  {},
	  {},
	  {' ',' ',' ',' ',' ','<','=','<','<',' ','<',' ','<'},
	  {'>',' ',' ',' ',' ',' ','>','>','>',' ','>',' ','>'},
	  {'>',' ',' ',' ',' ','<','>','>','>',' ','>',' ','>'},
	  {'>',' ',' ',' ',' ','<','>','<','>',' ','>',' ','<'},
	  {},
	  {'>',' ',' ',' ',' ','<','>','<','>',' ','>',' ','<'},
	  {},
	  {'>',' ',' ',' ',' ','<','>','>','>',' ','>',' ','>'},
	};
	return sign[a1][a2];
}

void Addition(Node& K, int s) {//加法运算
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
	if (s == 0) {
		cout << endl << "*计算后的结果为：" << endl << endl;
		cout << K.signresult;
		for (int i = 0;i <= k;i++) {//结果输出
			cout << K.cresult[i];
		}
		cout << endl << endl;
	}
}

void Subtraction(Node& K, int s) {//大数减法
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
	if (s == 0) {
		cout << endl << "*计算后的结果为：" << endl << endl;
		cout << K.signresult;
		for (int i = 0;i <= k;i++) {//结果输出
			cout << K.cresult[i];
		}
		cout << endl << endl;
	}
}

void Multiple(Node& K, int s) {//大数乘法
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
	if (s == 0) {
		cout << endl << "*计算后的结果为：" << endl << endl;
		cout << K.signresult;
		for (int i = 0;i <= k;i++) {//结果输出
			cout << K.cresult[i];
		}
		cout << endl << endl;
	}
}

void Division(Node& K, int s) {//大数除法运算
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
	char zsign = K.signresult;//最终结果商的符号位
	char bsign = K.sign1;//最终余数的符号位
	if (K.Lenctr1 < K.Lenctr2 || K.Lenctr1 == K.Lenctr2 && strcmp(K.ctr1, K.ctr2) < 0) {//若是数据1的长度小于数据2的长度或者数据1和数据2的长度相同且数据1数值小于数据2数值
		K.cresult[0] = '0';
		K.Lencresult = 1;
		if (s == 2) {
			cout << endl << "*计算后的结果为：" << endl << endl;
			cout << "商：" << K.signresult << K.cresult << endl << endl;
			cout << "余数：" << bsign << K.ctr1 << endl << endl;
		}
	}
	else {
		if (K.ctr2[0] == '0') {
			K.cresult[0] = '0';
			K.Lencresult = 1;
			if (s == 2) {
				cout << endl << "*计算后的结果为：" << endl << endl;
				cout << "商：" << K.signresult << K.cresult << endl << endl;
				//cout << "余数：" << bsign << "0" << endl << endl;
			}
			exit(0);
		}
		char str[MAXN];//被除数
		strcpy(str, K.ctr1);
		int Lenstr = K.Lenctr1;
		char signstr = K.sign1;

		char str1[MAXN];//被除数
		int Lenstr1 = K.Lenctr1;
		strcpy(str1, K.ctr1);
		K.sign1 = '+';

		char str2[MAXN];//除数
		int Lenstr2 = K.Lenctr2;
		strcpy(str2, K.ctr2);
		K.sign2 = '+';

		char result[MAXN] = { '0' };//商
		int Lenresult;

		char result1[MAXN];//余数

		char result2[MAXN];
		int Lenresult2;

		while (1) {
			Subtraction(K, s);//大数相减
			strcpy(str1, K.cresult);//将经过减法运算后的结果赋给字符串str1
			Lenstr1 = K.Lencresult;
			if (Lenstr1 < Lenstr2 || Lenstr1 == Lenstr2 && strcmp(str2, str1) == 1) {//判断是否继续运算
				InitNode(K);//初始化
				K.ctr2[0] = '1';//将1赋给字符串ctr2，进行下一次运算
				K.Lenctr2 = 1;//将字符串ctr2的长度赋为1
				strcpy(K.ctr1, result);//将字符串result的内容赋给字符串ctr1
				K.Lenctr1 = strlen(result);//将result的长度赋给Lenctr1
				Addition(K, s);//将商的整形数值内容+1
				strcpy(result, K.cresult);//计算后的结果重新赋给字符串result
				Lenresult = K.Lencresult;
				break;
			}
			InitNode(K);//初始化
			K.ctr2[0] = '1';//将1赋给字符串ctr2，进行下一次运算
			K.Lenctr2 = 1;//将字符串ctr2的长度赋为1
			strcpy(K.ctr1, result);//将字符串result的内容赋给字符串ctr1
			K.Lenctr1 = strlen(result);//将result的长度赋给Lenctr1
			Addition(K, s);//将商的整形数值内容+1
			strcpy(result, K.cresult);//计算后的结果重新赋给字符串result
			Lenresult = K.Lencresult;
			InitNode(K);//结点初始化
				  //为下一次计算做准备
			strcpy(K.ctr1, str1);
			K.Lenctr1 = strlen(str1);
			strcpy(K.ctr2, str2);
			K.Lenctr2 = strlen(str2);
		}
		K.signresult = zsign;
		if (s == 2) {//判断结果是否进行输出,若输出则计算
			cout << endl << "*计算后的结果为：" << endl << endl;
			cout << "商：" << K.signresult << K.cresult << endl << endl;
			InitNode(K);//结点初始化
			strcpy(K.ctr1, result);
			K.sign1 = '+';
			strcpy(K.ctr2, str2);
			K.sign2 = '+';
			K.Lenctr1 = strlen(K.ctr1), K.Lenctr2 = strlen(K.ctr2);
			Multiple(K, s);//大数乘法
			strcpy(result2, K.cresult);
			Lenresult2 = K.Lencresult;
			InitNode(K);//节点初始化
			K.sign1 = '+';
			strcpy(K.ctr1, str);
			K.Lenctr1 = Lenstr;
			K.sign2 = '+';
			strcpy(K.ctr2, result2);
			K.Lenctr2 = Lenresult2;
			Subtraction(K, s);//大数相减
			cout << "余数：" << bsign << K.cresult << endl << endl;
		}
	}
}

void Into() {//十进制转化为二进制，字符数组中数据皆为倒序
	char str[MAXN];
al:cin >> str;
	if (In(str[0])) {//格式错误，重新输入
		cout << "\n***格式错误，请重新输入！！！" << endl << endl;
		Sleep(1500);
		system("cls");
		page__title("进制转化");
		goto al;
	}
	int len = strlen(str);//计算str字符串长度
	char binary[10][6] = { "00000","10000","01000","11000","00100","10100","01100","11100","00010","10010" };//二进制表
	char result2[MAXN] = { '0' };//定义字符数组result2，初始化为'0'
	char result1[MAXN] = { '0' };//定义字符数组result1，初始化为'0'
	strcpy(result2, binary[(str[0] - '0')]);//将二进制表中所对应字符串赋给result2
	for (int i = 0;i < len - 1;i++) {
		strcpy(result1, result2);//使result1与result2字符串相同
		//起：给result最左边增添00
		for (int k = strlen(result2);k >= 0;k--) {
			result2[k + 2] = result2[k];
		}
		result2[0] = '0';
		result2[1] = '0';
		//止
		for (int j = 0;j < strlen(result1);j++) {//相同字符串错位相加
			result2[j] = ((result2[j] - '0') + (result1[j] - '0')) + '0';
		}
		for (int j = 0;j < strlen(result2);j++) {//判断字符串中是否有大于2的字符出现，若有，则给当前位赋'0',前一位加'1'
			if (result2[j] >= '2') {
				if (result2[j] == '2') result2[j] = '0';
				else result2[j] = '1';
				if (result2[j + 1] == NULL) result2[j + 1] = '0';
				result2[j + 1] = ((result2[j + 1] - '0') + 1) + '0';
			}
		}
		//起：给result最左边增添0
		for (int k = strlen(result2);k >= 0;k--) {
			result2[k + 1] = result2[k];
		}
		result2[0] = '0';
		//止
		for (int j = 0;j < 5;j++) {//加下一位数字的二进制数码
			result2[j] = ((result2[j] - '0') + (binary[(str[i + 1] - '0')][j] - '0')) + '0';
		}
		for (int j = 0;j < strlen(result2);j++) {//判断字符串中是否有大于2的字符出现，若有，则给当前位赋'0',前一位加'1'
			if (result2[j] >= '2') {
				if (result2[j] == '2') result2[j] = '0';
				else result2[j] = '1';
				if (result2[j + 1] == NULL) result2[j + 1] = '0';
				result2[j + 1] = ((result2[j + 1] - '0') + 1) + '0';
			}
		}
	}
	int num = 0;//记录字符数组最后一位不为'0'的下标
	for (int i = 0;i < strlen(result2);i++) {//判断字符数组最后一位不为'0'的下标
		if (result2[i] == '1') num = i;
	}
	cout << endl << "*计算后的结果为：" << endl << endl;
	for (int i = num;i >= 0;i--) {//字符串倒序输出
		cout << result2[i];
	}
	cout << endl << endl;
}

void Operate(char sign, Node& K, int s) {//进行运算
	switch (sign) {
	case '+':s = 1;//Subtraction(K,s);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
			break;
		case '+':
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
			break;
		default:
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
		}
		break;
	case '-':s = 1;//Addition(K,s);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
			break;
		case '+':
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
			break;
		default:
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
		}
		break;
	case '*':s = 1;Multiple(K, s);break;
	case '/':s = 1;Division(K, s);break;
	}
}


void EvalauteExpression(Node& K, int s) {
	char ch, ch1, a, b, x, theta;
	LinkStack OPTR, OPND;//OPTR寄存运算栈;OPND寄存操作数或运算结果
	InitStack(OPTR);//初始化栈 #*#
	InitStack(OPND);//初始化栈 #56*-56# 562-562
	cin >> ch;
	Push(OPTR, ch);//#入栈
	cin >> ch;
	if (ch == '-') {
		Push(OPND, ch);
		cin >> ch;
	}
	int count = 0;//记录每个数据的数字位数
	while (ch != '#' || GetTop(OPTR) != '#') {
		if (!In(ch)) {//不是运算符返回0是得话返回1
			Push(OPND, ch);//数字入栈（OPND）
			cin >> ch;//下一个字符输入
			ch1 = ch;
			count++;//如果为数字，则icount+1
		}
		else {
			if (count != 0) Push(OPND, (count + '0'));//如果数字位数不为0，则入栈（OPND）
			count = 0;//入栈后初始化
			switch (Precede(GetTop(OPTR), ch)) {
			case '<': {
				Push(OPTR, ch);//非数字或为运算符入栈（OPTR）
				cin >> ch;
				if (ch1 == '-' && ch1 == ch || In(ch1) == 1 && ch == '-') {
					if (ch1 == '-' && ch1 == ch) {
						Push(OPND, ch1);
					}
					else {
						Push(OPND, ch);
					}
					cin >> ch;
				}
				ch1 = ch;
				break;}
			case '>': {//如果优先级为 >，则提取数据元素进行计算，再将计算后的结果再次入栈（OPND）
				Pop(OPTR, theta);//输出需要进行何种运算的运算符
				Pop(OPND, a);//计数元素出栈
				K.Lenctr1 = a - '0';
				for (int i = K.Lenctr1 - 1;i >= 0;i--) {//将数据存入K.itr1
					Pop(OPND, K.ctr1[i]);
				}
				if (GetTop(OPND) == '-') Pop(OPND, K.sign1);
				Pop(OPND, b);//计数元素出栈
				K.Lenctr2 = b - '0';
				for (int i = K.Lenctr2 - 1;i >= 0;i--) {//将数据存入K.itr2
					Pop(OPND, K.ctr2[i]);
				}
				if (GetTop(OPND) == '-') Pop(OPND, K.sign2);//取出符号位
				swap(K.sign1, K.sign2);
				swap(K.ctr1, K.ctr2);
				swap(K.Lenctr1, K.Lenctr2);
				Operate(theta, K, s);//判断何种运算，并调用函数进行实现
				int number = 0;//判断进栈位数
				if (K.signresult == '-') Push(OPND, K.signresult);//取出符号位
				for (int i = 0;i < K.Lencresult;i++) {//计算后的结果入栈
					Push(OPND, K.cresult[i]);
					number++;
				}
				//cout << number << endl;
				Push(OPND, (number + '0'));
				number = 0;
				InitNode(K);
				break;}
			case '=': {
				Pop(OPTR, x);//非数字或为运算符入栈（OPTR）
				cin >> ch;
				if (ch1 == '-' && ch1 == ch || In(ch1) == 1 && ch == '-') {
					if (ch1 == '-' && ch1 == ch) {
						Push(OPND, ch1);
					}
					else {
						Push(OPND, ch);
					}
					cin >> ch;
				}
				ch1 = ch;
				break;}
			}
		}
	}
	char ch2, result[MAXN];
	char num;
	Pop(OPND, num);
	int clen = (num - '0');
	for (int i = clen - 1;i >= 0;i--) {
		Pop(OPND, result[i]);
	}
	if (GetTop(OPND) == '-') Pop(OPND, ch2);
	cout << endl << "*计算后的结果为：" << endl << endl;
	if (ch2 == '-') cout << ch2;
	cout << result << endl << endl;
}

void Factorial() {//求阶乘
	long long a[25000];//储存每一位所得到的数
	int temp, digit, n, i, j = 0;//temp每次的得数   digit每次得数的位数
	scanf("%d", &n);
	a[0] = 1;//从1开始乘
	digit = 1;//位数从第一位开始
	for (i = 2;i <= n;i++)
	{
		int num = 0;
		for (j = 0;j < digit;j++)
		{
			temp = a[j] * i + num;//将一个数的每一位数都分别乘以i，
			a[j] = temp % 10;//将一个数的每一位数利用数组进行储存
			num = temp / 10;
		}
		while (num)//判断退出循环后，num的值是否为0
		{
			a[digit] = num % 10;//继续储存
			num = num / 10;
			digit++;
		}
	}
	cout << endl << "*计算后的结果为：" << endl << endl;
	for (i = digit - 1;i >= 0;i--)//倒序输出每一位
		printf("%d", a[i]);
	printf("\n\n");
}

void power(Node& K) {

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
	int s = 0;//判断运算结果是否进行输出，若s为0，则输出，为非0值，则不予以输出
al:char ch;
	page_title();
	cin >> ch;
	switch (ch) {//选择何种算法
	case '1':system("cls");page__title("加法");InitNode(K);Charscanf(K);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
			break;
		case '+':
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
			break;
		default:
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
		}
		break;
	case '2':system("cls");page__title("减法");InitNode(K);Charscanf(K);
		switch (K.sign1) {
		case '-':
			if (K.sign2 == '-') Subtraction(K, s);
			else Addition(K, s);
			break;
		case '+':
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
			break;
		default:
			if (K.sign2 == '-') Addition(K, s);
			else Subtraction(K, s);
		}
		break;
	case '3':system("cls");page__title("乘法");InitNode(K);Charscanf(K);Multiple(K, s);break;
	case '4':system("cls");page__title("除法");InitNode(K);s = 2;Charscanf(K);Division(K, s);break;
	case '5':system("cls");page__title("表达式求值");cout << "请以此格式输入：#...表达式...#" << endl << endl;InitNode(K);EvalauteExpression(K, s);break;
	case '6':system("cls");page__title("进制转化");InitNode(K);Into();break;
	case '7':system("cls");page__title("阶乘");cout << "可计算数据范围(1~50000)" << endl << endl;Factorial();break;
	default:
		cout << "\n***格式错误，请重新输入！！！\n" << endl;
		Sleep(1500);
		system("cls");
		goto al;
	}
	return 0;
}

