#include <iostream>
using namespace std;
class calc{
	public:
	void funkcje();
	void menu();
	float dodawanie(float, float);
	float odejmowanie(float,float);
	float mnozenie(float,float);
	float dzielenie(float,float);
};
class memcalc :public calc{
public:
	
int num();
void memmenu();
void memfunkcje (int size);
};








