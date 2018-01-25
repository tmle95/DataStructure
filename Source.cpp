#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

struct node {
public:
	string info;
	node *next;
	node *prev;
	node(string);
	int count;
};
node::node(string value) {
	info = value;
	next = prev = NULL;
}
void display(node **head);
node* mergesortlist(node* list1, node* list2);
void split(node* head, node** list1, node** list2);

void mergesort(node** head)
{
	node* list1;
	node* list2;
	if ((*head == NULL) || ((*head)->next == NULL))
	{
		return;
	}
	split(*head, &list1, &list2);
	mergesort(&list1); //T(n/2)
	mergesort(&list2);//T(n/2)
	*head = mergesortlist(list1, list2); //2T(n/2)
}
node* mergesortlist(node* list1, node* list2)
{

	node* result = NULL;

	if (list1 == NULL) {
		return(list2); //n
	}
	else if (list2 == NULL) {
		return(list1); //n
	}

	if (list1->info <= list2->info)
	{
		list1->next = mergesortlist(list1->next, list2);//(2T(n/2)
		list1->next->prev = list1;//n
		list1->prev = NULL;//n
		return list1;
	}
	else
	{
		list2->next = mergesortlist(list1, list2->next);//(2T(n/2)
		list2->next->prev = list2;//n
		list2->prev = NULL;//n
		return list2;
	}
}
void split(node* head, node** list1, node** list2) {
	node* fast;
	node* slow;
	if (head == NULL || head->next == NULL) {
		*list1 = head; //n
		*list2 = NULL;
	}
	else {
		slow = head;
		fast = head->next;
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		*list1 = head;
		*list2 = slow->next;
		slow->next = NULL;
	}
}
int count(node* head) {
	node *temp = head;
	int length = 0;
	while (temp != NULL) {
		length++;
		temp = temp->next;
	}
	return(length);
}
string *convert(node* head, int length) {
	node *temp = head;
	int i = 0;
	string *array = new string[length];
	while (temp != NULL) {
		array[i] = temp->info;
		temp = temp->next;
		i++;
	}
	return array;
}
int RecBinSearch(string array[], node* head, int first, int size)
{

	if (size >= first) {
		int mid = first + (size - first) / 2;

		if (array[mid] == head->info)
		{
			return mid;
		}

		else if (array[mid] < head->info)
		{
			return RecBinSearch(array, head, mid + 1, size);
		}

		else
		{
			return RecBinSearch(array, head, first, mid - 1);
		}
	}
	return 0;
}
void insert(node** head, string value) {
	node *temp = new node(value);
	if (*head == NULL) {
		*head = temp;
	}
	else {
		temp->next = *head;
		(*head)->prev = temp;
		*head = temp;
	}
}
node *getIntersection(node *head1, node *head2)
{
	node *result = NULL;
	int length = count(head2);
	int i = 0;
	mergesort(&head2);
	mergesort(&head1);
	string *array = convert(head2, length);
	while (head1 != NULL) {
		if (RecBinSearch(array, head1, 0, length - 1)) {
			insert(&result, head1->info);
		}
		head1 = head1->next;
	}
	return result;
}
void Remove(node* head) {
	node *p2, *dup;
	node *temp = head;
	while (temp->next != NULL) {
		if (temp->info == temp->next->info) {
			p2 = temp->next->next;
			free(temp->next);
			temp->next = p2;
		}
		else
			temp = temp->next;
	}
}

void display(node* head) {
	node *temp = head;
	while (head != NULL) {
		cout << head->info << endl;
		temp = head;
		head = head->next;
	}
}

struct Node {
	string data;
	Node *next;
};
class Stack {

private:
	string *value;
	Node *top;

public:
	Stack();
	void push(string val);
	string pop();
	bool isEmpty();
	string Top();
};
Stack::Stack() {
	top = NULL;
}
bool Stack::isEmpty() {
	return (top == NULL);
}
void Stack::push(string val)
{
	Node *temp = new Node;
	temp->data = val;
	temp->next = top;
	top = temp;
}
string Stack::pop()
{
	if (!isEmpty()) {
		string value = top->data;
		Node *oldtop = top;
		top = oldtop->next;
		delete oldtop;
		return value;
	}
}
string Stack::Top() {
	return top->data;
}
bool isoperator(char c) {
	if (c == '+' || c == '*')
		return true;
	return false;
}
bool par(string s) {
	int count = 0;
	int size = s.length();
	for (int i = 0; i < size; i++) {
		if (s[i] == '(')
			count++;
		else if (s[i] == ')')
			count--;
		if (count < 0)
			return false;
	}
	return count == 0;
}
bool prec(char op1, char op2)
{
	int prec1, prec2;
	if (op1 == '*')
		prec1 = 2;
	else
		if (op1 == '+')
			prec1 = 1;
		else
			if (op1 = '(')
				prec1 = 0;
	if (op2 == '*')
		prec2 = 2;
	else
		if (op2 == '+')
			prec2 = 1;
	return(prec1 >= prec2);
}

string infixToPostfix(string s)
{
	Stack st;
	int size = s.length();
	string pfexp;
	string ch = "";
	string ch2 = "";
	string inv = "invalid";
	if (s == "") {
		return inv;
	}
	if (isoperator(s[0]) || isoperator(s[size - 1])) {
		return inv;
	}
	if (!par(s)) {
		return inv;
	}
	for (int i = 0; i < size; i++)
	{
		ch = s[i];
		if (isalpha(s[i])) {
			if (isdigit(s[i + 1])) {
				ch2 = s[i + 1];
				ch = ch + ch2;
				pfexp += ch;
			}
			else
				pfexp += ch;
		}
		else if (s[i] == '(' || s[i] == ')') {
			if (s[i] == '(') {
				st.push(ch);
			}
			if (s[i] == ')') {
				bool done = false;
				while (done == false) {
					ch = st.Top();
					if (ch == "(") {
						st.pop();
						done = true;
					}
					else {
						pfexp += ch;
						st.pop();
					}
				}
			}
		}
		else if (isoperator(s[i])) {
			if (isoperator(s[i + 1])) {
				return inv;
			}
			while (!st.isEmpty()) {
				if (prec(st.Top()[0], ch[0])) {
					pfexp += st.Top();
					st.pop();
				}
				else {
					break;
				}
			}
			st.push(ch);
		}
	}
	while (!st.isEmpty()) {
		ch = st.Top();
		pfexp += ch;
		st.pop();
	}
	return pfexp;
}
node* MergeLists(node *list1, node *list2) {
	if (list1 == NULL) return list2;
	if (list2 == NULL) return list1;

	if (list1->info < list2->info) {
		list1->next = MergeLists(list1->next, list2);
		return list1;
	}
	else {
		list2->next = MergeLists(list2->next, list1);
		return list2;
	}
}
int Rcheck(string R, string array[]) {
	for (int i = 0; i < 10; i++) {
		if (R == array[i]) {
			return 1;
		}
	}
	return 0;
}
string eval(string op2, string op1, char operate, node* head, node* head2) {
	string r, j, k, h, l, result;
	node *a = NULL;
	node *b = NULL;
	node *c = NULL;
	node *d = NULL;
	node *inter = NULL;
	node *uni = NULL;
	string x[10] = { "R0","R1","R2","R3","R4","R5","R6","R7","R8","R9" };
	if (operate == '*') {
		while (head2 != NULL) {
			if (op1 == head2->info) {
				op1 = head2->prev->info;
				stringstream ss(op1);
				while (ss >> j) {
					insert(&c, j);
				}
			}
			head2 = head2->next;
		}
		stringstream sss(op1);
		while (sss >> h) {
			insert(&c, h);
		}
		while (head != NULL) {
			if (op2 == head->info) {
				op2 = head->prev->info;
				stringstream ss(op2);
				while (ss >> k) {
					insert(&d, k);
				}
			}
			head = head->next;
		}
		stringstream ss(op2);
		while (ss >> l) {
			insert(&d, l);
		}
		inter = getIntersection(d, c);
	}
	if (operate == '+') {
		while (head2 != NULL) {
			if (op1 == head2->info) {
				op1 = head2->prev->info;
				insert(&a, op1);
			}
			head2 = head2->next;
		}
		insert(&a, op1);
		while (head != NULL) {
			if (op2 == head->info && !Rcheck(head->prev->info, x)) {
				op2 = head->prev->info;
				insert(&b, op2);
			}
			head = head->next;
		}
		insert(&b, op2);
		uni = mergesortlist(a, b);
	}
	while (inter != NULL) {
		r += inter->info;
		r += ' ';
		inter = inter->next;
	}
	while (uni != NULL) {
		r += uni->info;
		r += ' ';
		uni = uni->next;
	}
	return r;
}

string evaluatePostfix(string ns, node* head, node* head2)
{
	Stack st;
	string ch, ch2, c, k;
	int i = 0;
	string val;
	string op1, op2;
	int size = ns.length();
	for (int i = 0; i < size; i++) {
		ch = ns[i];
		if (isdigit(ns[i])) {
			ch2 = ns[i - 1];
			c = ch2 + ch;
			st.push(c);
		}
		else if (isalpha(ns[i])) {
			if (ns[i] != 'R') {
				st.push(ch);
			}
		}
		else {
			string op1 = st.Top();
			st.pop();
			string op2 = st.Top();
			st.pop();
			val = eval(op1, op2, ns[i], head, head2);
			st.push(val);
		}
	}
	while (head != NULL) {
		if (ns == head->info) {
			k = head->prev->info;
			st.push(k);
		}
		head = head->next;
	}
	return st.Top();
}
string Cases2(string tempstring)
{
	int size = tempstring.length();
	string c, ch;
	for (int j = 0; j < size; j++)
	{
		c = tempstring[j];
		if (ispunct(tempstring[j])) {
			tempstring[j] = ' ';
		}
		if (isdigit(tempstring[j]))
			tempstring[j] = ' ';
		if (isupper(tempstring[j])) {
			tempstring[j] = islower(tempstring[j]);
		}
	}
	return tempstring;
}
node* read(string setname, string filename) {
	string k, j, i, l;
	node* head = NULL;
	ifstream ifs(filename);
	while (getline(ifs, k)) {
		l = Cases2(k);
		stringstream ss(l);
		while (ss >> j) {
			i += j;
			i += ' ';
		}
	}
	insert(&head, i);
	insert(&head, setname);
	return head;
}
string store(string setname) {
	string set = setname;
	return set;
}
string storeR(string cmd) {
	string R = cmd;
	return R;
}
string storeIF(string setname) {
	string IF = infixToPostfix(setname);
	return IF;
}
string storePF(string R, string IF, node* head, node* head2) {
	string j;
	j = evaluatePostfix(IF, head, head2);
	return j;

}
node* writes(string setname, node* head) {
	string k, j;
	node *temp = NULL;
	while (head != NULL) {
		if (setname == head->info) {
			k = head->prev->info;
		}
		head = head->next;
	}
	stringstream ss(k);
	while (ss >> j) {
		insert(&temp, j);
	}
	mergesort(&temp);
	if (temp == NULL) {
		return temp;
	}
	Remove(temp);
	return temp;
}

string Cases(string tempstring)
{
	int size = tempstring.length();
	string c, ch;
	for (int j = 0; j < size; j++)
	{
		c = tempstring[j];

		if (tempstring[j] == ',') {
			tempstring[j] = ' ';
		}
		if (tempstring[j] == '(') {
			if (tempstring[j - 1] == 'd' || tempstring[j - 1] == 'e') {
				tempstring[j] = ' ';
			}
		}
		if (c == "'")
			tempstring[j] = ' ';
	}
	return tempstring;
}
string Cases3(string tempstring)
{
	int size = tempstring.length();
	string c, ch;
	for (int j = 0; j < size; j++)
	{
		c = tempstring[j];
		if (tempstring[2] != '=') {
			tempstring[2] == '(';
		}
		if (tempstring[j] == '=') {
			tempstring[j] = ' ';
		}
	}
	return tempstring;
}
int main(int argc, char* argv[])
{
	ifstream ip("input.script");
	string a, b;
	string cmd, setname, filename, R, IF, setdata, set, k, T, y, u;
	string search = "read";
	string write = "write";
	string inv = "invalid";
	node *cmds = NULL;
	node *setdatas = NULL;
	node *head = NULL;
	node *result = NULL;
	ofstream lf("logfile.txt");
	while (getline(ip, a)) {
		b = Cases(a);
		stringstream ss(b);
		ss >> cmd >> setname >> filename;
		if (cmd == search) {
			setdatas = read(setname, filename);
			while (setdatas != NULL) {
				insert(&head, setdatas->info);
				setdatas = setdatas->next;
			}
		}
		if (cmd != search && cmd != write) {
			R = storeR(cmd);
			T = Cases3(R);
			stringstream sss(T);
			sss >> y >> u;
			insert(&head, y);
			IF = storeIF(u);
			if (IF == inv) {
				lf << "Format is INVALID" << ": " << cmd << endl;
				k = inv;
			}
			else {
				k = storePF(R, IF, head, head);
			}
			insert(&head, k);
		}
		if (cmd == write) {
			result = writes(setname, head);
			ofstream ofs(filename);
			while (result != NULL) {
				ofs << result->info << endl;
				result = result->next;
			}
			ofs.close();
		}
	}
	ofstream rm("README.txt");
	rm << "Utilized Linked list of Linked lists as data structure to store all variables and inputs" << endl << "Infix to Postfix function reads and converts given expression from script into a valid postfix expression, also checks for expression validity" << endl << "Evaluate function took in and evaluated two operands dependant on the operation(s), If Intersection, calls for Recursive Binary Search, If Union, calls for merge list function" << endl << "Clean(Remove dups, numbers, lower case) and sorts(mergesort) results before writing to output file" << endl;
	rm.close();
	system("pause");
	return 0;
}