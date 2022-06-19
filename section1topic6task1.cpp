//Построение и обработка двоичных деревьев поиска
//Двоичное дерево поиска - двоичное дерево, если для каждой вершины  все ключи ее левого поддерева меньше
//ключа самой вершины, а все ключи правого поддерева, больше ключа самой вершины

#include <iostream>

using namespace std;
//bool find = 0;
int counter = 0;

struct Three {
	int value,count;//информационная часть и счетчик появлений ключа
	Three *left;
	Three *right;
}*Root,*Parent;//корень и родитель

Three* find(Three *three, Three *parent, int _value) {//поиск
	if (three != NULL) {
		Three* current = three;
		while (current != NULL) {
			if (current->value == _value) return current;
			else if (current->value > _value) {
				if (parent != NULL) parent = current;
				current = current->left;
			}
			else if (current->value < _value) {
				if (parent != NULL) parent = current;
				current = current->right;
			}
		}
		return NULL;
	}
	else {
		cout << "\nThree is empty";
		return NULL;
	}
}

void Add(Three *&three, int _value) {//добавление c рекурсией
	if (three == NULL) {
		three = new Three;
		counter++;
		three->value = _value;
		three->left = NULL;
		three->right = NULL;
		three->count = 1;
		return;
	}
	else {
		if (three->value < _value) Add(three->right, _value);
		else {
			if (three->value > _value) Add(three->left, _value);
			else three->count++;
		}
		
	}
}

/*void nonrecpush(int _value) {//добавление без рекурсии
	if (Root == NULL) {
		Root = new Three;
		Root->value = _value;
		Root->left = NULL;
		Root->right = NULL;
		Root->count = 1;
		return;
	}
	else {
		Three* parent = Root;
		Three* current = Root;
		while (current != NULL) {
			parent = current;
			if (_value > current->value)current = current->right;
			else {
				if (_value < current->value)current = current->left;
				else {
					current->count++; //current = NULL;
				}
			}
		}
		if (_value > current->value) {
			parent->right = new Three;
			parent->right->value = _value;
			parent->right->count = 1;
			parent->right->left = NULL;
			parent->right->right = NULL;
			counter++;
		}
		if (_value < current->value) {
			parent->left = new Three;
			parent->left->value = _value;
			parent->left->count = 1;
			parent->left->left = NULL;
			parent->left->right = NULL;
			counter++;
		}
	}
}*/

void recpush(Three *&three,int _value) {//добавление с участием рекурсии
	if (three != NULL) {
		if (three->value < _value)recpush(three->right, _value);
		else {
			if (three->value > _value)recpush(three->left, _value);
			else three->count++;
		}

	}
	else {
		three = new Three;
		counter++;
		three->value = _value;
		three->right = NULL;
		three->left = NULL;
		three->count = 1;
		return;
	}
}
void show(Three *three,int level,Three *prev) {
	if (three != NULL) {
		level++;
		show(three->right, level+1,three);
		string str;
		for (int i = 1; i < level; i++) {
			str += "   ";
		}
		cout << " " << str << three->value<<"("<<prev->value<<")" << "\n";/* "(" << three->count << ")";*/
		show(three->left, level+1,three);
	}
}
void aapp(Three *three,int level) {
	if (three != NULL) {
		level++;
		aapp(three->left, level);
		cout << three->value << " (" << three->count << ") ";
		aapp(three->right, level);
	}
 }

void Change(Three*& current, Three*& temp) {
	if (current->right != NULL) Change(current->right, temp);
	else {
		temp->value = current->value;
		temp = current;
		current = current->left;
	}
}
void pop(Three*& three, int _value) {
	if (three != NULL) {
		if (_value < three->value) pop(three->left, _value);
		else {
			if (_value > three->value) pop(three->right, _value);
			else {
				Three  *temp = three;
				if (temp->right == NULL) three = temp->left;
				else {
					if (temp->left == NULL) three = temp->right;
					else Change(three->left, temp);
				}
				free(temp);
				counter--;
			}
		}
	}
 }

void Destroy(Three *&three) {
	if (three != NULL) {
		Destroy(three->left);
		Destroy(three->right);
		free(three);
		counter--;
		if (counter == 0) three = NULL;
	}

}

int main() {
	int select=0;
	while (select != 7) {
		cout << "\nChoice command:";
		cout << "\n1. Create three";
		cout << "\n2. Add vertex(rec)";
		cout << "\n3. Find vertex";
		cout << "\n4. Show(reverse-symmetrical)";
		cout << "\n5. Delete vertex";
		cout << "\n6. Delete three";
		cout << "\n7. Exit";
		cout << "\n8.Snow in direct\n";
		cin >> select;
		if (select == 1) {
			int count;
			cout << "\nEnter the number of vertexes: \n";
			cin >> count;
			for (int i = 0; i < count; i++)
			{
				int _value = rand() % 100 + 1;
				Add(Root, _value);
			}
		}
		/*else if (select == 2) {
			int _value;
			cout << "\nenter your vertex: ";
			cin >> _value;
			nonrecpush(_value);
		}*/
		else if (select == 2) {
			int _value;
			cout << "\nenter your vertex: ";
			cin >> _value;
			recpush(Root, _value);
		}
		else if (select == 3) {
			int _value;
			cout << "\nenter your vertex which you want to find : ";
			cin >> _value;
			Three* found = find(Root, NULL, _value);
			if (found == NULL) {
				cout << "\nElement is not founded."; continue;
			}
			cout << found->value << found->count;
		}
		else if (select == 4) {
			if (Root != NULL) {
				show(Root, 0,Root);
			}
			else cout << "\nThree is empty.Nothing to Show.";
		}
		else if (select == 5) {
			if (Root != NULL) {
				int _value;
				cout << "\nEnter element which you want to delete: \n";
				cin >> _value;
				pop(Root, _value);
			}
			else cout << "\nNothing to delete.";
		}
		else if (select == 6) {
			Destroy(Root);
		}
		else if (select == 7) { break; }
		else if (select == 8)
		{
			aapp(Root,0);
		}
		else  cout << "\nError.Try again";
	}

}
