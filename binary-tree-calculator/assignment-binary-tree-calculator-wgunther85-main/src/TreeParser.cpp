// Copyright 2023, Bradley Peterson, Weber State University, all rights reserved. (4/2023)

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

#include "TreeParser.h"

using std::stack;
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::pow;


TreeParser::~TreeParser() {
	clear();
}

void TreeParser::clear() {
	clear(this->root);
	this->root = nullptr;
	this->expression = "";
	this->position = 0;
	while (!mathStack.empty()) {
		mathStack.pop();
	}
}

void TreeParser::clear(Node* p) {
	//The private clear() method uses post-order traversal to delete all nodes. 
	if (p) {
		clear(p->left);
		clear(p->right);
		p->data = "";
		delete p;
	}
}

void TreeParser::processExpression(string& expression) {
	clear();
	// First, it should call clear() to clear out any tree in the object that many have existed from a prior processExpression() call.The
	//method should check if there is an expression to compute by checking if the expression is not empty.If so, have the object
	//copy the mathematical expression into the data member called expression.Set the position data member to zero.Then create
	//a node, have root point to it, then call the private processExpression() passing in root.
	if (expression != "") {
		this->expression = expression;
		position = 0;
		Node* p = new Node;
		this->root = p;
		processExpression(this->root);
	}
}

void TreeParser::processExpression(Node* p) {
	std::string string = "";
	char c = '(';
	while (this->position < this->expression.length()){
		if (this->expression[position] == '(') {
			Node* node = new Node;
			p->left = node;
			position++;
			processExpression(p->left);
		}
		else if(isdigit(this->expression[position]) || this->expression[position] == '.') {
			string = "";
			while (isdigit(this->expression[position]) || this->expression[position] == '.') {
				string += this->expression[position];
				position++;
			}
			p->data = string;
			return;
		}
		else if(isOperator(this->expression[position])) {
			p->data = this->expression[position];
			Node* node = new Node;
			p->right = node;
			position++;
			processExpression(p->right);
		}
		else if (this->expression[position] == ')') {
			position++;
			return;
		}
		else if (this->expression[position] == ' ') {
			position++;
		}
	}
}

double TreeParser::computeAnswer() {
	computeAnswer(this->root);
	return mathStack.top();
}

void TreeParser::computeAnswer(Node* ptr) {
	// will take the data in the binary tree, process it in a postorder 
	//fashion described in this document’s Goal section, and then return the answer.

	//The private computeAnswer() handles the recursion. It uses a postfix traversal, which is a “Go Left-Go Right-Act On Node”. 
	//This means the code will start with :
	if (ptr) {
		computeAnswer(ptr->left);
		computeAnswer(ptr->right);
		char c = ptr->data[0];
		

		if (isDigit(c)) {
			double some_double_output = std::stod(ptr->data);
			mathStack.push(some_double_output);

		}

		else if (isOperator(c)) {
			double A = mathStack.top();
			mathStack.pop();

			double B = mathStack.top();
			mathStack.pop();
			
			double result = 0;

			switch (c)
			{
			case '+':
				result = A + B;
				mathStack.push(result);
				break;
			case '-':
				result = B - A;
				mathStack.push(result);

				break;
			case '*':
				result = A * B;
				mathStack.push(result);
				break;
			case '/':
				result = B / A;
				mathStack.push(result);
				break;
			case '^':
				result = pow(B, A);
				mathStack.push(result);
			}

		}
	
	
	}

	
}

bool TreeParser::isDigit(char c) const {
	return std::isdigit(c);
}

bool TreeParser::isOperator(char c) const {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void TreeParser::inOrderTraversal() const {
	inOrderTraversal(this->root);
}

void TreeParser::inOrderTraversal(Node* p) const {
//The private inOrderTraversal performs an in-order traversal, using cout to display the nodes contents, with a space character 
//	after to help separate the display for the next displayed item.
	if (!p) {
		return;
	}
	inOrderTraversal(p->left);
	cout << p->data << " ";
	inOrderTraversal(p->right);
}

void TreeParser::postOrderTraversal() const {
	postOrderTraversal(this->root);
}

void TreeParser::postOrderTraversal(Node* p) const {
	if (p) {
		postOrderTraversal(p->left);
		postOrderTraversal(p->right);
		cout << p->data << " ";
	}
}
