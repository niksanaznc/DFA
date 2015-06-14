// DFA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "dfa.h"

using namespace std;

void testMinimization()
{
	DFA A("S" , "ab");
	A.addState("A");
	A.addState("B");
	A.addState("C");
	A.addState("D");
	A.addState("E");
	A.addState("F");
	A.addState("G");
	A.addState("H");
	A.addFinal("C");
	A.addFinal("B");
	A.addFinal("E");
	A.addFinal("F");

	A.addFinal("G");
	A.addRule("SaA");
	A.addRule("SbD");
	A.addRule("AbB");
	A.addRule("AaC");
	A.addRule("BaB");
	A.addRule("BbH");
	A.addRule("CaC");
	A.addRule("CbH");
	A.addRule("DaF");
	A.addRule("DbE");
	A.addRule("EaE");
	A.addRule("EbH");
	A.addRule("FaG");
	A.addRule("FbH");
	A.addRule("GaG");
	A.addRule("GbH");
	A.addRule("HaH");
	A.addRule("HbH");
	A.makeTotal();
	A.makeMinimal();
	cout<<A;

	DFA B("S" , "ab");
	B.addState("A");
	B.addState("B");
	B.addState("C");
	B.addState("D");
	B.addState("E");
	B.addState("F");
	B.addFinal("C");
	B.addFinal("F");
	B.addRule("SaA");
	B.addRule("SbD");
	B.addRule("AbB");
	B.addRule("AaA");
	B.addRule("BaE");
	B.addRule("BbC");
	B.addRule("CaC");
	B.addRule("CbE");
	B.addRule("DaE");
	B.addRule("DbF");
	B.addRule("FaC");
	B.addRule("FbE");
	B.makeTotal();
	cout<<B;
	B.makeMinimal();
	cout<<B;
}

void testIntersection()
{
	DFA A("S" , "ab") , B("I" , "ab");
	A.addRule("SaS");
	A.addState("A");
	A.addRule("SbA");
	A.addRule("AbS");
	A.addFinal("S");
	B.addState("B");
	B.addRule("IbI");
	B.addRule("IaB");
	B.addRule("BaI");
	B.addFinal("I");
	cout<<A.read("abbaaabb")<<endl;
	cout<<B.read("bbaabaa")<<endl;
	DFA C = intersection(A , B);
	cout<<C.getRegularExpression("S,I" , "" , 0 , 0)<<endl;
	cout<<A.getRegularExpression("S" , "" , 0 , 0)<<endl;
	cout<<B.getRegularExpression("I" , "" , 0 , 0)<<endl;
}

void testUnion()
{
	DFA A("S" , "ab") , B("I" , "ab");
	A.addRule("SaS");
	A.addFinal("S");
	B.addRule("IbI");
	B.addFinal("I");
	cout<<A.read("aaaaa")<<endl;
	cout<<B.read("bbbbbb")<<endl;
	DFA C = Union(A , B);
	cout<<C.read("aabbaababab");
	cout<<C.getRegularExpression("I" , "" , 0 , 0)<<endl;
	cout<<A.getRegularExpression("S" , "" , 0 , 0)<<endl;
	cout<<B.getRegularExpression("I" , "" , 0 , 0)<<endl;
}

void testAddition()
{
	DFA A("S" , "ab");
	A.addState("A");
	A.addState("B");
	A.addState("C");
	A.addState("D");
	A.addState("E");
	A.addState("F");
	A.addState("G");
	A.addState("H");
	A.addFinal("C");
	A.addFinal("B");
	A.addFinal("E");
	A.addFinal("F");
	A.addFinal("G");
	A.addRule("SaA");
	A.addRule("SbD");
	A.addRule("AbB");
	A.addRule("AaC");
	A.addRule("BaB");
	A.addRule("BbH");
	A.addRule("CaC");
	A.addRule("CbH");
	A.addRule("DaF");
	A.addRule("DbE");
	A.addRule("EaE");
	A.addRule("EbH");
	A.addRule("FaG");
	A.addRule("FbH");
	A.addRule("GaG");
	A.addRule("GbH");
	A.addRule("HaH");
	A.addRule("HbH");

	cout<<A;
	cout<<endl;
	cout<<A.getAddition();
}

int main()
{
	testMinimization();
	testUnion();
	testIntersection();
	testAddition();
	system("pause");
	return 0;
}
