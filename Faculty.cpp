#include <sstream>
#include "Faculty.h"
using namespace std;

Faculty::Faculty(){
	ID = 0;
}

Faculty::Faculty(int ID, const string& name, const string& level, const string& dept, List<int>& list){
	this->ID = ID;
	this->name = name;
	this->level = level;
	this->dept = dept;
	adviseesIDs = list;
}

Faculty::~Faculty(){
}

int Faculty::getID(){
	return ID;
}

List<int> Faculty::getStudentList(){
	return adviseesIDs;
}

bool operator==(const Faculty& a, const Faculty& b){
	return  a.ID == b.ID;
}

bool operator>(const Faculty& a, const Faculty& b){
	return  a.ID > b.ID;
}

bool operator<(const Faculty& a, const Faculty& b){
	return  a.ID < b.ID;
}

ostream& operator<<(ostream& out, Faculty& f){
	out << f.ID << '\t' << f.name << '\t'
		<< f.level << '\t' << f.dept << '\t';

	for (int i = 0; i < f.adviseesIDs.size(); i++){
		int id = f.adviseesIDs.peekFront();
		out << id << '\t';
		f.adviseesIDs.removeFront();
		f.adviseesIDs.insertBack(id);
	}

	out << flush;
	return out;
}

istream& operator>>(istream &in, Faculty& f){
	in >> f.ID;

	in.ignore(1);
	getline(in, f.name, '\t');
	getline(in, f.level, '\t');
	getline(in, f.dept, '\t');

	//ensure that the list of student is cleaned out before writing data to it
	f.adviseesIDs.clear();

	//read in a list of student IDs
	string studentList;
	getline(in, studentList);

	istringstream sin(studentList);

	//while not the eof read in the student id's
	while (!sin.eof()){
		int studentID;
		sin >> studentID >> ws;
		f.adviseesIDs.insertBack(studentID);
	}
	return in;
}

void Faculty::removeAdvisee(int sid){
	//go through the list
	for (int i = 0; i <= adviseesIDs.size(); i++){
		int studentID = adviseesIDs.peekFront();
		//then remove
		adviseesIDs.removeFront();
		//only if it doesnt match then insert to back
		if (sid != studentID){
			adviseesIDs.insertBack(studentID);
		}
	}
}
