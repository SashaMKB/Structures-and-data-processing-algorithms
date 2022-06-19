#include <iostream>
using namespace std;


void show(int *a,int size) {
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
}

void PocketSortWithArray(int* a, int size) {//вспомогательный массив
	//элемент добавляется в массив к ячейку равную самому номеру элемента
	//при условии что ключи у элементов имеют значение от 1 до n, и их количество не больше n
	int *_a = (int*)malloc(size * sizeof(int));
	int changes = 0;
	for (int i = 0; i < size; i++)
	{
		_a[a[i]] = a[i];
		changes++;
	}
	cout << "\nSorted array:\n";
	show(_a, size);
	cout << "\nNumber of changes: " << changes ;
}

void PocketsortWithoutArray(int *a,int size) {
	/*берем 1 элемент,меняем местами с элементом равным ключу 1 элемента, после такой сортировки один из элементов окажется на своем месте*/
	int* m = (int*)malloc(size * sizeof(int));
	memcpy(m, a, size * sizeof(int));
	int compares = 0, changes = 0;
	for (int i = 0; i < size; i++)
	{
		compares++;
		while (m[i] != i) {
			compares++;
			int temp = m[i];
			m[i] = m[temp];
			m[temp] = temp;
			changes++;
		}
	}
	cout << "\nSorted list:\n";
	show(m, size);
	cout << "\nCompares: " << compares << "\nChanges: " << changes;
}
struct List
{
	int inf;
	List* next;
	List* left;
};
struct Array {
	List* el;
	List* last;
};

void PocketSort(int* a, int size)
{//Каждая ячейка массива соответствует одному конкретному значению
//ключа в диапазоне от 1 до n и хранит указатель на связанный список
//одноключевых элементов.
	int* m = (int*)malloc(size * sizeof(int));
	memcpy(m, a, size * sizeof(int));
	unsigned long changes = 0, compares = 0;
	Array* result = (Array*)malloc(size * (sizeof(Array)));
	for (int i = 0; i < size; i++)
	{
		result[i].el = NULL;
	}
	for (int i = 0; i < size; i++)
	{
		changes++;
		List* next = result[m[i]].el;
		result[m[i]].el = (List*)malloc(sizeof(List));
		result[m[i]].el->next = next;
		result[m[i]].el->inf = m[i];
	}
	for (int i = 0, j = 0; i < size; i++, compares++)
	{
		while (result[i].el != NULL)
		{
			compares++;
			changes++;
			m[j] = result[i].el->inf;
			j++;
			result[i].el = result[i].el->next;
		}
	}
	cout<<"\nSorted array:\n";
	show(m, size);
	cout << "\nNumber of compares:\n" << compares << "\nNumber of  changes:\n" << changes/3;
}

void RadixSort(int* a, int size)
{
	//обобщение карманное сортировки
	/*Смысл
	поразрядной сортировки заключается в том, что k раз повторяется карманная
	сортировка.На первом шаге все ключи группируются по младшей цифре
	(разряд единиц).Для этого в каждом ключе выделяется младшая цифра и
	элемент помещается в соответствующий список - карман для данной цифры.
	Потом все списки объединяются и создается новый массив, в котором
	элементы упорядочены по младшей цифре ключа.*/
	int* m = (int*)malloc(size * sizeof(int));
	memcpy(m, a, size * sizeof(int));
	unsigned long compares = 0, changes = 0;
	Array* result = (Array*)malloc(10 * (sizeof(Array)));
	for (int bitwise = 1; bitwise < 1000; bitwise = bitwise * 10)
	{
		for (int i = 0; i < 10; i++)
		{
			result[i].el = NULL;
			result[i].last = NULL;
		}
		for (int i = 0; i < size; i++)
		{
			changes++;
			int index = (m[i] % (10 * bitwise)) / bitwise;
			List* next = result[index].el;
			result[index].el = (List*)malloc(sizeof(List));
			result[index].el->next = next;
			result[index].el->left = NULL;
			result[index].el->inf = m[i];
			if (next != NULL)
			{
				next->left = result[index].el;
			}
			else
			{
				result[index].last = result[index].el;
			}
		}
		for (int i = 0, j = 0; i < 10; i++, compares++)
		{
			while (result[i].last != NULL && j < size)
			{
				compares++;
				changes++;
				m[j] = result[i].last->inf;
				result[i].last = result[i].last->left;
				j++;
			}
		}
	}
	cout << "\nSorted array:\n";
	show(m, size);
	cout << "\nNumber of compares:\n" << compares << "\nNumber of  changes:\n" << changes / 3;
}

int main()
{
	int size;
	cout << "\nEnter number of elements: ";
	cin >> size;
	int* a = (int*)malloc(size * sizeof(int));
	int select = 0;
	while (select != 5)
	{
		cout << "\nChoice command:\n1)Pocket sort with sub array\n2)Pocket sort\n3)Generic pocket sort\n4)Radix sort\n5)Exit\n";
		cin >> select;
		if (select == 1)
		{
			int i = 0;
			int sup;
			while (i < size)
			{
				sup = rand() % size;
				for (int j = i; j >= 0; j--)
				{
					if (a[j] == sup)
					{
						break;
					}
					else if (j == 0)
					{
						a[i] = sup;
						i++;
					}
				}
			}
			printf("\nArray:\n");
			show(a, size);
			PocketSortWithArray(a, size);
		}
		else if (select == 2) {
			int i = 0;
			int sup;
			while (i < size)
			{
				sup = rand() % size;
				for (int j = i; j >= 0; j--)
				{
					if (a[j] == sup)
					{
						break;
					}
					else if (j == 0)
					{
						a[i] = sup;
						i++;
					}
				}
			}
			printf("\nArray:\n");
			show(a, size);
			PocketsortWithoutArray(a, size);
		}
		else if (select == 3) {
			printf("\nArray:\n");
			for (int i = 0; i < size; i++)
			{
				a[i] = rand() % size;
				cout << a[i] << " ";
			}
			PocketSort(a, size);
		}
		else if (select == 4) {
			printf("\nArray:\n");
			for (int i = 0; i < size; i++)
			{
				a[i] = rand() % 900 +100;
				cout << a[i] << " ";
			}
			RadixSort(a, size);
		}
		else if (select == 5)
		{
			break;
		}
	}
}