// DFA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "dfa.h"

using namespace std;


int main()
{
	DFA A("S" , "a");
	A.addState("A");
	A.addState("B");
	A.addState("C");
	A.addState("D");
	A.addState("E");
	A.addState("F");
	A.addFinal("C");
	A.addFinal("F");
	/*A.addRule("SaA");
	A.addRule("SbD");
	A.addRule("AbB");
	A.addRule("AaA");
	A.addRule("BaE");
	A.addRule("BbC");
	A.addRule("CaC");
	A.addRule("CbE");
	A.addRule("DaE");
	A.addRule("DbF");
	A.addRule("EaE");
	A.addRule("EbE");
	A.addRule("FaC");
	A.addRule("FbE");*/
	A.addRule("AaA");
	A.addRule("BaB");
	A.addRule("CaC");
	A.addRule("DaD");
	A.addRule("EaE");
	A.makeMinimal();
	cout<<A;
	system("pause");
	return 0;
}