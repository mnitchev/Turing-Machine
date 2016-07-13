#include "turingmachine.h"

State::State(State& S){
	name = S.name;
	transitions = new char[strlen(S.transitions) + 1];
	strcpy(transitions, S.transitions);
}

State::State(char _name, char* _transitions){
	name = _name;
	transitions = new char[strlen(_transitions) + 1];
	strcpy(transitions, _transitions);
}

State& State::operator=(State& S){
	if (&S != this){
		if (transitions != NULL)
			delete[] transitions;
		name = S.name;
		transitions = new char[strlen(S.transitions) + 1];
		strcpy(transitions, S.transitions);
	}
	return *this;
}

bool State::operator==(char _name){
	return name == _name;
}

bool State::operator==(const State& S){
	return name == S.getName();
}

bool State::operator!=(const State& S){
	return name != S.getName();
}

void State::setState(const char _name, const char* _transitions){
	if (transitions != NULL)
		delete[] transitions;
	name = _name;
	transitions = new char[strlen(_transitions) + 1];
	strcpy(transitions, _transitions);
}



deltaFunction::deltaFunction(char* _states, char _start, char _haltTrue, char _haltFalse, char** _transitions){
	size = strlen(_states);
	states = new State[size];
	for (int i = 0; i < size; i++)
		states[i].setState(_states[i], _transitions[i]);
	for (int i = 0; i < size; i++){						//търси за start и halt в копираните states
		if (states[i] == _start)
			start = &states[i];
		if (states[i] == _haltTrue)
			haltTrue = &states[i];
		if (states[i] == _haltFalse)
			haltFalse = &states[i];
	}
	current = start;
}

deltaFunction::deltaFunction(deltaFunction& D){
	size = D.size;
	states = new State[size];
	for (int i = 0; i < size; i++)
		states[i].setState(D.states[i].getName(), D.states[i].getTransitions());
	for (int i = 0; i < size; i++){						//търси за start и halt в копираните states
		if (states[i] == *D.start)
			start = &states[i];
		if (states[i] == *D.haltTrue)
			haltTrue = &states[i];
		if (states[i] == *D.haltFalse)
			haltFalse = &states[i];
	}
	current = start;
}

deltaFunction& deltaFunction::operator=(deltaFunction& D){
	if (&D != this){
		size = D.size;
		for (int i = 0; i < size; i++)
			states[i].setState(D.states[i].getName(), D.states[i].getTransitions());
		for (int i = 0; i < size; i++){					//търси за start и halt в копираните states
			if (states[i] == *D.start)
				start = &states[i];
			if (states[i] == *D.haltTrue)
				haltTrue = &states[i];
			if (states[i] == *D.haltFalse)
				haltFalse = &states[i];
		}
		current = start;
	}
	return *this;
}



Strip::Strip(){
	strip = new char[MIN + 1];
	for (int i = 0; i < MIN; i++)
		strip[i] = ' ';
	strip[MIN] = '\0';
}

Strip::Strip(char* _strip){
	strip = new char[strlen(_strip) + 1];
	strcpy(strip, _strip);
}

Strip::Strip(Strip& S){
	if (strip != NULL)
		delete[] strip;
	strip = new char[strlen(S.strip) + 1];
	strcpy(strip, S.strip);
}

void Strip::write(char* _head, char letter){
	*_head = letter;
}

ostream& operator<<(ostream& os, Strip& S){
	return os << S.strip;
}

int Strip::resizeStrip(char dir, char* _head){
	int position = 0;
	int size = strlen(strip);
	for (int i = 0; i < size + 1; i++)
		if (&strip[i] == _head)
			position = i;
	if (dir == 'L'){
		char* newStrip = new char[MIN + size + 1];
		for (int i = 0; i < MIN + size - 1; i++){
			if (i < MIN)
				newStrip[i] = ' ';
			else
				newStrip[i] = strip[i - MIN];
		}
		newStrip[MIN + size] = '\0';
		setStrip(newStrip);
	}
	if (dir == 'R'){
		char* newStrip = new char[size + 1 +  MIN];
		for (int i = 0; i < size + MIN; i++){
			if (i >= size)
				newStrip[i] = ' ';
			else
				newStrip[i] = strip[i];
		}
		newStrip[MIN + size] = '\0';
		setStrip(newStrip);
	}
	return position;
}

void Strip::setStrip(char* _strip){
	if (strip != NULL)
		delete[] strip;
	strip = new char[strlen(_strip) + 1];
	strcpy(strip, _strip);
}

void Strip::setStrip(Strip& S){
	if (strip != NULL)
		delete[] strip;
	strip = new char[strlen(S.strip) + 1];
	strcpy(strip, S.strip);
}



TuringMachine::TuringMachine(): Strip(), deltaFunction(){
	char* newStrip = new char[MIN + 1];
	for (int i = 0; i < MIN; i++)
		newStrip[i] = ' ';
	newStrip[MIN] = '\0';
	setStrip(newStrip);
}

TuringMachine::TuringMachine(char* _states, char _start, char _haltTrue, char _haltFalse, char** _transitions, char* _strip) :deltaFunction(_states, _start, _haltTrue, _haltFalse, _transitions), Strip(_strip){
	bool done = false;
	for (int i = 0; i <= strlen(getStrip()) && !done; i++)
		if (getStrip()[i] != ' '){
		head = &getStrip()[i];
		done = true;
		}
}


TuringMachine::TuringMachine(TuringMachine& T): Strip(T), deltaFunction(T){
	bool done = false;
	for (int i = 0; i <= strlen(getStrip()) && !done; i++)
		if (getStrip()[i] != ' '){
			head = &getStrip()[i];
			done = true;
		}
}

void TuringMachine::move(char dir){
	if (dir == 'R'){
		if (head == &getStrip()[strlen(getStrip()) - 1])
			resize(dir);
		head += 1;
	}
	if (dir == 'L'){
		if (head == &getStrip()[0])
			resize(dir);
		head -= 1;
	}
}

void TuringMachine::resize(char dir){
	int position = resizeStrip(dir, head);
	if (dir == 'L')
		head = &getStrip()[position + MIN];
	if (dir == 'R')
		head = &getStrip()[position];

}

void TuringMachine::operator()(char a){
	int transitionsSize = strlen(getCurrent().getTransitions());
	char temp;
	bool done = false;
	for (int i = 0; i < transitionsSize && !done; i += 4){
		temp = getCurrent().getTransitions()[i];
		done = false;
		if (getCurrent().getTransitions()[i] == a){
			write(head, getCurrent().getTransitions()[i + 3]);
			move(getCurrent().getTransitions()[i + 2]);
			for (int j = 0; j < getSize() && !done; j++)
				if (getStates()[j].getName() == getCurrent().getTransitions()[i + 1]){
					setCurrent(getStates()[j]);
					done = true;
				}
		}
	}
}

void TuringMachine::startMachine(){
	setCurrent(getStart());
	while (!(&getCurrent() == &getHaltTrue() || &getCurrent() == &getHaltFalse())){
		this->operator()(*head);
	}
}

TuringMachine& TuringMachine::operator()(TuringMachine& T){
	T.startMachine();
	bool done = false;
	setStrip(T.getStrip());
	for (int i = 0; i < strlen(getStrip()) + 1 && !done; i++)
		if (getStrip()[i] != ' '){
		head = &getStrip()[i];
		done = true;
		}
	startMachine();
	return *this;
}

TuringMachine& TuringMachine::operator()(TuringMachine& T, TuringMachine& F){
	bool done = false;
	startMachine();
	if (&getCurrent() != &getHaltTrue()){
		done = false;
		T.setStrip(getStrip());
		for (int i = 0; i < strlen(T.getStrip()) + 1 && !done; i++)
			if (getStrip()[i] != ' '){
				T.head = &getStrip()[i];
				done = true;
			}
		T.startMachine();
		return T;
	}
	if (&getCurrent() != &getHaltFalse()){
		done = false;
		F.setStrip(getStrip());
		for (int i = 0; i < strlen(F.getStrip()) + 1 && !done; i++)
			if (getStrip()[i] != ' '){
			F.head = &getStrip()[i];
			done = true;
			}
		F.startMachine();
		return F;
	}
}

void TuringMachine::whileLoop(char haltChar){
	while (*head != haltChar){
		setCurrent(getStart());
		startMachine();
	}
}