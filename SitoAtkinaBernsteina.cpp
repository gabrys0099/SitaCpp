//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 3.2
// Sito Atkina-Bernsteina 
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
 
 
 // Funkcja dodaj�ca element na koniec listy
 
 void dodajOgon(node **head, int key, int znacznik) 
{
	node *newNode = (node *) malloc(sizeof(node)); // stworzenie nowego elementu listy
	newNode->key = key; //przypisanie warto�ci kluczowej do listy
	newNode->znacznik=znacznik; // przypisanie znacznika czy liczba jest pierwsza
	newNode->next = NULL; // wska�nik na nast�pny element listy
	if (*head == NULL)
	{
		*head = newNode;//jezeli lista jest pusta nowy element zostaje g�ow�
	}
	else
	{
		node *tmp = *head;
		// przej�cie na koniec listy
		while (tmp->next != NULL) 
		{
			tmp = tmp->next;// przej�cie na koniec listy
		}
		tmp->next = newNode;
	}
} 

//Funkcja znajdowania liczb pierwszych w�r�d element�w listy


void sitoAtkina(node *head, int n)
{
	unsigned int x, y, z, xx, yy;
	for( x=1;x<=sqrt(n);x++)
	{
		xx=x*x;
		for(y=1;y<=sqrt(n);y++)
		{
			yy=y*y;
			z=(xx<<2)+yy;
			if((z<=n) && ((z%12==1) ||(z%12==5)))
			{
				node *tmp=head;
				// przej�cie na dany elelement do oznaczenia jako pierwsza
				while(tmp->key!=z)
				{
					tmp=tmp->next;
				}
				// Je�eli dana liczba ju� by�a wcze�niej oznaczona to ponowne odznaczenie
				if(tmp->znacznik==1)
				{
					tmp->znacznik=0;
				}
				else if(tmp->znacznik==0)
				{
						tmp->znacznik=1;
				}
			}
			
			z-=xx;
			if( ( z <= n ) && ( z % 12 == 7 ) )
			{
				node *tmp2=head;
				while(tmp2->key!=z)
				{
					tmp2=tmp2->next;
				}
				if(tmp2->znacznik==1)
				{
					tmp2->znacznik=0;
				}
				else if(tmp2->znacznik==0)
				{
					tmp2->znacznik=1;
				}
				
			}
			if(x>y)
			{
				z-=yy<<1;
				if( ( z <= n ) && ( z % 12 == 11 ) )
				{
					node *tmp3=head;
					while(tmp3->key!=z)
					{
						tmp3=tmp3->next;
					}
					if(tmp3->znacznik==1)
					{
						tmp3->znacznik=0;
					}
					else if(tmp3->znacznik==0)
					{
						tmp3->znacznik=1;
					}
				}
			}
		}
		
	}
	//Znalezienie b�ednych liczb pierwszych 
	
	for(int i = 5; i <= sqrt(n); i++ )
	{
		node *tmp4=head;
		while(tmp4->key!=i)
		{
			tmp4=tmp4->next;
		}
		if(tmp4->znacznik==1)
		{
			xx=i*i;
			z=xx;
			while(z<=n)
			{
				while(tmp4->key!=z)
				{
					tmp4=tmp4->next;
				}
				tmp4->znacznik=0;
				z+=xx;
			}
		}
		
	}
}

//Funkcja Wy�wietlaj�ca wszystkie elementy listy

void wyswietlenieListy(node *head)
{
	node *tmp=head;
	if(tmp==NULL)
	{
		return;
	}
	int i=1;
	ofstream plik("wy.txt");
	plik<<2<<", "<<3<<", ";
	cout<<2<<", "<<3<<", ";
	do
	{
		if(i%10==0)
		{
			cout<<endl;
			plik<<endl;
		}
		//wypisanie elementu
		cout<<tmp->key<<", ";
		plik<<tmp->key<<", ";
		tmp=tmp->next;//Przej�cie do nast�pnego
		i++;
	}
	while(tmp!=NULL);
	
}

//Funkcja Usuwaj�ca elementy nie pierwsze

void usunNiePierwsze(node **head)
{
node *poprzedni = *head;
node *obecny=poprzedni;
obecny=obecny->next;

//Je�eli g�owa by�aby nie pierwsza p�tla usuwaj�ca g�ow�

while((*head)->znacznik==0)
{
	node *tmp=*head;
	*head=(*head)->next;
	free(tmp);
}

//P�tla usuwaj�ca wszystkie elementy oznaczone jako nie pierwsze
while(poprzedni->next!=NULL)
{
	if(obecny->znacznik == 0)
	{
		node *tmp=obecny;
		poprzedni->next=obecny->next;
		obecny=obecny->next;
		free(tmp);//zwolnienie elementu
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
	int n;
	cout<<"podaj gorny zakres przedzialu: ";
	cin>>n;//pobranie g�rnego zakresu
	
	//P�tla dodaj�ca elementy do tablicy
	for (int i=5;i<=n;i++)
	{
		dodajOgon(&head, i, 0);//dodanie n element�w
	}
	
	sitoAtkina(head, n);//Wywo�anie Funkcji sita
	usunNiePierwsze(&head);//Wywo�anie Funkcji usuwania nie pierwszych
	
	wyswietlenieListy(head);//Funkcja wy�wietlenia listy 
	
	return 0;
}

