//произвольнеы двоичные деревья
#include <iostream>

using namespace std;

bool stop = false;
int counter = 0;
struct Three {
	int value;
	Three* left;
	Three* right;
}*Root,*Parent;

void find(Three *three, int _value)
{
	if (stop == true) return;
	else if (three != NULL) {
		if (three->value == _value) {
			stop = true;
			Parent = three;
			return;
		}
		find(three->left, _value);
		find(three->right, _value);
	}
}

void push() {
	int _value;
	if (Root == NULL) {
		Root = new Three;
		cout << "\nEnter vertex: \n";
		cin >> _value;
		Root->value = _value;
		Root->left = NULL;
		Root->right = NULL;
	}
	else {
		int auxvar;
		cout << "\nEnter her parent: \n";
		cin >> auxvar;
		Parent = NULL;
		stop = false;
		find(Root, auxvar);
		if (Parent != NULL) {
			Three* current = new Three;
			cout << "\nEnter your element: \n";
			cin >> current->value;
			current->left = NULL;
			current->right = NULL;
			if ((Parent->left == NULL) && (Parent->right == NULL)) {
				int select;
				cout << "\nAdd:\n1-left\n2-right\n";
				cin >> select;
				if (select == 1) {
					Parent->left = current;
				}
				else if (select == 2) {
					Parent->right = current;
				}
			}
			else {
				if (Parent->left == NULL) {
					cout << "\nAdd on left\n";
					Parent->left = current;
				}
				else if (Parent->right==NULL) {
					cout << "\nAdd on right\n";
					Parent->right = current;
				}
				else  cout << "\nYou can not add.More than 2 child.\n";
			}
	}
		else {
			cout << "\nCan not find parent\n";
			return;
		}
	}
	counter++;
}

/*void ReverseSummetry(Three *head,int level) {
	if (head != NULL) {
		(level)++;
		ReverseSummetry(head->left, level);
		for (int i = 0; i < 4 * (level - 1); i++) {
			cout << "\t\t\t";
		}
		cout << "\n\n" << head->value;
		ReverseSummetry(head->right, level);
	}
}*/

//ПОСТРОЧНЫЙ ВЫВОД В ПРЯМОМ НАПРАВЛЕНИИ
void Forward(Three* head, int level) {
	if (head != NULL) {
		string str; //обработка корневой вершины head
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << head->value << "\n";
		Forward(head->left, level + 1); //обработка  всех левых поддеревьев
		Forward(head->right, level + 1); //обработка  всех правых поддеревьев
	}
}

//ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
void Symmetric(Three* head, int level) {
	if (head != NULL) {
		Symmetric(head->left, level + 1); //обработка  всех левых поддеревьев
		string str; //обработка корневой вершины head
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << head->value << "\n";
		Symmetric(head->right, level + 1); //обработка  всех правых поддеревьев
	}
}

void ReverseSummetry(Three *head, int level) {
	if (head != NULL) {
		ReverseSummetry(head->right, level + 1); //обработка  всех правых поддеревьев
		string str; //обработка корневой вершины head
		for (int i = 0; i < level; i++)
			str += "     ";
		cout << " " << str << head->value << "\n";
		ReverseSummetry(head->left, level + 1); //обработка  всех левых поддеревьев
	}
}

void pop(Three *&head) {
	if (head != NULL) {
		pop(head->left);
		pop(head->right);
		free(head);
		counter--;
		if (counter == 0) {
			head = NULL;
		}
	}
}

void menu() {
	int select = 0;
	while (select != 5) {
		cout << "\nChoice command:";
		cout << "\n1. Add element";
		cout << "\n2. Find";
		cout << "\n3. Show";
		cout << "\n4. Delete three";
		cout << "\n5.Exit\n";
		cin >> select;
		if (select == 1) push();
		else if (select == 2) {
			if (Root != NULL) {
				cout << "\nEnter element which you want to find: \n";
				int _value;
				cin >> _value;
				Parent = NULL;
				stop = false;
				find(Root, _value);
				if (Parent != NULL) cout << "\nElement " << _value << " is founded";
				else cout << "\nElement " << _value << " is not  founded";
			}
			else cout << "\nThree is empty";
		}
		else if (select == 3) {
			if (Root != NULL)
			{
				int choice;
				while (choice = -1) {
					cout << "\nWhich view you wold prefer:\n1-in direct\n2-in symmerical\n3-in reverse-symmetrical";
					cin >> choice;
					if (choice == 1) {Forward(Root, 0); break;
				}
					else if (choice == 2) { Symmetric(Root, 0); break; }
					else if (choice == 3) { ReverseSummetry(Root, 0); break; }
					else cout << "\nError. Try again"; choice = -1;
				}
			}
			else cout << "\nError.Create three";
		}
		else if (select == 4) {
			pop(Root);
		}
		else if (select == 5) break;
		else cout << "\nError.Try again";
	}
}

int main() {
	menu();
	return 0;
}