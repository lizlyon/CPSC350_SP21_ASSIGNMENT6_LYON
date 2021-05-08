#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

class Faculty{
public:
	Faculty();
	Faculty(int ID, const string& name, const string& level, const string& dept, List<int>& list);
	~Faculty();
	int getID();
	List<int> getStudentList();
	void removeAdvisee(int sid);

	//operator overloads
	friend bool operator==(const Faculty& a, const Faculty& b);
	friend bool operator>(const Faculty& a, const Faculty& b);
	friend bool operator<(const Faculty& a, const Faculty& b);
	friend ostream& operator<<(ostream& out, Faculty& f);
	friend istream& operator>>(istream& in, Faculty& f);

private:
	int ID;
	string name;
	string level;
	string dept;
	List<int> adviseesIDs;
};
#endif
