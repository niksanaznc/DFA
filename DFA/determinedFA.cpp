#include "stdafx.h"
#include <iostream>
#include "dfa.h"


using namespace std;

DFA::DFA(char* I , char* _alphabet) : initial(NULL) , rules(NULL) , rulesCounter(0) , capacity(5) , alphabet(NULL)
										, finalStates(0) , finalCap(1) , States(NULL) , final(NULL) , stateCap(2) , stateCounter(0)
{
	alphabet = new char[strlen(_alphabet) + 1];
	strcpy(alphabet , _alphabet);
	initial = new char[strlen(I) + 1];
	strcpy(initial , I);
	rules = new char*[capacity];
	States = new char*[stateCap];
	addState(initial);
	final = new char*[finalCap];		
}

void DFA::copy(DFA const& dfa)
{
	States = new char*[dfa.stateCounter + 1];
	for(int i = 0 ; i < dfa.stateCounter ; i++)
		addState(dfa.getStates()[i]);
	initial = new char[strlen(dfa.initial) + 1];
	strcpy(initial , dfa.initial);
	alphabet = new char[strlen(dfa.alphabet) + 1];
	strcpy(alphabet , dfa.alphabet);
	final = new char*[dfa.finalStates + 1];
	for(int i = 0 ; i < dfa.finalStates ; i++)
		addFinal(dfa.getFinals()[i]);
	rules = new char*[dfa.capacity + 1];
	for(int i = 0 ; i < dfa.rulesCounter ; i++)
		addRule(dfa.rules[i]);
}

DFA::DFA(DFA const& A) : capacity(A.capacity) , rulesCounter(0) , stateCap(A.stateCap) , stateCounter(0) , finalStates(0) 
						, finalCap(A.finalCap) , initial(NULL) , rules(NULL) , final(NULL) , States(NULL) , alphabet(NULL)
{
	copy(A);
}

DFA& DFA::operator=(DFA const& A) 
{
	if(this != &A)
	{
		erase();
		capacity = A.capacity;
		rulesCounter = 0;
		stateCap = A.stateCap;
		stateCounter = 0;
		finalStates = 0;
		finalCap = A.finalCap;
		copy(A);
	}
	return *this;
}

DFA::~DFA()
{
	erase(); 
}

void DFA::erase()
{
	delete[] alphabet;
	delete[] initial;
	for(int i = 0 ; i < stateCounter ; i++)
		delete[] States[i];
	delete[] States;
	for(int i = 0 ; i < finalStates ; i++)
		delete[] final[i];
	delete[] final;
	for(int i = 0 ; i < rulesCounter ; i++)
		delete[] rules[i];
	delete[] rules;
}

void DFA::addState(char* q)
{
	if(strcmp(q , " ") != 0)
	{
		bool newState = true;
		for(int i = 0 ; i < stateCounter ; i++)
			if(strcmp(States[i],q) == 0)
				newState = false;
		if(newState)
		{
			int len = strlen(q);
			if(stateCounter == stateCap - 1)
				resizeStates();
			States[stateCounter] = new char[len+1];
			strcpy(States[stateCounter] , q);
			stateCounter++;
		}
	}
}

void DFA::addRule(char* _rule)
{
	bool newRule = true;
	for(int i = 0 ; i < rulesCounter ; i++)
		if(strcmp(rules[i] , _rule) == 0)
			newRule = false;
	if(newRule)
	{
		bool isValid = false;
		if(isState(getLeftState(_rule)) && isState(getRightState(_rule)))
			isValid = true;
		if(isValid)
		{
			if(rulesCounter == capacity - 1)
				resize();
			int x = strlen(_rule) + 1;
			rules[rulesCounter] = new char[x];
			strcpy(rules[rulesCounter] , _rule);
			rulesCounter++;
		}
	}
}

void DFA::resize()
{
	capacity *= 2;
	char** newRules = new char*[capacity];
	for(int i = 0 ; i < rulesCounter ; i++)
		newRules[i] = rules[i];
	delete[] rules;
	rules = newRules;
}

void DFA::resizeStates()
{
	stateCap *= 2;
	char** newStates = new char*[stateCap];
	for(int i = 0 ; i < stateCounter ; i++)
		newStates[i] = States[i];
	delete[] States;
	States = newStates;
}

void DFA::resizeFinal()
{
	finalCap *= 2;
	char** newFinals = new char*[finalCap];
	for(int i = 0 ; i < finalStates ; i++)
		newFinals[i] = final[i];
	delete[] final;
	final = newFinals;
}

void DFA::printRules() const
{
	for(int i = 0 ; i < rulesCounter ; i++)
		cout<<rules[i]<<' ';
	cout<<endl;
}

void DFA::setInitial(char* I)
{
	removeState(initial);
	delete[] initial;
	initial = new char[strlen(I) + 1];
	addState(I);
	strcpy(initial , I);
}

void DFA::addFinal(char* F)
{
	bool isState = false;
	for(int i = 0 ; i < stateCounter ; i++)
		if(strcmp(States[i], F) == 0)
			isState = true;
	if(isState)
	{
		bool newFinal = true;
		for(int i = 0 ; i < finalStates ; i++)
			if(strcmp(final[i], F) == 0)
				newFinal = false;
		if(newFinal)
		{
			if(finalStates == finalCap - 1)
				resizeFinal();
			final[finalStates] = new char[strlen(F) + 1];
			strcpy(final[finalStates] , F);
			finalStates++;
		}
	}
}

char* DFA::deltaFunction(char* state , char letter) const
{
	int k = strlen(state);
	for(int i = 0 ; i < rulesCounter ; i++)
	{
		bool matchState = false;
		if(strncmp(rules[i] , state , k) == 0 && rules[i][k] == letter)
			matchState = true;
		if(matchState)
			return getRightState(rules[i]);
	}
	return " ";
}

bool DFA::read(const char* word)
{
	int len = strlen(word);
	int i = 0;
	char *currentState = initial , *nextCurrent;
	while(i < len)
	{
		nextCurrent = deltaFunction(currentState , word[i]);
		if(strcmp(nextCurrent," ") != 0)
		{
			currentState = nextCurrent;
			i++;
		}
		else
			break;
	}
	if(i == len)
	{
		for(int k = 0 ; k < finalStates ; k++)
			if(strcmp(currentState , final[k]) == 0)
				return true;
	}
	return false;
}

void DFA::removeState(char* state)
{
	for(int i = 0 ; i < stateCounter ; i++)
		if(strcmp(States[i] , state) == 0)
		{
			delete[] States[i];
			for(int k = i ; k < stateCounter - 1; k++)
				States[k] = States[k+1];
			stateCounter--;
		}
	for(int i = 0 ; i < rulesCounter ; i++)
	{
		for(int loop = 0 ; loop < 3 ; loop++)
		{
			if(strcmp(getLeftState(rules[i]) , state) == 0)
				removeRule(rules[i]);
			if(strcmp(getRightState(rules[i]) , state) == 0)
				removeRule(rules[i]);
		}
	}
	removeFinalState(state);
}

void DFA::removeFinalState(char* state)
{
	for(int i = 0 ; i < finalStates ; i++)
		if(strcmp(final[i] , state) == 0)
		{
			delete[] final[i];
			for(int k = i ; k < finalStates - 1; k++)
				final[k] = final[k+1];
			finalStates--;
		}
}

void DFA::removeRule(char* rule)
{
	for(int i = 0 ; i < rulesCounter ; i++)
		if(strcmp(rules[i] , rule) == 0)
		{
			delete[] rules[i];
			for(int k = i ; k < rulesCounter - 1; k++)
				rules[k] = rules[k+1];
			rulesCounter--;
		}
}

void DFA::printFinalStates() const
{
	for(int i = 0 ; i < finalStates ; i++)
		cout<<final[i]<<' ';
	cout<<endl;
}

void DFA::printStates() const
{
	for(int i = 0 ; i < stateCounter ; i++)
		cout<<States[i]<<' ';
	cout<<endl;
}

DFA Union(DFA const& A , DFA const& B)
{
	DFA newAutomat("I");
	for(int i = 0 ; i < A.getStatesCount() ; i++)
		newAutomat.addState(A.getStates()[i]);
	for(int i = 0 ; i < B.getStatesCount() ; i++)
		newAutomat.addState(B.getStates()[i]);
	for(int i = 0 ; i < A.getFinalCount() ; i++)
		newAutomat.addFinal(A.getFinals()[i]);
	for(int i = 0 ; i < B.getFinalCount() ; i++)
		newAutomat.addFinal(B.getFinals()[i]);
	for(int i = 0 ; i < A.getRulesCount() ; i++)
		newAutomat.addRule(A.getRules()[i]);
	for(int i = 0 ; i < B.getRulesCount() ; i++)
		newAutomat.addRule(B.getRules()[i]);
	for(int i = 0 ; i < newAutomat.getRulesCount() ; i++)
	{
		int k = strlen(A.getInitial());
		if(strncmp(newAutomat.getRules()[i] , A.getInitial() , k) == 0 && isLetter(newAutomat.getRules()[i][k]))
		{
			int len = strlen(newAutomat.getRules()[i]) - strlen(A.getInitial());
			char* rule1 = new char[len + strlen(newAutomat.getInitial())];
			strcpy(rule1 , newAutomat.getInitial());
			for(int p = 0 ; p < len; p++)
				rule1[strlen(newAutomat.getInitial()) + p] = newAutomat.getRules()[i][p + k];
			rule1[len + strlen(newAutomat.getInitial())] = '\0';
			newAutomat.removeRule(newAutomat.getRules()[i]);
			newAutomat.addRule(rule1);
			delete[] rule1;
		}
		int z = strlen(A.getInitial());
		if(strncmp(newAutomat.getRules()[i] , B.getInitial() , z) == 0 && isLetter(newAutomat.getRules()[i][z]))
		{
			int len2 = strlen(newAutomat.getRules()[i]) - strlen(B.getInitial());
			char* rule1 = new char[len2 + strlen(newAutomat.getInitial())];
			strcpy(rule1 , newAutomat.getInitial());
			for(int p = 0 ; p < len2; p++)
				rule1[strlen(newAutomat.getInitial()) + p] = newAutomat.getRules()[i][p + z];
			rule1[len2 + strlen(newAutomat.getInitial())] = '\0';
			newAutomat.removeRule(newAutomat.getRules()[i]);
			newAutomat.addRule(rule1);
			delete[] rule1;
		}
	}
	if(strcmp(A.getInitial() , newAutomat.getInitial()) != 0)
		newAutomat.removeState(A.getInitial());
	if(strcmp(B.getInitial() , newAutomat.getInitial()) != 0)
		newAutomat.removeState(B.getInitial());
	return newAutomat;
}

bool isLetter(char c)
{
	if(c >= 'a' && c <= 'z')
		return true;
	if(c >= '0' && c <= '9')
		return true;
	return false;
}

DFA DFA::getAddition() const
{
	DFA A = *this;
	for(int i = 0 ; i < A.finalStates ; i++)
		A.removeFinalState(A.getFinals()[i]);
	for(int i = 0 ; i < stateCounter ; i++)
	{
		if(!isFinal(States[i]))
			A.addFinal(States[i]);
	}
	return A;
}

DFA intersection(DFA const& A , DFA const& B)
{
	if(strcmp(A.alphabet , B.alphabet) == 0)
	{
		char* newInitial = new char[strlen(A.getInitial()) + strlen(B.getInitial()) + 2];
		strcpy(newInitial , A.getInitial());
		strcat(newInitial , ",");
		strcat(newInitial , B.getInitial());
		DFA newDfa(newInitial);

		for(int i = 0 ; i < A.stateCounter ; i++)
		{
			for(int j = 0 ; j < B.stateCounter ; j++)
			{
				char* state = new char[strlen(A.getStates()[i]) + strlen(B.getStates()[j]) + 2];
				strcpy(state , A.getStates()[i]);
				strcat(state , ",");
				strcat(state , B.getStates()[j]);
				newDfa.addState(state);

				if(A.isFinal(A.getStates()[i]) && B.isFinal(B.getStates()[j]))
					newDfa.addFinal(state);

				for(int k = 0 ; k < A.getLetterCount() ; k++)
				{
					if(A.deltaFunction(A.getStates()[i] , A.alphabet[k]) != " " && A.deltaFunction(A.getStates()[i] , A.alphabet[k]) != "Err" 
						&& B.deltaFunction(B.getStates()[j] , B.alphabet[k]) != " " && B.deltaFunction(B.getStates()[j] , B.alphabet[k]) != "Err" )
					{
						char* rule = new char[strlen(A.deltaFunction(A.getStates()[i] , A.alphabet[k])) + strlen(state)
													+ strlen(B.deltaFunction(B.getStates()[j] , B.alphabet[k])) + 3];
						strcpy(rule , state);
						rule[strlen(state)] = A.alphabet[k];
						rule[strlen(state) + 1] = '\0';
						strcat(rule , A.deltaFunction(A.getStates()[i] , A.alphabet[k]));
						strcat(rule , ",");
						strcat(rule , B.deltaFunction(B.getStates()[j] , B.alphabet[k]));
						newDfa.addRule(rule);
						delete[] rule;
					}
				}
				delete[] state;
			}
		}
		delete[] newInitial;
		return newDfa;
	}
	cout<<"Cannot intersect automats with different alphabets!"<<endl;
	return DFA();
}

void DFA::makeTotal()
{
	for(int i = 0 ; i < stateCounter ; i++)
	{
		int k = strlen(States[i]);
		for(int j = 0 ; j < getLetterCount() ; j++)
		{
			if(strcmp(deltaFunction(States[i] , alphabet[j]) , " ") == 0)
			{
				char* rule = new char[k + 5];
				strcpy(rule , States[i]);
				rule[k] = alphabet[j];
				rule[k + 1] = '\0';
				strcat(rule , "Err");
				addRule(rule);
				delete[] rule;
			}
		}
	}
}

char* DFA::getLeftState(char* rule) const
{
	int i = 0;
	while(!isLetter(rule[i]))
	{
		i++;
	}
	char* state = new char[i + 1];
	for(int k = 0 ; k < i ; k++)
		state[k] = rule[k];
	state[i] = '\0';
	return state;
}

char* DFA::getRightState(char* rule) const
{
	int i = strlen(rule) - strlen(getLeftState(rule));
	char* state = new char[i];
	for(int k = 0 ; k < i - 1; k++)
		state[k] = rule[i + k];
	state[i - 1] = '\0';
	return state;
}

void DFA::changeRulesRightState(char* rule , char* newRight)
{
	for(int i = 0 ; i < rulesCounter ; i++)
		if(strcmp(rules[i] , rule) == 0)
		{
			int oldRuleLen = strlen(getRightState(rules[i]));
			int len = strlen(rules[i]) - oldRuleLen + strlen(newRight);
			char* newRule = new char[len + 1];
			strcpy(newRule , getLeftState(rules[i]));
			newRule[strlen(getLeftState(rules[i]))] = rules[i][strlen(getLeftState(rules[i]))];
			newRule[strlen(getLeftState(rules[i])) + 1] = '\0';
			strcat(newRule , newRight);
			removeRule(rules[i]);
			addRule(newRule);
			delete[] newRule;
			i = rulesCounter;
		}
}

void DFA::changeRulesLeftState(char* rule , char* newLeft)
{
	for(int i = 0 ; i < rulesCounter ; i++)
		if(strcmp(rules[i] , rule) == 0)
		{
			int oldRuleLen = strlen(getLeftState(rules[i]));
			int len = strlen(rules[i]) - oldRuleLen + strlen(newLeft);
			char* newRule = new char[len + 1];
			strcpy(newRule , newLeft);
			for(int k = oldRuleLen ; k < len; k++)
				newRule[k] = rules[i][k];
			newRule[len] = '\0';
			removeRule(rules[i]);
			addRule(newRule);
			delete[] newRule;
			i = rulesCounter;
		}
}

bool DFA::isFinal(char* state) const
{
	for(int i = 0 ; i < finalStates ; i++)
		if(strcmp(final[i] , state) == 0)
			return true;
	return false;
}

bool DFA::isState(char* state) const
{
	for(int i = 0 ; i < stateCounter ; i++)
		if(strcmp(States[i] , state) == 0)
			return true;
	return false;
}

char* DFA::getRegularExpression(char* currentState , char* word , int count) const
{
	if(isFinal(currentState))
	{
		cout<<word<<endl;
		count--;
	}
	for(int i = 0 ; i < getLetterCount() ; i++)
	{
		if(deltaFunction(currentState , alphabet[i]) != " " && deltaFunction(initial , alphabet[i]) != "Err")
		{
			word[count] = alphabet[i];
			count++;
			getRegularExpression(deltaFunction(currentState , alphabet[i]) , word , count);
		}
	}
	return "not working yet!";
}

ostream& operator<<(ostream& os , DFA const& A)
{
	os<<"States : ";
	for(int i = 0 ; i < A.getStatesCount() ; i++)
		os<<A.getStates()[i]<<"  ";
	os<<endl;
	os<<"Alphabet : ";
	for(int i = 0 ; i < A.getLetterCount() ; i++)
		os<<A.alphabet[i]<<"  ";
	os<<endl;
	os<<"Rules : ";
	for(int i = 0 ; i < A.getRulesCount() ; i++)
		os<<A.getRules()[i]<<"  ";
	os<<endl;
	os<<"Initial state : "<<A.getInitial()<<endl;
	os<<"Final states : ";
	for(int i = 0 ; i < A.getFinalCount() ; i++)
		os<<A.getFinals()[i]<<"  ";
	os<<endl;
	return os;
}

bool DFA::hasEmptyLanguage()
{
	/*for(int i = 0 ; i < finalStates ; i++)
		if(strcmp(initial , final[i]) == 0)
			return false;*/
	for(int i = 0 ; i < finalStates ; i++)
		if(regularExpression(*this , initial , final[i] , initial , 0 , 0))
			return false;
	return true;
}

bool DFA::hasFullLanguage()
{
	for(int i = 0 ; i < stateCounter ; i++)
		if(!isFinal(States[i]) && regularExpression(*this , initial , States[i] , initial , 0 , 0))
			return false;
	return true;
}

bool DFA::regularExpression(DFA A ,char* firstState , char* lastState , char* previous , int i , int previousLetterNumber)
{ 
	if(strcmp(initial , firstState) == 0 && strcmp(lastState , initial) == 0)
		return true;
	for(int k = i ; k < getLetterCount() ; k++)
	{
		if(strcmp(A.deltaFunction(firstState , alphabet[k]) , lastState) == 0)
			return true;
		if(strcmp(A.deltaFunction(firstState , alphabet[k]) , " ") != 0 && strcmp(A.deltaFunction(firstState , alphabet[k]) , "Err") != 0 &&
			strcmp(A.deltaFunction(firstState , alphabet[k]) , firstState) != 0 && strcmp(A.deltaFunction(firstState , alphabet[k]) , previous) != 0)
		{
			for(int j = 0 ; j < A.getRulesCount() ; j++)
			{
				if(strcmp(A.getRightState(A.getRules()[j]) , previous) == 0)
					A.removeRule(A.getRules()[j]);
			}
			previous = firstState;
			return regularExpression(A , A.deltaFunction(firstState , alphabet[k]) , lastState , previous , i , k);
		}
	}
	if(previousLetterNumber + 1 < getLetterCount())
		return regularExpression(A , previous , lastState , previous , previousLetterNumber + 1 , previousLetterNumber + 1);
	return false;
}

bool DFA::hasFiniteLanguage()
{
	for(int i = 0 ; i < stateCounter ; i++)
		for(int j = i ; j < stateCounter ; j++)
			if((strcmp(initial , States[i]) != 0 || strcmp(initial , States[j]) != 0) && regularExpression(*this , States[i] , States[j] , States[i] , 0 , 0) 
									&& regularExpression(*this , States[j] , States[i] , States[j] , 0 , 0))
				return false;
	return true;
}

void DFA::makeMinimal()
{
	int classes = 2;
	int* classesElements = new int[stateCounter];
	char*** equivalentClasses = new char**[stateCounter];
	equivalentClasses[0] = new char*[finalStates];
	for(int i = 0 ; i < finalStates ; i++)
	{
		equivalentClasses[0][i] = new char[strlen(final[i]) + 1];
		strcpy(equivalentClasses[0][i] , final[i]);
	}
	classesElements[0] = finalStates;
	equivalentClasses[1] = new char*[stateCounter - finalStates];
	classesElements[1] = 0;
	for(int i = 0 ; i < stateCounter ; i++)
	{
		if(!isFinal(States[i]))
		{
			equivalentClasses[1][classesElements[1]] = new char[strlen(States[i]) + 1];
			strcpy(equivalentClasses[1][classesElements[1]] , States[i]);
			classesElements[1]++;
		}
	}
	int loop = max(classesElements[1] , classesElements[0]);
	for(int i = 2 ; i < stateCounter ; i++)
	{
		classesElements[i] = 0;
	}
	DFA B = *this;
	for(int i = 0 ; i < loop ; i++)
	{
		for(int br = 0 ; br < B.stateCounter ; br++)
		{
			for(int k = 0 ; k < B.rulesCounter ; k++)
			{
				for(int p = 0 ; p < classes ; p++)
				{
					for(int j = 1 ; j < classesElements[p] ; j++)
					{
						if(strcmp(B.getRightState(rules[k]) , equivalentClasses[p][j]) == 0)
						{
							B.changeRulesRightState(rules[k] , equivalentClasses[p][0]);
							p = classes;
						}
					}
				}
			}
		}
		for(int k = 0 ; k < classes ; k++)
		{
				for(int j = 0 ; j < classesElements[k] ; j++)
					cout<<k<<' '<<j<<' '<<equivalentClasses[k][j]<<' '<<B.deltaFunction(equivalentClasses[k][j] , alphabet[0])<<endl;//' '<<B.deltaFunction(equivalentClasses[k][j] , alphabet[1])<<endl;
		cout<<"================   "<<i<<endl;
			for(int p = 1 ; p < classesElements[k] ; p++)
			{
				for(int j = 0 ; j < B.getLetterCount() ; j++)
				{
					if(classesElements[k] > 1 && strcmp(B.deltaFunction(equivalentClasses[k][p] , B.alphabet[j]) , B.deltaFunction(equivalentClasses[k][p-1] , B.alphabet[j])) != 0)
					{
						bool newClass = true;
						for(int t = 0 ; t < classes ; t++)
						{
							bool found = true;
							for(int w = 0 ; w < B.getLetterCount() ; w++)
								if(strcmp(B.deltaFunction(equivalentClasses[k][p] , B.alphabet[w]) , B.deltaFunction(equivalentClasses[t][0] , B.alphabet[w])) != 0)
									found = false;
							if(found)
							{
								equivalentClasses[t][classesElements[t]] = new char[strlen(equivalentClasses[k][p]) + 1];
								strcpy(equivalentClasses[t][classesElements[t]] , (equivalentClasses[k][p]));
								classesElements[t]++;
								newClass = false;
								t = classes;
							}
						}
						if(newClass)
						{
							equivalentClasses[classes] = new char*[loop];
							equivalentClasses[classes][classesElements[classes]] = new char[strlen(equivalentClasses[k][p]) + 1];
							strcpy(equivalentClasses[classes][classesElements[classes]] , equivalentClasses[k][p]);
							classesElements[classes]++;
							classes++;
						}
						delete[] equivalentClasses[k][p];
						for(int z = p ; z < classesElements[k] - 1 ; z++)
							equivalentClasses[k][z] = equivalentClasses[k][z + 1];
						classesElements[k]--;
						p--;
					}
				}
			}
		}
	}

	DFA A("fordelete" , alphabet);
	for(int i = 0 ; i < classes ; i++)
	{
		A.addState(equivalentClasses[i][0]);
		if(isFinal(equivalentClasses[i][0]))
			A.addFinal(equivalentClasses[i][0]);
		for(int j = 0 ; j < classesElements[i] ; j++)
		{
			if(strcmp(equivalentClasses[i][j] , initial) == 0)
				A.setInitial(equivalentClasses[i][0]);
		}
	}
	for(int i = 0 ; i < A.stateCounter ; i++)
	{
		for(int j = 0 ; j < getLetterCount() ; j++)
		{
			if(strcmp(deltaFunction(A.States[i] , alphabet[j]) , " ") != 0 && strcmp(deltaFunction(A.States[i] , alphabet[j]), "Err") != 0)
			{
				if(A.isState(deltaFunction(A.States[i] , alphabet[j])))
				{
					char* rule = new char[strlen(A.States[i]) + strlen(deltaFunction(A.States[i] , alphabet[j])) + 2];
					strcpy(rule , A.States[i]);
					rule[strlen(A.States[i])] = alphabet[j];
					rule[strlen(A.States[i]) + 1] = '\0';
					strcat(rule , deltaFunction(A.States[i] , alphabet[j]));
					A.addRule(rule);
					delete[] rule;
				}
				else
				{
					for(int z = 0 ; z < classes ; z++)
					{
						for(int y = 0 ; y < classesElements[z] ; y++)
						{
							if(strcmp(deltaFunction(A.States[i] , alphabet[j]) , equivalentClasses[z][y]) == 0)
							{
								bool foundState = false;
								int state = 0;
								while(!foundState && state < classesElements[z])
								{
									if(A.isState(equivalentClasses[z][state]))
									{
										char* rule = new char[strlen(equivalentClasses[i][0]) + strlen(equivalentClasses[z][state]) + 2];
										strcpy(rule , equivalentClasses[i][0]);
										rule[strlen(equivalentClasses[i][0])] = alphabet[j];
										rule[strlen(equivalentClasses[i][0]) + 1] = '\0';
										strcat(rule , equivalentClasses[z][state]);
										A.addRule(rule);
										delete[] rule;
										foundState = true;
									}
									state++;
								}
								z = classes;
							}
						}
					}
				}
			}
		}
	}
	for(int i = 0 ; i < classes ; i++)
	{
		for(int k = 0 ; k < classesElements[i] ; k++)
			delete[] equivalentClasses[i][k];
		delete[] equivalentClasses[i];
	}
	delete[] classesElements;
	*this = A;
} // не напълно довършено