#include <iostream>
#include "calc.h"
#include <stdlib.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main() {
	cout<<"przepraszam, ale w kodzie moga znajdowac sie jakies niepotrzebne zmienne powolane w czasie procesu tworzenia programu"<<endl;
	cout<<"wybierz kalkulator"<<endl<<"1=zwykly, 2=z pamiecia"<<endl;
	int wybor;
	punkt:
	cin>>wybor;
	if(wybor==2){
	int number, i=0;
	memcalc uruchom2;
	uruchom2.memmenu();
	number=uruchom2.num();
	

uruchom2.memfunkcje(number);
}
else if (wybor==1){

	 calc uruchom;
	uruchom.funkcje();
	}
	else {
		cout<<"niewlasciwe dane"<<endl;
		goto punkt;
	}
	return 0;
}
