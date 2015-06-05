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
	A.addRule("AaA");
	A.addRule("SaA");
	A.addRule("SbB");
	A.addRule("BaC");
	A.addRule("CbD");
	A.addRule("DaD");
	A.addRule("EaE");
	cout<<A.read("babba")<<endl;
	system("pause");
	return 0;
}
