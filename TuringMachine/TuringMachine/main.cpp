#include "turingmachine.h"

int main(){
	Strip S("111111111111");
	char** _transitions = new char*[6];
	_transitions[0] = new char[strlen(" HN 1BR ") + 1];
	strcpy(_transitions[0], " HN 1BR ");
	_transitions[1] = new char[strlen(" CR 1BR1") + 1];
	strcpy(_transitions[1], " CR 1BR1");
	_transitions[2] = new char[strlen(" DL11CR1") + 1];
	strcpy(_transitions[2], " DL11CR1");
	_transitions[3] = new char[strlen(" EL01DL1") + 1];
	strcpy(_transitions[3], " EL 1DL1");
	_transitions[4] = new char[strlen(" AR11EL1") + 1];
	strcpy(_transitions[4], " AR11FL1");
	_transitions[5] = new char[strlen("    ") + 1];
	strcpy(_transitions[5], "    ");
	char* _states = new char[strlen("ABCDEH") + 1];
	strcpy(_states, "ABCDEH");


	TuringMachine T(_states, 'A', 'H', 'H', _transitions, S.getStrip());
	
	
	Strip S1("111111");
	char** _transitions1 = new char*[4];
	_transitions1[0] = new char[strlen(" CR 1BR1") + 1];
	strcpy(_transitions1[0], " CR 1BR1");
	_transitions1[1] = new char[strlen(" DR 1AR1") + 1];
	strcpy(_transitions1[1], " DR 1AR1");
	_transitions1[2] = new char[strlen("       ") + 1];
	strcpy(_transitions1[2], "       ");
	_transitions1[3] = new char[strlen("       ") + 1];
	strcpy(_transitions1[3], "       ");
	char* _states1 = new char[strlen("ABCD") + 1];
	strcpy(_states1, "ABCD");
	
	TuringMachine R(_states1,'A','C','D', _transitions1, S1.getStrip());

	cout << T << endl;
	T.startMachine();
	cout << T << endl << endl;
	cout << R << endl;
	R.startMachine();
	cout << R << endl;
	R.whileLoop(' ');
	cout << R.getCurrent().getName()<< endl;
	cout << T(R);


	for (int i = 0; i < 6; i++)
		delete[] _transitions[i];
	for (int i = 0; i < 4; i++)
		delete[] _transitions1[i];
	delete[] _transitions;
	delete[] _transitions1;
    delete[] _states;
	delete[] _states1;
	cin.get();
	return 0;
}