//внутреннее хеширование
#include <iostream>

using namespace std;
//внутреннее хеширование
//если два ключа претендуют на одно место тоББ то он помещается в след ячейку
//хеш - таблица - массив, заполненный элементами исходного набора в порядке, определяемом хеш - функцией.

int _hash(char* word, int m)
{
	int sum = 0;
	for (int i = 0; i < strlen(word); i++)
	{
		sum += (int)word[i];
	}
	return sum % m + 1;
}

int main()
{
	int select = 0;
	int n, s;
	char* key = (char*)malloc(256 * sizeof(char));
	cout<<"Enter size of table: ";
	cin >> n;
	char** table = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		table[i] = NULL;
	}
	while (select != 4)
	{
		cout<<"1)Add key\n2)Find\n3)Show\n4)Exit\n";
		cin >> select;
		if (select == 1)
		{
			char* key = (char*)malloc(256 * sizeof(char));
			cout<<"Enter key: ";
			cin >> key;
			int index = _hash(key, n);
			if (table[index] == NULL)
			{
				table[index] = (char*)malloc(sizeof(key));
				table[index] = key;
				cout << "Element add\n";
			}
			else
				if (!strcmp(table[index], key))
				{
					cout<<"Element is already exist\n";
					continue;
				}
				else
				{
					bool flag = false;
					for (int i = 0; i < n; i++)
					{
						int j = (_hash(key, n) + i) % n;
						if (table[j] == NULL)
						{
							table[j] = (char*)malloc(sizeof(key));
							table[j] = key;
							cout<<"Element add\n";
							flag = true;
							break;
						}
						else if (table[j] != NULL)
						{
							if (!strcmp(table[j], key))
							{
								cout << "Element is already exist\n";
								flag = true;
								break;
							}
						}
					}
					if (!flag)
					{
						cout<<"Table is full,cant add\n";
					}
				}
		}
		else if (select == 2)
		{
			int count = 0;
			char* key = (char*)malloc(256 * sizeof(char));
			cout<<"Enter key: ";
			cin >> key;
			int index = _hash(key, n);
			if (table[index] != NULL)
			{
				if (!strcmp(table[index], key))
				{
					cout << "Index: " << index;
					cout<<"Number of compares: 1\n";
					continue;
				}
			}
			bool flag = false;
			for (int i = 0; i < n; i++)
			{
				int j = ((_hash(key, n) + i) % n);
				if (table[j] == NULL)
				{
					continue;
				}
				count++;
				if (!strcmp(table[j], key))
				{
					cout << "Index: " << j;
					cout << "Number of compares: " << count << "\n";
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				cout << "Element is not found";
			}
		}
		else if (select == 3)
		{
			for (int i = 0; i < n; i++)
			{
				if (table[i] != NULL)
				{
					cout<<"Index: "<<i<<" Key:"<< table[i]<<"\n";
				}
			}
		}
		else if (select == 4)
		{
			break;
		}
	}
}