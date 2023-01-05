#pragma once
#include "gates.h"

class Or:public Gate{
public:
	Or(unsigned int bemenet):Gate(bemenet){
		
	this->in=new Gate*[bemenet];};
	Or(){}
	~Or(){
		for(unsigned int i=0; i<inputsNum; i++)
		{
			delete [] in[i];
		}
		delete [] in;
		};
	void setOutput(){
		bool a=false;
	for(unsigned int i=0; i<inputsNum; i++)
	{
		if(a!=in[i]->getOutput())
			{output=true;
		return;}
	}
	output= false;
	return;
	}
	bool getOutput()const{return output;}


};