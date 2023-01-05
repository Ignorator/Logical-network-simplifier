//Szamjegyes minimalizalas
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "minimize.h"
#include <iostream>
#include "push_kapu.h"
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------------------
//kulonbozo osztalyok letrehozasa egyes oszlopokhoz es azok soraihoz 

//elo oszlop es sorai
class binarywss{									//ososztaly, privat tagvaltozokkal. Akar struktura is lehetne.
public:
	unsigned int l;									//ki kell e iratni az aktualis elemet? Alapesetben 0 az erteke, melyre a progam kiirja
	binarywss();
	binarywss(unsigned int l):l(l){};
	virtual ~binarywss(){};
};

class binaryw0:public binarywss{
public:
	unsigned int nul;
	binaryw0():binarywss(0){};
};

class binaryw1:public binarywss{
public:
	unsigned int egy;
	binaryw1():binarywss(0){};
};

class binaryw2:public binarywss{
public:
	unsigned int ketto;
	binaryw2():binarywss(0){};
};

class binaryw3:public binarywss{
public:
	unsigned int harom;
	binaryw3():binarywss(0){};
};

class binaryw4:public binarywss{
public:
	unsigned int negy;
	binaryw4():binarywss(0){};
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//masoik oszlop sorai
class bss{
public:
	unsigned int kulonbseg;
	unsigned int l;
	bss();
	bss(int l):l(l){};
	virtual ~bss(){};
};

class bs01:public bss{									//0. es 1. binaris sulyt fogja kozre
public:
	unsigned int bs0;
	unsigned int bs1;
	bs01():bss(0){};
};

class bs12:public bss{									//1. es 2. biranis suly
public:
	unsigned int bs1;
	unsigned int bs2;
	bs12():bss(0){};
};

class bs23:public bss{									//2. es 3. binaris suly
public:
	unsigned int bs2;
	unsigned int bs3;
	bs23():bss(0){};
};

class bs34:public bss{									//3. es 4. biranis suly
public:
	unsigned int bs3;
	unsigned int bs4;
	bs34():bss(0){};
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//harmadik oszlop elemei
class bsso{													//A masodik oszlop elemi szereplnek itt parosaval
public:
	unsigned int kulonbseg1;
	unsigned int kulonbseg2;
	unsigned int l;
	bsso();
	bsso(unsigned int l):l(l){};
	virtual ~bsso(){};
};

class bsem:public bsso{										//II. oszlop elso masodik
public:
	bs01 e;
	bs12 m;
	bsem():bsso(0){};
};


class bsmh:public bsso{										//II. oszlop masodik harmadik 
public:
	bs12 m;
	bs23 h;
	bsmh():bsso(0){};
};

class bshn:public bsso{										//II. oszlop harmadik negyedik
public:
	bs23 h;
	bs34 n;
	bshn():bsso(0){};
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//negyeidik oszlop elemei
class bn{
public:
	unsigned int kulonbseg1;
	unsigned int kulonbseg2;
	unsigned int kulonbseg12;
	unsigned int l;
	bn();
	bn(int l):l(l){};
	virtual ~bn(){};
};


class bno1:public bn{									//III. oszlop elso masodik
public:
	bsem em;	//II.oszlop elso-masodik
	bsmh mh;	//II.oszlop masodik-harmadik
	bno1():bn(0){};
};

class bno2:public bn{									//III.oszlop masodik harmadik
public:
	bsmh mh;	//II.oszlop masodik-harmadik
	bshn hn;	//II.oszlop harmadik-negyedik
	bno2():bn(0){};
};

//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------

//A fuggveny kezdete:

unsigned int minimize(unsigned int* tomb, unsigned int m, unsigned int* &kapuk, unsigned int &kapum)
{
//SZUKSEGES VALTOZOK DEKLARALASA
 // van-e az aktualis oszlopban kiirando elem?
	int bit01=0;
	int bit12=0;
	int bit23=0;
	int bit34=0;

	int bitem=0;
	int bitmh=0;
	int bithn=0;

	int bnbit1=0;
	int bnbit2=0;
//---------------------------------------------------------------------------------------------------------------------------------------------------
//irtam mar a kepernyore?
	int kiir=0;				
	unsigned int t=0;
	unsigned int tn=0;
	unsigned int tnm=0;
	unsigned int tnc=0;
	unsigned int tnmt=0;
	unsigned int tna=0;
//---------------------------------------------------------------------------------------------------------------------------------------------------	
//osztalyok kezdo inicializalasa

	//elso oszlop
	binaryw0*bw0=new binaryw0[0];
	binaryw1*bw1=new binaryw1[0];
	binaryw2*bw2=new binaryw2[0];
	binaryw3*bw3=new binaryw3[0];
	binaryw4*bw4=new binaryw4[0];

	//masodik oszlop
	bs01 *elso=new bs01[0];
	bs12 *masodik=new bs12[0];
	bs23 *harmadik=new bs23[0];
	bs34 *negyedik=new bs34[0];

	//harmadik oszlop
	bsem *elm=new bsem[0];
	bsmh *mah=new bsmh[0];
	bshn *han=new bshn[0];

	//negyedik oszlop
	bno1*n1=new bno1[0];
	bno2*n2=new bno2[0];
//---------------------------------------------------------------------------------------------------------------------------------------------------
//oszlopok sorainak darabszama

	//elso oszlop (binaris sulyu elemek darabszamai)
	int j0=0;
	int j1=0;
	int j2=0;
	int j3=0;
	int j4=0;

	//masodik oszlop sorai
	int z01=0;
	int z12=0;
	int z23=0;
	int z34=0;

	//masodik oszlop dinam. memfoglalashoz
	int valt1=0;
	int valt2=0;
	int valt3=0;

	//harmadik oszlop sorai
	int sem=0;
	int smh=0;
	int shn=0;

	//negyedik oszlop sorai
	unsigned int ns1=0;
	unsigned int ns2=0;

	//negyedik oszlop dinam.memfoglalashoz
	int valtn1=0;
	int valtn2=0;
//---------------------------------------------------------------------------------------------------------------------------------------------------

	//kulonbozo binaris sulyu szamok
	unsigned int bs0[1]={0};
	unsigned int bs1[4]={1, 2, 4, 8};
	unsigned int bs2[6]={3, 5, 6, 9, 10, 12};
	unsigned int bs3[4]={7, 11, 13, 14};
	unsigned int bs4[1]={15};

	//ABCD minternertekei peremezesnel
	unsigned int A[8]={8,9,10,11,12,13,14,15};	
	unsigned int AN[8]={0,1,2,3,4,5,6,7};			
	unsigned int B[8]={4,5,6,7,12,13,14,15};	
	unsigned int BN[8]={0,1,2,3,8,9,10,11};			
	unsigned int C[8]={2,3,6,7,10,11,14,15};		
	unsigned int CN[8]={0,1,4,5,8,9,12,13};			
	unsigned int D[8]={1,3,5,7,9,11,13,15};			
	unsigned int DN[8]={0,2,4,6,8,10,12,14};		

	//ha csak 8 valtozot ad meg a felhasznalo akkor mas a peremezes:
	if(m == 8)
{
	A[0]=4;A[1]=5;A[2]=6;A[3]=7;A[4]=55;A[5]=55;A[6]=55;A[7]=55;
	AN[0]=0;AN[1]=1;AN[2]=2;AN[3]=3;AN[4]=55;AN[5]=55;AN[6]=55;AN[7]=55;
	B[0]=2;B[1]=3;B[2]=6;B[3]=7;B[4]=55;B[5]=55;B[6]=55;B[7]=55;
	BN[0]=0;BN[1]=1;BN[2]=4;BN[3]=5;BN[4]=55;BN[5]=55;BN[6]=55;BN[7]=55;
	C[0]=1;C[1]=3;C[2]=5;C[3]=7;C[4]=55;C[5]=55;C[6]=55;C[7]=55;
	CN[0]=0;CN[1]=2;CN[2]=4;CN[3]=6;CN[4]=55;CN[5]=55;CN[6]=55;CN[7]=55;
	D[0]=55;D[1]=55;D[2]=55;D[3]=55;D[4]=55;D[5]=55;D[6]=55;D[7]=55;
	DN[0]=55;DN[1]=55;DN[2]=55;DN[3]=55;DN[4]=55;DN[5]=55;DN[6]=55;DN[7]=55;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//A BINARIS SULYOK VIZSGALATA, TOMBOK FELTOLTESE

//I. OSZLOP FELTOLTESE

for(unsigned int i=0; i< 1; i++)
{
	if(tomb[i] == 1)
		{
			binaryw0* tmp0=new binaryw0[1];
			tmp0[0].nul=i;
			delete [] bw0;
			bw0=tmp0;
		j0++;}
}



for(unsigned int e=0; e<4; e++)
{
for(unsigned int i=1; i< 9; i++)
{
	if(tomb[i] == 1 && i==bs1[e])
		{
			binaryw1*tmp=new binaryw1[j1+1];
			for(int w=0; w<j1; w++)
			{
				tmp[w].egy=bw1[w].egy;
			}
			tmp[j1].egy=i;
			delete []bw1;
			bw1=tmp;
			j1++;
		}
}
}
for(unsigned int e=0; e<6; e++)
{
for(unsigned int i=3; i< 13; i++)
{
	if(tomb[i] == 1 && i==bs2[e])
		{
			binaryw2*tmp2=new binaryw2[j2+1];
			for(int w=0; w<j2; w++)
			{
				tmp2[w].ketto=bw2[w].ketto;
			}
			tmp2[j2].ketto=i;
			delete [] bw2;
			bw2=tmp2;
			j2++;
		}
}
}
for(unsigned int e=0; e<4; e++)
{
for(unsigned int i=7; i< 15; i++)
{
	if(tomb[i] == 1 && i==bs3[e])
		{
			binaryw3*tmp3=new binaryw3[3+1];
			for(int w=0; w<j3; w++)
			{
				tmp3[w].harom=bw3[w].harom;
			}
			tmp3[j3].harom=i;
			delete []bw3;
			bw3=tmp3;
			j3++;
		}
}
}


for(unsigned int i=15; i< 16; i++)
{
	if(tomb[i] == 1)
		{
			binaryw4* tmp4=new binaryw4[1];
			tmp4[0].negy=i;
			delete []bw4;
			bw4=tmp4;
			j4++;
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//II. OSZLOP ELEMEINEK FELTOLTESE

if(bw0!=NULL && bw1!=NULL)
{
	for(int x=0; x<j0; x++)
	{
		for(int y=0; y<j1; y++)
		{
			if((bw1[y].egy-bw0[x].nul==1) || (bw1[y].egy-bw0[x].nul)%2 == 0)
			{
				bs01 *tmp=new bs01[z01+1];
				for(int i=0; i<z01; i++)
				{
					tmp[i].bs0=elso[i].bs0;
					tmp[i].bs1=elso[i].bs1;
					tmp[i].kulonbseg=elso[i].kulonbseg;
				}
				tmp[z01].bs0=bw0[x].nul;
				bw0[x].l=1;
				tmp[z01].bs1=bw1[y].egy;
				bw1[y].l=1;
				tmp[z01].kulonbseg=bw1[y].egy-bw0[x].nul;
				delete [] elso;
				elso=tmp;
				z01++;
			}
		}
	}
}


if(bw1!=NULL && bw2!=NULL)
{
	for(int x=0; x<j1; x++)
	{
		for(int y=0; y<j2; y++)
		{
			if(((bw2[y].ketto-bw1[x].egy==1) || (bw2[y].ketto-bw1[x].egy)%2 == 0) && (bw2[y].ketto>bw1[x].egy) && (bw2[y].ketto-bw1[x].egy != 6) && (bw2[y].ketto-bw1[x].egy != 10))
			{
				bs12 *tmp=new bs12[z12+1];
				for(int i=0; i<z12; i++)
				{
					tmp[i].bs1=masodik[i].bs1;
					tmp[i].bs2=masodik[i].bs2;
					tmp[i].kulonbseg=masodik[i].kulonbseg;
				}
				tmp[z12].bs1=bw1[x].egy;
				bw1[x].l=1;
				tmp[z12].bs2=bw2[y].ketto;
				bw2[y].l=1;
				tmp[z12].kulonbseg=bw2[y].ketto-bw1[x].egy;
				delete [] masodik;
				masodik=tmp;
				z12++;
			}
		}
	}
}

if(bw2!=NULL && bw3!=NULL)
{
	for(int x=0; x<j2; x++)
	{
		for(int y=0; y<j3; y++)
		{
			if(((bw3[y].harom-bw2[x].ketto==1) || (bw3[y].harom-bw2[x].ketto)%2 == 0) && (bw3[y].harom>bw2[x].ketto) && (bw3[y].harom-bw2[x].ketto != 6) && (bw3[y].harom-bw2[x].ketto != 10))
			{
				bs23 *tmp=new bs23[z23+1];
				for(int i=0; i<z23; i++)
				{
					tmp[i].bs2=harmadik[i].bs2;
					tmp[i].bs3=harmadik[i].bs3;
					tmp[i].kulonbseg=harmadik[i].kulonbseg;
				}
				tmp[z23].bs2=bw2[x].ketto;
				bw2[x].l=1;
				tmp[z23].bs3=bw3[y].harom;
				bw3[y].l=1;
				tmp[z23].kulonbseg=bw3[y].harom-bw2[x].ketto;
				delete [] harmadik;
				harmadik=tmp;
				z23++;
			}
		}
	}
}

if(bw3!=NULL && bw4!=NULL)
{
	for(int x=0; x<j3; x++)
	{
		for(int y=0; y<j4; y++)
		{
			if(((bw4[y].negy-bw3[x].harom==1) || (bw4[y].negy-bw3[x].harom)%2 == 0) && (bw4[y].negy>bw3[x].harom) && (bw4[y].negy-bw3[x].harom != 6) && (bw4[y].negy-bw3[x].harom != 10))
			{
				bs34 *tmp=new bs34[z34+1];
				for(int i=0; i<z34; i++)
				{
					tmp[i].bs3=negyedik[i].bs3;
					tmp[i].bs4=negyedik[i].bs4;
					tmp[i].kulonbseg=negyedik[i].kulonbseg;
				}
				tmp[z34].bs3=bw3[x].harom;
				bw3[x].l=1;
				tmp[z34].bs4=bw4[y].negy;
				bw4[y].l=1;
				tmp[z34].kulonbseg=bw4[y].negy-bw3[x].harom;
				delete [] negyedik;
				negyedik=tmp;
				z34++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//III.OSZLOP ELEMEINEK FELTOLTESE

if(harmadik!=NULL && negyedik!=NULL)
{
for(int p=0; p<z23; p++)
{
	for(int q=0; q<z34; q++)
	{
		if(((harmadik[p].kulonbseg-negyedik[q].kulonbseg)==0) && ((((negyedik[q].bs3-harmadik[p].bs2)%2 == 0)) || (negyedik[q].bs3-harmadik[p].bs2)==1) && (negyedik[q].bs3-harmadik[p].bs2)!=6 && (negyedik[q].bs3-harmadik[p].bs2)!=10)
		{
			bshn* tmp=new bshn[shn+1];
			for(int i=0; i<shn; i++)
				{tmp[i].h.bs2=han[i].h.bs2;
				 tmp[i].h.bs3=han[i].h.bs3;
				 tmp[i].n.bs3=han[i].n.bs3;
				 tmp[i].n.bs4=han[i].n.bs4;
				 tmp[i].kulonbseg1=han[i].kulonbseg1;
				 tmp[i].kulonbseg2=han[i].kulonbseg2;
				}
			tmp[shn].h.bs2=harmadik[p].bs2;
			tmp[shn].h.bs3=harmadik[p].bs3;
			tmp[shn].n.bs3=negyedik[q].bs3;
			tmp[shn].n.bs4=negyedik[q].bs4;
			tmp[shn].kulonbseg1=harmadik[p].kulonbseg;
			tmp[shn].kulonbseg2=negyedik[q].bs3-harmadik[p].bs2;
			delete []han;
			han=tmp;
			shn++;
	
			harmadik[p].l=1;
			negyedik[q].l=1;
		}
	}
}
}

if(masodik!=NULL && harmadik!=NULL)
{
for(int p=0; p<z12; p++)
{
	for(int q=0; q<z23; q++)
	{
		if(((masodik[p].kulonbseg-harmadik[q].kulonbseg)==0) && (((harmadik[q].bs2-masodik[p].bs1)%2 == 0) || harmadik[q].bs2-masodik[p].bs1 == 1 ) && (harmadik[q].bs3-masodik[p].bs2<100) && (harmadik[q].bs2-masodik[p].bs1)!=6 && (harmadik[q].bs2-masodik[p].bs1)!=10)
		{
			bsmh* tmp=new bsmh[smh+1];
			for(int i=0; i<smh; i++)
				{tmp[i].m.bs1=mah[i].m.bs1;
				 tmp[i].m.bs2=mah[i].m.bs2;
				 tmp[i].h.bs2=mah[i].h.bs2;
				 tmp[i].h.bs3=mah[i].h.bs3;
				 tmp[i].kulonbseg1=mah[i].kulonbseg1;
				 tmp[i].kulonbseg2=mah[i].kulonbseg2;
				}
			tmp[smh].m.bs1=masodik[p].bs1;
			tmp[smh].m.bs2=masodik[p].bs2;
			tmp[smh].h.bs2=harmadik[q].bs2;
			tmp[smh].h.bs3=harmadik[q].bs3;
			tmp[smh].kulonbseg1=masodik[p].kulonbseg;
			tmp[smh].kulonbseg2=harmadik[q].bs2-masodik[p].bs1;
			delete []mah;
			mah=tmp;
			smh++;


			masodik[p].l=1;
			harmadik[q].l=1;
		}
	}
}
}



if(elso!=NULL && masodik!=NULL)
{
for(int p=0; p<z01; p++)
{
	for(int q=0; q<z12; q++)
	{
		if((elso[p].kulonbseg-masodik[q].kulonbseg)==0  &&(((masodik[q].bs1-elso[p].bs0)==1) || ((masodik[q].bs1-elso[p].bs0)%2 == 0)) && (masodik[q].bs1-elso[p].bs0)!=10 && (masodik[q].bs1-elso[p].bs0)!=6)
		{
			bsem* tmp=new bsem[sem+1];
			for(int i=0; i<sem; i++)
				{tmp[i].e.bs0=elm[i].e.bs0;
				 tmp[i].e.bs1=elm[i].e.bs1;
				 tmp[i].m.bs1=elm[i].m.bs1;
				 tmp[i].m.bs2=elm[i].m.bs2;
				 tmp[i].kulonbseg1=elm[i].kulonbseg1;
				 tmp[i].kulonbseg2=elm[i].kulonbseg2;
				}
			tmp[sem].e.bs0=elso[p].bs0;
			tmp[sem].e.bs1=elso[p].bs1;
			tmp[sem].m.bs1=masodik[q].bs1;
			tmp[sem].m.bs2=masodik[q].bs2;
			tmp[sem].kulonbseg1=elso[p].kulonbseg;
			tmp[sem].kulonbseg2=masodik[q].bs1-elso[p].bs0;
			delete []elm;
			elm=tmp;
			sem++;


			elso[p].l=1;
			masodik[q].l=1;
		}
	}
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//III.OSZLOP ELEMEINEK FELEZESE
	//A harmadik oszlop elemei duplikalva jelennek meg, ezeket folosleges ketszer bekotni, ezer kiszurjuk ezeket az elemeket

if(sem>0)
{
	bsem*tmp=new bsem[sem/2];
	int i=0;
	while(i<sem)
	{
		tmp[valt1].e.bs0=elm[i].e.bs0;
		tmp[valt1].e.bs1=elm[i].e.bs1;
		tmp[valt1].m.bs1=elm[i].m.bs1;
		tmp[valt1].m.bs2=elm[i].m.bs2;
		tmp[valt1].kulonbseg1=elm[i].kulonbseg1;
		tmp[valt1].kulonbseg2=elm[i].kulonbseg2;
		valt1++;
			i++;
		for(int j=0; j<valt1; j++)
		{
			for(int q=0; q<sem-valt1; q++)
			{
		if(((elm[i].kulonbseg1==tmp[j].kulonbseg1) && (elm[i].kulonbseg2==tmp[j].kulonbseg2)) || ((elm[i].kulonbseg1==tmp[j].kulonbseg2) && (elm[i].kulonbseg2==tmp[j].kulonbseg1)))
		{i++;j=0;}
			}
		}
	}
	delete []elm;
	elm=tmp;
	sem=sem/2;
}

if(smh>0)
{
	bsmh*tmp=new bsmh[smh/2];
	int i=0;
	while(i<smh)
	{
		tmp[valt2].m.bs1=mah[i].m.bs1;
		tmp[valt2].m.bs2=mah[i].m.bs2;
		tmp[valt2].h.bs2=mah[i].h.bs2;
		tmp[valt2].h.bs3=mah[i].h.bs3;
		tmp[valt2].kulonbseg1=mah[i].kulonbseg1;
		tmp[valt2].kulonbseg2=mah[i].kulonbseg2;
		valt2++;
			i++;
		for(int j=0; j<valt2; j++)
		{
			for(int q=0; q<smh-valt2; q++)
			{
		if(((mah[i].m.bs1==tmp[j].m.bs1) || (mah[i].m.bs1==tmp[j].m.bs2) || (mah[i].m.bs1==tmp[j].h.bs2) || (mah[i].m.bs1==tmp[j].h.bs3)) && ((mah[i].m.bs2==tmp[j].m.bs1) || (mah[i].m.bs2==tmp[j].m.bs2) || (mah[i].m.bs2==tmp[j].h.bs2) || (mah[i].m.bs2==tmp[j].h.bs3)) && ((mah[i].h.bs2==tmp[j].m.bs1) || (mah[i].h.bs2==tmp[j].m.bs2) || (mah[i].h.bs2==tmp[j].h.bs2) || (mah[i].h.bs2==tmp[j].h.bs3)) && ((mah[i].h.bs3==tmp[j].m.bs1) || (mah[i].h.bs3==tmp[j].m.bs2) || (mah[i].h.bs3==tmp[j].h.bs2) || (mah[i].h.bs3==tmp[j].h.bs3)))
		{i++;j=0;}
			}
		}
	}
	delete []mah;
	mah=tmp;
	smh=smh/2;
}

if(shn>0)
{
	bshn*tmp=new bshn[shn/2];
	int i=0;
	while(i<shn)
	{
		tmp[valt3].h.bs2=han[i].h.bs2;
		tmp[valt3].h.bs3=han[i].h.bs3;
		tmp[valt3].n.bs3=han[i].n.bs3;
		tmp[valt3].n.bs4=han[i].n.bs4;
		tmp[valt3].kulonbseg1=han[i].kulonbseg1;
		tmp[valt3].kulonbseg2=han[i].kulonbseg2;
		valt3++;
			i++;
		for(int j=0; j<valt3; j++)
		{
			for( int q=0; q<shn-valt3; q++)
			{
		if(((han[i].kulonbseg1==tmp[j].kulonbseg1) && (han[i].kulonbseg2==tmp[j].kulonbseg2)) || ((han[i].kulonbseg1==tmp[j].kulonbseg2) && (han[i].kulonbseg2==tmp[j].kulonbseg1)))
		{i++;j=0;}
			}
		}
	}
	delete []han;
	han=tmp;
	shn=shn/2;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//HA NEGYVALTOZOS A MEGADOTT FUGGVENY AKKOR A IV. OSZLOPT IS FEL KELL TOLTENI
if(m==16)
{
if(elm!=NULL && mah!=NULL)
{
	for(int p=0; p<sem; p++)
	{
		for(int q=0; q<smh; q++)
		{
			if(	(elm[p].kulonbseg1==mah[q].kulonbseg1) && (elm[p].kulonbseg2==mah[q].kulonbseg2)  )
				{
					bno1* tmp=new bno1[ns1+1];
					for(unsigned int i=0; i<ns1; i++)
						{
							tmp[i].em.e.bs0=n1[i].em.e.bs0;
							tmp[i].em.e.bs1=n1[i].em.e.bs1;
							tmp[i].em.m.bs1=n1[i].em.m.bs1;
							tmp[i].em.m.bs2=n1[i].em.m.bs2;
							tmp[i].mh.m.bs1=n1[i].mh.m.bs1;
							tmp[i].mh.m.bs2=n1[i].mh.m.bs2;
							tmp[i].mh.h.bs2=n1[i].mh.h.bs2;
							tmp[i].mh.h.bs3=n1[i].mh.h.bs3;
							tmp[i].kulonbseg1=n1[i].kulonbseg1;
							tmp[i].kulonbseg2=n1[i].kulonbseg2;
							tmp[i].kulonbseg12=n1[i].kulonbseg12;
						}
				tmp[ns1].em.e.bs0=elm[p].e.bs0;
				tmp[ns1].em.e.bs1=elm[p].e.bs1;
				tmp[ns1].em.m.bs1=elm[p].m.bs1;
				tmp[ns1].em.m.bs2=elm[p].m.bs2;
				tmp[ns1].mh.m.bs1=mah[q].m.bs1;
				tmp[ns1].mh.m.bs2=mah[q].m.bs2;
				tmp[ns1].mh.h.bs2=mah[q].h.bs2;
				tmp[ns1].mh.h.bs3=mah[q].h.bs3;
				tmp[ns1].kulonbseg1=elm[p].kulonbseg1;
				tmp[ns1].kulonbseg2=elm[p].kulonbseg2;
				tmp[ns1].kulonbseg12=mah[q].m.bs1-elm[p].e.bs0;
				delete []n1;
				n1=tmp;
				ns1++;
	
				elm[p].l=1;
				mah[q].l=1;
			}
		}
	}
}

if(mah!=NULL && han!=NULL)
{
	for(int p=0; p<smh; p++)
	{
		for(int q=0; q<shn; q++)
		{
			if(	(mah[p].kulonbseg1==han[q].kulonbseg1) && (mah[p].kulonbseg2==han[q].kulonbseg2)  )
				{
					bno2* tmp=new bno2[ns2+1];
					for(unsigned int i=0; i<ns2; i++)
						{
							tmp[i].mh.m.bs1=n2[i].mh.m.bs1;
							tmp[i].mh.m.bs2=n2[i].mh.m.bs2;
							tmp[i].mh.h.bs2=n2[i].mh.h.bs2;
							tmp[i].mh.h.bs3=n2[i].mh.h.bs3;
							tmp[i].hn.h.bs2=n2[i].hn.h.bs2;
							tmp[i].hn.h.bs3=n2[i].hn.h.bs3;
							tmp[i].hn.n.bs3=n2[i].hn.n.bs3;
							tmp[i].hn.n.bs4=n2[i].hn.n.bs4;
							tmp[i].kulonbseg1=n2[i].kulonbseg1;
							tmp[i].kulonbseg2=n2[i].kulonbseg2;
							tmp[i].kulonbseg12=n2[i].kulonbseg12;
						}
				tmp[ns2].mh.m.bs1=mah[p].m.bs1;
				tmp[ns2].mh.m.bs2=mah[p].m.bs2;
				tmp[ns2].mh.h.bs2=mah[p].h.bs2;
				tmp[ns2].mh.h.bs3=mah[p].h.bs3;
				tmp[ns2].hn.h.bs2=han[q].h.bs2;
				tmp[ns2].hn.h.bs3=han[q].h.bs3;
				tmp[ns2].hn.n.bs3=han[q].n.bs3;
				tmp[ns2].hn.n.bs4=han[q].n.bs4;
				tmp[ns2].kulonbseg1=mah[p].kulonbseg1;
				tmp[ns2].kulonbseg2=mah[p].kulonbseg2;
				tmp[ns2].kulonbseg12=han[q].h.bs2-mah[p].m.bs1;
				delete []n2;
				n2=tmp;
				ns2++;
	
				mah[p].l=1;
				han[q].l=1;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//IV.OSZLOP ELEMEI IS TOBBSZOR KERULNEK BE
	//Ezeket is kiszurjuk
if(ns1>0)
{
	bno1*tmp=new bno1[ns1/2];
	unsigned int i=0;
	while(i<ns1)
	{    // a legelsõ elemet mindenképp átmásolom
		tmp[valtn1].em.e.bs0=n1[i].em.e.bs0;
		tmp[valtn1].em.e.bs1=n1[i].em.e.bs1;
		tmp[valtn1].em.m.bs1=n1[i].em.m.bs1;
		tmp[valtn1].em.m.bs2=n1[i].em.m.bs2;
		tmp[valtn1].mh.m.bs1=n1[i].mh.m.bs1;
		tmp[valtn1].mh.m.bs2=n1[i].mh.m.bs2;
		tmp[valtn1].mh.h.bs2=n1[i].mh.h.bs2;
		tmp[valtn1].mh.h.bs3=n1[i].mh.h.bs3;
		tmp[valtn1].kulonbseg1=n1[i].kulonbseg1;
		tmp[valtn1].kulonbseg2=n1[i].kulonbseg2;
		tmp[valtn1].kulonbseg12=n1[i].kulonbseg12;
		valtn1++;
			i++;
		for(int j=0; j<valtn1; j++)
		{
			for(unsigned 
				int q=0; q<ns1-valtn1; q++)
			{
				if(((n1[i].kulonbseg1==tmp[j].kulonbseg1) && (n1[i].kulonbseg2==tmp[j].kulonbseg2) && (n1[i].kulonbseg12==tmp[j].kulonbseg12)) || ((n1[i].kulonbseg1==tmp[j].kulonbseg2) && (n1[i].kulonbseg2==tmp[j].kulonbseg1) && (n1[i].kulonbseg12==tmp[j].kulonbseg12)) || ((n1[i].kulonbseg1==tmp[j].kulonbseg1) && (n1[i].kulonbseg2==tmp[j].kulonbseg12) && (n1[i].kulonbseg12==tmp[j].kulonbseg2)) || ((n1[i].kulonbseg1==tmp[j].kulonbseg12) && (n1[i].kulonbseg2==tmp[j].kulonbseg2) && (n1[i].kulonbseg12==tmp[j].kulonbseg1)) || ((n1[i].kulonbseg1==tmp[j].kulonbseg12) && (n1[i].kulonbseg2==tmp[j].kulonbseg1) && (n1[i].kulonbseg12==tmp[j].kulonbseg2)) || ((n1[i].kulonbseg1==tmp[j].kulonbseg2) && (n1[i].kulonbseg2==tmp[j].kulonbseg12) && (n1[i].kulonbseg12==tmp[j].kulonbseg1)))
				{i++;j=0;}
			}
		}
	}
	delete []n1;
	n1=tmp;
	ns1=valtn1;
}

if(ns2>0)
{
	bno2*tmp=new bno2[ns2/2];
	unsigned int i=0;
	while(i<ns2)
	{    // a legelsõ elemet mindenképp átmásolom
		tmp[valtn2].mh.m.bs1=n2[i].mh.m.bs1;
		tmp[valtn2].mh.m.bs2=n2[i].mh.m.bs2;
		tmp[valtn2].mh.h.bs2=n2[i].mh.h.bs2;
		tmp[valtn2].mh.h.bs3=n2[i].mh.h.bs3;
		tmp[valtn2].hn.h.bs2=n2[i].hn.h.bs2;
		tmp[valtn2].hn.h.bs3=n2[i].hn.h.bs3;
		tmp[valtn2].hn.n.bs3=n2[i].hn.n.bs3;
		tmp[valtn2].hn.n.bs4=n2[i].hn.n.bs4;
		tmp[valtn2].kulonbseg1=n2[i].kulonbseg1;
		tmp[valtn2].kulonbseg2=n2[i].kulonbseg2;
		tmp[valtn2].kulonbseg12=n2[i].kulonbseg12;
		valtn2++;
			i++;
		for(int j=0; j<valtn2; j++)
		{
			for(unsigned int q=0; q<ns2-valtn2; q++)
			{
		if(((n2[i].kulonbseg1==tmp[j].kulonbseg1) && (n2[i].kulonbseg2==tmp[j].kulonbseg2) && (n2[i].kulonbseg12==tmp[j].kulonbseg12)) || ((n2[i].kulonbseg1==tmp[j].kulonbseg2) && (n2[i].kulonbseg2==tmp[j].kulonbseg1) && (n2[i].kulonbseg12==tmp[j].kulonbseg12)) || ((n2[i].kulonbseg1==tmp[j].kulonbseg1) && (n2[i].kulonbseg2==tmp[j].kulonbseg12) && (n2[i].kulonbseg12==tmp[j].kulonbseg2)) || ((n2[i].kulonbseg1==tmp[j].kulonbseg12) && (n2[i].kulonbseg2==tmp[j].kulonbseg2) && (n2[i].kulonbseg12==tmp[j].kulonbseg1)) || ((n2[i].kulonbseg1==tmp[j].kulonbseg12) && (n2[i].kulonbseg2==tmp[j].kulonbseg1) && (n2[i].kulonbseg12==tmp[j].kulonbseg2)) || ((n2[i].kulonbseg1==tmp[j].kulonbseg2) && (n2[i].kulonbseg2==tmp[j].kulonbseg12) && (n2[i].kulonbseg12==tmp[j].kulonbseg1)))
		{i++;j=0;}
			}
		}
	}
	delete []n2;
	n2=tmp;
	ns2=valtn2;
}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//KIIRHATJUK AZ OSZLOPOKAT, AZOK SORAIT ES ELEMEIT


std::cout<<"Az egyszerusitett fuggveny:"<<endl;

std::cout<<"I. oszlop elemei:"<<endl;
for(int v=0; v<j0; v++)
	std::cout<<bw0[v].nul<<"\t"<<bw0[v].l<<endl;

std::cout<<"--------"<<endl;
for(int v=0; v<j1; v++)
	std::cout<<bw1[v].egy<<"\t"<<bw1[v].l<<endl;

std::cout<<"--------"<<endl;
for(int v=0; v<j2; v++)
	std::cout<<bw2[v].ketto<<"\t"<<bw2[v].l<<endl;

std::cout<<"--------"<<endl;
for(int v=0; v<j3; v++)
	std::cout<<bw3[v].harom<<"\t"<<bw3[v].l<<endl;

std::cout<<"--------"<<endl;
for(int v=0; v<j4; v++)
	std::cout<<bw4[v].negy<<"\t"<<bw4[v].l<<endl;

std::cout<<endl;
std::cout<<"II. oszlop elemei:"<<endl;
for(int i=0; i<z01; i++)
{
	std::cout<<elso[i].bs0<<","<<elso[i].bs1<<"("<<elso[i].kulonbseg<<")"<<"\t"<<elso[i].l<<endl;
}
std::cout<<"--------"<<endl;
for(int i=0; i<z12; i++)
{
	std::cout<<masodik[i].bs1<<","<<masodik[i].bs2<<"("<<masodik[i].kulonbseg<<")"<<"\t"<<masodik[i].l<<endl;
}

std::cout<<"--------"<<endl;
for(int i=0; i<z23; i++)
{
	std::cout<<harmadik[i].bs2<<","<<harmadik[i].bs3<<"("<<harmadik[i].kulonbseg<<")"<<"\t"<<harmadik[i].l<<endl;
}

std::cout<<"--------"<<endl;
for(int i=0; i<z34; i++)
{
	std::cout<<negyedik[i].bs3<<","<<negyedik[i].bs4<<"("<<negyedik[i].kulonbseg<<")"<<"\t"<<negyedik[i].l<<endl;
}

std::cout<<endl;
std::cout<<"III. oszlop elemei:"<<endl;
for(int i=0; i<sem; i++)
{
	std::cout<<elm[i].e.bs0<<","<<elm[i].e.bs1<<","<<elm[i].m.bs1<<","<<elm[i].m.bs2<<"("<<elm[i].kulonbseg1<<","<<elm[i].kulonbseg2<<")"<<"\t"<<elm[i].l<<endl;
}

std::cout<<"--------"<<endl;
for(int i=0; i<smh; i++)
{
	std::cout<<mah[i].m.bs1<<","<<mah[i].m.bs2<<","<<mah[i].h.bs2<<","<<mah[i].h.bs3<<"("<<mah[i].kulonbseg1<<","<<mah[i].kulonbseg2<<")"<<"\t"<<mah[i].l<<endl;
}

std::cout<<"--------"<<endl;
for(int i=0; i<shn; i++)
{
	std::cout<<han[i].h.bs2<<","<<han[i].h.bs3<<","<<han[i].n.bs3<<","<<han[i].n.bs4<<"("<<han[i].kulonbseg1<<","<<han[i].kulonbseg2<<")"<<"\t"<<han[i].l<<endl;
}

cout<<endl;
cout<<"IV. oszlop elemi:"<<endl;
for(unsigned int i=0; i<ns1; i++)
{
	std::cout<<n1[i].em.e.bs0<<","<<n1[i].em.e.bs1<<","<<n1[i].em.m.bs1<<","<<n1[i].em.m.bs2<<","<<n1[i].mh.m.bs1<<","<<n1[i].mh.m.bs2<<","<<n1[i].mh.h.bs2<<","<<n1[i].mh.h.bs3<<"("<<n1[i].kulonbseg1<<","<<n1[i].kulonbseg2<<","<<n1[i].kulonbseg12<<")"<<"\t"<<n1[i].l<<endl;
}

std::cout<<"--------"<<endl;
for(unsigned int i=0; i<ns2; i++)
{
	std::cout<<n2[i].mh.m.bs1<<","<<n2[i].mh.m.bs2<<","<<n2[i].mh.h.bs2<<","<<n2[i].mh.h.bs3<<","<<n2[i].hn.h.bs2<<","<<n2[i].hn.h.bs3<<","<<n2[i].hn.n.bs3<<","<<n2[i].hn.n.bs4<<"("<<n2[i].kulonbseg1<<","<<n2[i].kulonbseg2<<","<<n2[i].kulonbseg12<<")"<<"\t"<<n2[i].l<<endl;
}
std::cout<<endl;



//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//MEGVIZSGALJUK HOGY AZ ADOTT OSZLOPOKBAN VAN E ELEM AMIT MEG KELL MAJD VALOSITANI A FUGGVENYBEN
for(int r=0; r<sem; r++)
{
	if(elm[r].l==0)
		bitem=1;
}

for(int r=0; r<smh; r++)
{
	if(mah[r].l==0)
		bitmh=1;
}

for(int r=0; r<shn; r++)
{
	if(han[r].l==0)
		bithn=1;
}

for(int r=0; r<z34; r++)
{
	if(negyedik[r].l ==0)
		 bit34=1;
}

for(int r=0; r<z23; r++)
{
	if(harmadik[r].l ==0)
		 bit23=1;
}

for(int r=0; r<z12; r++)
{
	if(masodik[r].l ==0)
		 bit12=1;
}

for(int r=0; r<z01; r++)
{
	if(elso[r].l ==0)
		 bit01=1;
}

for(unsigned int r=0; r<ns1; r++)
{
	if(n1[r].l==0)
		bnbit1=1;
}

for(unsigned int r=0; r<ns2; r++)
{
	if(n2[r].l==0)
		bnbit2=1;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//KIIRJUK A KEPERNYORE A MEGFELELO ELEMEKET ES ATADJUK OKET AZ ATALAKITO FUGGVENYNEK, AMI A HALOZAT EPITESET KESZITI ELO
if(bw0[0].l==0 && m==16)
{
	push_kapu(kapuk, kapum, "ANBNCNDN");
	cout<<"ANBNCNDN";
	tna++;
	tnc++;
	tnm++;
	tn++;
	t++;
}

if(bw0[0].l==0 && m==8)
{
	push_kapu(kapuk, kapum, "ANBNCN");
	cout<<"ANBNCN";
	tna++;
	tnc++;
	tnm++;
	tn++;
	t++;
}



for(int i=0; i<j1; i++)
{
	if(tna>0 && bw1[i].l==0 && tnc>0 && i==0)
		{cout<<"+";push_kapu(kapuk, kapum,"+");}
	
	if(bw1[i].l==0)
	{
		if(i>0 && tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
			kiir++;
		for(int j=0; j<8; j++)
		{
			if(bw1[i].egy==A[j])
			{cout<<"A";push_kapu(kapuk, kapum,"A");}
			if(bw1[i].egy==AN[j])
			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
			if(bw1[i].egy==B[j])
			{cout<<"B";push_kapu(kapuk, kapum,"B");}
			if(bw1[i].egy==BN[j])
			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
			if(bw1[i].egy==C[j])
			{cout<<"C";push_kapu(kapuk, kapum,"C");}
			if(bw1[i].egy==CN[j])
			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
			if(bw1[i].egy==D[j])
			{cout<<"D";push_kapu(kapuk, kapum,"D");}
			if(bw1[i].egy==DN[j])
			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
		}
			tnm++;
			tnc++;
			t++;
			tna++;
	}
}

for(int i=0; i<j2; i++)
{
	if(tna>0 && bw2[i].l==0 && tnc>0 && i==0)
		{cout<<"+";push_kapu(kapuk, kapum,"+");}
	
	if(bw2[i].l==0)
	{
		if(i>0 && tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
			kiir++;
		for(int j=0; j<8; j++)
		{
			if(bw2[i].ketto==A[j])
			{cout<<"A";push_kapu(kapuk, kapum,"A");}
			if(bw2[i].ketto==AN[j])
			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
			if(bw2[i].ketto==B[j])
			{cout<<"B";push_kapu(kapuk, kapum,"B");}
			if(bw2[i].ketto==BN[j])
			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
			if(bw2[i].ketto==C[j])
			{cout<<"C";push_kapu(kapuk, kapum,"C");}
			if(bw2[i].ketto==CN[j])
			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
			if(bw2[i].ketto==D[j])
			{cout<<"D";push_kapu(kapuk, kapum,"D");}
			if(bw2[i].ketto==DN[j])
			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
		}
			tnm++;
			tnc++;
			t++;
			tna++;
	}

}

for(int i=0; i<j3; i++)
{
	if(tna>0 && bw3[i].l==0 && tnc>0 && i==0)
		{cout<<"+";push_kapu(kapuk, kapum,"+");}
	if(bw3[i].l==0)
	{
		if(i>0 && tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
			kiir++;
		for(int j=0; j<8; j++)
		{
			if(bw3[i].harom==A[j])
			{cout<<"A";push_kapu(kapuk, kapum,"A");}
			if(bw3[i].harom==AN[j])
			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
			if(bw3[i].harom==B[j])
			{cout<<"B";push_kapu(kapuk, kapum,"B");}
			if(bw3[i].harom==BN[j])
			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
			if(bw3[i].harom==C[j])
			{cout<<"C";push_kapu(kapuk, kapum,"C");}
			if(bw3[i].harom==CN[j])
			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
			if(bw3[i].harom==D[j])
			{cout<<"D";push_kapu(kapuk, kapum,"D");}
			if(bw3[i].harom==DN[j])
			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
		}
			tnm++;
			tnc++;
			t++;
			tna++;
	}

}

for(int i=0; i<j4; i++)
{
	if(tna>0 && bw4[i].l==0 && tnc>0 &&i==0)
		{cout<<"+";push_kapu(kapuk, kapum,"+");}
	if(bw4[i].l==0)
	{
		if(i>0 && tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
			kiir++;
		for(int j=0; j<8; j++)
		{
			if(bw4[i].negy==A[j])
			{cout<<"A";push_kapu(kapuk, kapum,"A");}
			if(bw4[i].negy==AN[j])
			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
			if(bw4[i].negy==B[j])
			{cout<<"B";push_kapu(kapuk, kapum,"B");}
			if(bw4[i].negy==BN[j])
			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
			if(bw4[i].negy==C[j])
			{cout<<"C";push_kapu(kapuk, kapum,"C");}
			if(bw4[i].negy==CN[j])
			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
			if(bw4[i].negy==D[j])
			{cout<<"D";push_kapu(kapuk, kapum,"D");}
			if(bw4[i].negy==DN[j])
			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
		}
			tnm++;
			tnc++;
			t++;
			tna++;
	}
}








if(z01>0 && bit01==1)
{
	for(int p=0; p<z01; p++)
	{
			if((tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0 || kiir>0) && elso[p].l==0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
		if(elso[p].l==0)
		{
				kiir++;
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == A[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == A[j])
					{cout<<"A";push_kapu(kapuk, kapum,"A");}
				}
			}
		}

		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == AN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == AN[j])
					{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
				}
			}
		}

		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == B[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == B[j])
					{cout<<"B";push_kapu(kapuk, kapum,"B");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == BN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == BN[j])
					{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == C[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == C[j])
					{cout<<"C";push_kapu(kapuk, kapum,"C");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == CN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == CN[j])
					{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == D[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == D[j])
					{cout<<"D";push_kapu(kapuk, kapum,"D");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(elso[p].bs0 == DN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(elso[p].bs1 == DN[j])
					{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
				}
			}
		}
		t++;
		tn++;}}

}
if(z12>0 && bit12==1)
{
	for(int p=0; p<z12; p++)
	{
		if((tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0 || kiir>0) && masodik[p].l==0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
		if(masodik[p].l==0)
		{
				kiir++;
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == A[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == A[j])
					{cout<<"A";push_kapu(kapuk, kapum,"A");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == AN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == AN[j])
					{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == B[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == B[j])
					{cout<<"B";push_kapu(kapuk, kapum,"B");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == BN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == BN[j])
					{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == C[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == C[j])
					{cout<<"C";push_kapu(kapuk, kapum,"C");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == CN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == CN[j])
					{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == D[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == D[j])
					{cout<<"D";push_kapu(kapuk, kapum,"D");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(masodik[p].bs1 == DN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(masodik[p].bs2 == DN[j])
					{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
				}
			}
		}
		t++;
		tn++;}}
}

if(z23>0 && bit23==1)
{
	for(int p=0; p<z23; p++)
	{
			if((tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0|| kiir>0) && harmadik[p].l==0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
		if(harmadik[p].l==0)
		{
				kiir++;
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == A[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == A[j])
					{cout<<"A";push_kapu(kapuk, kapum,"A");}
				}
			}
		}

		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == AN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == AN[j])
					{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
				}
			}
		}	
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == B[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == B[j])
					{cout<<"B";push_kapu(kapuk, kapum,"B");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == BN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == BN[j])
					{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == C[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == C[j])
					{cout<<"C";push_kapu(kapuk, kapum,"C");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == CN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == CN[j])
					{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == D[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == D[j])
					{cout<<"D";push_kapu(kapuk, kapum,"D");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(harmadik[p].bs2 == DN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(harmadik[p].bs3 == DN[j])
					{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
				}
			}
		}
		t++;
		tn++;}}

}


if(z34>0 && bit34==1)
{
	
	for(int p=0; p<z34; p++)
	{
			if((tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0 || kiir>0) && negyedik[p].l==0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
		if(negyedik[p].l==0)
		{
				kiir++;
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == A[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == A[j])
					{cout<<"A";push_kapu(kapuk, kapum,"A");}
				}
			}
		}

		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == AN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == AN[j])
					{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == B[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == B[j])
					{cout<<"B";push_kapu(kapuk, kapum,"B");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == BN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == BN[j])
					{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == C[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == C[j])
					{cout<<"C";push_kapu(kapuk, kapum,"C");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == CN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == CN[j])
					{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == D[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == D[j])
					{cout<<"D";push_kapu(kapuk, kapum,"D");}
				}
			}
		}
		for(int i=0; i<8; i++)
		{
			if(negyedik[p].bs3 == DN[i])
			{
				for(int j=0; j<8; j++)
				{
					if(negyedik[p].bs4 == DN[j])
					{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
				}
			}
		}
		t++;tn++;}
	}
}

if(sem>0 && bitem==1)
{
	if(tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
	for(int p=0; p<sem; p++)
		{ 
			if( elm[p].l==0 && p>0 && kiir>0)
			{cout<<"+";push_kapu(kapuk, kapum,"+");}
			if(elm[p].l==0)
			{
					kiir++;
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == A[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == A[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == A[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==A[m])
											{cout<<"A";push_kapu(kapuk, kapum,"A");}
										}
									}
								}
							}
						}
					}
			}
	



	 
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == AN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == AN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == AN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==AN[m])
											{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
										}
									}
								}
							}
						}
					}
			}
	



	
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == B[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == B[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == B[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==B[m])
											{cout<<"B";push_kapu(kapuk, kapum,"B");}
										}
									}
								}
							}
						}
					}
			}
	



	 
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == BN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == BN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == BN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==BN[m])
											{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
										}
									}
								}
							}
						}
					}
			}
	


	 
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == C[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == C[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == C[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==C[m])
											{cout<<"C";push_kapu(kapuk, kapum,"C");}
										}
									}
								}
							}
						}
					}
			}
	



	 
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == CN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == CN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == CN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==CN[m])
											{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
										}
									}
								}
							}
						}
					}
			}
	



	
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == D[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == D[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == D[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==D[m])
											{cout<<"D";push_kapu(kapuk, kapum,"D");}
										}
									}
								}
							}
						}
					}
			}
	



	
			for(int i=0; i<8; i++)
				{
					if (elm[p].e.bs0 == DN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(elm[p].e.bs1 == DN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(elm[p].m.bs1 == DN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(elm[p].m.bs2==DN[m])
											{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
										}
									}
								}
							}
						}
					}
			}
	}
}
	t++;
}

if(smh>0 && bitmh==1)
{
	if(tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
	for(int p=0; p<smh; p++)
		{ 
			if(mah[p].l==0 && p>0 && kiir>0)
			{
				{cout<<"+";push_kapu(kapuk, kapum,"+");}
			}
			if(mah[p].l==0)
			{
					kiir++;
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == A[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == A[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == A[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==A[m])
											{cout<<"A";push_kapu(kapuk, kapum,"A");}
										}
									}
								}
							}
						}
					}
			}
	

	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == AN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == AN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == AN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==AN[m])
											{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
										}
									}
								}
							}
						}
					}
			}
	


	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == B[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == B[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == B[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==B[m])
											{cout<<"B";push_kapu(kapuk, kapum,"B");}
										}
									}
								}
							}
						}
					}
			}
	


	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == BN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == BN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == BN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==BN[m])
											{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
										}
									}
								}
							}
						}
					}
			}
	


	 
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == C[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == C[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == C[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==C[m])
											{cout<<"C";push_kapu(kapuk, kapum,"C");}
										}
									}
								}
							}
						}
					}
			}
	


	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == CN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == CN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == CN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==CN[m])
											{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
										}
									}
								}
							}
						}
					}
			}
	


	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == D[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == D[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == D[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==D[m])
											{cout<<"D";push_kapu(kapuk, kapum,"D");}
										}
									}
								}
							}
						}
					}
			}
	


	
			for(int i=0; i<8; i++)
				{
					if (mah[p].m.bs1 == DN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(mah[p].m.bs2 == DN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(mah[p].h.bs2 == DN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(mah[p].h.bs3==DN[m])
											{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
										}
									}
								}
							}
						}
					}

			}
}

	}
		t++;
}


if(shn>0 && bithn==1)
{
	if(tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
	for(int p=0; p<shn; p++)
		{ 
			if(p>0 && han[p].l==0 && kiir>0)
			{cout<<"+";push_kapu(kapuk, kapum,"+");}
			if(han[p].l==0)
			{
					kiir++;
			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == A[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == A[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == A[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==A[m])
											{cout<<"A";push_kapu(kapuk, kapum,"A");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == AN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == AN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == AN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==AN[m])
											{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == B[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == B[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == B[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==B[m])
											{cout<<"B";push_kapu(kapuk, kapum,"B");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == BN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == BN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == BN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==BN[m])
											{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == C[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == C[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == C[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==C[m])
											{cout<<"C";push_kapu(kapuk, kapum,"C");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == CN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == CN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == CN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==CN[m])
											{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == D[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == D[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == D[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==D[m])
											{cout<<"D";push_kapu(kapuk, kapum,"D");}
										}
									}
								}
							}
						}
					}
			}

			for(int i=0; i<8; i++)
				{
					if (han[p].h.bs2 == DN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(han[p].h.bs3 == DN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(han[p].n.bs3 == DN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(han[p].n.bs4==DN[m])
											{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
										}
									}
								}
							}
						}
					}
			}

	}

}
	t++;
}

if(ns1>0 && bnbit1==1)
{
	if(tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0 || tnmt>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
	for(unsigned int p=0; p<ns1; p++)
		{ 
			if( n1[p].l==0 && p>0 && kiir>0)
			{cout<<"+";push_kapu(kapuk, kapum,"+");}
			if(n1[p].l==0)
			{
					kiir++;
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == A[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == A[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == A[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==A[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==A[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==A[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==A[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==A[x])
																			{cout<<"A";push_kapu(kapuk, kapum,"A");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == AN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == AN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == AN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==AN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==AN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==AN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==AN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==AN[x])
																			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == B[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == B[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == B[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==B[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==B[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==B[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==B[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==B[x])
																			{cout<<"B";push_kapu(kapuk, kapum,"B");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == BN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == BN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == BN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==BN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==BN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==BN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==BN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==BN[x])
																			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == C[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == C[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == C[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==C[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==C[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==C[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==C[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==C[x])
																			{cout<<"C";push_kapu(kapuk, kapum,"C");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == CN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == CN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == CN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==CN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==CN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==CN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==CN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==CN[x])
																			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == D[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == D[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == D[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==D[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==D[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==D[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==D[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==D[x])
																			{cout<<"D";push_kapu(kapuk, kapum,"D");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			for(int i=0; i<8; i++)
				{
					if (n1[p].em.e.bs0 == DN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n1[p].em.e.bs1 == DN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n1[p].em.m.bs1 == DN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n1[p].em.m.bs2==DN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n1[p].mh.m.bs1==DN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n1[p].mh.m.bs2==DN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n1[p].mh.h.bs2==DN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n1[p].mh.h.bs3==DN[x])
																			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}




			}
		}
	tnmt++;
}



if(ns2>0 && bnbit2==1)
{
	if(tn>0 || tnm>0 || t>0 || tna>>0 || tnc>0 || tnmt>0)
	{cout<<"+";push_kapu(kapuk, kapum,"+");}
	for(unsigned int p=0; p<ns2; p++)
		{ 
			if( n2[p].l==0 && p>0 && kiir>0)
			{cout<<"+";push_kapu(kapuk, kapum,"+");}
			if(n2[p].l==0)
			{
					kiir++;
			for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == A[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == A[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == A[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==A[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==A[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==A[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==A[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==A[x])
																			{cout<<"A";push_kapu(kapuk, kapum,"A");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
				for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == AN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == AN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == AN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==AN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==AN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==AN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==AN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==AN[x])
																			{cout<<"AN";push_kapu(kapuk, kapum,"AN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
					for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == B[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == B[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == B[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==B[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==B[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==B[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==B[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==B[x])
																			{cout<<"B";push_kapu(kapuk, kapum,"B");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
						for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == BN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == BN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == BN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==BN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==BN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==BN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==BN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==BN[x])
																			{cout<<"BN";push_kapu(kapuk, kapum,"BN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
							for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == C[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == C[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == C[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==C[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==C[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==C[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==C[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==C[x])
																			{cout<<"C";push_kapu(kapuk, kapum,"C");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
								for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == CN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == CN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == CN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==CN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==CN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==CN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==CN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==CN[x])
																			{cout<<"CN";push_kapu(kapuk, kapum,"CN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
									for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == D[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == D[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == D[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==D[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==D[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==D[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==D[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==D[x])
																			{cout<<"D";push_kapu(kapuk, kapum,"D");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
										for(int i=0; i<8; i++)
				{
					if (n2[p].mh.m.bs1 == DN[i])
					{
						for(int j=0; j<8; j++)
						{
							if(n2[p].mh.m.bs2 == DN[j])
							{
								for(int k=0; k<8; k++)
								{
									if(n2[p].mh.h.bs2 == DN[k])
									{
										for(int m=0; m<8; m++)
										{
											if(n2[p].mh.h.bs3==DN[m])
											{
												for(int n=0; n<8; n++)
												{
													if(n2[p].hn.h.bs2==DN[n])
													{
														for(int o=0; o<8; o++)
														{
															if(n2[p].hn.h.bs3==DN[o])
															{
																for(int w=0; w<8; w++)
																{
																	if(n2[p].hn.n.bs3==DN[w])
																	{
																		for(int x=0; x<8; x++)
																		{
																			if(n2[p].hn.n.bs4==DN[x])
																			{cout<<"DN";push_kapu(kapuk, kapum,"DN");}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
	}
	tnmt++;
}
cout<<endl;
cout<<endl;
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
//TOMBOK FELSZABADITASA

delete [] bw0;
delete [] bw1;
delete []bw2;
delete []bw3;
delete []bw4;

delete []n1;
delete []n2;

delete []elso;
delete []masodik;
delete []harmadik;
delete []negyedik;

delete []elm;
delete []mah;
delete []han;

return kapum;
}