#include <iostream>
#include <windows.h> 
#include <random>
#include <thread>
#include<chrono>
#include<iomanip>
#include<stdlib.h>
#include <ctime>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <cstddef>

//кольцевая очередь 


using namespace std;

char symbols[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
int maxElementToAction = 3;
int secondsTime = 5;
int hours = 0, minutes = 0;
double seconds = 0;

/*Описание струкруы очередь. Информационная часть - value,сслыка на следующий элемент - next*/
struct QueueItem {
	std::string value;
	QueueItem* Next;

}*First, *Last;//указатели на первый и последний элемент очереди соответсвенно

/*инициализация и создание пустой очереди*/
void initQueue() {
	First = new QueueItem;//выделяем память для заголовка с помощью указателя First
	First->Next = NULL;//занесение в ссылочную часть заголовка пустого  указателя
	Last = First;// конец очереди 
}

//проврека очереди  на пустоту 
bool isEmpty() {
	if (First->Next == NULL) {
		return 1; 
	}
	else return 0;
}

//проход по очереди и вывод состояния
void ShowQueue() {
	if (!isEmpty()) {//проверка возможности удаления
		QueueItem* current;//вспомогательный указатель
		current = First->Next;//установка указателя в первый реальный элемент
		int i = 1;
		while (current != NULL) {
			std::cout << i << ")" << current->value << "\n";
			current = current->Next;
			i++;
		}
	}
	else std::cout << "\nQueue is empty";
}

void push(/*std::string*/char _value) {//добавление элемента в конец очереди 
	QueueItem* current = new QueueItem;//выделяем память для нового элемента
	current->value = _value;//заполняем информационное поле 
	current->Next = NULL;//ставим нул в связующую часть
	Last->Next = current;//поставим бывший пустой указатель последнего элемента на только что добавленный элемент
	Last = current;//указатель указывает на новый последний элемент в очереди
}

string pop() {//удаление элемента из начала очереди( но после заголовка)
	if (!isEmpty())//проверяем возможность удаления
	{
		QueueItem *current;//ввод вспомогательной ссылочной переменной
		current = First->Next;//установка переменной в адрес первого реального элемента 
		First->Next = current->Next;//изменим связующую часть загоовка так, чтобы она указывала на второй элемент очереди 
		if (isEmpty()) { 
			Last = First; 
		};//если не останется элеменов в очереди
		std::string _value = current->value;
		delete current;//удаляем  элемент
		return _value;
	}
	else std::cout << "\nQueue is empty.Nothing to Delete."; return "-1";
}
int getRandom(int maxValue) { return(rand() % maxValue) + 1; } //вспомогательная функция для получения случайногоч числа от 1 до 100


//моделирование работы очереди
void RandomAction() {
	int randomAction = getRandom(100);//исходя из полученного числа определяем действие со списком
	int randomCount = getRandom(maxElementToAction);
	bool isPush = randomAction % 2 == 0;
	std::cout << "\nAction:" << (isPush ? "Added" : "delete") << "\nNumber of element: " << randomCount;
	if (isPush) {
		for (int i = 0; i < randomCount; i++) {
			char symbol = symbols[getRandom(26)];
			push(symbol);//??????????
			std::cout << "\nAdd: [" << symbol << "]\n";
		}

	}
	else {
		for (int i = 0; i < randomCount; i++) {
			if (!isEmpty())
			{
				std::cout << "\nDelete: [" << pop() << "]";
			}
			else { std::cout << "Queue is empty"; break; }
		}
	}
	ShowQueue();
}

void timer() {
	srand(time(NULL));
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		seconds += 0.1;
		if (seconds >= secondsTime) {
			RandomAction();
			seconds = 0;
		}
		if (GetAsyncKeyState('Q')  < 0) {
			break;
		}
	}
}

int main() {
	initQueue();
	timer();
	return 0;
}