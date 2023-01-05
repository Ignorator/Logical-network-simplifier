#pragma once
#include "gates.h"

class Not:public Gate{
public:
	Not(unsigned int bemenet):Gate(bemenet){
		this->in=new Gate*[bemenet];
		};
	Not(){};
	~Not(){for(unsigned int i=0; i<1; i++)
		{
			delete [] in;
		}
		};
	void setOutput(){
		if (this->in[0]->getOutput()==true)
			{output=false;
				return;}
		if (this->in[0]->getOutput()==false)
			{output=true;
				return;}
	}
	bool getOutput()const{return output;}
};

class Vezetek:public Gate{
public:
	Vezetek(unsigned int bemenet):Gate(bemenet){
		this->in=new Gate*[bemenet];}
	Vezetek(){};
	~Vezetek(){for(unsigned int i=0; i<1; i++)
		{
			delete [] in;
		}}
	void setOutput(){
		output=this->in[0]->getOutput();
		}
	bool getOutput()const{return output;}
};
