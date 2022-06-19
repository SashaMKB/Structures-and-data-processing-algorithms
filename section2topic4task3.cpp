#include <iostream>
//открытое хеширование за счет вспомогательного линейного списка. привязка к одному инексу
using namespace std;

struct ListItem
{
	char* key;
	ListItem* left;
	ListItem* right;
};
struct List
{
	ListItem* head;
	ListItem* last;
};

void addNewKey(List** list, char* key)
{
	if (*list == NULL)
	{
		*list = (List*)malloc(sizeof(List));
		(*list)->last = (ListItem*)malloc(sizeof(ListItem));
		(*list)->last->key = key;
		(*list)->last->left = NULL;
		(*list)->last->right = NULL;
		(*list)->head = (*list)->last;
	}
	else
	{
		ListItem* oldTail = (*list)->last;
		(*list)->last = (ListItem*)malloc(sizeof(ListItem));
		(*list)->last->key = key;
		(*list)->last->left = NULL;
		(*list)->last->right = oldTail;
		oldTail->left = (*list)->last;
	}
}

int Search(List* list, char* key, int index)
{
	if (list != NULL)
	{
		int count = 0;
		ListItem* cur = list->head;
		while (cur != NULL)
		{
			count++;
			if (!strcmp(cur->key, key))
			{
				cout << "Index: " << index << " Key:" << cur->key << " Compares:" << count;
				return 1;
			}
			else
			{
				cur = cur->left;
			}
		}
	}
	return 0;
}

void Show(List* list, int index)
{
	if (list != NULL)
	{
		ListItem* cur = list->head;
		while (cur != NULL)
		{
			cout << "Index: " << index << " Key:" << cur->key<<"\n";
			cur = cur->left;
		}
	}
}

int Hash(char* word, int m)
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
	int size, select = 0;
	cout<<"Enter size of table:\n";
	cin>>size;
	List** table = (List**)malloc(size * sizeof(List*));
	for (int i = 0; i < size; i++)
	{
		table[i] = NULL;
	}
	while (select != 5)
	{
		cout<<"\n1)Add key\n2)Delete key\n3)Find\n4)Show\n5)Exit\n";
		cin>>select;
		if (select == 1)
		{
			char* key = (char*)malloc(256 * sizeof(char));
			cout<<"Enter key\n";
			cin>>key;
			int index = Hash(key, size);
			if (Search(table[index], key, index) != 0)
			{
				continue;
			}
			addNewKey(&table[index], key);
		}
		else if (select == 2)
		{
			char* key = (char*)malloc(256 * sizeof(char));
			cout<<"Enter key:\n";
			cin>>key;
			int index = Hash(key, size);
			if (table[index] != NULL)
			{
				ListItem* cur = table[index]->head;
				if (table[index]->head == table[index]->last)
				{
					delete table[index];
					table[index] = NULL;
					continue;
				}
				if (!strcmp(table[index]->head->key, key))
				{
					ListItem* deleted = table[index]->head;
					table[index]->head = deleted->left;
					deleted->left->right = NULL;
					delete deleted;
					continue;
				}
				if (!strcmp(table[index]->last->key, key))
				{
					ListItem* deleted = table[index]->last;
					table[index]->last = deleted->right;
					deleted->right->left = NULL;
					delete deleted;
					continue;
				}
				while (cur->left != NULL)
				{
					if (!strcmp(cur->key, key))
					{
						ListItem* deleted = cur;
						cur->left->right = cur->right;
						if (cur->right != NULL)
						{
							cur->right->left = cur->left;
						}
						deleted->left = NULL;
						deleted->right = NULL;
						delete deleted;
						break;
					}
					cur = cur->left;
				}
			}
		}
		else if (select == 3)
		{
			char* key = (char*)malloc(256 * sizeof(char));
			cout<<"Enter key\n";
			cin>>key;
			int index = Hash(key, size);
			if (Search(table[index], key, index) == 0)
			{
				cout<<"Element is not exist\n";
			}
		}
		else if (select == 4)
		{
			for (int i = 0; i < size; i++)
			{
				Show(table[i], i);
			}
		}
		else if (select == 5)
		{
			break;
		}
	}
}