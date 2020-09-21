#include <stdio.h>
#include <stdlib.h>

typedef struct llist Llist;

struct llist {
	int c;
	Llist *next;
	Llist *prev;
};

Llist	*newlnode(int);
Llist	*lalloc();
Llist	*inserthead(Llist *, int);
Llist 	*inserttail(Llist *, int);
Llist	*insertprev(Llist *, int);
Llist   *insertnext(Llist *, int);
Llist   *addlist(Llist *, int);
Llist	*llookup(Llist *, int);
void	deletelnode(Llist *);
void	lprintfwrd(Llist *);
void	lprintrevr(Llist *);

Llist	*head;
Llist	*tail;
Llist	*list;

void main()
{

	list = addlist(list, 2);
	list = addlist(list, 5);
	list = addlist(list, 3);
	list = addlist(list, 7);
	list = addlist(list, 1);
	list = addlist(list, 8);
	list = addlist(list, 10);
	list = addlist(list, 1);

	list = addlist(list, 5);
	list = addlist(list, 2);
	list = addlist(list, 3);
	list = addlist(list, 6);
	list = addlist(list, 1);
	list = addlist(list, 4);
	inserthead(list, 11);
	insertnext(tail, 0);
	
	insertnext(list, 98);
	insertprev(list, -99);
	insertnext(list, 97);
	printf("forward\n");
	lprintfwrd(head);
	printf("reverse\n");
	lprintrevr(tail);
	deletelnode(head);
	deletelnode(tail);
	deletelnode(head->next->next);
	printf("forward\n");
	lprintfwrd(head);
	if (llookup(head, 3))
		printf("node present\n");
	if (!llookup(head, 99))
		printf("node absent\n");
	printf("forward\n");
	lprintfwrd(head);
	printf("reverse\n");
	lprintrevr(tail);
	Llist *p = llookup(head, 4);
	printf("p->c: %d\n", p->c);
	
}

void lprintrevr(Llist *l)
{
	if (l) {
		printf("num: %5d\n", l->c);
		lprintrevr(l->prev);
	}
}

void lprintfwrd(Llist *l)
{
	if (l) {
		printf("num: %5d\n", l->c);
		lprintfwrd(l->next);
	}
}

void deletelnode(Llist *l)
{
	if (l == head) {
		head = l->next;
		head->prev = 0;
	} else if (l == tail) {
		tail = l->prev;
		tail->next = 0;
	} else {
		l->prev->next = l->next;
		l->next->prev = l->prev;
	}
	free(l);	
}

Llist *llookup(Llist *l, int c)
{
	return (!l || l->c == c) ? l : llookup(l->next, c);
}	

Llist *inserthead(Llist *l, int c)
{
	Llist *new;

	new = newlnode(c);
	new->next = l;
	l->prev = new;
	head = new;
	return new;
}

Llist *insertnext(Llist *l, int c)
{
	Llist *new;
	
	if (!l->next) //pushing to tail
		return new = inserttail(l, c);
	new = newlnode(c);
	new->next = l->next;
	l->next = new;
	new->prev = l;
	new->next->prev = new;
	return new;
}

Llist *insertprev(Llist *l, int c)
{
	Llist *new;

	if (!l->prev) //pushing to head
		return new = inserthead(l, c);
	new = newlnode(c);
	new->prev = l->prev;
	l->prev = new;
	new->next = l;
	new->prev->next = new;
	return new;
}

Llist *inserttail(Llist *l, int c)
{
	Llist *new;

	new = newlnode(c);
	new->prev = l;
	l->next = new;
	tail = new;
	return l;
}

Llist *addlist(Llist *l, int c)
{	
	if (!head) {
		l = newlnode(c);
		head = l;
	} else if (l->c < c) 
		l = insertprev(l, c);
	else if (!l->next) 
		l = insertnext(l, c); 	
	else 
		l->next = addlist(l->next, c);	
	return l;
}

Llist *lalloc()
{
	return (Llist *) malloc(sizeof(Llist));
}

Llist *newlnode(int c)
{
	Llist *new;
	
	new = lalloc();
	new->c = c;
	new->next = 0;
	new->prev = 0;
	return new;
}
