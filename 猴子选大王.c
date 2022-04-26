#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef int Elem;
typedef struct Node {
	Elem data;
	struct Node* next;
} Node, *Linklist;
int n, m, q;
int main() {
	Linklist Head = (Linklist)malloc(sizeof(Node));
	Linklist p, r;
	p = Head;
	Head->next = NULL;
//=============================================================
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		r = (Linklist)malloc(sizeof(Node));
		r->data = i;
		p->next = r;
		r->next = NULL;
		p = p->next;
	}
	p->next = Head->next;
//==============================================================
	p = Head;
	for (int i = 0; i < q; i++) {
		p = p->next;
	}
//==============================================================
	for (int i = 0; i < n-1; i++) {
		for (int i = 0; i < m - 2; i++) {
			p = p->next;
		}
		Linklist t;
		t=p->next;
		p->next=t->next;
		free(t);
		p=p->next;
		/*s = p;
		l=p->next;
		p = p->next->next;
		s->next = p;
		free(l);*/
	}
	for (int i = 0; i < m - 2; i++) {
		p = p->next;
	}
//==============================================================
	printf("%d ", p->data);
	return 0;
}
