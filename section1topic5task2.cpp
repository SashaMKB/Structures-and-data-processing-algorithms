//ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДВОИЧНОЕ ДЕРЕВО С НЕРЕКУРСИВНЫМ ВАРИАНТОМ СИММЕТРИЧНОГО ОБХОДА (ВСПОМОГАТЕЛЬНЫЙ СТЕК)
//

#include <iostream>
#include <cstdlib>

using namespace std;

int N; //количество вершин в дереве, глобальная переменная

//ОПИСАНИЕ СТРУКТУРЫ ДЕРЕВА TreePoint
struct Tp {
    int value; //строка-значение
    Tp* Left; //ссылочная переменная-указатель на левый элемент
    Tp* Right; //ссылочная переменная-указатель на правый элемент
} *pRoot; //ссылочная переменная для адреса корневой вершины.

struct Stack {
    int level; //"уровень" вершины
    Tp* Point; //указатели на пройденную вершину дерева
    Stack* next; //указатели на следующий элемент стека
} *sp; // sp - указатель вершины главного стека

//инициализация, создание пустого стека
inline void initStack(Tp* pRoot) {
    sp = new Stack;
    sp->Point = pRoot;
    sp->level = -1;
    sp->next = NULL;
}

// Проверка пустоты стека
bool isEmpty() {
    if (sp->level < 0) return 1;
    else return 0;
}

Tp* AddNodes(Tp* pCurrent, int aN) { //ДОБАВЛЕНИЕ ВЕРШИН (ПОСТРОЕНИЕ ИСД)
    Tp* pTemp;
    int Nl, Nr;
    if (aN == 0)  // если нет вершин для размещения
        return NULL; // формируем пустую ссылку
    else {
        Nl = aN / 2; //число вершин слева
        Nr = aN - Nl - 1; //число вершин справа
        pTemp = new Tp; //создаем корень поддерева, выделяем память
        pTemp->value = rand() % 100; //заносим в информационную часть случайное целое число в интервале от 0 до 99
        pTemp->Left = AddNodes(pTemp->Left, Nl); // уходим на создание левого поддерева
        pTemp->Right = AddNodes(pTemp->Right, Nr);
        pCurrent = pTemp;
        //        cout << "\n Вершина создана\n";
        return pTemp; //возвращаем адрес созданного корня
    }
}

void Forward(Tp* pCurrent, int level) { //ПОСТРОЧНЫЙ ВЫВОД В ПРЯМОМ НАПРАВЛЕНИИ
    if (pCurrent != NULL) {
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        Forward(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
        Forward(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
    }

}

void Nonrecursive() { //НЕРЕКУРСИВНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
    initStack(pRoot);
    Tp* pCurrentTree = pRoot; //начинаем с корневой вершины дерева
    bool Stop = false;
    int level = 0;

    while (!Stop) {
        while (pCurrentTree != NULL) {

            Stack* item = new Stack; //занести pCurrent в стек
            item->level = level;
            item->Point = pCurrentTree;
            item->next = sp;
            sp = item;
            pCurrentTree = sp->Point;
            pCurrentTree = pCurrentTree->Left;
            level++;
        }
        if (isEmpty()) //если стек пуст
            Stop = true; //завершить основной цикл
        else { //обработка и вывод вершины
            level = sp->level;
            pCurrentTree = sp->Point;
            string str = ""; //обработка корневой вершины pCurrent
            for (int i = 0; i < level; i++)
                str += "     ";
            cout << " " << str << (pCurrentTree->value) << "\n";
            Stack* current = sp;
            sp = sp->next;
            delete current;
            pCurrentTree = pCurrentTree->Right;
            level++;
        }
    }
}

void Symmetric(Tp* pCurrent, int level) { //ПОСТРОЧНЫЙ ВЫВОД В СИММЕТРИЧНОМ НАПРАВЛЕНИИ
    if (pCurrent != NULL) {
        Symmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        Symmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
    }
}

void BackSymmetric(Tp* pCurrent, int level) {//ПОСТРОЧНЫЙ ВЫВОД В ОБРАТНО-СИММЕТРИЧНОМ НАПРАВЛЕНИИ
    if (pCurrent != NULL) {
        BackSymmetric(pCurrent->Right, level + 1); //обработка  всех правых поддеревьев
        string str; //обработка корневой вершины pCurrent
        for (int i = 0; i < level; i++)
            str += "     ";
        cout << " " << str << pCurrent->value << "\n";
        BackSymmetric(pCurrent->Left, level + 1); //обработка  всех левых поддеревьев
    }
}

//ОЧИСТКА ПАМЯТИ (УДАЛЕНИЕ ВЕРШИН ДЕРЕВА)
void delTp(Tp* pCurrent) {
    if (pCurrent != NULL) {
        delTp(pCurrent->Left); // сначала удалять все элементы с левого конца
        delTp(pCurrent->Right); // потом удалять все элементы с правого конца
        delete pCurrent; // в конце удалить сам элемент-корень
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); //инициализация генератора псевдослучайных чисел rand
    while (true) {
        N = -1;
        while (N <= 0) { //ПОСТРОЕНИЕ ИСД С ЗАДАННЫМ ЧИСЛОМ ВЕРШИН
            cout << " How many vertexes you have? ";
            cin >> N;
            if (N <= 0) cout << "Error.Try again\n";
            else {
                pRoot = AddNodes(pRoot, N);
                cout << " Perfectly balanced tree built\n";
            }
        }
        //cout << "\nLine-by-line output in direct order:\n\n";
        //Forward(pRoot, 0);
        cout << "\nLine-by-line output in syymetric order::\n\n";
        Symmetric(pRoot, 0);
        cout << "\n Non-recursive symmetric traversal:\n\n";
        Nonrecursive();
        delTp(pRoot);
    }
    return 0;
}

