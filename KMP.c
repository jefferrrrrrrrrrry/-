#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#define OK 1
int Index_KMP(char *S, char *T, int pos);
int get_next(char *T, int *next);
int main() {
	char s[100] = {'\0'};
	char t[100] = {'\0'};
	scanf("%s", s);
	scanf("%s", t);
	printf("%d", Index_KMP(s, t, 0));
	return 0;
}
int Index_KMP(char *S, char *T, int pos) {

	int len_s = strlen(S);
	int len_t = strlen(T);
	int *next = (int*)malloc(sizeof(int) * (strlen(T) + 1));
	get_next(T, next);
	for (int i = 0; i < len_t; i++) {
		printf("%d ", next[i]);
	}
	printf("\n");

	int i = pos, j = 0;
	while (i < len_s && j < len_t) {

		if (S[i] == T[j]) {
			i++;
			j++;
		} else {
			j == 0 ? i++ : (j = next[j]);
		}
	}
	if (j == len_t) return (i - j);
	return -1;
}
int get_next(char *T, int *next) {
	int len = strlen(T);
	for (int i = 0; i < len; i++) {
		int num = i - 1;
		if (i == 0) {
			next[i] = -1;
			continue;
		}
		for (int l = 0; l < num; l++) {
			if (T[l] != T[i - num + l]) {
				num--;
				l = -1;
			}
		}
		next[i] = num;
	}
	return OK;
}
