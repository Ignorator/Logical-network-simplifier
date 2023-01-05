#include "build.h"
#include <iostream>
#include <fstream>

using namespace std;

bool if_egyezik(unsigned int e, unsigned int f);

int diagnostic_kiir(unsigned int meret, unsigned int eredmeny, unsigned int &hanyadik, ofstream &os, unsigned int &a, unsigned int &b, double &c, double &d, unsigned int *it)
{


	if(meret==8)
	{
		if(hanyadik==0)
			{os << "A\tB\tC\teredmeny\tF\tegyezes" << endl;}

		if(hanyadik==4)
		{a=1;b=0;}
		if(hanyadik==2 || hanyadik==6)
		{b=1;}
		if(hanyadik!=0 && hanyadik%2!=0)
			c=1;
		else c=0;
		os <<a<<"\t"<<b<<"\t"<<(int)c<<"\t"<<eredmeny<<"\t\t"<<it[hanyadik]<<"\t"<<if_egyezik(eredmeny, it[hanyadik])<<endl;

	}
	if(meret==16)
	{
		if(hanyadik==0)
			{os << "A\tB\tC\tD    eredmeny\t\tF\tegyezes" << endl;}
		if(hanyadik==8)
		{a=1;b=0;}
		if(hanyadik==4 || hanyadik==12)
		{b=1;}
		if(hanyadik==2||hanyadik==6||hanyadik==10||hanyadik==14)
			c=1;
		if(hanyadik==0 || hanyadik%4==0)
			c=0;
		if(hanyadik!=0 && hanyadik%2!=0)
			d=1;
		else d=0;
		os <<a<<"\t"<<b<<"\t"<<(int)c<<"\t"<<(int)d<<"\t"<<eredmeny<<"\t\t"<<it[hanyadik]<<"\t"<<if_egyezik(eredmeny, it[hanyadik])<<endl;
	}



	return 1;
	}


bool if_egyezik(unsigned int e, unsigned int f)
{return e==f;}