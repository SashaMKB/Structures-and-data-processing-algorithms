#include<iostream>

using namespace std;

//ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДВОИЧНОЕ ДЕРЕВО
//Двоичное(каждая вершина имеет не более 2 потомков) дерево называется идеально сбалансированным (ИСД),
//если для каждой его вершины размеры левого и правого поддеревьев отличаются не более чем на 1.
/*1. Обход в прямом направлении:
-обработать корневую вершину текущего поддерева
-перейти к обработке левого поддерева таким же образом
-обработать правое поддерево таким же образом
2. Симметричный обход:
-рекурсивно обработать левое поддерево текущего поддерева
-обработать вершину текущего поддерева
-рекурсивно обработать правое поддерево
3. Обход в обратно-cимметричном направлении:
-рекурсивно обработать правое поддерево текущего поддерева
-вершину текущего поддерева
-затем рекурсивно обработать правое поддерево



      1)           /     (А)                              
                  /     /   \
                 /     /     \
                /    (В)      (С)
               |
                ----------------->
  
  
                    -----------
         2)        /     (А)    \                           
                  /     /   \    \
                 /     /     \    \
                /    (В)      (С)  \
                                    \->   
                
                     -----------
         3)        /     (А)    \
                  /     /   \    \
                 /     /     \    \
                /    (В)      (С)  \
            <- /                      

*/

int N; //количество вершин в дереве, глобальная переменная


//ОПИСАНИЕ СТРУКТУРЫ ДЕРЕВА TreePoint
struct Tp {
    int value; //строка-значение
    Tp* Left; //ссылочная переменная-указатель на левый элемент
    Tp* Right; //ссылочная переменная-указатель на правый элемент
} *pRoot; //ссылочная переменная для адреса корневой вершины.

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

//ОЧИСТКА ПАМЯТИ
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
        while (N <= 0) {
            cout << " How many vertexes you have? \n";
            cin >> N;
            if (N <= 0) cout << "\nError.Try Again";
            else {
                pRoot = AddNodes(pRoot, N);
                cout << "\nPerfectly balanced tree built";
            }
        }
        cout << "\n Line-by-line output in direct order:\n\n";
        Forward(pRoot, 0);

        cout << "\n Line-by-line output in symmetrical order:\n\n";
        Symmetric(pRoot, 0);

        cout << "\n  Line-by-line output in reverse-symmetrical order:\n\n";
        BackSymmetric(pRoot, 0);

        delTp(pRoot);
    }

    return 0;
}