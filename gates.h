#pragma once

// oszosztaly letrehozasa, minden elem rendelkezik majd ezekkel a tulajdonsagokkal

class Gate{
protected:
	unsigned int inputsNum;			//a kapuba kotott bemeno ertekek darabszama
	bool output;					//a kapu kimenete
	Gate** in;						//a kapuba kotott elemekre mutato tomb
public:
	Gate(unsigned int inNum=0):inputsNum(inNum){};
	virtual ~Gate(){
		};
	virtual void setOutput(){};
	virtual bool getOutput()const=0;
	friend void build(unsigned int* kapukt, unsigned int kapukm, unsigned int meret, unsigned int*it);


};

