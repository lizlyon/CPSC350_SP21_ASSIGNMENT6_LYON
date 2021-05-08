#ifndef BST_H
#define BST_H
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class TreeNode{
  public:
    TreeNode(const T& d);
    ~TreeNode();
    TreeNode* left;    //L child tree node poiner
    TreeNode* right;   //R child tree node poiner
    T data;            //the key value
};

template <typename T>
TreeNode<T>::TreeNode(const T& d){ //constant
  data = d;         //data passed in
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
}

template <typename T>
class BST{ //the actual search class
  public:
  BST();
	BST(const BST<T>& original);
	~BST();
	BST<T>& operator=(const BST<T>& rhs);
  void insert(const T& d); //added, takes a data point
  bool contains(const T& d); //returns T if BST contains the data if not will return F
  bool search(int d, T& data);
  void printInOrder();    //print the tree in order
  void printPostOrder();
  void deleteValue(int d); //delete id that is passed in
  void writeToFile(const string& fileName);

private:
	TreeNode<T> *root;    //treenode T pointer root
	int iSize;
	bool searchHelper(TreeNode<T> *n, int d , T& data); //takes the tree node T pointer and the data
	void printInOrderHelper(TreeNode<T> *n);   //helps the print in order method
	void printPostOrderHelper(TreeNode<T> *n);
	void insertHelper(TreeNode<T>*&n, const T& d); //bc we are inserting recursively  - take tree node pointer and the data to insert
	TreeNode<T>* getSuccessor(TreeNode<T>* child); //get the successor of R child in tree
	void findTarget(int key, TreeNode<T>*& target, TreeNode<T>*& parent); //target tells us where to locate the key
	void copyHelper(TreeNode<T>* originalRoot);
	void clear(TreeNode<T>*& root);
	void deleteHelper(int d, TreeNode<T>* root);
	void writeToFileHelper(TreeNode<T>*n, ofstream& out);
};

template <typename T>
BST<T>::BST(){
  root = NULL;
  iSize = 0;
}

template<typename T>
inline BST<T>::BST(const BST<T>& original){
	copyHelper(original.root);
}

template <typename T>
BST<T>::~BST(){
	clear(root);
}

template<typename T>
inline BST<T>& BST<T>::operator=(const BST<T>& rhs){
	if(this != &rhs){
		clear(root);
		copyHelper(rhs.root);
	}
	return *this;
}

template <typename T>
void BST<T>::printInOrder(){
  return printInOrderHelper(root);
}

//PRINTS RECURSIVELY IN ORDER
template <typename T>
void BST<T>::printInOrderHelper(TreeNode<T> *n){
  //if n doesnt = NULL
  if(n!=NULL){
    //you can do this w post fix
    printInOrderHelper(n->left);
    cout << n->data << endl;  //print the tree in order
    printInOrderHelper(n->right);
  }
}

template <typename T>
void BST<T>::printPostOrder(){
  printPostOrderHelper(root);
}

//PRINTS RECURSIVELY IN ORDER
template <typename T>
void BST<T>::printPostOrderHelper(TreeNode<T> *n){
  //if n doesnt = NULL
  if (n != NULL){
    printPostOrderHelper(n->left);
    printPostOrderHelper(n->right);
    cout << n->data << endl;  //print the tree in order
  }
}

template <typename T>
bool BST<T>::search(int key, T& data){
  //method calls another method that takes the tree pointer and the data (key value)
  return searchHelper(root, key, data);
}

template <typename T>
//this function actually does the werk
bool BST<T>::searchHelper(TreeNode<T>* n, int key, T& data){
  //if the root in null
  if(n == NULL){
    return false;
  }
  //if the root is the key val we are looking for
  if(n->data.getID() == key){
	  data = n->data;
	  return true;
  }
  //if the thing i'm looking for is greater than the root node
  if(key > n->data.getID()){
    //then go right
    return searchHelper(n->right, key, data);
  }
  else{
    //or go left
    return searchHelper(n->left, key, data);
  }
}

template <typename T>
bool BST<T>::contains(const T& d){
  //if we start at root
  if(root == NULL){
    //then its false bc empty
    return false;
  }
  if(root->data == d){
    //check the root to see if its what we are looking for
    return true;
  }
  bool found = false;
  TreeNode<T>* current = root;

  //while we have not found the key
  while(!found){
    //key value is greater than the current node
    if(d > current->data){
      //thn current is the current pointer to the right node s
      current = current->right;
    }
    else{
      current = current->left;
    }
    if(current->data == d){
      found = true;
      break;   //break the loop
    }
    //if we hit a null
    if(current == NULL){
      found = false;
      break; //break the loop
    }
  }
  return found;
}

template <typename T>
void BST<T>::insert(const T& d){
  insertHelper(root, d);
}

template <typename T>
void BST<T>::insertHelper(TreeNode<T>*&n, const T& d){ //have to pass w the & bc it's getting the actual
  //base case: if the tree is empty
  //if the node you passed in is NULL
  if(n == NULL){
    //then set the tree = to a new node
    n = new TreeNode<T>(d);
  }
  //else if the data is less than the node data ---ex: is 6 < 4 NO so go to the next
  else if (d < n->data){
    //insert to the left of the node
    insertHelper(n->left, d);
  }
  else{
    //ex: 6 < 4
    //or else it must be greater than insert to the right
    insertHelper(n->right, d);
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* child){
  //check the r child left pointer is not null
  while(child->left != NULL){
    //move as far left until you hit NULL
    child = child->left;
  }
  return child;
}


template<typename T>
void BST<T>::clear(TreeNode<T>*& root){
	if (root){
		clear(root->left);
		clear(root->right);
		delete root;
		root = NULL;
	}
}

template<typename T>
inline void BST<T>::copyHelper(TreeNode<T>* originalRoot){
	if (originalRoot != NULL){
		insert(originalRoot->data);
		copyHelper(originalRoot->left);
		copyHelper(originalRoot->right);
	}
}

template <typename T>
void BST<T>::findTarget(int key, TreeNode<T>*& target, TreeNode<T>*& parent){ //tells us where to locate the key
  //create new pointer
	TreeNode<T> *node = parent;
  //base case
	if(node == NULL){
		target = NULL;
	}
	if(key < node->data.getID()){
		//then go left
		findTarget(key, target, node->left);
	}
	else if(key > node->data.getID()){
		//else go right
		findTarget(key, target, node->right);
	}
	else{
    //then the target has to be node
		target = node;
	}
}

template <typename T>
void BST<T>::deleteValue(int d) {
  //call delete
	deleteHelper(d, root);
}

template <typename T>
void BST<T>::deleteHelper(int d, TreeNode<T>* root){
	TreeNode<T>* current = NULL;
  //call find
	findTarget(d, current, root);

	if(current == NULL){
		return;
	}

	TreeNode<T>*& pos = current;
	//cases 1 and 2 0 or 1 child
	if(current->right == NULL){
    //the pos is the currents r child
		pos = current->right;
		delete current;
		return;
	}
	else if(current->left == NULL){
    //the pos is the currents l child
		pos = current->left;
		delete current;
		return;
	}
	//case 3, 2 children
	TreeNode<T>* suc = current->right;
	//find successor
	while(suc->left != NULL){
		suc = suc->left;
		//swap values and delete the suc
		current->data = suc->data;
    //call itself
		deleteHelper(current->data.getID(), current->right);
	}
}

template <typename T>
void BST<T>::writeToFile(const string& filename){
	ofstream fout;
  //open outside of method
	fout.open(filename, ios::out | ios::trunc);
	writeToFileHelper(root, fout);
	fout.close();
}

template <typename T>
void BST<T>::writeToFileHelper(TreeNode<T>*n, ofstream& fout){
	if (n != NULL){
		fout << n->data << endl;  //print the tree in order
		writeToFileHelper(n->left, fout);
		writeToFileHelper(n->right, fout);
	}
}
#endif
