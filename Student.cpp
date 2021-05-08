#include "Student.h"

using namespace std;

Student::Student(){
	ID = advisorID = 0;
	gpa = 0.0;
}

Student::Student(int ID, const string& name, const string& year, const string& major, double gpa, int advisorID){}

Student::~Student(){
}

int Student::getID(){
	return ID;
}

int Student::getAdvisorID(){
	return advisorID;
}

void Student::setAdvisor(int advisorID){
	advisorID = advisorID;
}

bool Student::operator==(const Student& rhs) const{
	return this->ID == rhs.ID;
}

bool Student::operator<(const Student& rhs) const{
	return this->ID < rhs.ID;
}

bool Student::operator>(const Student& rhs) const{
	return this->ID > rhs.ID;
}

ostream& operator<<(ostream &out, const Student& s){
	out << s.ID << '\t' << s.name << '\t'
		<< s.year << '\t' << s.major << '\t'
		<< s.gpa << '\t' << s.advisorID << flush;

	return out;
}

istream& operator>>(istream &in, Student& s){
	in >> s.ID;

	in.ignore(1);
	getline(in, s.name, '\t');
	getline(in, s.year, '\t');
	getline(in, s.major, '\t');

	in >> s.gpa;
	in >> s.advisorID;

	return in;
}
