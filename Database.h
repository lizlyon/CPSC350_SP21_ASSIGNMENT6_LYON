#ifndef DATABASE_H
#define DATABASE_H
#include "BST.h"
#include "Faculty.h"
#include "Student.h"

class Database{
public:
	Database();
	void readInFiles();
	void printAllStudents();
	void printAllFaculty();
	void findStudent(int id);
	void findFaculty(int id);
	void printStudentsAdvisor(int id);
	void printAdvisorsStudents(int id);
	void addStudent(const Student& s);
	void deleteStudent(int id);
	void addFaculty(const Faculty& f);
	void deleteFaculty(int id);
	void changeAdvisor(int sid, int fid);
	void removeAdvisee(int sid, int fid);
	void exit();

private:
	BST<Faculty> fTable;
	BST<Student> sTable;
	List<int> list;
	Student* s;
	Faculty* f;
};
#endif
