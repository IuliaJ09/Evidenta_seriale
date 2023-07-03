//realiazati un program in C care tine evidenta serialelor vizualizate. Fiecare serial este caracterizat din
//nume,producator si nr de episoade. Realizati un meniu interactiv cu urmatoarele optiuni:
//1.Adaugare unui serial intr-o lista folosind algoritmul de inserare in spate
//2.Afisarea serialelor
//3.cautarea tuturor serialelor care au numar de ep mai mic decat un nr dat de utilizator de la tastatura
//4.Calcularea sumei nr de episoade a tuturor serialelor si reprezentarea acesteia in forma binara
//5.Salvarea intr-un fisier text cu numele dat de utilizator a tuturor serialelor care apartin producatorului cu numele
//Mihai 0.iesire obs:numele serialului este considerat citit corect daca are cel putin 3 caractere si
//contine doar litere mici; nr de episoade este dat automat fiind egal cu formula 10*nr.Caractere.producator
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef  struct serial
{
	char * nume;
	char producator[20];
	int episoade;
	struct serial* urm;
}S;
int validare(char s[20])
{
	int ok = 0,i;
	if (strlen(s) < 3)
		return 0;
	else
		for (i = 0; i < strlen(s); i++)
			if (s[i] >= 'A' && s[i] <= 'Z')
				return 0;
				
	return 1;
}
S* adaugare(S* prim)
{
	S* p,*q;
	
	
	char num[20],pro[20];
	int ep;
	do
	{
		printf("Introduceti nume serial:");
		scanf("%s", num);
	}
	while (!validare(num));
	printf("Introduceti nume producator:");
	scanf("%s", pro);
	ep = strlen(pro) * 10;
	p = (S*)malloc(sizeof(S));
	p->nume = (char*)malloc(strlen(num)+1);
	strcpy(p->nume, num);
	strcpy(p->producator, pro);
	p->episoade = ep;
	p->urm = NULL;
	if (prim == NULL)
	{
		p->urm = prim;
		return p;
	}
	else
	{
		q = prim;
		while (q->urm != NULL)
			q = q->urm;
		p->urm = q->urm;
		q->urm = p;
		return prim;
	}
}
void afisare(S* prim)
{
	S* p = prim;
	while (p != NULL)
	{
		printf("%s \n", p->nume);
		printf("%s \n", p->producator);
		printf("%d \n", p->episoade);
		p = p->urm;

	}
}
void cautare(S* prim, int nr)
{
	S* p = prim;
	while (p != NULL)
	{
		if (p->episoade == nr)
		{
			printf("%s \n", p->nume);
			printf("%s \n", p->producator);
			printf("%d \n", p->episoade);
		}
		p = p->urm;
	}
}
void suma(S* prim)
{
	int s=0,i,k;
	S* p;
	for (p = prim; p != NULL; p = p->urm)
		s = s + p->episoade;
	for (i = 31; i >= 0; i--)
	{
		k = s >> i;
		if (k & 1)
			printf("1");
		else 
			printf("0");
	}
}
int main()
{
	int opt,nr;
	char n[20];
	S* prim = NULL;
	S* p;
	FILE* f;
	do
	{
		printf("1.Adaugarea unui serial\n");
		printf("2.Afisarea serialelor\n");
		printf("3.Cautarea serialelor dupa ep\n");
		printf("4.Reprezentare binara a sumei nr de episoade\n");
		printf("5.Salvare fisier dupa producator\n");
		printf("0.iesire\n");
		printf("Optiunea dvs este:");
		scanf("%d", &opt);
		switch (opt)
		{
		case 0:
			exit(0);
		case 1:
			prim = adaugare(prim);
			break;
		case 2:
			afisare(prim);
			break;
		case 3:
			printf("\n Introduceti nr de ep:");
			scanf("%d", &nr);
			cautare(prim, nr);
			break;
		case 4:
			suma(prim);
			break;
		case 5:
			printf("\nDati numele fisierului:");
			scanf("%s", n);
			f = fopen(n,"wt");
			for (p = prim; p != NULL; p = p->urm)
				if (strcmp(p->producator, "Mihai") == 0)
				{
					fprintf(f, "%s ", p->nume);
					fprintf(f, "%s ", p->producator);
					fprintf(f, "%d", p->episoade);
					fprintf(f, "\n");
				}
			
			break;
		default:
			printf("Optiunea invalida");
			break;
		}
	} while (1);
	system("pause");
	return 0;
}