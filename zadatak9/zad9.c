#include <stdio.h>
#include <stdlib.h>

typedef struct stablo *poz;
struct stablo
{
	int el;
	poz lijevo;
	poz desno;
};

poz Unos(poz, poz);
int IspisInOrder(poz);
poz Trazi(poz, int);
poz Brisi(poz, int);
poz TraziMIN(poz);
poz TraziMAX(poz);

int main(void)
{
	poz root=NULL;
	poz clan=(poz)malloc(sizeof(struct stablo));
	clan->el = 4;
	clan->desno = NULL;
	clan->lijevo = NULL;

	root = Unos(root, clan);
	root = Brisi(root, 5);
	Trazi(root, 14);
	IspisInOrder(root);

	return 0;
}

poz Unos(poz p, poz q)
{
	if (NULL == p)
		return q;
	if (p->el > q->el)
		p->lijevo = Unos(p->lijevo, q);
	else if (p->el < q->el)
		p->desno = Unos(p->desno, q);
	else
	{
		printf("Greska! Element %d se ponavlja!\n", q->el);
		free(q);
	}
	return p;

}

int IspisInOrder(poz p)
{
	if (NULL == p)
		return 0;
	IspisInOrder(p->lijevo);
	printf("%d", p->el);
	IspisInOrder(p->desno);
	return 0;
}

poz Trazi(poz p, int broj)
{
	if (p == NULL)
	{
		printf("Greska! Broj nije pronaden!\n");
		return NULL;
	}
	if (p->el == broj)
		return p;
	else if (p->el > broj)
		return Trazi(p->lijevo, broj);
	else
		return Trazi(p->desno, broj);
}

poz Brisi(poz p, int broj)
{
	if (NULL == p)
		return NULL;
	if (p->el == broj)
	{
		if (p->lijevo != NULL)
		{
			poz q = TraziMAX(p->lijevo);
			p->el = q->el;
			p->lijevo = Brisi(p->lijevo, q->el);
		}
		else if (p->desno != NULL)
		{
			poz q = TraziMIN(p->desno);
			p->el = q->el;
			p->desno = Brisi(p->desno, q->el);
		}
		else
		{
			free(p);
			return NULL;
		}
	}
	else if (p->el > broj)
		p->lijevo = Brisi(p->lijevo, broj);
	else
		p->desno = Brisi(p->desno, broj);
	return p;
}

poz TraziMAX(poz p)
{
	if (NULL == p)
		return NULL;
	while (p->desno != NULL)
		p = p->desno;
	return p;
}

poz TraziMIN(poz p)
{
	if (NULL == p)
		return NULL;
	while (p->lijevo != NULL)
		p = p->lijevo;
	return p;
}