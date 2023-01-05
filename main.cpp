#include <iostream>
#include "beolv.h"
#include "minimize.h"
#include "gates.h"
#include <fstream>
#include "build.h"
#include <time.h>

#include <vld.h>

using namespace std;


int main()
{
	clock_t tStart = clock();

	unsigned int *it=new unsigned int[0];    //igazsagtabla valtozoinak tombje, nem lehet kozombos
	unsigned int meret=0;					// kezdetben a valtozok tombjeben nincs elem
	int bvisszateres;						// beolvasas visszateresi erteke kivetelkezeleshez

	unsigned int* kapuk=new unsigned int[0];	//kapuba kotott elemek tombje, ebbol epitkezunk
	unsigned int kapukm=0;						//kezdetben ebben sincs elem

	ifstream is("igazsagtabla.txt");
	if (!is) {
		cerr << "Error opening input file: " << "igazsagtabla.txt" << endl;
		delete [] it;
		delete [] kapuk;
		return -1;
	}


	bvisszateres=beolv(is, it, meret);		//tomb feltoltese


	if (bvisszateres<0)
		{
	delete [] it;
	delete [] kapuk;
	return -1;}
	is.close();
	if (!is) {
		cerr << "Error reading input file: " << "igazsagtabla.txt"<< endl;
		delete [] it;
		delete [] kapuk;
		return -1;
	}

		if((meret==8) || (meret==16))
			{}
		else 
			{cout<<"8 vagy 16 sort kell megadnod es egy vegjelet"<<endl;
		delete [] it;
		delete [] kapuk;
		return -1;}

	kapukm=minimize(it, meret, kapuk, kapukm);							//szamjegyes minimalizalas


	if(kapukm==0)
	{cout<<"Nem adtal meg valtozot, vagy rosszul adtad meg"<<endl;
	delete [] it;
	delete [] kapuk;
	return -1;}

	build(kapuk, kapukm, meret, it);		// megepeti a halozatot, de tesztelni is itt kell, mert az objektumok megszunnek
	
	cout<<"Futasi ido:"<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<"sec"<<endl;

	delete[] it;
	delete[] kapuk;

	return 0;
}