#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

using namespace std;
void calc::funkcje()
{
	menu();
	float v, w=3, g;
	int i, j;
	int p, k;
	
	float liczba;
	string liczba2;
	cin>>liczba;
	char tab[100];
	char tab2[100];

	while(true){
	
		cin>>liczba2;
	for (i=0;i<100;i++)
	{
		tab[i]='\0';
		tab2[i]='\0';
	}
	i=1;
	j=0;
	while(((liczba2[i]>47)&&(liczba2[i]<58))||(liczba2[i]==46))
	{
		tab[i-1]=liczba2[i];
		i++;
	}
		while(((liczba2[j]>47)&&(liczba2[j]<58))||(liczba2[j]==46))
	{
		tab2[j]=liczba2[j];
		j++;
	}
	
	
sscanf(tab,"%f",&v);
sscanf(tab2,"%f",&g);
if (liczba2[0]==43)
{
	liczba=dodawanie(liczba, v);
}
else if(liczba2[0]==45)
{
	liczba=odejmowanie(liczba,v);
}
else if(liczba2[0]==42)
{
	liczba=mnozenie(liczba,v);
}
else if(liczba2[0]==47)
{
	liczba=dzielenie(liczba,v);
}
else if(liczba2[0]==99)
{
	liczba=0;
	system ("CLS");
	menu();
	cin>>liczba;
}
else if(liczba2[0]==101)
{
	printf ("goodbye:>");
	exit(0);
}
else if((liczba2[0]>47)&&(liczba2[0]<58))
{
	pyt1:
	cout <<"chcesz zastapic wartosc domyslna? (1-tak, 2-nie)"<<endl;
	cin>>p;
	if(p==1)
	{
		cout <<"nadpisac zerem czy wpisana wartoscia? (1 - zerem, 2 - wpisana wartoscia)";
	pyt2:
		cin>>k;
		
	if(k==2){
		cout <<g<<endl;
		liczba=g;
		}
		else if(k==1){
		cout<<0<<endl;
		liczba=0;
	}
	else {
		cout<<"dane nie prawidlowe, potwierdz jeszcze raz"<<endl;
		goto pyt2;
	}
		
	}
	else if(p==2)
	{
		cout <<""<<endl;
	}
	else {
		cout<<"dane nie prawidlowe, potwierdz jeszcze raz"<<endl;
		goto pyt1;
	}
}

else cout<<"nothing done here"<<endl;
	system("CLS");
	menu();

cout<<liczba<<endl;

}
}

void calc::menu(){
	cout<<"witaj w kalkulatorze"<<endl<<"dostepne sa nast. funkcje:"<<endl<< "+ (dodawanie), - (odejmowanie), * (mnozenie), / (dzielenie), c (kasowanie), e (wylaczenie programu)"<<endl<<endl;
	cout<<"wpisz najpierw wartosc poczatkowa, a pozniej wybrany operand z druga wartoscia"<<endl<<"przyklad: 347>enter>+4334>enter"<<endl<<endl;
}
float calc::dodawanie (float an, float bn){
float c=an+bn;
return c;
}
float calc::odejmowanie (float an, float bn){
	float c=an-bn;
	return c;
}
float calc::mnozenie (float an, float bn){
	float c=an*bn;
	return c;
}
float calc::dzielenie (float an, float bn)
{
	float c= an/bn;
	return c;
}


int memcalc::num()
{
	int number;
 cout<<"podaj ilosc komorek \n";
 cin>>number;
 return number;
}

void memcalc::memmenu(){
	cout<<"witaj w kalkulatorze z pamiecia"<<endl<<"podaj ilosc komorek do zaalokownia a potem wykonuj obliczenia wg. wzoru:"<<endl<<"14+50, gdzie 14 to numer komorki, + to operand a 50 to wartosc dodana do wartosci w komorce"<<endl<<"domyslne wartosci komorek to 0, pierwsza komorka ma numer zerowy"<<endl<<"obslugiwane operandy: + - / * = (=ustawia wartosc w komorce)"<<endl<<"kalkulator mozna wylaczyc funkca e"<<endl; 
}





void memcalc::memfunkcje(int size){

	
	
	float tab[size];
	for(int g=0;g<size;g++)
	{
		tab[g]=0;
	}
	float liczba;
	char pomocnicza[100];
	char operand;
	char pomocnicza2[100];
	int p;
	string wartosc;
	int i=0,j, numer;
	while(true){
		
		point2:
			
		cin>>wartosc;
	
		
		if(wartosc[0]==101)
	{
		cout<<"chcesz wylaczyc?(1 tak, 2 nie)"<<endl;
		cin>>p;
		point:
		if(p==1){
			cout<<"goobye:>"<<endl;
		exit(0);}
		else if(p==2) {
			cout<<"wprowadz nowe dane"<<endl;
		goto point2;}
		else {
			cout <<"dane nie prawidlowe, wprowadz jeszcze raz"<<endl;
			goto point;
		}
	}
		
		
	for (i=0;i<100;i++)
	{
		pomocnicza[i]='\0';
		pomocnicza2[i]='\0';
			
	
	}
	i=0;
	
	while(((wartosc[i]>47)&&(wartosc[i]<58))||(wartosc[i]==46))
	{
		pomocnicza[i]=wartosc[i];
		i++;
	}
	operand=wartosc[i];
	i=i+1;
	j=0;
		while(((wartosc[i]>47)&&(wartosc[i]<58))||(wartosc[i]==46))
	{
		pomocnicza2[j]=wartosc[i];
		j++;
		i++;
	}

	
	sscanf(pomocnicza,"%d",&numer);
	sscanf(pomocnicza2,"%f",&liczba);
	
	if(operand==43)
	{
		tab[numer]=calc::dodawanie(tab[numer], liczba);
	}
	else if(operand==45)
	{
		tab[numer]=calc::odejmowanie(tab[numer],liczba);
	}
	else if(operand==42)
	{
		tab[numer]=calc::mnozenie(tab[numer], liczba);
	}
	else if(operand==47)
	{ 
		tab[numer]=calc::dzielenie(tab[numer], liczba);
	}
	else if(operand==61)
	{
		tab[numer]=liczba;
	}
	

	system ("CLS");
	memmenu();
	printf("%f\n", tab[numer]);
	
	
	
	
	
}

}
