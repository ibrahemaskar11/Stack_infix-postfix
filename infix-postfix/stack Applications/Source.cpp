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
/*
isValid function used to test if the infix expression is valid or not
*/
bool isValid(string infix) {
	/*
	first index and last index using find_first_not_of to find the first index that is not a space
	*/
	size_t firstIndex = infix.find_first_not_of(' ');
	size_t lastIndex = infix.find_last_not_of(' ');
	/*
	if statement used to check if the expression starts or ends with an arthmetic operator
	*/
	if (isCalcOperator(infix[firstIndex]) || isCalcOperator(infix[lastIndex])) {
		cout << "Invalid input first/last character can not be an operator" << endl;
		return false;
	}
	int open = 0;
	int close = 0;
	for (int i = 0; i < infix.length() - 1; i++) {
		/*
		if statement to skip any space in the string
		*/
		if (infix[i] == ' ') {
			continue;
		}
		/*
		if statement used to check if there's an invalid character in the string
		*/
		if (!isOperator(infix[i]) && !isOperand(infix[i])) {
			cout << "Invalid input user has entered an invalid character" << endl;
			return false;
		}
		/*
		if statement used to check if there's two arthmetic operators next to each other
		*/
		else if (isCalcOperator(infix[i]) && isCalcOperator(infix[i+1])) {
			cout << "Invalid input two operators next to each other" << endl;
			return false;
		}
		/*
		if statement used to check if there's an arthemtic operator after '(' or before ')'
		*/
		else if (isCalcOperator(infix[i]) && infix[i-1] == '(' || isCalcOperator(infix[i]) && infix[i+1] == ')') {
			cout << "Invalid input an operator can't come after '(' or before ')'" << endl;
			return false;
		}
		/*
		if statements to accumulate the number of '(' and the number of ')' to be later checked on
		*/
		else if (infix[i] == '(') {
			open++;
		}
		else if (infix[i] == ')') {
			close++;
		}
		/*
		if statements to avoid division by zero
		*/
		else if (infix[i] == '/' && infix[i+1] == '0') {
			cout << "Invalid input division by zero is not possible" << endl;
			return false;
		}
	}
	if (infix[lastIndex] == '(') {
		open++;
	}
	else if (infix[lastIndex] == ')') {
		close++;
	}
	/*
	if statements to help the user know what is wrong with his/her expression
	*/
	if (open > close) {
		cout << "Invalid input missing closing parentheses" << endl;
		return false;
	}
	else if (open < close) {
		cout << "Invalid input missing opening parentheses" << endl;
		return false;
	}
	return true;
}
/*
is valid for evaluation function returns a boolean value and is used to check 
if the postfix expression is valid for evaluation or not
*/
bool isValidForEvaluation(string input) {
	for (int i = 0; i < input.length(); i++) {
		/*
		if statement used to check if the string has an alphapetic character to check 
		if it could be evaluated or not
		*/
		if (isalpha(input[i])) {
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
and gets a parameter from the user passed by reference to store the evaluated 
value in the program if the expression is valid for evaluation
*/
string conv_postfix(string infix, int &val) {
	/*
	try catch statement used to check if the fucntion is valid for conversion 
	if not valid the code is not to be continued and the function returns an
	error message
	*/
	try
	{
		if (!isValid(infix)) {
			return ("INVALID ARGUMENT");
			throw 201;
		}
		string  postfix = "";
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
		}
		/*
		erase function used to remove the semi colons from the postfix string
		to print the correct postfix expression to the user
		*/
		string dummy = postfix;
		dummy.erase(remove(dummy.begin(), dummy.end(), ';'), dummy.end());
		if (isValidForEvaluation(postfix)) {
			val = evaluation_postfix(postfix);
		}
			
		return dummy;
	}
	catch (int x)
	{
		cout << "INVALID ARGUMENT" << endl;
	}
}


void main() {

	int val = 0;
	string infix;
	string postfix;
	char ch;
	/*
	do while function to execute the following code first and then ask the user 
	if he/she wants to enter another expression
	*/
	do
	{

		cout << "Please enter Infix Expression: ";
		getline(cin, infix);
		postfix = conv_postfix(infix, val);
		cout << "Postfix Expression: " << postfix << endl;
		if (isValidForEvaluation(postfix)) {
			cout << "Evaluated value: " << val << endl;
		}
		else {
			cout << "Expression does not need to be evaluated" << endl;
		}
		cout << "Do you want to enter another expression (y/Y) for yes (n/N) for No: ";
		cin >> ch;
		cout << endl;
		/*
		ignore function is used to allow the program to use getline inside the while loop
		*/
		cin.ignore(1);
	} while (ch == 'y' || ch == 'Y');
}