#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>

using namespace std;

class Student{
public:
  Student();
  Student(int ID, const string& name, const string& year, const string& major, double gpa, int advisorID);
  ~Student();
  int getID();
  int getAdvisorID();
  void setAdvisor(int advisorID);
  bool operator==(const Student& rhs) const;
  bool operator<(const Student& rhs) const;
  bool operator>(const Student& rhs) const;
  friend ostream& operator<<(ostream& out, const Student& s);
  friend istream& operator>>(istream& in, Student& s);

private:
  int ID;
  string name;
  string year;
  string major;
  double gpa;
  int advisorID;
};
#endif
