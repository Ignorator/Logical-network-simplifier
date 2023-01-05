#include "build.h"
#include "gates.h"
#include "or.h"
#include "and.h"
#include "not.h"
#include "valtozok.h"
#include "teszt.h"
#include <iostream>
#include <fstream>
using namespace std;


void build(unsigned int* kapukt, unsigned int kapukm, unsigned int meret, unsigned int*it)
{
	//valtozok letrehozasa:
	A A1;
	B B1;
	C C1;
	D D1;
	unsigned int hanyadik=0;		//teszteleshez: eppen hanyadik elemnek jarunk


	unsigned int sumorbe=0;			//hany bemenetu az or kapunk
	unsigned int sumandbe=0;		//hany bemenetu az aktualis and kapunk
	unsigned int* andbe=new unsigned int[0];	//and kapuk bemenetet tarolja
	unsigned int andbenum=0;					//kezdetben ez a tomb ures
	unsigned int q=0;							//and kapuk bemenetenek tombjen jarunk vele vegig
	int c=0;			//and kapuba hany elem kerul
	int k=0;		//kapuk tombjen jarunk vele vegig
	int k2=0;		//kapuk tombjen jarunk vele vegig	

	//diagnosztikia kiiratashoz itt kell deklaralnunk a vegigjarashoz szukseges elemeket 
	unsigned int a1=0;
	unsigned int b1=0;
	double c1=0;
	double d1=0;





	char* fname = "osszehasonlitas.txt";
	ofstream os (fname);
	if(!os)
	{
		cerr << "Error opening output file: " << fname << endl;
		return;
	}

	// megszámolom hány bemenete van az or kapunak
	// megszámolom a lefoglalandó and kapubemenetek
	for(unsigned int i=0; i<kapukm; i++)
	{
		if(kapukt[i]==8)				//ha + jelet talál
			{
				sumorbe++;
				unsigned int* tmp=new unsigned int[andbenum+1];
				for(unsigned int j=0; j<andbenum; j++)
					{tmp[j]=andbe[j];}
				tmp[andbenum]=c;
				andbenum++;
				delete []andbe;
				andbe=tmp;
				c=-1;
		}
		c++;
	}

	//and kapuk miatt le kell futnia megegyszer

	sumorbe++;
				unsigned int* tmp=new unsigned int[andbenum+1];
				for(unsigned int j=0; j<andbenum; j++)
					{tmp[j]=andbe[j];}
				tmp[andbenum]=c;
				andbenum++;
				delete []andbe;
				andbe=tmp;

	if(sumorbe>1)
	{

	Or or1(sumorbe);								//eggyel több bemenet van mint "+" jel


		for(unsigned int i=0; i<sumorbe; i++)
			{
						or1.in[i]=new And(andbe[q]);		//q-adik eleme az andbe tombnek eltarolja az aktualis and kapu bemeneteinek szamat
						for(unsigned int j=0; j<(or1.in[i]->inputsNum); j++)
						{
							//bekotesek az and kapu(k)ba
								switch(kapukt[k]){
									case 0:
										or1.in[i]->in[j]=new Vezetek(1);
										or1.in[i]->in[j]->in[0]=&A1;
										break;
									case 1:
										or1.in[i]->in[j]=new Not(1);
										or1.in[i]->in[j]->in[0]=&A1;
										break;
									case 2:
										or1.in[i]->in[j]=new Vezetek(1);
										or1.in[i]->in[j]->in[0]=&B1;
										break;
									case 3:
										or1.in[i]->in[j]=new Not(1);
										or1.in[i]->in[j]->in[0]=&B1;
										break;
									case 4:
										or1.in[i]->in[j]=new Vezetek(1);
										or1.in[i]->in[j]->in[0]=&C1;
										break;
									case 5:
										or1.in[i]->in[j]=new Not(1);
										or1.in[i]->in[j]->in[0]=&C1;
										break;
									case 6:
										or1.in[i]->in[j]=new Vezetek(1);
										or1.in[i]->in[j]->in[0]=&D1;
										break;
									case 7:
										or1.in[i]->in[j]=new Not(1);
										or1.in[i]->in[j]->in[0]=&D1;
										break;
								}
							k++;
							if(kapukt[k]==8)
								k++;
						}
				q++;
			}
		// diagnosztika minden lehetséges esetre
		if(meret==16)
		{
		for(unsigned int p1=0; p1<2; p1++)
		{
			for(unsigned int p2=0; p2<2; p2++)
			{
				for(unsigned int p3=0; p3<2; p3++)
				{
					for(unsigned int p4=0; p4<2; p4++)
					{
						A1.setOutput((bool)p1);
						B1.setOutput((bool)p2);
						C1.setOutput((bool)p3);
						D1.setOutput((bool)p4);

						for(unsigned int i=0; i<sumorbe; i++)
							{		
								for(unsigned int j=0; j<(or1.in[i]->inputsNum); j++)
									{or1.in[i]->in[j]->setOutput();}		//Not, vagy vezetek beallitasa
							or1.in[i]->setOutput();				//And kapuk beallitasa
							}
						or1.setOutput();		//utolso "nagy" or kapu beallitasa
						/*cout<<"A valtozo:"<<A1.getOutput()<<endl;
						cout<<"B valtozo:"<<B1.getOutput()<<endl;
						cout<<"C valtozo:"<<C1.getOutput()<<endl;
						cout<<"D valtozo:"<<D1.getOutput()<<endl;
						cout<<"A halozat kimenete:"<<or1.getOutput()<<endl<<endl;*/

						diagnostic_kiir(meret, (int)or1.getOutput(), hanyadik, os, a1, b1, c1, d1, it);
						hanyadik++;
					}
				}
			}
		}
		}

		if(meret==8)
		{
				for(unsigned int p1=0; p1<2; p1++)
		{
			for(unsigned int p2=0; p2<2; p2++)
			{
				for(unsigned int p3=0; p3<2; p3++)
				{
						A1.setOutput((bool)p1);
						B1.setOutput((bool)p2);
						C1.setOutput((bool)p3);

						for(unsigned int i=0; i<sumorbe; i++)
							{		
								for(unsigned int j=0; j<(or1.in[i]->inputsNum); j++)
									{or1.in[i]->in[j]->setOutput();}		//Not, vagy vezetek beallitasa
							or1.in[i]->setOutput();				//And kapuk beallitasa
							}
						or1.setOutput();		//utolso "nagy" or kapu beallitasa
						/*cout<<"A valtozo:"<<A1.getOutput()<<endl;
						cout<<"B valtozo:"<<B1.getOutput()<<endl;
						cout<<"C valtozo:"<<C1.getOutput()<<endl;
						cout<<"A halozat kimenete:"<<or1.getOutput()<<endl<<endl;*/

						diagnostic_kiir(meret, (int)or1.getOutput(), hanyadik, os, a1, b1, c1, d1, it);
						hanyadik++;
				}
			}
		}
		}





	}
	else{
		And and1(andbe[q]);									// ha csak egy mintern van nincs or kapu
						for(unsigned int j=0; j<(and1.inputsNum); j++)
						{
							//bekotesek az and kapu(k)ba
								switch(kapukt[k2]){
									case 0:
										and1.in[j]=new Vezetek(1);
										and1.in[j]->in[0]=&A1;
										break;
									case 1:
										and1.in[j]=new Not(1);
										and1.in[j]->in[0]=&A1;
										break;
									case 2:
										and1.in[j]=new Vezetek(1);
										and1.in[j]->in[0]=&B1;
										break;
									case 3:
										and1.in[j]=new Not(1);
										and1.in[j]->in[0]=&B1;
										break;
									case 4:
										and1.in[j]=new Vezetek(1);
										and1.in[j]->in[0]=&C1;
										break;
									case 5:
										and1.in[j]=new Not(1);
										and1.in[j]->in[0]=&C1;
										break;
									case 6:
										and1.in[j]=new Vezetek(1);
										and1.in[j]->in[0]=&D1;
										break;
									case 7:
										and1.in[j]=new Not(1);
										and1.in[j]->in[0]=&D1;
										break;
								}
							k2++;
			}
					if(meret==16)
		{
		for(unsigned int p1=0; p1<2; p1++)
		{
			for(unsigned int p2=0; p2<2; p2++)
			{
				for(unsigned int p3=0; p3<2; p3++)
				{
					for(unsigned int p4=0; p4<2; p4++)
					{
						A1.setOutput((bool)p1);
						B1.setOutput((bool)p2);
						C1.setOutput((bool)p3);
						D1.setOutput((bool)p4);
								for(unsigned int j=0; j<(and1.inputsNum); j++)
									{and1.in[j]->setOutput();}		//Not, vagy vezetek beallitasa
							and1.setOutput();				//And kapuk beallitasa
						/*cout<<"A valtozo:"<<A1.getOutput()<<endl;
						cout<<"B valtozo:"<<B1.getOutput()<<endl;
						cout<<"C valtozo:"<<C1.getOutput()<<endl;
						cout<<"D valtozo:"<<D1.getOutput()<<endl;
						cout<<"A halozat kimenete:"<<and1.getOutput()<<endl<<endl;*/

						diagnostic_kiir(meret, (int)and1.getOutput(), hanyadik, os, a1, b1, c1, d1, it);
						hanyadik++;
					}
				}
			}
		}
		}

		if(meret==8)
		{
				for(unsigned int p1=0; p1<2; p1++)
		{
			for(unsigned int p2=0; p2<2; p2++)
			{
				for(unsigned int p3=0; p3<2; p3++)
				{
						A1.setOutput((bool)p1);
						B1.setOutput((bool)p2);
						C1.setOutput((bool)p3);
		
								for(unsigned int j=0; j<(and1.inputsNum); j++)
									{and1.in[j]->setOutput();}		//Not, vagy vezetek beallitasa
							and1.setOutput();				//And kapuk beallitasa
						/*cout<<"A valtozo:"<<A1.getOutput()<<endl;
						cout<<"B valtozo:"<<B1.getOutput()<<endl;
						cout<<"C valtozo:"<<C1.getOutput()<<endl;
						cout<<"A halozat kimenete:"<<and1.getOutput()<<endl<<endl;*/

						diagnostic_kiir(meret, (int)and1.getOutput(), hanyadik, os, a1, b1, c1, d1, it);
						hanyadik++;
				}
			}
		}
		}
	}
		os.close();

	if (!os) {
		cerr << "Error writing output file: " << fname << endl;
		delete [] andbe;
		return;}


	delete [] andbe;

}
