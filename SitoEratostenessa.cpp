//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 3.1
// Sito Eratostenessa 
//
//  WCY21IY1S1  Go��biowski Gabriel
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

//Zdefiniowanie struktury

typedef struct lista
 {
 	int key;
 	int znacznik;
 	struct lista *next;   
 }node;

//Funkcja dodaj�ca element na koniec listy 


void dodajOgon(node **head, int key, int znacznik) 
{
	node *newNode = (node *) malloc(sizeof(node));
	newNode->key = key;
	newNode->znacznik=znacznik;
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		node *tmp = *head;
		while (tmp->next != NULL) 
		{
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
} 

//Funkcja Sita

void SitoErast2(node *head, int n)
{
	node *tmp=head;
	int a;
	while((tmp->key)<=sqrt(n))//p�tla do momentu gdy wartosc elementu jest mniejsza ni� pierwiastek z n
	{
		
		node *tmp2=tmp;
		a=tmp->key;
		a=2*a;
		while(a<=n)
		{
			while(tmp2->key!=a)
			{
				tmp2=tmp2->next;//przej�cie do elementu o numerze a
			}
			tmp2->znacznik=1;//ustawienie znacznika jako liczba pierwsza
			a=a+tmp->key;
			
		}
		tmp=tmp->next;
		
	}
}

//Funkcja Wy�wietlania listy liczb pierwszych


void wyswietlenieListy(node *head)
{
	node *tmp=head;
	if(tmp==NULL)
	{
		return;
	}
	int i=1;
	ofstream plik("wy.txt");
	do
	{
		if(i%10==0)
		{
			plik<<endl;
			cout<<endl;
		}
		cout<<tmp->key<<", ";
		plik<<tmp->key<<", ";
		tmp=tmp->next;
		i++;
	}while(tmp!=NULL);
	
}

//Funkcja usuwaj�ca wszystkie nie pierwsze elementy


void usunNiePierwsze(node **head)
{
node *poprzedni = *head;
node *obecny=poprzedni;
obecny=obecny->next;
while((*head)->znacznik==1)
{
	
	node *tmp=*head;
	*head=(*head)->next;
	free(tmp);
}

while(poprzedni->next!=NULL)
{
	if(obecny->znacznik == 1)
	{
		node *tmp=obecny;
		poprzedni->next=obecny->next;
		obecny=obecny->next;
		free(tmp);
	}
	else
	{
		poprzedni = obecny;
		obecny = obecny->next;
	}
}

}


int main()
{
	node *head=NULL;
	int z, xx, yy;
	yy=3;
	xx=4;
	z=(xx<<2)+yy;
	cout<<endl<<z;
	int n;
	cout<<"podaj gorny zakres przedzialu: ";
	cin>>n;//pobranie g�rnego zakresu
	//P�tla dodaj�ca n element�w
	for (int i=2;i<=n;i++)
	{
		dodajOgon(&head, i, 0);//dodanie n element�w
	}
	SitoErast2(head, n);//Wywo�anie funkcji oznaczaj�cej liczb pierwsze
	usunNiePierwsze(&head);//Funkcja usuwaj�ca pozosta�e
	wyswietlenieListy(head);//Funkcja wy�wietlaj�ca liste
	
	
	return 0;
}

