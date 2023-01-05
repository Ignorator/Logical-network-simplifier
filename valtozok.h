#pragma once
#include "gates.h"



class A:public Gate{
public:
	A(){};
	~A(){};
	void setOutput(){output=1;}
	void setOutput(bool v){
		output=v;
	}
	bool getOutput()const{return output;}

};

class B:public Gate{
public:
	B(){};
	~B(){};
	void setOutput(){output=1;}
	void setOutput(bool v){
		output=v;
	}
	bool getOutput()const{return output;}
};

class C:public Gate{
public:
	C(){};
	~C(){};
	void setOutput(){output=1;}
	void setOutput(bool v){
		output=v;
	}
	bool getOutput()const{return output;}
};

class D:public Gate{
public:
	D(){};
	~D(){};
	void setOutput(){output=1;}
	void setOutput(bool v){
		output=v;
	}
	bool getOutput()const{return output;}
};


