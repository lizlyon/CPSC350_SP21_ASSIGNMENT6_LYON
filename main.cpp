#include <iostream>
#include <string>
#include "Database.h"
#include "DbStack.h"
//#include "Student.h"

using namespace std;

int main(){
  bool loadMenu = true;
  string userChoice;
  int id, sid, fid = 0;

  Database db;
  DbStack stack;

  while(loadMenu){
    //prompt user with menu options
    cout << "\nPlease type an integer from the menu below: " << endl;
    cout << "\n1.Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2.Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3.Find and display student information given the students id" << endl;
    cout << "4.Find and display faculty information given the faculty id" << endl;
    cout << "5.Given a student's id, print the name and info of their faculty advisor" << endl;
    cout << "6.Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7.Add a new student" << endl;
    cout << "8.Delete a student given the id" << endl;
    cout << "9.Add a new faculty member" << endl;
    cout << "10.Delete a faculty member given the id." << endl;
    cout << "11.Change a student's advisor given the student id and the new faculty id." << endl;
    cout << "12.Remove an advisee from a faculty member given the ids" << endl;
    cout << "13.Rollback" << endl;
    cout << "14.Exit" << endl;

    //read in user choice
    cout << "\nSelection: ";
    cin >> userChoice;

    while (userChoice != "1" && userChoice != "2" && userChoice != "3" && userChoice != "4" &&
    userChoice != "5" && userChoice != "6" && userChoice != "7" && userChoice != "8" && userChoice != "9" &&
    userChoice != "10" && userChoice != "11" && userChoice != "12" && userChoice != "13" &&
    userChoice != "14") {

      cout << "Error. Please enter an integer from the list!" << endl;
      cout << "Selection: ";
      cin >> userChoice;
  }

  cout << "Thank you for choosing " << userChoice << endl;

  cin.ignore();

  if (userChoice == "1"){
    //call method to print ALL students and their info (sorted by ascending id #)
    cout << "All students:" << endl;
    db.printAllStudents();
  }

  else if (userChoice == "2"){
    //call method to print all faculty and their info (sorted by ascending id #)
    cout << "All faculty members:" << endl;
    db.printAllFaculty();
  }

  else if (userChoice == "3"){
    //call method to find and display student information given the students id
    cout << "Student information:" << endl;

	  cout << "\nEnter student ID: ";
	  cin >> id;

    //call method in Database to find the student
	  db.findStudent(id);
  }

  else if (userChoice == "4"){
    //call method to find and display faculty information given the faculty id
    cout << "Faculty information:" << endl;

	  cout << "\nEnter faculty ID: ";
	  cin >> id;

    //call method in Database to find the faculty member
    db.findFaculty(id);
  }

  else if (userChoice == "5"){
    //call method given a student’s id, print the name and info of their faculty advisor
    cout << "A student's faculty advisor" << endl;

	  cout << "\nEnter student ID: ";
	  cin >> id;

    //method to print the students advisor
	  db.printStudentsAdvisor(id);
  }

  else if (userChoice == "6"){
    //call method given a faculty id, print ALL the names and info of his/her advisees
    cout << "A faculty member's advisees:" << endl;
    cout << "\nEnter faculty ID: ";
  	cin >> id;

    //method that prints the advisors students
    db.printAdvisorsStudents(id);
  }

  else if (userChoice == "7"){
   //call method to add a student
   cout << "Add a student:" << endl;

	 int ID, advisorID;
	 double gpa;
	 string name, year, major;

	 //prompt new student for their name, year, major, gpa, and advisor ID
	 cout << "\nEnter student ID: ";
	 cin >> ID;
   cin.ignore();

   cout << "Enter name: ";
   getline(cin, name);
	 cout << "Enter year: ";
	 getline(cin, year);
	 cout << "Enter major: ";
	 getline(cin, major);
	 cout << "Enter gpa: ";
	 cin >> gpa;
	 cout << "Enter advisor id: ";
	 cin >> advisorID;

	 cout << "New student " << name << " successfully added!" << endl;
	 //create new student and insert into tree
	 db.addStudent(Student(ID, name, year, major, gpa, advisorID));
   stack.push(db);
  }

  else if (userChoice == "8"){
    //call method that deletes a student given their id
    cout << "Delete a student:" << endl;

    cout << "\nEnter student ID: ";
    cin >> id;
    //method that deletes the student from tree
    db.deleteStudent(id);

    //push change to the stack
    stack.push(db);
  }

  else if (userChoice == "9"){
    //call method to add a new faculty member
    cout << "Add a faculty member:" << endl;

	  int ID;
	  string name, level, dept;
    //list for students
	  List<int> list;

	  cout << "\nEnter faculty ID: ";
	  cin >> ID;

	  cin.ignore();

	  cout << "Enter name: ";
	  getline(cin, name);
	  cout << "Enter level: ";
	  getline(cin, level);
	  cout << "Enter department: ";
	  getline(cin, dept);

    int studentID = 0;

    while (studentID != -1){
		cout << "Enter advisee id(s) (enter -1 to quit entering id(s)): ";
		cin >> studentID;

		if (studentID == -1){
			continue;
		}

		list.insertBack(studentID);
	}

	db.addFaculty(Faculty(ID, name, level, dept, list));
	 cout << "Successfully added " << name << " to the database!" << endl;

	//push changes to stack (error here)
	stack.push(db);
  }

  else if (userChoice == "10"){
    //call method to delete a faculty member given their id
    cout << "Delete a faculty member:" << endl;
    cout << "\nEnter faculty ID: ";
  	cin >> id;
    //method to delete faculty from the tree
    db.deleteFaculty(id);
    //push change on stack
    stack.push(db);
  }

  else if (userChoice == "11"){
    //call method that changes a student’s advisor given the student id and the new faculty id
    cout << "Change a student's advisor:" << endl;
    cout << "\nEnter student ID: ";
  	cin >> sid;
  	cout << "Enter faculty ID: ";
  	cin >> fid;
    //call method to change advisor
    db.changeAdvisor(sid,fid);
    //push change on stack
    stack.push(db);
  }

  else if (userChoice == "12"){
    //call method that removes an advisee from a faculty member given the ids
    cout << "Remove an advisee from a faculty member's list:" << endl;
    cout << "\nEnter faculty ID: ";
    cin >> fid;
    cout << "\nEnter student ID you wish to remove from list: ";
    cin >> sid;

    //remove advisee from advisors list, not the tree
    db.removeAdvisee(sid, fid);
    //push change on stack
    stack.push(db);
  }

  else if (userChoice == "13"){
    //call method to rollback to undo previous action
    cout << "Rollback:" << endl;

    //if the stack is not empty then get the top and pop max 5x
	  if(!stack.empty()){
		   db = stack.top();
		   stack.pop();
	   }
  }

  else if (userChoice == "14"){
    //call method to write the faculty and student tables back out to the
    //“facultyTable” and “studentTable” files, clean up, and quit
    cout << "\nWriting to facultyTable.txt" << endl;
    cout << "Writing to studentTable.txt" << endl;
    cout << "\nGoodbye!" << endl;

    db.exit();
    return 0;
  }
} //end of while loop
  return 0;
}
