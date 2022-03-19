#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
using namespace std;
#define MAX 20

/*
we use template stack to not rewrite the same code twice
class H will be specified in the compile time
we switch the template class between char and int to convert infix 
expressions and evalute the resulted postfix expression 
*/
template<class H>
/*
stack is a FILO/LIFO data structure
First In Last Out/Last In First Out
*/
class Stack {
	H arr[MAX];
	/*
	Top is a pointer to the last element in the stack
	*/
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
/*
Stack constructor use to intialize top equal to -1
*/
template <class H>
Stack<H>::Stack() {
	top = -1;
}
/*
push function used to insert elements to the stack
*/
template <class H>
void Stack<H>::push(H elem) {
	/*
	before inserting elements to the stack we check if it is full first
	if full we print an error message
	*/
	if (isFull()) {
		cout << "Stack is Full \n";
		system("pause");
		exit(1);
	}
	top++;
	arr[top] = elem;
}
/*
peak function is used to return the last element in the stack
*/
template <class H>
H Stack<H>::peak() {
	/*
	before deleting elements from the stack we check if it is empty first
	if empty we print an error message
	*/
	if (isEmpty()) {
		cout << "Stack is Empty \n";
		system("pause");
		exit(1);
	}
	return arr[top];
};
/*
pop function is used to delete elements from the stack
*/
template <class H>
H Stack<H>::pop() {
	/*
	before deleting elements from the stack we check if it is empty first
	if empty we print an error message
	*/
	if (isEmpty()) {
		cout << "Stack is Empty \n";
		system("pause");
		exit(1);
	}
	H elem = arr[top];
	top--;
	return elem;
}
/*
isFull function is used to check if the stack is full
if full returns true
*/
template <class H>
bool  Stack<H>::isFull() {
	return(top == MAX - 1);
}
/*
isEmpty function is used to check if the stack is empty
if empty returns true
*/
template <class H>
bool Stack<H>::isEmpty() {
	return(top == -1);
}
/*
display function is used to print out the stack elements
*/
template <class H>
void Stack<H>::display() {
	for (int i = top; i >= 0; i--)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
}
/*
size function is used to return the size of the stack
*/
template <class H>
int Stack<H>::size() {
	return top + 1;
}
/*
isOperand function is used to return a boolean value based on the input
if element is operand returns true
used in the convertion to postfix function
*/
bool isOperand(char elem) {
	return ('0' <= elem && elem <= '9')
		|| ('a' <= elem && elem <= 'z')
		|| ('A' <= elem && elem <= 'Z');

}
/*
isOperator function is used to return a boolean value based on the input
if element is operator returns true
used in the convertion to postfix function
*/
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
/*
returns the percedence of the operators
used to determine the priorty of operators
used in the convertion to postfix function
*/
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
/*
used to do simple calculations 
used in the evaluation of postfix expression function
*/
int calc(int operand1, int operand2, char op) {
	switch (op)
	{
	case '+':
		return operand1 + operand2;
		break;
	case '-':
		return operand1 - operand2;
		break;
	case '*':
		return operand1 * operand2;
		break;
	case '/':
		return operand1 / operand2;
		break;
	case '^':
		return pow(operand1, operand2);
		break;
	case '%':
		return operand1 % operand2;
		break;
	}
}
bool isCalcOperator(char op) {
	return op == '^'
		|| op == '*'
		|| op == '/'
		|| op == '%'
		|| op == '+'
		|| op == '-';

}
bool isValid(string infix) {
	bool valid;
	size_t firstAlpha = infix.find_first_not_of(' ');
	size_t lastAlpha = infix.find_last_not_of(' ');
	if (isCalcOperator(infix[firstAlpha]) || isCalcOperator(infix[lastAlpha])) {
		cout << "Invalid input first/last character can not be an operator" << endl;
		return false;
	}
	int open = 0;
	int close = 0;
	for (int i = 0; i < infix.length() - 1; i++) {
		if (infix[i] == ' ') {
			continue;
		}
		if (!isOperator(infix[i]) && !isOperand(infix[i])) {
			cout << "Invalid input user has entered an invalid character" << endl;
			return false;
		}
		else if (isCalcOperator(infix[i]) && isCalcOperator(infix[i + 1])) {
			cout << "Invalid input two operators next to each other" << endl;
			return false;
		}
		else if (isCalcOperator(infix[i]) && infix[i - 1] == '(' || isCalcOperator(infix[i]) && infix[i + 1] == ')') {
			cout << "Invalid input an operator can't come after '(' or before ')'" << endl;
			return false;
		}
		else if (infix[i] == '(') {
			open++;
		}
		else if (infix[i] == ')') {
			close++;
		}
		else if (infix[i] == '/' && infix[i + 1] == '0') {
			cout << "Invalid input division by zero is not possible" << endl;
			return false;
		}
	}
	if (infix[lastAlpha] == '(') {
		open++;
	}
	else if (infix[lastAlpha] == ')') {
		close++;
	}
	if (open > close) {
		cout << "Invalid input missing closing parentheses" << endl;
		return false;
	}
	else if (open < close) {
		cout << "Invalid input missing opening parentheses" << endl;
		return false;
	}
	else if (!isOperand(infix[lastAlpha]) && !isOperator(infix[lastAlpha])) {
		cout << "Invalid input user has entered an invalid character" << endl;
		return false;
	}
	return true;
}

bool isValidForEvaluation(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '.') {
			return false;
		}
		else if (isalpha(input[i])) {
			return false;
		}

	}
	return true;
}

/*
Evaluation function is used to evalute only the valid postfix expressions
and return the resulted value of the expression
*/
int evaluation_postfix(string postfix) {
	Stack<int> operator_stk;
	/*
	dummy string acts as an accmulator to the multi digits operands for it
	to be later converted into intger values
	*/
	string dummy = "";
	/*
	for loop is used to scan each character in the string to convert the string
	*/
	for (int i = 0; i < postfix.length(); i++)
	{
		/*
		if statement used to handle the space error in the infix string (invalid input)
		*/
		if (postfix[i] == ' ') {
			continue;
		}
		/*
		if statement used to check if the scanned character is an operand
		*/
		if (isOperand(postfix[i])) {
			/*
			if the sacnned character is an operand and not equal to ; we add it to a dummy string
			then when we scan the ; we push the value to the stack to be later evaluated
			*/
			if (postfix[i] != ';')
				dummy += postfix[i];


		}
		if (postfix[i] == ';') {
			int value = stoi(dummy);
			operator_stk.push(value);
			dummy = "";
		}
		/*
		if statement  used to check for operators
		*/
		if (isOperator(postfix[i])) {
			/*
			if the scanned character is an operator we do two pops from the stack
			the first pop is the second value
			the second pop is the first value
			After that we push the value to the stack
			*/
			int value2 = operator_stk.pop();
			int value1 = operator_stk.pop();
			operator_stk.push(calc(value1, value2, postfix[i]));
		}
	}
	return operator_stk.pop();
}
/*
Conversion function is used to convert an infix expression to postfix expression
*/
string conv_postfix(string infix) {
	try
	{
		if (!isValid(infix)) {
			return ("INVALID ARGUMENT");
			throw 201;
		}
		string  postfix = "";
		Stack<int> operandSt;
		Stack<char> operatorSt;
		/*
		Parenthesize the expression starting from left to light
		we push ( to the stack and end the infix string with )
		*/
		infix += ')';
		operatorSt.push('(');
		/*
		for loop is used to scan each character in the string to convert the string
		*/
		for (int i = 0; i < infix.length(); i++)
		{
			/*
			if statement used to handle the space error in the infix string (invalid input)
			*/
			if (infix[i] == ' ') {
				continue;
			}
			/*
			if statement used to check if the character is an operand
			if character is an operand we add it to the postfix string
			*/
			if (isOperand(infix[i])) {
				postfix += infix[i];
			}
			/*
			if statement used to check if the character is an operator
			if character is an operator we push it to the stack
			*/
			else if (isOperator(infix[i])) {
				/*
				we add a semi colon to identify the operands from each other
				*/
				postfix += ';';
				if (infix[i] == '(') {
					operatorSt.push(infix[i]);
				}
				/*
				if a ) is scanned the algorithm starts to pop operators from the stack
				to the postfix string till it finds a ( */
				else if (infix[i] == ')') {
					while (operatorSt.peak() != '(')
					{
						postfix += operatorSt.pop();
					}
					/*
					Another pop is used to delete the ( from the stack
					*/
					operatorSt.pop();
				}
				/*
				if the scanned character is not a ( or ) we pop or push to or from the stack
				passed on the percedence
				*/
				else {
					while (perc(infix[i]) <= perc(operatorSt.peak()))
					{
						postfix += operatorSt.pop();
					}
					operatorSt.push(infix[i]);

				}
			}
			/*
			if the scanned character is in invalid we print an error message to the user
			*/
			/*
			else {
				cout << "NOT VALID EXPRESSION!";
				system("pause");
				exit(1);
			}
			*/
		}
		/*
		erase function used to remove the semi colons from the postfix string
		to print the correct postfix expression to the user
		*/
		string dummy = postfix;
		dummy.erase(remove(dummy.begin(), dummy.end(), ';'), dummy.end());
		cout << dummy << endl;
		cout << postfix << endl;
		cout << evaluation_postfix(postfix) << endl;
		return postfix;
	}
	catch (int x)
	{
		cout << "INVALID ARGUMENT" << endl;
	}
}


void main() {
	
	string test = conv_postfix("10+20*50+80)");

}