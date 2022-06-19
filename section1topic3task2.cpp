﻿// section1topic3task2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <string>
//упорядоченный линейный список на основе массива 
using namespace std;

const int array_size = 10;//размер массива 
int counter;//счетчик элементов в списке

struct List {
	int value;//информационная часть элемента списка
}list[array_size];

void initList(){ //инициализация списка
	for (int i = 0; i < array_size; i++) list[i].value = NULL;
	counter = 0;
}

int isEmpty() {//проврека на пустоту 
	if (counter == 0) return 1;
	else return 0;
}

int isFull() {//проверка заполненности списка
	if (counter == array_size) return 1;
	else return 0;
}

int sort() {//сортировка элементов списка по возрастанию
	if (!isEmpty()) {//проверка списка на пустоту
		if (counter == 1) return 2;//для случая если в списке 1 элемент
		else {
			int _value;//вспомогательная переменная
			for (int i = 0; i < counter; i++) {
				for (int j = counter - 1; j > i; j--) {
					if (list[j - 1].value > list[j].value) {
						_value = list[j - 1].value;
						list[j - 1].value = list[j].value;
						list[j].value = _value;
					}
					/*если элемент стоящий на j-1 местеюольше по значению элемента на j,то
					вспомогательной переменной присваивается значение элемента j-1,
					значению элементаj-1  присваевается значение j, и наоборот через всопомгатльную переменную */
				}
			}
			return 1;
		}
	}
	else return 0;
}

void Show() {//проход по списку и его показ
	if (!isEmpty()) {
		cout << "\nList is filled with  " << counter << "elements out of " << array_size << "\n";
		for (int i = 0; i < counter; i++) {
			cout << i + 1 <<")"<< list[i].value << "\n";
	}
	}
	else { cout << "\nThe list is empty\n"; }
}

void push() {
	if (!isFull()) {
		bool a = 1;
		int _value;
		if (isEmpty()) {
			cout << "\nThe list is empty.Element will be add first\n" << "Enter your element:\n ";
			cin >> _value;
			list[0].value = _value;
			counter++;
			return;
		}
		cout << "\nEnter your element:\n";
		cin >> _value;

		for (int i = 0; i < counter; i++) {
			if (_value < list[i].value) {
				if (i == counter) list[counter].value = _value;//добавление в конец
				if (i < counter) {
					for (int k = counter; k > i; k--) //копирование ячеек с конца 
						list[k].value = list[k - 1].value;
					list[i].value = _value;//запись в новую ячейку
				}
				a = 0;
				cout << "\nElement added to cell " << i + 1 << "\n";
				break;
			}
		}
		if (a) {
			list[counter].value = _value;//запись в конец если все элементы меньше заданного
			cout << "\nElement entered to the end of list";
		}
		counter++;
}
	else { cout << "\nEnter is impossible. The list is full"; }
}

void pop() {
	if (!isEmpty()) {
		Show();
		int _value;
		cout << "\nEnter element wich to be removed:\n";
		cin >> _value;
		int k = -1;
		while (k == -1) {
			for (int i = 0; i < counter; i++) {
				if (list[i].value == _value) {
					k++;
					for (int k = i; k < counter; k++) {
						list[k].value = list[k + 1].value;
					}
						counter--;
						cout << "\nElement " << _value << "is deleted" << "Now,you have " << counter << "in list\n";
				}
			}
			if (k == -1) cout << "\nThere is no such element in list";
		}
	}
	else cout << "\nNothing to delete.List is empty";
}

void find() {
	if (!isEmpty()) {
		int auxiliary_count = 0;
		Show();
		int _value;
		cout << "\nEnter the element you want to find\n ";
		cin >> _value;
		//cin.clear(); cin.ignore(32767, '\n'); getline(cin, _value);
		for (int i = 0; i < counter; i++) {
			if (list[i].value == _value) auxiliary_count = i + 1;
		}
		if (auxiliary_count != 0) cout << "\nElement " << _value << "is founded.\nHis number is:" << auxiliary_count;
		else cout << "\nElement" << _value << "is not founded";
	}
	else cout << "\nNothing to find.List is empty";
}

void clear() {
	for (int i = 0; i < array_size; i++) list[i].value = NULL;
	counter = 0;
	cout << "\nList is cleared";
}

int failure() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "\nError. Try again. \n" << endl;
	}
	return a;
}

void menu() {
	int number;
	string value;
	while (true) {
		cout << "\nChoice your command\n";
		cout << "\n1.Show list";
		cout << "\n2.Is List empty?";
		cout << "\n3.Is List full?";
		cout << "\n4.Add element";
		cout << "\n5.Delete element";
		cout << "\n6.Find element";
		cout << "\n7. Sort List";
		cout << "\n8.Clear List";
		cout << "\n9.Exit";
		cout << "\nNumber of command:\n";
		number = failure();
		if (number == 1) {
			Show();

		}
		else if (number == 2) {
			if (isEmpty() == 1)cout << "\nList is empty";
			else cout << "\nList is not empty";
		}
		else if (number == 3) {
			if (isFull() == 1)cout << "\nList is full";
			else cout << "\nList is not full";

		}
		else if (number == 4) {
			push();
		}
		else if (number == 5) {
			pop();
		}
		else if (number == 6) {
			find();
		}
		else if (number == 7) {
			int act = -1;
			cout << "\nYou want to sort list?\n1- yes, 0- no";
			while ((act != 0) && (act != 1)) {
				act = failure();
				if (act == 1) {
					sort();
					if (sort() == 1) {
						cout << "\nlist is sorted";
						break;
					}
					if (sort() == 2) {
						cout << "\n List have 1 element";
						break;
					}
					if (sort() == 0) {
						cout << "\nList is empty";
					}
				}
				else if (act == 0) return;
				else {
					act = -1;
					cout << "\nError. Choice right command";
				}
			}
		}
		else if (number == 8) {
			clear();
		}
		else if (number == 9) {
			clear();
			break;
		}
		else cout << "\nError. Choice right command";
	}
}



int main() {
	initList();
	menu();
	return 0;
}
