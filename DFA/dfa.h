#ifndef DFA_H
#define DFA_H

#include <iostream>

using namespace std;

class DFA
{
private:
	char *initial, **final , **States , *alphabet;
	char** rules;
	char* deltaFunction(char* , char) const;
	int rulesCounter , capacity , finalStates , finalCap , stateCounter , stateCap;
	
	void resize();
	void resizeFinal();
	void resizeStates();
	
	void copy(DFA const&);
	void erase();

	char* getLeftState(char*) const;
	char* getRightState(char*) const;

public:
	DFA(char* = " " , char* = "a");
	DFA(DFA const&);
	DFA& operator=(DFA const&);
	~DFA();

	void changeRulesRightState(char* , char*);
	void changeRulesLeftState(char* , char*);
	void addRule(char*);
	void addFinal(char*);
	void addState(char*);
	void removeRule(char*);
	void removeState(char*);
	void removeFinalState(char*);
	
	bool read(const char*);

	char* getInitial() const{return initial;}
	int getStatesCount() const{return stateCounter;}
	int getFinalCount() const{return finalStates;}
	int getRulesCount() const{return rulesCounter;}
	char** getStates() const{return States;}
	char** getFinals() const{return final;}
	char** getRules() const{return rules;}
	void setInitial(char*);
	int getLetterCount() const {return strlen(alphabet);}

	bool hasEmptyLanguage();
	bool hasFullLanguage();
	bool hasFiniteLanguage();
	bool regularExpression(DFA , char* , char* , char* , int , int);
	
	char* getRegularExpression(char* , char* , int) const;

	void printRules() const;
	void printFinalStates() const;
	void printStates() const;

	bool isFinal(char*) const;
	bool isState(char*) const;

	DFA getAddition() const;
	void makeTotal();
	friend DFA intersection(DFA const& , DFA const&);
	void makeMinimal();

	friend ostream& operator<<(ostream& , DFA const&);
};

bool isLetter(char);

DFA Union(DFA const& , DFA const&);


#endif