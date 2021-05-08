#include <fstream>
#include <sstream>
#include "Database.h"
#include "Student.h"
#include "List.h"

using namespace std;

Database::Database(){
	readInFiles();
}

void Database::readInFiles(){
	ifstream fin;

	fin.open("facultyTable.txt");

	if (fin.is_open()){
		cout << "\nFound facultyTable.txt" << endl;
		Faculty f;

		while (!fin.eof()){
			fin >> f >> ws;
			fTable.insert(f);
		}
	}
	fin.close();

	fin.open("studentTable.txt");
	if (fin.is_open()){
		cout << "Found studentTable.txt" << endl;
		Student s;

		while(!fin.eof()){
			fin >> s >> ws;
			sTable.insert(s);
		}
	}
	fin.close();
}

void Database::printAllStudents(){
	//call BST pio method for sTable
	sTable.printInOrder();
}

void Database::printAllFaculty(){
	//call BST pio method for fTable
	fTable.printInOrder();
}

void Database::findStudent(int id){
	Student student;
	//call BST search method
	if (sTable.search(id, student)){
		//print the student info
		cout << student << endl;
	}
	else{
		cout << "Student ID " << id << " not recognized." << endl;
		return;
	}
}

void Database::findFaculty(int id){
	//create faculty object
	Faculty faculty;
	//call BST search method and print the faculty members data
	if (fTable.search(id, faculty)){
		cout << faculty << endl;
	}
	//else error message
	else{
		cout << "Faculty ID: " << id << " not recognized." << endl;
	}
}

void Database::printStudentsAdvisor(int id){
	Student student;
	//search student table for student id to ensure id exists
	if(sTable.search(id, student)){
		findFaculty(student.getAdvisorID());
	}
	else{
		cout << "Student ID " << id << " not recognized." << endl;
	}
}

void Database::printAdvisorsStudents(int id){
	Faculty faculty;
	//search the faculty table to ensure id exists
	if (fTable.search(id, faculty)){
		//get the list
		List<int> list = faculty.getStudentList();
		//go through the list
		for (int i = 0; i < list.size(); i++){
			int studentID = list.peekFront();
			//find id
			findStudent(studentID);
			//remove
			list.removeFront();
			//insert
			list.insertBack(studentID);
		}
	}
	else{
		cout << "Faculty ID " << id << " not recognized." << endl;
	}
}

void Database::addStudent(const Student& s){
	//insert new student into the tree
	sTable.insert(s);
}

void Database::deleteStudent(int id){
	//search to make sure id exists in tree
	Student student;
	if(sTable.search(id, student)){
		cout << "ID: " << id << " found" << endl;

		//delete from the tree
		sTable.deleteValue(id);
		cout << "ID: " << id << " deleted" << endl;
	}
	else{
		cout << "Student ID not recognized." << endl;
	}
}

void Database::addFaculty(const Faculty& f){
	//insert new faculty into the tree
	fTable.insert(f);
}

void Database::deleteFaculty(int id){
	//search to make sure id exists in tree
	Faculty faculty;
	if(fTable.search(id, faculty)){
		cout << "ID: " << id << " found" << endl;
		//delete from the tree error here
		//fTable.deleteValue(id);
		cout << "ID: " << id << " deleted" << endl;
	}
	else{
		cout << "Faculty ID not recognized." << endl;
	}
}

void Database::changeAdvisor(int sid, int fid){
	Student student;
	Faculty faculty;

	if (sTable.search(sid, student)){
		if (fTable.search(fid, faculty)){
			cout << "\nFound student ID" << endl;
			cout << "Found faculty ID" << endl;
			//set a new advisor for student
			s->setAdvisor(fid);

			cout << "Student ID: " << sid << " has faculty ID: " << fid << " as their advisor." << endl;
		}
		else{
			cout << "Error ID(s) not recognized. Try selecting menu item '11' again and entering valid ID's." << endl;
			return;
		}
	}
}

void Database::removeAdvisee(int sid, int fid){
	//create Faculty obj
	Faculty faculty;
	if (fTable.search(fid, faculty)){
		//remove from faculty list, not the tree
		faculty.removeAdvisee(sid);
		deleteFaculty(fid);
		fTable.insert(faculty);
	}
}

void Database::exit(){
	//calls methods in BST to write out the student and faculty txt files
	fTable.writeToFile("facultyTable.txt");
	sTable.writeToFile("studentTable.txt");
}
