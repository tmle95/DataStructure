#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct node {
public:
	string info;
	node *next;
	node *prev;
	node(string);
};
node::node(string value) {
	info = value;
	next = prev = NULL;
}
void display(node **head);
node* mergesortlist(node* list1, node* list2);
void split(node* head, node** list1, node** list2);

void swap(node** head, node* a, node* b, node* prev)
{
	*head = b;
	prev->next = a;
	node * temp = b->next;
	b->next = a->next;
	a->next = temp;
}

node* ssort(node* head)
{
	node* temp = head;
	if (temp->next == NULL) {
		return temp;
	} //n
	node* min = head;
	node* beforeMin = NULL;
	node* ptr;

	for (ptr = head; ptr->next != NULL; ptr = ptr->next) {
		if (ptr->next->info < min->info) {
			min = ptr->next;
			beforeMin = ptr;
		}
	}
	if (min != temp) {
		swap(&head, head, min, beforeMin);
	}
	head->next = ssort(head->next);
	return head;
}
void selectionsort(node ** head) {
	if ((*head) == NULL) {
		return;
	}
	*head = ssort(*head);
}

void mergesort(node** head)
{
	node* list1;
	node* list2;
	if ((*head == NULL) || ((*head)->next == NULL))
	{
		return;
	}
	split(*head, &list1, &list2);
	mergesort(&list1);
	mergesort(&list2);
	*head = mergesortlist(list1, list2);
}
node* mergesortlist(node* list1, node* list2)
{
	node* result = NULL;

	if (list1 == NULL) {
		return(list2);
	}
	else if (list2 == NULL) {
		return(list1);
	}

	if (list1->info <= list2->info)
	{
		list1->next = mergesortlist(list1->next, list2);
		list1->next->prev = list1;
		list1->prev = NULL;
		return list1;
	}
	else
	{
		list2->next = mergesortlist(list1, list2->next);
		list2->next->prev = list2;
		list2->prev = NULL;
		return list2;
	}
}
void split(node* head, node** list1, node** list2) {
	node* fast;
	node* slow;
	if (head == NULL || head->next == NULL) {
		*list1 = head;
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
int *createarray(int size) {
	int *array = new int[size];
	for (int i = 0; i < size; i++) {
		array[i] = rand() % size;
	}
	return array;
}
int BinSearch(string array[], node* head, int size) {
	int low = 0;
	int high = size - 1;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (array[mid] == head->info)
		{
			return 1;
		}
		else if (array[mid] > head->info)
		{
			high = mid - 1;
		}
		else if (array[mid] < head->info)
		{
			low = mid + 1;
		}
	}
	return -1;
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
	return -1;
}
int RecSearch(string array[], node* head, int size) {
	size = size - 1;

	if (size < 0) {
		return -1;
	}
	else if (head->info == array[size]) {
		return 1;
	}
	else
		return RecSearch(array, head, size);
}
int Search(string array[], node*head, int size) {
	int i, j;
	for (j = 0; j < size; j++) {
		if (array[j] == head->info) {
			return 1;
		}
	}
	return -1;
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
void Delete(node* head) {
	node* temp = head;
	node *n = head;
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
string Cases(string tempstring)
{
	int size = tempstring.length();
	for (int j = 0; j < size; j++)
	{
		if (isupper(tempstring[j]))
			tempstring[j] = tolower(tempstring[j]);
	}
	return tempstring;
}
void countword(string array[], int size) {
	ofstream ofs("output.txt");
	int *seen = new int[size];
	for (int i = 0; i < size; i++)
		seen[i] = 0;
	for (int i = 0; i < size; i++) {
		if (seen[i] == 0) {
			int count = 0;
			for (int j = i; j < size; j++)
				if (array[j] == array[i]) {
					count += 1;
					seen[j] = 1;
				}
			ofs << array[i] << " " << count << endl;
		}
	}
	ofs.close();
}
int main(int argc, char* argv[]) {

	ifstream dict("dictionary.txt");
	string a, b, c;
	int length, length2;
	node *head = NULL;
	node *ilist = NULL;
	while (getline(dict, a)) {
		stringstream ss(a);
		while (ss >> b) {
			c = Cases(b);
			insert(&head, c);
		}
	}
	Delete(head);
	mergesort(&head);
	//selectionsort(&head);
	Remove(head);
	length = count(head);
	//display(head);
	string *array = convert(head, length);
	string word, text, ctext;
	ifstream ifs("input.txt");
	while (getline(ifs, word)) {
		stringstream ss(word);
		while (ss >> text) {
			ctext = Cases(text);
			insert(&ilist, ctext);
		}
	}
	Delete(ilist);
	mergesort(&ilist);
	//display(ilist);
	length2 = count(ilist);
	string *array2 = new string[length2];
	int result;
	int i = 0;
	while (ilist != NULL) {
		result = RecBinSearch(array, ilist, 0, length - 1);
		if (result == -1) {
			array2[i] = ilist->info;
			i++;
		}
		ilist = ilist->next;
	}
	countword(array2, i);

	system("pause");
	return 0;
}
