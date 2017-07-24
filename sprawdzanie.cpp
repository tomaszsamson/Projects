#include<iostream>
#include<time.h>
using namespace std;

int main()
{
	string sd;
	int i=0, flag=0, z=0;
	while (1)
	{
		cout<<"wprowadz ciag: "<<endl;
		cin>>sd;
		while(sd[i]!=NULL)
		{
			if(sd[i]<48 || sd[i]>57)
			{
				flag++;
			}
			i++;
		}
		z=i-flag;
		system("cls");	
		cout<<"ciag to:"<<sd<<endl;
		if(flag>0)
		{
			if(flag==i)
			{
				cout<<"to nie liczba, ciag sklada sie z "<<flag<<" znakow(i)"<<endl;
				goto point;
			}
			cout<<"to czesciowo liczba, zawiera "<<z<<" cyfr(y) oraz "<<flag<<" innych(e) znakow(i)"<<endl;
		}
		else
			cout<<"jest to liczba zawierajaca "<<z<<" cyfr(y)"<<endl;
		point:
		flag=i=z=0;
		cout<<"dawaj  dalej"<<endl;
	}
	return 0;
}