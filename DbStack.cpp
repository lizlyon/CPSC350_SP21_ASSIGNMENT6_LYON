#include "DbStack.h"

//initialize member variable
DbStack::DbStack() : count(0){}

void DbStack::push(const Database& db){
	if(count == 5){
		deque.removeBack();
		count--;
	}
	deque.insertFront(db);
	count++;
}

void DbStack::pop(){
	if(deque.isEmpty()){
		return;
	}
	deque.removeFront();
	count--;
}

Database DbStack::top(){
	return deque.peekFront();
}

bool DbStack::empty(){
	return count == 0;
}
