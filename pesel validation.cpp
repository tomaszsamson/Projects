#include <iostream>
#include <time.h>
using namespace std;


int main(){
	cout<<"--------------j to janusz, g to grazyna-----------------"<<endl;
	string pesel;
	int i=0, h=0, g, kont=0,ckont;
	char k;
	char pomocnicza;
	char rok[2];
	char wiek[2];
	char miesiac[2];
	char dzien[2];
	char lkontr[11];
	int lkontr1[11];
	string plec;
	char tabela[11];
	while(1){
		point:
		i=0;
		cin>>pesel;
		while(pesel[i]!=NULL){
			if(pesel[i]<48 || pesel[i]>57)
			{
				system("cls");
				cout<<"he he tfoja matka, wpisz poprawny pesel"<<endl;
				goto point;
			}
			if(i<2) rok[i]=pesel[i];
			if(i>1 && i<4) miesiac[i-2]=pesel[i];
			if(i>3 && i<6) dzien[i-4]=pesel[i];
			if(i==9){
				if(pesel[i]%2==1) plec= 'j';
				else plec ='g';
			}
			i++;
			
		}i=0;
		if(pesel[2] == 48 || pesel[2] == 49){
			wiek[0]=49;
			wiek[1]=57;
		}
		if(pesel[2] == 56 || pesel[2] == 57){
			k=miesiac[0];
			k=k-8;
			miesiac[0]=k;
			wiek[0]=49;
			wiek[1]=56;
		}
		if(pesel[2] == 50 || pesel[2] == 51){
			k=miesiac[0];
			k=k-2;
			miesiac[0]=k;
			wiek[0]=50;
			wiek[1]=48;
		}
		if(pesel[2] == 52 || pesel[2] == 53){
			k=miesiac[0];
			k=k-4;
			miesiac[0]=k;
			wiek[0]=50;
			wiek[1]=49;
		}
		if(pesel[2] == 54 || pesel[2] == 55){
			k=miesiac[0];
			k=k-6;
			miesiac[0]=k;
			wiek[0]=50;
			wiek[1]=50;
		}
		for(h=0;h<11;h++){
			lkontr[h]=pesel[h];
			g=lkontr[h];
			g=g-48;
			lkontr1[h]=g;
		}
		kont=9*lkontr1[0]+7*lkontr1[1]+3*lkontr1[2]+lkontr1[3]+9*lkontr1[4]+7*lkontr1[5]+3*lkontr1[6]+lkontr1[7]+9*lkontr1[8]+7*lkontr1[9];
		kont=kont%10;
		ckont=lkontr[10];
		ckont=ckont-48;
		if(kont!=ckont) {
			system("cls");
			cout<<"he he tfoja matka, wpisz poprawny pesel"<<endl;
			goto point;
		}
		
		pomocnicza=pesel[2];
		pomocnicza=pomocnicza-48;
		while(pomocnicza>1) pomocnicza=pomocnicza-2;
		
		if(((pomocnicza%2)==1) && (pesel[3]>50))
		{
			system("cls");
			cout<<"he he nie ma takiego miesiaca, wpisz poprawny pesel"<<endl;
			goto point;
		}
		if((pesel[3]==50) && (pomocnicza%2==0))
		{
			if ((((rok[0]-48)*10)+(rok[1]-48))%4==0){
				if((((dzien[0]-48)*10)+(dzien[1]-48))>29)
				{
					system("cls");
					cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
					goto point;
				}
				if((((dzien[0]-48)*10)+(dzien[1]-48))>29){
					system("cls");
					cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
					goto point;
				}
			}
		}
		if((pesel[3]==48) && (pomocnicza%2==0))
		{
			system("cls");
			cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
			goto point;	
		}
		if(((pesel[3]==49)||(pesel[3]==51)||(pesel[3]==53)||(pesel[3]==55)||(pesel[3]==56))&& (pomocnicza%2==0))
		{
			if((((dzien[0]-48)*10)+(dzien[1]-48))>31)
			{
				system("cls");
				cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
				goto point;
			}
		}
		if(((pesel[3]==52)||(pesel[3]==54)||(pesel[3]==57)) && (pomocnicza%2==1))
		{
			if((((dzien[0]-48)*10)+(dzien[1]-48))>30)
			{
				system("cls");
				cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
				goto point;
			}
		}
		if(((pesel[3]==48)||(pesel[3]==50)) && (pomocnicza%2==1))
		{
			if((((dzien[0]-48)*10)+(dzien[1]-48))>31)
			{
				system("cls");
				cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
				goto point;
			}
		}
		if(((pesel[3]==49))&& (pomocnicza%2==1))
		{
			if((((dzien[0]-48)*10)+(dzien[1]-48))>30)
			{
				system("cls");
				cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
				goto point;
			}
		}
		if(pomocnicza==48 && pesel[3]==48)
		{
			system("cls");
			cout<<"he he nie ma takiego miesiaca, wpisz poprawny pesel"<<endl;
			goto point;
		}
		if(pesel[4]==48 && pesel[5]==48)
		{
			system("cls");
			cout<<"he he nie ma takiego dnia, wpisz poprawny pesel"<<endl;
			goto point;
		}		
		system("cls");
		cout<<"--------------j to janusz, g to grazyna-----------------"<<endl;
		cout<<"to jest "<<plec<<", data urodzenia: "<<wiek[0]<<wiek[1]<<rok[0]<<rok[1]<<"."<<miesiac[0]<<miesiac[1]<<"."<<dzien[0]<<dzien[1]<<endl;
		
	}
	return 0;
}