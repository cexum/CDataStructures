#include <stdio.h>
#include <stdlib.h>

#define RSIZE	1
#define WORD	16

typedef struct tnode Tnode;

struct tnode {
	char *word;
	int count;
	Tnode *left;
	Tnode *right;
};

int 		scmp(char *, char*);
char		*sdup(char *);
int		slen(char *);
void		scpy(char *, char *, int);
Tnode		*talloc();
Tnode		*addtree(Tnode *, char *);
void		treeprint(Tnode *);
int		getwd(char *, int);
int		isalph(int);
int		getch(int);
void		ungetch();

char		buf[RSIZE];
char		*sp, *ep;
int 		fd;
char		wd[WORD];
Tnode		*root;

int main(int argc, char **argv)
{
	if (!(fd = open(argv[1], 0))) {
		printf("err: open\n");
		return -1;
	}
	while (getwd(wd, fd)) 
		root = addtree(root, wd);
	treeprint(root);
	return 0;
}

Tnode *addtree(Tnode *p, char *w)
{
	int cond;
						
	if (!p) {
		p = talloc();
		p->word = sdup(w);
		p->count = 1;
		p->left = p->right = 0;
	} else if ((cond = scmp(w, p->word)) == 0) 
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

Tnode *talloc(void)
{
	return (Tnode*) malloc(sizeof(Tnode));	
}

void treeprint(Tnode *p)
{
	if (p) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);	
	}
}

int getwd(char *word, int fd)
{
	int c;
	char *w;
	
	for (w = word; !isalph(c = getch(fd)); )
		if (c <= 0)
			goto term;
	for ( ; isalph(c); c = getch(fd))
		*w++ = c;
	ungetch();
term:	*w = 0;
	return word[0];
}

void ungetch()
{
	sp--;
}

int getch(int fd)
{
	if (sp == ep) {
		if ((read(fd, buf, RSIZE)) <= 0) //reconsider
			return 0;		
	sp = buf;
	ep = sp + RSIZE;
	}
	return *sp++;
}

int isalph(int c)
{
	return (c >= 65 && c <= 90 || c >= 97 && c <= 122) ? 1 : 0;
}


void scpy(char *src, char *dst, int len)
{
	int c;

	for (c = 0; c < len; c++)
		dst[c] = src[c];
}

char *sdup(char *s)
{
	char *p;
	int len;

	len = slen(s);
	p = malloc(sizeof(len + 1));
	scpy(s, p, len);
	return p;
}

int slen(char *s)
{
	int n;

	for (n = 0; s[n]; n++)
		;
	return n;
}

int scmp(char *s1, char *s2)
{
	int c;

	for (c = 0; s1[c] == s2[c]; c++)
		if (s1[c] == 0)
			return 0;
	return s1[c] - s2[c];
}

