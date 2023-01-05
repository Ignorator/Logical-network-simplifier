#include <iostream>
#include "push_kapu.h"

using namespace std;

void push_kapu(unsigned int* &kapuk, unsigned int &kapum, char* sz)
{
	if(strcmp(sz,"A")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=0; // A
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"AN")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=1; // AN
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"B")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=2; // B
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"BN")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=3; // BN
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"C")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=4; // C
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"CN")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=5; // CN
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"D")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=6; // D
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"DN")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=7; // DN
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}

	if(strcmp(sz,"+")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=8; // +
		delete []kapuk;
		kapuk=tmp;
		kapum++;
	}


	if(strcmp(sz,"ANBNCNDN")==0)
	{
		// ANBNCNDN 1 3 5 7
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=1; // AN
		delete []kapuk;
		kapuk=tmp;
		kapum++;

		unsigned int*tmp1=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp1[s]=kapuk[s];
		}
		tmp1[kapum]=3; // BN
		delete []kapuk;
		kapuk=tmp1;
		kapum++;

		unsigned int*tmp2=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp2[s]=kapuk[s];
		}
		tmp2[kapum]=5; // CN
		delete []kapuk;
		kapuk=tmp2;
		kapum++;

		unsigned int*tmp3=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp3[s]=kapuk[s];
		}
		tmp3[kapum]=7; // DN
		delete []kapuk;
		kapuk=tmp3;
		kapum++;
	}

	if(strcmp(sz,"ANBNCN")==0)
	{
		unsigned int*tmp=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp[s]=kapuk[s];
		}
		tmp[kapum]=1; // AN
		delete []kapuk;
		kapuk=tmp;
		kapum++;

		unsigned int*tmp2=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp2[s]=kapuk[s];
		}
		tmp2[kapum]=3; // BN
		delete []kapuk;
		kapuk=tmp2;
		kapum++;

		unsigned int*tmp3=new unsigned int[kapum+1];
	for(unsigned int s=0; s<kapum; s++)
		{
			tmp3[s]=kapuk[s];
		}
		tmp3[kapum]=5; // CN
		delete []kapuk;
		kapuk=tmp3;
		kapum++;

	}


}