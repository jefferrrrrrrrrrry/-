#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#define ERROR -1
#define OK 1
typedef int Status;
typedef struct Stack1 {
	double data[1000];
	int top;//top是索引，-1代表空栈
} Stack1;
typedef struct Stack2 {
	char data[1000];
	int top;//top是索引，-1代表空栈
} Stack2;
Status Push1(Stack1*, double);//数字栈
Status Pop1(Stack1*, double*);
Status Push2(Stack2*, char);//符号栈
Status Pop2(Stack2*, char*);
Stack1 numstack;//数字栈
Stack2 opstack;//符号栈
char a[1000];
int priority(int a);
double Calculate(double num1, double num2, double old_op);
int main() {
	numstack.top = opstack.top = -1;
	gets(a);
	int flag = 0;
	double num = 0;
	for (int i = 0; a[i] != '\0'; i++) {
		if (a[i] >= '0' && a[i] <= '9') {
			num *= 10;
			num += (double)(a[i] - '0');
			if (a[i + 1] == '.') {
				double t = 0;
				int j = 2;
				for (j = 2; a[j + i] >= '0' && a[i + j] <= '9'; j++) {
					t += (a[i + j] - '0') / pow(10, j - 1);
				}
				num += t;
				i = i + j - 1;
			}
			if (flag == 0)flag = 1;//1为正，2为负，0为非数字 

		} else {
			if (flag == 1) {
				Push1(&numstack, num);
				num = 0;
				flag = 0;
			}
			if (a[i] == '=') {
				while (opstack.top != -1) {
					char old_op;
					double num1, num2;
					Pop2(&opstack, &old_op);
					Pop1(&numstack, &num2);
					Pop1(&numstack, &num1);
					num1 = Calculate(num1, num2, old_op);
					Push1(&numstack, num1);
				}
			} else if (a[i] == '(' && a[i + 1] != '-') {
				Push2(&opstack, a[i]);
			} else if (a[i] == '(' && a[i + 1] == '-') {//计算负数
				flag = 2;
				i++;
			} else if (isspace(a[i]));//过滤空格
			else if (a[i] == ')') {
				if (flag == 2) {
					num *= -1;
					Push1(&numstack, num);
					num = 0;
					flag = 0;
				} else {
					while (1) {
						char old_op;
						double num1, num2;
						Pop2(&opstack, &old_op);
						if (old_op == '(')break;
						Pop1(&numstack, &num2);
						Pop1(&numstack, &num1);
						num1 = Calculate(num1, num2, old_op);
						Push1(&numstack, num1);
					}
				}
			} else {
				if ((opstack.top == -1) || priority(a[i]) > priority(opstack.data[opstack.top])) {
					Push2(&opstack, a[i]);
				} else {
					double num1, num2;
					char old_op;
					Pop2(&opstack, &old_op);
					Pop1(&numstack, &num2);
					Pop1(&numstack, &num1);
					num1 = Calculate(num1, num2, old_op);
					Push1(&numstack, num1);
					Push2(&opstack, a[i]);
				}
			}
		}
	}
	printf("%.2f", numstack.data[0]);
	return 0;
}
int priority(int a) {
	if (a == '+' || a == '-')return 1;
	if (a == '%' || a == '*' || a == '/')return 2;
	if (a == '^')return 3;
	return 0;
}
double Calculate(double num1, double num2, double old_op) {
	if (old_op == '+')num1 = num1 + num2;
	if (old_op == '-')num1 = num1 - num2;
	if (old_op == '*')num1 = num1 * num2;
	if (old_op == '/')num1 = num1 * 1.0 / num2;
	if (old_op == '%')num1 = (int)num1 % (int)num2 * 1.0;
	if (old_op == '^')num1 = pow(num1, num2);
	return num1;
}
Status Push1(Stack1* L, double e) {
	if (L->top == 999)return ERROR;
	L->data[++(L->top)] = e;
	return OK;
}
Status Pop1(Stack1* L, double*e) {
	if (L->top == -1)return ERROR;
	*e = L->data[L->top--];
	return OK;
}
Status Push2(Stack2* L, char e) {
	if (L->top == 999)return ERROR;
	L->data[++(L->top)] = e;
	return OK;
}
Status Pop2(Stack2* L, char*e) {
	if (L->top == -1)return ERROR;
	*e = L->data[L->top--];
	return OK;
}
