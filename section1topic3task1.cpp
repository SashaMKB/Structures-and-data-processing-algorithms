#include <iostream>
//линейный динамический двунаправленный список 
//каждый элемент иммет указатель на левого и правого соседей
//выделяется память под заголовок и указатели устанавливаются в вершину
using namespace std;

int counter;

struct DynamicBiDirectionalList {
	int value;
	DynamicBiDirectionalList* right, * left;
}*Head;

void initList() {
	Head = new DynamicBiDirectionalList();
	Head->left = Head;
	Head->right = Head;
	Head->value = NULL;
	counter = 0;
}

bool isListEmpty() {
	if (Head->right == Head) return 1;
	else return 0;
}

void showList() {
	cout << "\nList\n";
	if (!isListEmpty())
	{
		cout << "\nList nave" << counter << "elements\n";
		int choice;
		while (true) {
			cout << "\nWhice direcion you want?\n0-in direct\n1-in reverse\n";
			cin >> choice;
			DynamicBiDirectionalList* current;
			int i;
			int leftlink, rightlink;
			if (choice == 0) {
				i = 1;
				current = Head->right;
				while (current != Head) {
					rightlink = (current->right)->value;
					leftlink = (current->left)->value;
					cout << i << ")" << current->value << " , left  : " << leftlink << ", right : " << rightlink << "\n";
					current = current->right;
					i++;
				}
				break;
			}
			else if (choice == 1) {
				i = counter;
				current = Head->left;
				while (current != Head)
				{
					rightlink = (current->right)->value;
					leftlink = (current->left)->value;
					cout << i << ")" << current->value << " , left  : " << leftlink << ", right  : " << rightlink << "\n";
					current = current->left;
					i--;
				}
				break;
			}
			else {
				cout << "\nError. Try enter command again\n";
			}
		}
	}
	else cout << "\nList is empty\n";
}
void push() {
	int _value;
	DynamicBiDirectionalList* current = nullptr;
	DynamicBiDirectionalList* Temp = new DynamicBiDirectionalList;
	int choice;
	while (true) {
		cout << "\nWhere you want add element?\n0- before\n1-after\n";
		cin >> choice;
		int i = -1;
		if (choice == 0) {
			if (!isListEmpty()) {
				while (i == -1)
				{
					current = Head->right;
					cout << "\nEnter element before which you want to add:\n";
					cin >> _value;
					while ((current != Head) && (current->value != _value)) {
						current = current->right;
					}
					if (current != Head) {
						i++;
						Temp->right = current;
						Temp->left = current->left;
						(current->left)->right = Temp;
						current->left = Temp;
					}
					else cout << "\nElement" << _value << " is not founded. Try again.";
				}
				break;
			}
			else cout << "\nYou can not 'add before' for empty list.Try later.";
		}
		else if (choice == 1) {
			if (!isListEmpty()) {
				while (i == -1) {
					current = Head->right;
					cout << "\nEnter element after witch you wanr to add:\n";
					cin >> _value;
					while ((current != Head) && (current->value != _value)) {
						current = current->right;
					}
					if (current != Head) {
						i++;
						Temp->right = current->right;
						Temp->left = current;
						(current->right)->left = Temp;
						current->right = Temp;
					}
					else cout << "\nElement" << _value << " is not founded. Try again.";
				}
				break;
			}
			else
			{
				Temp->right = Head;
				Temp->left = Head;
				Head->right = Temp;
				Head->left = Temp;
				break;
			}
		}
		else cout << "\nError,try again.";
	}
	cout << "\nEnter your element:\n";
	cin >> _value;
	Temp->value = _value;
	counter++;
}
void pop() {
	if (!isListEmpty()) {
		int _value;
		DynamicBiDirectionalList* current;
		current = Head->right;
		int i = -1;
		showList();
		while (i == -1) {
			cout << "\nEnter element what you want to delete: \n";
			cin >> _value;
			while ((current != Head) && (current->value != _value)) {
				current = current->right;
			}
			if (current != Head) {
				i++;
				cout << "\nElement " << _value << " is founded";
				(current->left)->right = current->right;
				(current->right)->left = current->left;
				counter--;
				cout << "\nElement " << current->value << " is deleted. Now you have " << counter << " elements in list";
				delete current;
			}
			else cout << "\nElement " << _value << "is not founded\n";
		}
	}
	else cout << "\nNothing to delete. List is empty";
}

void find() {
	if (!isListEmpty()) { 
		int _value;
		cout << "\nEnter element which you want to find: ";
		cin >> _value;
		int choice = -1, i;
		DynamicBiDirectionalList* current; 
		while ((choice != 0) && (choice != 1)) {
			cout << "\nIn which direction to search\n 0 - in direct\n 1 - in revere\n ";
			cin >> choice; 
			if (choice == 0) {
				i = 1;
				current = Head->right; 
				while ((current != Head) && (current->value != _value)) {
					current = current->right;
					i++;
				}
				if (current != Head) cout << "\nElement  " << _value << " id found under number " << i << "\n";
				else cout << "\nElement " << _value << " is not founded\n";
			}
			else if (choice == 1) {
				i = counter;
				current = Head->left; 
				while ((current != Head) && (current->value != _value)) {
					current = current->left;
					i--;
				}
				if (current != Head) cout << "Element  " << _value << " is found under number " << i << "\n";
				else cout << "Element " << _value << " is not founded\n";
			}
			else {
				cout << "\nError. Try again\n"; choice = -1;
			}
		}
	}
	else {
		cout << "\nNothing to find.List is empty.\n";
	}
}


void menu() {
	int number;
	//int value;
	while (true) {
		cout << "\n Choice command:\n";
		cout << "1. Show list\n";
		cout << "2. Is list Empty?\n";
		cout << "3. Add element\n";
		cout << "4. Delete element\n";
		cout << "5. Find element\n";
		cout << "0. Exit\n";
		cin >> number;
		if (number == 1) showList(); //1. Вывод текущего состояния списка на экран
		else if (number == 2) { 
			if (isListEmpty() == 1) cout << "\nList is Empty\n";
			else cout << "\nList is not Empty\n";
		}
		else if (number == 3) push(); //3. Добавить элемент в список
		else if (number == 4) pop(); 
		else if (number == 5) find(); 
		else if (number == 0) {
			break;
		}
		else cout << "\nError. Try again.\n";
	}
}

int main() {
	initList(); 
	menu(); 
	return 0;
}
