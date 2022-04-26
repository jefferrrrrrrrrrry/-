#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
typedef char Elem;
typedef struct Node {
	Elem data;
	struct Node* next;
} Node, *Linklist;
char s[50];
int key[127];
int main() {
	gets(s);
	int len = strlen(s);
	Linklist p;
	Linklist Head = (Linklist)malloc(sizeof(Node));
	p = Head;
	Head->next = NULL;
	for (int i = 0; i < len; i++) {
		if(!(s[i]<=126&&s[i]>=32))continue;
		int flag = 1;
		for (int j = 0; j < i; j++) {
			if (s[i] == s[j])flag = 0;
		}
		if (flag) {
			Linklist t = (Linklist)malloc(sizeof(Node));
			t->data = s[i];
			p->next = t;
			t->next = NULL;
			p = p->next;
		}
	}
	for (char i = 32; i <= 126; i++) {
		int flag = 1;
		for (int j = 0; j < len; j++) {
			if (s[j] == i)flag = 0;
		}
		if (flag) {
			Linklist t = (Linklist)malloc(sizeof(Node));
			t->data = i;
			p->next = t;
			t->next = NULL;
			p = p->next;
		}
	}
	p->next = Head->next;
	//===================================================
	p = Head;
	char first=Head->next->data;
	for (int i = 0; i <= (126 - 32); i++) {
		p = p->next;
	}
	int num = p->next->data;
	Linklist q;
	q = p->next;
	p->next = q->next;
	p = q->next;
	free(q);
	for (int i = 0; i < num - 2; i++) {
		p = p->next;
	}
	key[num]=p->next->data;
	for (int i = 0; i < (126 - 32) - 1; i++) {
		int num = p->next->data;
		Linklist q;
		q = p->next;
		p->next = q->next;
		p = q->next;
		
		free(q);
		for (int i = 0; i < num - 2; i++) {
			p = p->next;
		}
		key[num]=p->next->data;
	}
	key[(int)p->next->data]=first;
	//===============================================
	FILE *in=fopen("in.txt","r");
	FILE *out=fopen("in_crpyt.txt","w");
	if(in==NULL||out==NULL)printf("no");
	char l;
	while((l=fgetc(in))!=EOF){
		if(l<=126&&l>=32)fputc(key[(int)l],out);
		else fputc(l,out);
	}
	fclose(in);
	fclose(out);
	return 0;
}
