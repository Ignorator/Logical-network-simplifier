#include "beolv.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


int beolv(ifstream &is, unsigned int* &tomb, unsigned int &m)
{
	int szam;
	string x;
	getline(is, x);
	istringstream szamok(x);
	szamok>>szam;
	if(szam<0)
	{cout<<"0 vagy 1 ertekeket kell megadnod"<<endl;
	return -1;}
	if(szam>1)
	{cout<<"0 vagy 1 ertekeket kell megadnod"<<endl;
	return -1;}
	while(!is.eof())
	{
	unsigned int* tmp=new unsigned int[m+1];
	for(unsigned int i=0; i<m; i++)
		tmp[i]=tomb[i];
	tmp[m]=szam;
	m++;
	delete [] tomb;
	tomb=tmp;					//elso elemet beolvastam
	szam=2;
	getline(is, x);
	istringstream szamok(x);
	szamok>>szam;
	if(szam<0)
	{if(m==16 || m==8)
	{break;}
		cout<<"0 vagy 1 ertekeket kell megadnod"<<endl;
	return -1;}
	if(szam>1)
	{if(m==16 || m==8)
	{break;}
		cout<<"0 vagy 1 ertekeket kell megadnod"<<endl;
	return -1;}
	}			//vegjelig olvasok
	return 1;
}