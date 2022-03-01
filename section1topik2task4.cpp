#include <iostream>

using namespace std;

int failry() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nError.Do it again. \n" << endl;
    }
    return a;
} 

//описание стека 
struct Stack
{
    int value; //информационная часть стека, хранящее число
    Stack* next; // указатель ссылка на следующий элемент в стеке
} *sp, *sp_auxiliary; // указатели вершин главного и вспомогательного стеков


//инициализация стека

inline void initStack()
{
    sp = NULL; //пустой основной стек
    sp_auxiliary = NULL;//пустой вспомогательный стек( используется для удаленных данных)
}

/*элементы стека при его динамической реализации могут занимать любую свобоную область памяти,
 для связи элементов используются переменные ссылчоного типа*/


//проврека пустоты стека
bool isEmpty()
{
    if (sp == NULL) return  1;
    else return 0;
}

//проврека пустоты стека(вспомогательного)

bool IsSecondEmpty()
{
    if (sp_auxiliary == NULL) return 1;
    else return 0;
}
// вывод состояния и проверка заполненности 

void ShowStack(Stack* _sp)
{
    if (_sp != NULL)  //если указатель стека на вершину не пуст
    {
        std::cout << "\n";
        Stack *current;
        current = _sp;
        int i = 1;
        do 
        {
        std:cout << i <<")"<< current->value << "\n";  // выводим информационную часть элемента стека (value) 
        current = current->next;//перекидываем указатель на элемент  дальше
        i++;
        }         while (current != NULL); 
    }
    else
    {
        std::cout << "Stack is empty";
    }
}


//добавление элемента
Stack *push(Stack* _sp, int _value)
{
    Stack *item = new Stack;
    item->value = _value;
    item->next = _sp;
    _sp = item;
    return _sp; //возвращает ссылку на новый элемент стека 
}

//добавление случайного количества элементов в стек
void PushRand() 
{
    int newrand;
    std:cout << "How many elements you want to join?";
    newrand = failry();
    for (int i = 0; i<newrand; i++)
    {
        sp = push(sp, rand());
    }
}

//удаление элемента
int pop()
{
    if (!(isEmpty()))
    {
        int value = sp->value; // запоминаем число находящееся в вершине стека
        Stack* current;
        current = sp;//указываем что указатель на врешину стека в current
        sp = sp->next;// перекидываем указатель на следущую элемент, делая его новой вершиной стека
        delete current;// удаляем текущий указатель на вершину стека
        return value;// возвращаем число находящееся в удаленном элементе
    }
    else return -1;
}

//перемещение во вспомогательный стек(вместо удаления)
void MoveToSecondStack()
{
    Stack *current = sp;
    sp->next = sp;
    current->next = sp_auxiliary;
    sp_auxiliary = current;
}
//добавление с вершины вспомогательного стека

void add_from_second()
{
    Stack* current = sp_auxiliary;
    sp_auxiliary->next = sp_auxiliary;
    current->next = sp;
    sp = current;
}

void menu()
{
    int console_command_number, value, auxiliary_console_command_nuber;
    while (true)
    {
        std::cout << "\nEnter command number:\n";
        std::cout<<"1.Output the state of main stack.\n" <<"2.Add element to  main stack\n"
            <<"3.Delete elemet from main stack\n"<<"4.Add random number to main stack\n"
            <<"5.Output the state of auxiliary stack\n"<<"6.End programm\n";
        std::cout << "Your choice:\n";
        console_command_number = failry();

        if (console_command_number == 1) {
            std::cout << "State of main stack:\n";
            ShowStack(sp);
        }
        else if (console_command_number == 2)
        {
            std::cout << "Choice wat to add:1.To main stack.\n2.From auxiliary stack.";
            auxiliary_console_command_nuber = failry();
            if (auxiliary_console_command_nuber == 1)
            {
                std::cout << "Enter number: ";
                value = failry();
                sp = push(sp, value);
            }
            else if (auxiliary_console_command_nuber == 2)
            {
                if (!IsSecondEmpty())
                {
                    add_from_second();
                }
                else
                {
                    std::cout << "Auxiliary stack is emrty";
                }
            }
            else
            {
                std::cout << "Error.Try again";
            }
        }
        else if (console_command_number == 3)
        {
            std::cout << "Choice coomand:1.Delete element with memory realase.\n2.Move element to auxiliary stack.";
            auxiliary_console_command_nuber = failry();
            if (auxiliary_console_command_nuber == 1)
            {
                value = pop();
                if (value != -1)
                {
                    std::cout << "Element " << value << " delete";
                }
                else
                    std::cout << "Stack is empty";
            }
            else if (auxiliary_console_command_nuber == 2)
            {
                if (sp != NULL)
                {
                    MoveToSecondStack();
                }
                else {
                    std::cout << "Stack is empty";
                }
            }
            else  std::cout << "Error.Try command again";
        }
        else if (console_command_number == 4) {
            PushRand();
        }
        else if (console_command_number == 5) {
            std::cout << "State of auxiliary stack:\n";
            ShowStack(sp_auxiliary);
        }
        else if (console_command_number == 6) break;
        else std::cout << "Error.Try again.";
    }
}

int main()
{ 
    initStack();
    srand(static_cast<unsigned int> (time(0)));
    menu();
    return 0;
}