#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <class T>
struct node
{
public:
	T info;
	node<T> *next;
	node<T> *prev;
	node(T value) : info(value) {
		next = NULL;
		prev = NULL;
	};
};


template <class T> class
DoublyLinkedList
{
private:
	node<T> *head;
	node<T> *tail;

public:
	DoublyLinkedList() {
		head = NULL;
		tail = NULL;
	}
	void InsertHead(T value);
	void Display();
	template <class O> friend ostream &operator << (ostream &s, DoublyLinkedList<O> list);
	void reverse();
	void outfile(string filename);
	int count(); //count node bytes
	bool Delete(T &value);
	void Delete();
};

template <class T> int DoublyLinkedList<T>::count() {
	node<T> *temp = head;
	int length = 0;
	while (temp != NULL) {
		length++;
		temp = temp->next;
	}
	return(length);
}
template <class T> bool DoublyLinkedList<T>::Delete(T &value) {
	if (head == tail)
	{
		value = head->info;
		head = tail = nullptr;
	}
	else
	{
		value = head->info;
		node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	return true;
}
template <class T> void DoublyLinkedList<T>::InsertHead(T value) //inserting a node to the beginning
{
	node<T> *n = new node<T>(value);
	if (head == NULL) {
		head = n;
		tail = head;
	}
	else {
		tail->next = n;
		n->prev = tail;
		n->next = NULL;
		tail = n;
	}
}
template <class T> void DoublyLinkedList<T>::Delete() {
	node<T>* temp = head;
	node<T> *n = head;
	string word;
	while (temp != NULL) {
		word = temp->info;
		if (word[0] <= '9' && word[0] >= '0') {
			if (temp->next != NULL) {
				n = temp->next;
			}
			else {
				n = n->prev;
				n->next = NULL;
				tail = n;
			}
			if (temp->prev != NULL) {
				n->prev = temp->prev;
			}
			else {
				n->prev = NULL;
				head = n;
			}
			if (temp->next != NULL) {
				if (n->prev != NULL)
					n->prev->next = temp->next;
			}
			else
				n->prev->next = NULL;
			delete temp;
			temp = n;
		}
		else if (temp->next != NULL) {
			temp = temp->next;
		}
		else {
			temp = temp->next;
		}
	}
}
template <class T> void DoublyLinkedList<T>::reverse() {
	node<T> *temp = head;
	node<T> *n;
	while (temp != NULL) {
		n = temp->next;
		temp->next = temp->prev;
		temp->prev = n;
		if (n == NULL) {
			tail = head;
			head = temp;
		}
		temp = n;
	}
}

template <class T> void DoublyLinkedList<T>::Display()
{
	node<T> *temp = tail;
	while (temp != NULL)
	{
		cout << temp->info << endl; //p.s going to print in reverse
		temp = temp->prev;
	}
	cout << endl;
}
template <class T> void DoublyLinkedList<T>::outfile(string filename) {
	ofstream ofs("output.txt");
	node<T> * temp = tail;
	while (temp != NULL) {
		ofs << temp->info << endl;
		temp = temp->prev;
	}
	ofs.close();
}

template <class O> ostream &operator << (ostream &s, DoublyLinkedList<O> list)
{
	node<O> *temp = list.head;
	while (temp != NULL)
	{
		s << temp->info << " ";
		temp = temp->next;
	}
	return s;
}
string insertSpace(string& line) {
	string res;
	res += line[0];
	for (int i = 1; i < line.size(); ++i) {
		if ((isalpha(line[i]) && isdigit(line[i - 1]))
			|| (isalpha(line[i - 1]) && isdigit(line[i])))
			res += ' ';
		res += line[i];
	}
	return res;
}
string Cases(string tempstring)
{
	int size = tempstring.length();
	for (int j = 0; j < size; j++)
	{
		if (isupper(tempstring[j]))
			tempstring[j] = tolower(tempstring[j]);
		if (ispunct(tempstring[j]))
			tempstring[j] = ' ';
	}
	return tempstring;
}
string Delete(string tempstring) {
	int size = tempstring.length();
	for (int j = 0; j < size; j++) {
		if (isdigit(tempstring[j]))
			tempstring[j] = ' ';
		if (isupper(tempstring[j]))
			tempstring[j] = tolower(tempstring[j]);
		if (ispunct(tempstring[j]))
			tempstring[j] = ' ';
	}
	return tempstring;
}
int main(int argc, char* argv[])
{

	DoublyLinkedList< DoublyLinkedList<string> > MainList;
	string a, b, c, d, e;
	int lines = 0;
	ifstream ifs("Text.txt");
	while (getline(ifs, a)) {
		DoublyLinkedList<string> sublist;
		lines++;
		d = insertSpace(a);
		b = Cases(d);
		stringstream ss(b);
		while (ss >> c)
		{

			sublist.InsertHead(c);
		}
		sublist.reverse();
		sublist.Delete();
		MainList.InsertHead(sublist);


	}

	MainList.Display();
	//MainList.outfile("output.txt");
	//ofstream ofs("README.TXT");
	//ofs << "Struct Node declares T datatype info, prev and next node ptrs;head and tail ptrs declared private access in DoublyLinkedList class; all other functions declared public; count function counts size of bytes used; InsertHead function takes the data and stores into one doubly linked list as a node; Reverse function traverses through the created doubly linked list and then reverses the data stored in it; in main, each line of text file were stored into a single doubly linked list called sublist, and then each sublist were stored into one list called MainList; Display(for testing purposes) and Outfile used for outputting the created MainList in REVERSED order." << endl;
	//ofs.close();
	system("pause");
	return 0;
}
