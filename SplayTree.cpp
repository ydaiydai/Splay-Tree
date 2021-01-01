// Created by Yi Dai
// SplayTree.cpp

/*
This is my full implementation of Splay Tree (a binary search tree)
in C++
*/


// Splay func referenced from https://codeforces.com/blog/entry/18462

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// node with info and three pointers, one left, one right, 
// and one points to the parent (dad)
struct node{
	int key;
	struct node *left;
	struct node *right;
	struct node *dad;
};
node *root;

// struct to make two nodes
struct twoNodes{
	struct node *t1;
	struct node *t2;
};

// initialize a new node
struct node * newNode(int key){
	struct node *New = (struct node*)malloc(sizeof(struct node));
	New->key = key;
	New->left = New->right = New->dad = NULL;			
	return (New);
}

// function for right rotation
void rightRotate(node *P)
{
	node *T=P->left;
	node *B=T->right;
	node *D=P->dad;
	if(D)
	{	
		//cout << "D" << endl;
		if(D->right==P) D->right=T;
		else D->left=T;
	}
	if(B){
		//cout << "B" << endl;
		B->dad=P;
	}
	//cout << "OG" << endl;
	T->dad=D;
	T->right=P;
	
	P->dad=T;
	P->left=B;
}

// function for left rotation
void leftRotate(node *P)
{
	node *T=P->right;
	node *B=T->left;
	node *D=P->dad;
	if(D)
	{
		if(D->right==P) D->right=T;
		else D->left=T;
	}
	if(B){
		B->dad=P;
	}
	T->dad=D;
	T->left=P;
	
	P->dad=T;
	P->right=B;
}

// Function for splay action
void Splay(node *T)
{
	while(true)
	{
		node *p=T->dad;
		if(!p) break;
		node *pp=p->dad;
		if(!pp)//Zig
		{
			if(p->left==T){
				rightRotate(p);
				//cout << "1r" << endl;
			}
			else{
				leftRotate(p);
				//cout << "2r" << endl;
			}
			break;
		}
		if(pp->left==p)
		{
			if(p->left==T)
			{//ZigZig
				rightRotate(pp);
				rightRotate(p);
				//cout << "3r" << endl;
			}
			else
			{//ZigZag
				leftRotate(p);
				rightRotate(pp);
				//cout << "4r" << endl;
			}
		}
		else
		{
			if(p->left==T)
			{//ZigZag
				rightRotate(p);
				leftRotate(pp);
				//cout << "5r" << endl;
			}
			else
			{//ZigZig
				leftRotate(pp);
				leftRotate(p);
				//cout << "6r" << endl;
			}
		}
	}
	root=T;
}

// function for accessing a specific value
node* access(int v)
{
	if(!root) return NULL;
	node *P=root;
	while(P)
	{
		if(P->key==v)
			break;
		if(v<(P->key))
		{
			if(P->left)
				P=P->left;
			else
				break;
		}
		else
		{
			if(P->right)
				P=P->right;
			else
				break;
		}
	}
	Splay(P);
	if(P->key==v) return P;
	else return NULL;
}

// function to find a specific value
void find(int i){
	if (access(i)==NULL){
		cout << "item " << i << " not found" << endl;
	}
	else{
		cout << "item " << i << " found" << endl;
	}
}

// function to split into two nodes
twoNodes* split(int num) {
	twoNodes* fake = (twoNodes *)malloc(sizeof(twoNodes));
	fake->t1 = NULL;
	fake->t2 = NULL;
	//fake->dad = NULL;
	//fake->key = -1;

	if(root){

	access(num);
	//node* temp = access(num);
	//node *temp = root;
		if (root->key > num){
			if (root->left == NULL){
				node* RIGHT = root;
				fake->t2 = RIGHT;
				//RIGHT->dad = fake;
			}
			else{
				node* LEFT = root->left;
				fake->t1 = LEFT;
				//LEFT->dad = fake;
				root->left = NULL;
				node* RIGHT = root;
				fake->t2 = RIGHT;
				//RIGHT->dad = fake;
			}	
		}
		else{
			if (root->right == NULL){
				node* LEFT = root;
				fake->t1 = LEFT;
				//LEFT->dad = fake;
			}
			else{
				node* RIGHT = root->right;
				fake->t2 = RIGHT;
				//RIGHT->dad = fake;
				root->right = NULL;
				//root->right->dad = NULL;
				node* LEFT = root;
				fake->t1 = LEFT;
				//LEFT->dad = fake;
			}
		}
	}
	return fake;
}

// function for insertion
void insert(int i){
	if (root){
		twoNodes* fake = split(i);
		//printf("%d ", fake->t2->key);
		if(fake->t2 && fake->t1){
			if (fake->t1->key == i){
				
				root = fake->t1;
				root->right = fake->t2;
				root->right->dad = root;
				cout << "item " << i << " not inserted; already present" << endl;
				
				//cout << "c" << endl;
			}
			else{
				
				node* newRoot = (node *)malloc(sizeof(node));
				newRoot->key = i;
				newRoot->left = newRoot->right = newRoot->dad = NULL;
				node* T1 = fake->t1;
				node* T2 = fake->t2;
				newRoot->left = T1;
				newRoot->left->dad = newRoot;
				newRoot->right = T2;
				newRoot->right->dad = newRoot;
				root = newRoot;
				
				cout << "item " << i << " inserted" << endl;
				//cout << "d" << endl;

			}
		}
		else if(!fake->t1){
				
			node* newRoot = (node *)malloc(sizeof(node));
			newRoot->key = i;
			newRoot->left = newRoot->right = newRoot->dad = NULL;
			node* T2 = fake->t2;
			newRoot->right = T2;
			newRoot->right->dad = newRoot;
			root = newRoot;
			cout << "item " << i << " inserted" << endl;
				
		}
		
		else{
			if (fake->t1->key == i){
				
				root = fake->t1;
				cout << "item " << i << " not inserted; already present" << endl;
				
				//cout << "b" << endl;
			}
			else{
				
				node* newRoot = (node *)malloc(sizeof(node));
				newRoot->key = i;
				newRoot->left = newRoot->right = newRoot->dad = NULL;
				node* T1 = fake->t1;
				newRoot->left = T1;
				newRoot->left->dad = newRoot;
				root = newRoot;
				cout << "item " << i << " inserted" << endl;
				
			}
		}
	}
	else{
		node* newRoot = (node *)malloc(sizeof(node));
		newRoot->key = i;
		newRoot->left = newRoot->right = newRoot->dad = NULL;
		root = newRoot;
		cout << "item " << i << " inserted" << endl;
	}
}

// function to join two nodes
node* join(node *t1, node *t2) {
	node* temp = t1;
	while(temp->right){
		temp = temp->right;
	}

	int i = temp->key;
 	root = t1;
 	access(i);

 	root->right = t2;
 	t2->dad = root;
 	
 	return root;
}

// pre-order tree traversal
void preOrder(struct node *root) 
{ 
    if(root != NULL) 
    { 
        printf("%d ", root->key); 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
}

// print out the splay tree
void printSplayTree(struct node* root) {
	if (root != NULL) {
		string output = "";
		queue<node*> q;
		q.push(root);

		while(!q.empty()){
			// counts how many numbers in the level
			int nodeCount = q.size();

			while(nodeCount > 0) {
				struct node* temp = q.front();
				output += to_string(temp->key);
				output += ",";

				q.pop();	

				if(temp->left != NULL)
					q.push(temp->left);
				if(temp->right != NULL)
					q.push(temp->right);
				nodeCount--;
			}
			// take off the last comma
			output = output.substr(0, output.size()-1);
			output += "\n";
		}
		cout << output;
	}
}

// function for deleting a number 
void splayDelete (int i){
	access(i);

	if (!root){
		cout << "item " << i << " not deleted; not present" << endl;
		//cout << "a" << endl;
	}
	else if (i != root->key){
		cout << "item " << i << " not deleted; not present" << endl;
		//cout << "b" << endl;
	}
	else{
		if(!root->left && !root->right){
			root = NULL;
			cout << "item " << i << " deleted" << endl;
			//cout << "c" << endl;
		}
		else if (root->left && !root->right){
			root = root->left;
			root->dad = NULL;
			cout << "item " << i << " deleted" << endl;
			//cout << "d" << endl;
		}
		else if (root->right && !root->left){
			//printSplayTree(root);
			root = root->right;
			root->dad = NULL;
			//printSplayTree(root);
			//preOrder(root);
			cout << "item " << i << " deleted" << endl;
			//cout << "e" << endl;
		}
		else {
			node* tempLeft = root->left;
			node* tempRight = root->right;
			root = join(tempLeft, tempRight);
			root->dad = NULL;
			cout << "item " << i << " deleted" << endl;
			//cout << "f" << endl;
		}
	}
	
}

// function to obtain command from input
string getCommand(string line){
	string command;
	char space = ' ';
	int position = line.find(' ');
	command = line.substr(0, position);

	return command;
}

// function to obtain number from input
int getNumber(string line) {
	int number;
	char space = ' ';
	int position = line.find(' ');
	number = stoi(line.substr(position + 1));

	return number;
}

int main () {

	string line;
	string command;
	string input;
	bool firstLine = true;
	int operationCount = 0;
	int number;

	while(getline(cin, line)) {
		if(firstLine) {
			operationCount = stoi(line);
			firstLine = false;
		} else if (line == "print") {
			printSplayTree(root);
		} else {
			//cout << line << endl;
			command = getCommand(line);
			number = getNumber(line);
			if(command == "insert") {
				insert(number);
			}
			else if (command == "find") {
				find(number);
			}
			else if (command == "delete") {
				splayDelete(number);
			}
		}
	}

	return 0;
}