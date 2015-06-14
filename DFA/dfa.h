#ifndef DFA_H
#define DFA_H

#include <iostream>

using namespace std;

class DFA
{
private:
	char *initial, **final , **States , *alphabet; // състояния и азбука
	char** rules; // правила
	char* deltaFunction(char* , char) const; // делта функция
	int rulesCounter , capacity , finalStates , finalCap , stateCounter , stateCap; // броячи и капацитет на правила и състояния
	
	// функции за разширяване на масивите от правила и състояния
	void resize();
	void resizeFinal();
	void resizeStates();
	
	void copy(DFA const&); // копи функция
	void erase(); // функция за триене на автомата

	char* getLeftState(char*) const; // личен селектор за лява част на правило
	char* getRightState(char*) const; // личен селектор за дясна част на правило

public:
	// Голяма четворка
	DFA(char* = " " , char* = "a");
	DFA(DFA const&);
	DFA& operator=(DFA const&);
	~DFA();

	// мутатори за промяна на лява и дясна част на правило
	void changeRulesRightState(char* , char*);
	void changeRulesLeftState(char* , char*);

	// мутатори за добавяне и премахване на правила и състояния
	void addRule(char*);
	void addFinal(char*);
	void addState(char*);
	void removeRule(char*);
	void removeState(char*);
	void removeFinalState(char*);
	
	bool read(const char*); // функция за разпознаване на дума

	// селектори
	char* getInitial() const{return initial;} // селектор за начално състояние
	int getStatesCount() const{return stateCounter;} // селектр за брой на състоянията
	int getFinalCount() const{return finalStates;} // селектор за брой на финалните състояния
	int getRulesCount() const{return rulesCounter;} // селектор за брой на правилата
	char** getStates() const{return States;} // селектор за състоянията
	char** getFinals() const{return final;} // селектор за финалните състояния
	char** getRules() const{return rules;} // селектор за правилата
	int getLetterCount() const {return strlen(alphabet);} // селектор за брой на буквите в азбуката

	void setInitial(char*); // мутатор за промяна на началното състояние
	

	bool hasEmptyLanguage(); // проверка за празнота на езика
	bool hasFullLanguage(); // проверка за пълнота на езика
	bool hasFiniteLanguage(); // проверка за крайност на езика
	bool regularExpression(DFA , char* , char* , char* , int , int); // проверка дали има път от едно състояние до друго
	
	char* getRegularExpression(char* , string , int , int); 

	bool isFinal(char*) const; 
	bool isState(char*) const; 

	DFA getAddition() const; 
	void makeTotal(); 
	friend DFA intersection(DFA const& , DFA const&); 
	friend DFA Union(DFA const& , DFA const&); 
	void makeMinimal(); 

	friend ostream& operator<<(ostream& , DFA const&); 
};

bool isLetter(char); 



bool belongsTo(char* , char** , int); 


#endif
