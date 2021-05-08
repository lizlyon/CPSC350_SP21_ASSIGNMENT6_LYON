#ifndef DB_QUEUE_H
#define DB_QUEUE_H
#include "Database.h"
#include "List.h"

class DbStack{
public:
	DbStack();
	void push(const Database& db);
	void pop();
	Database top();
	bool empty();

private:
	const static int MAX = 5;
	List<Database> deque;
	int count;
};
#endif
