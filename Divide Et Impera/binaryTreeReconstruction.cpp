#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Node{
	Node *left, *right;
	int value;

	Node(){
		left = right = NULL;
	}

	Node(int x){
		value = x;
		left = right = NULL;
	}
	int getValue(){
		return value;
	}
};

int displayList(list<int> myList){
	list<int>::iterator it;
	for (it = myList.begin(); it != myList.end(); it ++)
		cout << *it << " ";
	cout << endl;
}

Node* reconstruction(Node *&root, list<int> inorder, list<int> postorder){
	
	//VERIFYING STOP CONDITIONS

	if (inorder.size() == 0){
		return NULL;
	}

	if (inorder.size() == 1){
			Node *thisChild = new Node(inorder.back());
			return thisChild;
	}

	//CREATING NEW NODE TO HOLD THE CHILD TREE

	Node *newRoot = new Node(postorder.back());
	
	//CREATING THE RIGHT SUBSET

	list<int>::reverse_iterator itPost = postorder.rend();
	list<int>::reverse_iterator itIn = inorder.rend();
	itPost ++;
	itPost ++;
	itIn ++;

	list<int> newRightPostorder;
	list<int> newRightInowrder;

	while (*itIn != newRoot -> value){
		int newValue = *itIn;
		newRightInorder.push_front(neValue);
		itIn ++;
	}	

	for (int i = 0; i < newRightInorder.size(); i ++){
		int newValue = *itPost;
		newRightPostorder.push_front(newValue);
		itPost ++;
	}

	//CREATING THE LEFT SUBSET

	list<int>::iterator itLeftPost = postorder.begin();
	list<int>::iterator itLeftIn = inorder.begin();

	list<int> newLeftPostorder;
	list<int> newLeftInorder;
	while (*itLeftIn != newRoot -> value){
		int newValue = *itLeftIn;
		newLeftInorder.push_back(newValue);
		itLeftIn ++;
	}

	for (int i = 0; i < newLeftInorder.size(); i ++){
		int newValue = *itLeftPost;
		newLeftPostorder.push_back(newValue);
		itLeftPost ++;
	}

	//ADVANCING RECURSION STEPS

	newRoot -> right = reconstruction(newRoot, newRightInorder, newRightPostorder);
	newRoot -> left = reconstruction(newRoot, newLeftInorder, newLeftPostorder);

	// EXIT RECURSION STEP

	return newRoot;
}

int preorder(Node* root){
	if (root){
		cout << root -> value << " ";
		preorder(root -> left);
		preorder(root -> right);
	}
	return 0;
}

int main(){
	ifstream f;
	f.open("dateTreen.in");
	int n;

	f >> n;

	list<int> inorder;
	list<int> postorder;


	for (int i = 0; i < n; i ++){
		int newValue;
		f >> newValue;
		postorder.push_back(newValue);
	}

	for (int i = 0; i < n; i ++){
		int newValue;
		f >> newValue;
		inorder.push_back(newValue);
	}
	Node *newRoot = new Node;
	newRoot = reconstruction(newRoot, inorder, postorder);
	preorder(newRoot);
	cout << endl;
	displayList(inorder);
	displayList(postorder);
	return 0;
}
