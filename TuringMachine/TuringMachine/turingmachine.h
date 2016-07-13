#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_
#define MIN 11

#include <iostream>
#include <cstring>
using namespace std;

class State{
	char name;
	char* transitions;
public:
	State() :name(' '), transitions(NULL) {}
	State(State&);
	State(char, char*);
	State& operator=(State&);
	~State() { delete[] transitions; }

	bool operator==(char);
	bool operator==(const State&);
	bool operator!=(const State&);
	const char getName() const { return name; }
	const char* getTransitions() const { return transitions; }
	void setState(const char, const char*);
};

class deltaFunction{
	State* states;
	State* start;
	const State* current;
	State* haltTrue;
	State* haltFalse;
	int size;
public:
	deltaFunction() :states(NULL), start(NULL), current(NULL), haltTrue(NULL), haltFalse(NULL),  size(0){}
	deltaFunction(char* _states, char start, char haltTrue, char haltFalse,  char** _transitions);
	deltaFunction(deltaFunction&);
	deltaFunction& operator=(deltaFunction&);
	~deltaFunction() { for (int i = 0; i < size; i++)  states[i].~State(); }

	const State* getStates() const { return states; }
	const State& getStart() const { return *start; }
	const State& getCurrent() const { return *current; }
	const State& getHaltTrue() const { return *haltTrue; }
	const State& getHaltFalse() const { return *haltFalse; }
	int getSize() const { return size; }
	void setCurrent(const State& _state) { current = &_state; }
};

class Strip{
	char* strip;
public:
	Strip();
	Strip(Strip&);
	Strip(char*);
	Strip& operator=(const Strip&);
	~Strip() { delete[] strip; }
	void write(char*,char);
	friend ostream& operator<<(ostream&, Strip&);
	char* getStrip() const { return strip; }
	void setStrip(char*);
	void setStrip(Strip&);
	int resizeStrip(char, char*);	//връща на коя позиция е била главата преди разширяването
};

class TuringMachine: public Strip, public deltaFunction{
	char* head;
public:
	TuringMachine();
	TuringMachine(TuringMachine&);
	TuringMachine(char* _states, char start,char hatTrue, char haltFalse, char** _transitions, char* strip);
	TuringMachine& operator=(TuringMachine&);
	void operator()(char);
	void move(char);
	void resize(char);
	void startMachine();
	void whileLoop(char);
	TuringMachine& operator()(TuringMachine&, TuringMachine&);
	TuringMachine& operator()(TuringMachine&);
};









#endif