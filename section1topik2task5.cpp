//кольцевая очередь на основе статического массива

#include <iostream>
const int array_size = 5;
int First, Last = 0;
int array_count = 0;


using namespace std;

int failure() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nError.Try again. \n" << endl;
    }
    return a;
}

int IsEmpty() {
    if (array_count == 0) return 1;
    else return 0;
}

int IsFull() {
    if (array_count == array_size) return 1;
    else return 0;
}
 
void push(int *queue_array, int value)
/*Само добавление элемента в очередь выполняется следующим образом:
1)проверить возможность добавления (в массиве есть свободные ячейки?)
2)добавить элемент в массив по индексу Last
3)изменить указатель Last на 1
4)если Last выходит за пределы массива, то установить Last в 1
5)увеличить счетчик числа элементов в очереди*/
{
    if (!IsFull()) {
        queue_array[Last] = value;
        Last++;
        if (Last == array_size) Last = 0;
        array_count++;
    }
    else std::cout << "Error. Massive is full. Try again later";
}

int pop(int *queue_array) {
    /*Удаление элемента из очереди:
1)проверить возможность удаления (в очереди есть элементы?)
2)извлечь элемент из массива по индексу First и выполнить с ним
необходимые действия
3)увеличить указатель First на 1
4)если First выходит за пределы массива, то установить First в 1
5)уменьшить счетчик числа элементов в очереди
*/
    if (!IsEmpty())
    {
        int value = queue_array[First];
        First++;
        if (First == array_size) First = 0;
        array_count--;
        return value;
    }
    else
    {
        std::cout << "Error. Massive is empty.Try again.";
            return -1;
    }
}

void show_queue(int* queue_array)
{
    if (!IsEmpty())
    {
        std::cout << "\n";
        int current = First;
        int i = 1;
        do {
            std::cout << i << ")" << queue_array[current] << "\n";
            current++;
            if (current == array_size) current = 0;
            i++;
        } while (current != Last);
    }
}

void menu(int *queue_array)
{
    while (true) {
        int menu_number;
        int auxiliary_value;
        std::cout << "\nChoice yor coomand:\n" << "1.Is queue is empty?\n2.Is queue is full?\n3.Add element to queue in the end.\n" <<
            "4.Delete element from queue.\n5.Show queue.\n6.End program.\n";
        menu_number = failure();

        if (menu_number == 1)
        {
            if (IsEmpty() == 1)
            {
                std::cout << "\nQueue is empty.";
            }
            else std::cout << "Queue is not empty";
        }
        else if (menu_number == 2)
            if (IsFull() == 1) std::cout << "Queue is full.";
            else std::cout << "Queue is not full.";
        else if (menu_number == 3)
        {
            if (!IsFull())
            {
                std::cout << "\nEnter you value:\n";
                int auxiliary_value = failure();
                push(queue_array, auxiliary_value);
            }
            else std::cout << "Error. Massive is full.";
        }
        else if (menu_number == 4)
        {
            int value = pop(queue_array);
            if (value != -1)
                std::cout << "Element " << value << " is deleted";
        }
        else if (menu_number == 5)
        {
            std::cout << "Queue: ";
            show_queue(queue_array);
        }
        else if (menu_number == 6)
        {
            break;
        }
        else std::cout << "Error. Try again";
    }
}
int main()
{
    int queue_array[array_size];//инициализация пустой очереди размерностью 6
    menu(queue_array);
    return 0;
}
