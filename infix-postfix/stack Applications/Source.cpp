#include <iostream>
#include <string>
using namespace std;
#define MAX 100

template<class H>
class Stack {
	H arr[MAX];
	int top;
public:
	Stack();
	void push(H elem);
	H pop();
	void display();
	bool isFull();
	bool isEmpty();
	int size();
	H peak();
};
template <class H>
Stack<H>::Stack() {
	top = -1;
}
template <class H>
void Stack<H>::push(H elem) {
	if (isFull()) {
		cout << "Stack is Full \n";
		system("pause");
		exit(1);
	}
	top++;
	arr[top] = elem;
}
template <class H>
H Stack<H>::peak() {
	if (isEmpty()) {
		cout << "Stack is Empty \n";
		system("pause");
		exit(1);
	}
	return arr[top];
};
template <class H>
H Stack<H>::pop() {
	if (isEmpty()) {
		cout << "Stack is Empty \n";
		system("pause");
		exit(1);
	}
	H elem = arr[top];
	top--;
	return elem;
}
template <class H>
bool  Stack<H>::isFull() {
	return(top == MAX - 1);
}
template <class H>
bool Stack<H>::isEmpty() {
	return(top == -1);
}
template <class H>
void Stack<H>::display() {
	for (int i = top; i >= 0; i--)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
}
template <class H>
int Stack<H>::size() {
	return top + 1;
}
bool isOperand(char elem) {
	return ('0' <= elem && elem <= '9')
		|| ('a' <= elem && elem <= 'z')
		|| ('A' <= elem && elem <= 'Z');

}
bool isOperator(char elem) {
	return elem == '+'
		|| elem == '-'
		|| elem == '*'
		|| elem == '/'
		|| elem == '%'
		|| elem == '^'
		|| elem == '('
		|| elem == ')';
}
int perc(char elem) {
	if (elem == '(') {
		return -1;
	}
	if (elem == '+' || elem == '-') {
		return 1;
	}
	if (elem == '*' || elem == '/' || elem == '%') {
		return 2;
	}
	if (elem == '^') {
		return 3;
	}
}
void main() {
	Stack<int> operandSt;
	Stack<char> operatorSt;
	string infix = "", postfix = "";
	cout << "Please enter the infinx expression: ";
	getline(cin, infix);
	infix += ')';
	operatorSt.push('(');
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] == ' ') {
			continue;
		}
		if (isOperand(infix[i])) {
			postfix += infix[i];
		}
		else if (isOperator(infix[i])) {
			if (infix[i] == '(') {
				operatorSt.push(infix[i]);
			}
			else if (infix[i] == ')') {
				while (operatorSt.peak() != '(')
				{
					//check on stack is empty

					postfix += operatorSt.pop();
				}
				operatorSt.pop();
			}
			// */+-
			else {
				while (perc(infix[i]) <= perc(operatorSt.peak()))
				{
					//check on stack is empty
					postfix += operatorSt.pop();
				}
				operatorSt.push(infix[i]);

			}
		}
		else {
			cout << "NOT VALID EXPRESSION!";
			system("pause");
			exit(1);
		}
	}
	cout << postfix;
	cout << "hello world!" << endl;
	system("pause");
}