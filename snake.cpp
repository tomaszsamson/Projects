#include <iostream>
#include <conio.h> //getch()
#include <cstdlib>  //cls
#include <time.h>  //srand
#include <windows.h> //sleep




using namespace std;

char zmiana;

int rat;

int szerokosc, wysokosc, szybkosc;

int gora, dol, prawo, lewo;

int dlugosc=4, historiawspolzendnejX[10000], historiawspolzendnejY[10000];

int ile=0;

int klawisz;

int wspolzendnaXweza, wspolzendnaYweza;

int wspolzendnaXjedzenia, wspolzendnaYjedzenia;

char waz=219, jed=168, pd=188, pg=187, lg=201 , ld=200 , pion=186, poziom=205;

char kierunek='p';

char pole[35][35];

int przeszkody;
// funkcja dzieki ktorej ekran nie miga niezbedna biblioteka windows.h
class snake{
public:


void idzdoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X=x;
    dwPos.Y=y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);

}
int zwymyslaj(int &x)
{
    cout<<"Miedzy 5 a 35!!! Jeszcze raz!"<<endl;
    cin>> x;
    if (x<5 || x>35) x=15;
}


void mai()
{	
	int qwe;
	int licznikgier=0;
	char yes, no;
	int licznik=0;
	int tablicawynikow[100];
	int z=0;
	
	for(z;z<100;z++){
		tablicawynikow[z]='0';
	}
	int przeszkody;
	char menuchoice;
	


	menu:
		cout<<"---------------MENU GLOWNE-----------------"<<endl<<"1-rozpocznij gre"<<endl<<"2-tablica wynikow"<<endl<<"3-exit"<<endl;
		cin>>menuchoice;
		if (menuchoice=='1'){
			goto graj;
		}
		else if (menuchoice=='2'){
			system("CLS");
			goto tablica;
		}
		else if (menuchoice=='3')
		{
			exit(0);
		}
		graj:
	cout<<"wlaczyc teleprtacje?, y-tak, everything else-nie"<<endl;	
	cin>>zmiana;
	cout<<"ile chesz przeszkod ( w %)"<<endl;
	point:
	cin>>przeszkody;
	if((przeszkody>100)||(przeszkody<0))
	{
		cout<<"jeszce raz"<<endl;
			goto point;
	}

    cout << "Podaj szerokosc planszy od 5 do 35:" << endl;
    cin>>szerokosc;
    if (szerokosc<5 || szerokosc>35) zwymyslaj(szerokosc);

    cout << "Podaj wysokosc planszy od 5 do 35:" << endl;
    cin>>wysokosc;
    if (wysokosc<5 || wysokosc>35) zwymyslaj(wysokosc);

    cout<<"Podaj szbkosc gry o 1 do 10"<<endl;
    cin>>szybkosc;
    if (szybkosc<1) szybkosc=1;
    if (szybkosc>10) szybkosc=10;

    cout<<"Podaj przyciski ktorymi chcesz zagrac"<<endl;

    cout<<"GORA"<<endl;
    gora=getch();
    if(gora==224) gora+=getch();
    if(gora==0) gora-=getch();

    cout<<"DOL"<<endl;
    dol=getch();
    if(dol==224) dol+=getch();
    if(dol==0) dol-=getch();

    cout<<"LEWO"<<endl;
    lewo=getch();
    if(lewo==224) lewo+=getch();
    if(lewo==0) lewo-=getch();

    cout<<"PRAWO"<<endl;
    prawo=getch();
    if(prawo==224) prawo+=getch();
    if(prawo==0) prawo-=getch();
    // tutaj bedziemy deklarowac pole za pomoca petli

    for (int i=0; i<wysokosc; i++)
    {
        for(int j=0; j<szerokosc; j++)
        {
            pole[i][j]='p';//puste pole
			rat=rand()%(100);
			if (rat<przeszkody)
			pole[i][j]='k';
        }
    }

    srand(time(NULL));


    wspolzendnaXweza=rand()%szerokosc;
    wspolzendnaYweza=rand()%wysokosc;

    pole[wspolzendnaXweza][wspolzendnaYweza] = 'w';

    do
    {
        wspolzendnaXjedzenia=rand()%szerokosc;
        wspolzendnaYjedzenia=rand()%wysokosc;
    }
    while(pole[wspolzendnaXjedzenia][wspolzendnaYjedzenia]!='p');

    pole[wspolzendnaXjedzenia][wspolzendnaYjedzenia] = 'j';


//poczatek gry
    system("cls");

    idzdoxy(0,0);  //czysczenie okna + biblioteka cstdlib

    cout<<lg;

    for (int i=0; i<szerokosc; i++)
    {
        cout<<poziom<<poziom;
    }
    cout<<pg;

    for (int i=0; i<wysokosc; i++)
    {
        cout<<endl<<pion;
        pole[i][szerokosc]='|';
        for (int j=0; j<szerokosc; j++)
        {
            if (pole[j][i]=='p') cout<<"  ";//puste pole
            if (pole[j][i]=='w') {
			cout<<waz;
			cout<<" ";
		}
            if (pole[j][i]=='j') {
			cout<<jed;
            	cout<<" ";
		}
            if (pole[j][i]=='k') cout<<"xx";
        }
		cout<<pole[i][szerokosc];

    }
    cout<<endl;
    cout<<ld;

    for (int i=0; i<szerokosc; i++)
    {
        cout<<poziom<<poziom;
    }
    cout<<pd;

    for(;;)
    {
        ile++;
        historiawspolzendnejX[ile]=wspolzendnaXweza;
        historiawspolzendnejY[ile]=wspolzendnaYweza;

        Sleep(1000/szybkosc);

        if(kbhit())  //jesli zostanie nacisniety jakis klawisz
        {
            klawisz=getch();
            if(klawisz==224)klawisz+=getch();
            if(klawisz==0)klawisz-=getch();

            if(klawisz==gora && (kierunek=='p' || kierunek=='l')) kierunek='g';
            if(klawisz==dol && (kierunek=='p' || kierunek=='l')) kierunek='d';
            if(klawisz==lewo && (kierunek=='g' || kierunek=='d')) kierunek='l';
            if(klawisz==prawo && (kierunek=='g' || kierunek=='d')) kierunek='p';
        }
	
        if(kierunek=='d') wspolzendnaYweza++;
        if(kierunek=='g') wspolzendnaYweza--;
        if(kierunek=='l') wspolzendnaXweza--;
        if(kierunek=='p') wspolzendnaXweza++;

        if(wspolzendnaXweza==szerokosc)
		 {
		 wspolzendnaXweza=0;
		if(zmiana=='y') wspolzendnaYweza=rand()%(wysokosc-1);
		 
	}
        if(wspolzendnaXweza==-1) {
		wspolzendnaXweza=szerokosc -1;
		if(zmiana=='y') wspolzendnaYweza=rand()%(wysokosc-1);
	}
        if(wspolzendnaYweza==wysokosc){
		 wspolzendnaYweza=0;
		 if(zmiana=='y') wspolzendnaXweza=rand()%(szerokosc-1);
	}
        if(wspolzendnaYweza==-1) 
		{
		wspolzendnaYweza=wysokosc -1;
		if(zmiana=='y') wspolzendnaXweza=rand()%(szerokosc-1);
	}


        if((pole[wspolzendnaXweza][wspolzendnaYweza]=='w')||(pole[wspolzendnaXweza][wspolzendnaYweza]=='k'))
        {
            idzdoxy(0,wysokosc+4);
            cout<<endl<<"\aKoniec";
            cout<<endl<<"Dlugosc weza = "<<ile<<endl;
            tablicawynikow[licznik]=ile;
            licznik++;
            licznikgier++;
            point3:
			cout<<"jeszzcze raz? (y=yes, w=tablica wynikow, m=menu, everythin else coloses app)"<<endl;
            cin>>yes;
            if(yes=='y'){
			
            system ("CLS");
            ile=0;
            dlugosc=4;
            goto graj;
        
			}
			else if (yes=='w'){
		tablica:
			cout<<"------wyniki-------"<<endl;
			dlugosc=4;
			for (qwe=0;qwe<licznikgier;qwe++)
			{
				cout<<tablicawynikow[qwe]<<endl;
			}
			goto menu;
			}
			else if(yes=='m'){
			
			goto menu;
			}
            else{
			
            break;
        }
        }


        if(pole[wspolzendnaXweza][wspolzendnaYweza]=='j')
        {
            dlugosc++;
            do
            {
                wspolzendnaXjedzenia=rand()%szerokosc;
                wspolzendnaYjedzenia=rand()%wysokosc;
            }
            while(pole[wspolzendnaXjedzenia][wspolzendnaYjedzenia]!='p');

            pole[wspolzendnaXjedzenia][wspolzendnaYjedzenia] = 'j';
            idzdoxy(wspolzendnaXjedzenia*2+1,wspolzendnaYjedzenia+1);
            cout<<jed<<jed;

        }
        else
        {
            pole[historiawspolzendnejX[ile-dlugosc]][historiawspolzendnejY[ile-dlugosc]]='p';
            idzdoxy(historiawspolzendnejX[ile-dlugosc]*2+1,historiawspolzendnejY[ile-dlugosc]+1);
            cout<<"  ";

        }


        pole[wspolzendnaXweza][wspolzendnaYweza]='w';
        idzdoxy(wspolzendnaXweza*2+1,wspolzendnaYweza+1);
        cout<<waz<<waz;

    }
    getch();

}

};
int main(){
	
	snake snejk;
	snejk.mai();
	
	return 0;
}