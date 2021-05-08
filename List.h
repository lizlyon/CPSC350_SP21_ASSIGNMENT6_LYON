#ifndef LIST_H
#define LIST_H
#include "Student.h"
#include "Faculty.h"

template <typename T>
class IList{
public:
	virtual void clear() = 0;
	virtual int size() const= 0;
	virtual bool isEmpty() const = 0;
	virtual void removeFront() = 0;
	virtual void removeBack()  = 0;
	virtual void insertFront(const T& item) = 0;
	virtual void insertBack(const T& item) = 0;
	virtual T peekFront() const = 0;
	virtual T peekBack() const = 0;
};

template <typename T>
class ListNode{
public:
	ListNode<T>(const T& data, ListNode<T>* next = NULL, ListNode<T>* prev = NULL);
	T data;
	ListNode<T>* next;
	ListNode<T>* prev;
};

template <typename T>
ListNode<T>::ListNode(const T& data, ListNode<T>* next, ListNode<T>* prev) :
	data(data), next(next), prev(prev){}

template<typename T>
class List : public IList<T>{
public:
	List<T>();
	virtual ~List<T>();
	List<T>(const List<T>& original);
	List<T>& operator=(const List<T>& that);
	void clear();
	int size() const;
	bool isEmpty() const;
	void removeFront();
	void removeBack();
	void insertFront(const T& item);
	void insertBack(const T& item);
	T peekFront() const;
	T peekBack() const;
	bool searchList(int id);

private:
	ListNode<T>* front;
	ListNode<T>* back;
	int isize;
};

template <typename T>
List<T>::List(){
	front = back = NULL;
	isize = 0;
}

template <typename T>
List<T>::~List(){
	clear();
}

template<typename T>
inline List<T>::List(const List<T>& original){
	isize = 0;

	ListNode<T>* current = NULL;
	//loop through i = 0; i != NULL; i++
	for (current = original.front; current != NULL; current = current->next){
		this->insertBack(current->data);
	}
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& that){
	if (this != &that){
		clear();

		ListNode<T>* current = NULL;
		for (current = that.front; current != NULL; current = current->next){
			this->insertBack(current->data);
		}
	}
	return *this;
}

//get the elements
template<typename T>
bool List<T>::searchList(int id){

	ListNode<T>* current = NULL;

	//search the list elements to display the data for students and faculty
	for (current = front; current != NULL; current = current->next){
		if(current->data.getID() == id){
			return true;
		}
	}
	return false;
}

template <typename T>
void List<T>::clear(){
	//create new node
	ListNode<T>* current = front;

	//delete
	while (current != NULL){
		ListNode<T>* temp = current;
		current = current->next;
		delete temp;
	}
	front = back = NULL;
	isize = 0;
}


template <typename T>
bool List<T>::isEmpty()const{ //constant
	return isize == 0;
}

template <typename T>
int List<T>::size() const{ //constant
	return isize;
}

template <typename T>
void List<T>::removeBack(){ //remove from front of queue
	//check if empty
	if (isEmpty()){
		//if the back is empty then return
		return;
	}
	//if single element
	else if (isize == 1){
		clear();
		return;
	}
	else{
		ListNode<T>* temp = back;
		back = back->prev;

		//back->next = temp;
		back->next = NULL;
		delete temp;
	}
	//decrement the size
	--isize;
}

template <typename T>
void List<T>::removeFront(){
	//check if empty
	if (isEmpty()){
		//if the front is empty then return
		return;
	}
	//if single element
	else if (isize == 1){
		clear();

		return;
	}
	else{
		ListNode<T>* temp = front;
		front = front->next;
		front->prev = NULL;
		//delete temp
		delete temp;
	}
	//decrement the size
	--isize;
}

template <typename T>
void List<T>::insertFront(const T& item){
	//create new node
	ListNode<T>* newNode = new ListNode<T>(item, front);

	//assign newNode to the front pointer
	front = newNode;

	if (isize == 0){
		back = newNode;
	}
	++isize;
}

template <typename T>
void List<T>::insertBack(const T& item){ //insert at the back
	//create new node
	ListNode<T>* newNode = new ListNode<T>(item, NULL, back);

	// assign newNode to the back pointer
	if (isize == 0){
		front = back = newNode;
	}
	else{
		back->next = newNode;
	}
	back = newNode;
	//increment the size
	++isize;
}

template <typename T>
T List<T>::peekFront() const{
	return front->data;
}

template <typename T>
T List<T>::peekBack() const{
	return back->data;
}
#endif
