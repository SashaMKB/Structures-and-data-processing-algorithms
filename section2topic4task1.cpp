//безконфликтная хештаблица для заданного набора ключей
#include <iostream>
using namespace std;
//хеш таблица - особый вид структуры данных
//где каждому ключу соответсвует индекс

//хеш функция-функция благодаря которой для входного ключа вычисляется индекс

int _hash(char* word)
{
	int sum = 0;
	for (int i = 0; i < strlen(word); i++)
	{
		sum += word[i];
	}
	sum = sum % 10 + 1;
	return sum;
}

int search(char* key, char** table)
{
	int index = _hash(key);
	if (strcmp(table[index], key) == 0)
	{
		return index;
	}
	else
	{
		return NULL;
	}
}
int main()
{
	char* k = (char*)malloc(256 * sizeof(char));
	char** table = (char**)malloc(10 * sizeof(char*));
	for (int i = 0; i < 10; i++)
	{
		table[i] = NULL;
	}
	int select = 0;
	while (select != 4)
	{
		cout<<"1)Add\n2)Show\n3)Find\n4)Exit\n";
		cin >> select;
		if (select == 1)
		{
			char* key = (char*)malloc(256 * sizeof(char));
			cout << "Enter key-word:\n";
			cin >> key;
			int index = _hash(key);
			if (table[index] == NULL)
			{
				table[index] = (char*)malloc(sizeof(key));
				table[index] = key;
				cout<<"Element is added\n";
			}
			else
			{
				if (table[index] != NULL)
				{
					cout<<"Element is already exsist\n";
				}
			}
		}
		else if (select == 2)
		{
			if (table != NULL)
			{
				cout<<"Hash-table:\n";
				for (int i = 0; i < 10; i++)
				{
					if (table[i] != NULL)
					{
						cout << "Index:" << i << " " << "Key:" << table[i] << "\n";
					}
				}
			}
			else
			{
				cout<<"Table is empty\n";
			}
		}
		else if (select == 3)
		{
			if (table != NULL)
			{
				cout<<"enter key for find:\n";
				cin >> k;
				int index = _hash(k);
				if (strcmp(table[index], k) == 0)
				{
					cout << "Index:" << index;
				}
				else
				{
					cout<<"Not found\n";
				}
			}
			else
			{
				cout << "Table is empty\n";
			}
		}
		else if (select == 4)
		{
			break;
		}
	}
}