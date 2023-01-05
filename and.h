#pragma once
#include "gates.h"

class And:public Gate{
public:
	And(unsigned int bemenet):Gate(bemenet){
		this->in=new Gate*[bemenet];
		};
	And(){};
	~And(){
		for(unsigned int i=0; i<inputsNum; i++)
		{
			delete [] in[i];
		}
		delete [] in;
		};
	void setOutput(){
		if(inputsNum==1)
		{output=in[0]->getOutput();
		return;}
		bool a=true;
		for(unsigned int i=0; i<inputsNum; i++)
		{
			if(in[i]->getOutput()!=a)
				{output=false;
			return;}
		}
		output=true;
	}
	bool getOutput()const{return output;}

};