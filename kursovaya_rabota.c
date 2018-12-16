#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define MAXLINE 1000

typedef struct sNode  // обьявление структуры узла односвзяного списка
{
	int id;
	char name[100];
	char ingr[100];
	char recept[100];
struct sNode *next;
}Node;

static Node *head;

//выделение памяти для корня списка
void init_head()
{
	head = (Node *)malloc(sizeof(Node));
	head->next = NULL;

};

// выделение памяти для последующих узлов списка.
// аргумент указатель на предыдущий элемент списка

Node *init_Node(Node *prev_Node)
{
	Node *nNode;

	nNode = (Node *)malloc(sizeof(Node));
	nNode->next = NULL;
	prev_Node->next = nNode;

	return nNode;
}
// заполняет поля узла pNode из строки, на которую указывает ptr
void give_data(Node *pNode, char buf[])
{
	char line[100];
	char *ptr_line;
	char *ptr_buf = buf;
	int i = 0, count = 0;

	ptr_line = line;
	

	//инициализация поля id
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	do
	{
		*ptr_line = *ptr_buf;
		ptr_buf++;
		ptr_line++;

	} while (*ptr_buf != '|');
	*ptr_line = '\0';
	pNode->id = atoi(line); // конвектируем в число 
	ptr_line = line;

	//инициализация поля name
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;

	do
	{
		pNode->name[i] = *ptr_buf;
		ptr_buf++;
		i++;

	} while (*ptr_buf != '|');
	pNode->name[i] = '\0';


	//инициализация поля ingr
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;
	i = 0;
	do
	{
		pNode->ingr[i] = *ptr_buf;
		ptr_buf++;
		i++;

	} while (*ptr_buf != '|');
	pNode->ingr[i] = '\0';
	

	//инициализация поля recept
	while (*ptr_buf == '.' || *ptr_buf == '|')
		ptr_buf++;
	i = 0;
	do
	{
		pNode->recept[i] = *ptr_buf;
		ptr_buf++;
		i++;

	} while (*ptr_buf != '|');
	pNode->recept[i] = '\0';

}


// Вывод базы данных на экран

void print_table(char *line_head_table)
{
	printf("%s",line_head_table);

	int len = 0;
	int id, count;
	Node *pNode = head;
	while (pNode != NULL)
	{
		printf("|");

		id = pNode->id;
		count = 0;
		do 
		{
			id = id / 10;
			count++;
		}while (id != 0);

		while (6 - count != 0)
		{
			printf(".");
			count++;
		}	
		printf("%d", pNode->id);
		printf("|");

		len = strlen(pNode->name);
		while (16 - len != 0)
		{
			printf(".");
			len++;
		}
		printf("%s", pNode->name);
		printf("|");

		len = 0;
		len = strlen(pNode->ingr);
		while (44 - len != 0)
		{
			printf(".");
			len++;
		}
		printf("%s", pNode->ingr);
		printf("|");

		len = strlen(pNode->recept);
		while (46 - len != 0)
		{
			printf(".");
			len++;
		}
		printf("%s", pNode->recept);
		printf("|");
		printf("\n");

		pNode = pNode->next;
	}
}

// Добавление рецепта 

Node * add_recept(int num_string_add)//n- номер строки, куда нужно вставить новый рецепт
{
	Node *nNode;
	Node *prevNode;
	Node *new_ptr;

	if (num_string_add == 1)
	{
		new_ptr = (Node *)malloc(sizeof(Node));
		new_ptr->next = head;
		head = new_ptr;
		return head;
	}

	nNode = head;
	prevNode = nNode;

	for (; num_string_add > 1; num_string_add--)
	{
		if (nNode->next == NULL)//следует необходимо добавить в конец списка
		{
			new_ptr = (Node *)malloc(sizeof(Node));
			nNode->next = new_ptr;
			new_ptr->next = NULL;
			return new_ptr;
		}

		prevNode = nNode;
		nNode = nNode->next;

	}

	new_ptr = (Node *)malloc(sizeof(Node));
	prevNode->next = new_ptr;
	new_ptr->next = nNode;

	return new_ptr;
}

// ЗАполнение полей нового узла

void init_new_node(Node *pNode)
{
	system("cls");
	
	//заполнеие узла списка
	getchar();
	printf("Введите ID нового реципла, в числовом формате: ");
	scanf("%d", &pNode->id);
	printf("\n");
	getchar();

	printf("Введите название рецепта: ");
	gets(pNode->name);
	printf("\n");

	printf("Введите ингридиенты: ");
	gets(pNode->ingr);
	printf("\n");

	printf("Введите способ приготовления: ");
	gets(pNode->recept);
	printf("\n");


}

// Удаление узла

void delete_node(Node *pNode)
{
	Node *nNode;
	Node *prevNode;

	//Если удаляемый узел в начале вписка
	if (pNode == head)
	{
		head = pNode->next;
		free(pNode);
	}
	else
	{//если удаляемый узел в конце списка
		if (pNode->next == NULL) // проверка на последний узел списка
		{
			nNode = head;
			prevNode = nNode;
			while (nNode->next != NULL)
			{
				prevNode = nNode;
				nNode = nNode->next;
			}
			free(nNode);
			prevNode->next = NULL;
		}
		else//если удаляемый узел не является началом или концом списка
		{
			nNode = head;
			prevNode = nNode;
			nNode = nNode->next;
			while (prevNode->next != pNode)
			{
				prevNode = nNode;
				nNode = nNode->next;
			}

			prevNode->next = nNode->next; // связываем предыдущий узел и следующий
			free(nNode); // очищаем память нынешнего узла
		}
	}
}

// Вывод 1 узла (рецепта)

void print_node(Node *pNode)
{
	int id = 0, count = 0, len =0;

	printf("|");

	id = pNode->id;
	count = 0;
	do
	{
		id = id / 10;
		count++;
	} while (id != 0);

	while (6 - count != 0)
	{
		printf(".");
		count++;
	}
	printf("%d", pNode->id);
	printf("|");

	len = strlen(pNode->name);
	while (16 - len != 0)
	{
		printf(".");
		len++;
	}
	printf("%s", pNode->name);
	printf("|");

	len = 0;
	len = strlen(pNode->ingr);
	while (44 - len != 0)
	{
		printf(".");
		len++;
	}
	printf("%s", pNode->ingr);
	printf("|");

	len = strlen(pNode->recept);
	while (46 - len != 0)
	{
		printf(".");
		len++;
	}
	printf("%s", pNode->recept);
	printf("|");
	printf("\n");
	
}

// освобождение памяти 

void struct_free()
{
	Node *pNode = NULL;
	Node *nNode = head;

	while ((pNode = nNode) != NULL)
	{
		nNode = nNode->next;
		free(pNode);
	}

}

// поиск по неполному совпадению

int find_ingr() 
{
	Node *pNode;
	int choice_num = 0; 
	char line_ingr[100][100];
	char line_mas[100][100];
	int i = 0, j = 0, k = 0, flag=0;
	int count_ingr = 0, count_mas = 0;

	printf("Введите [1], если хотите добавить ингридиент в список для поиска, иначе[0]\n");
	scanf("%d", &choice_num);
	while (choice_num == 1)
	{
		getchar();
		gets(*(line_mas + i));
		count_mas++;
		i++;
		printf("Введите [1], если хотите добавить ингридиент в список для поиска, иначе[0]\n");
		scanf("%d", &choice_num);
		

	}
	

	printf("По данному запросу найдены рецепты:\n");
	pNode = head;
	while (pNode != NULL)
	{
		//получение из pNode->ingr всех ингридиентов
		j = i = k = 0;

		do // обрабатываем строку ингридиентов данного узла и записываем ингридиенты по отдельности
			// в массив line_ingr
		{

			do
			{
				*(*(line_ingr+i)+j) = *(pNode->ingr+k);
				j++;
				k++;
				char c = *(pNode->ingr + k);
				if (*(pNode->ingr + k) == ' ' || *(pNode->ingr + k) == ',' || *(pNode->ingr + k) == '\0') break; // kostyl'
			} while ( *(pNode->ingr + k) != ' ' || *(pNode->ingr + k) != ',' || *(pNode->ingr + k) !='\0'); // тут прикол 
			*(*(line_ingr + i) + j) = '\0';
			i++;
			count_ingr++;
			j = 0;
			while ((*(pNode->ingr + k) == ' ' || *(pNode->ingr + k) == ',' ) && *(pNode->ingr + k) != '\0')
				k++;

		} while (*(pNode->ingr + k) != '\0');

		flag = 0;
		//считаем сколько должно быть совпадений


		for (i = 0; i<count_ingr; i++)
		{
			for (j = 0; j<count_mas; j++)
			{
				if (strcmp(*(line_ingr + i), *(line_mas + j)) == 0)
				{
					flag++;
				}

			}
		}

		if (flag >= count_mas)
		{
			print_node(pNode);
		}
		pNode = pNode->next;

	}
	system("pause");
}

int main()
{
	FILE *fptr = NULL;
	char *ptr = NULL;
	char line[MAXLINE];
	char head_table[MAXLINE];
	Node *pNode = NULL;
	int choice, choice_num;
	int num_delete;
	int find, flag;
	char **ptr_mas;
	int count;
	Node **ptr_mn;

	system("chcp 1251");

	fopen_s(&fptr, "Kniga.txt", "rt");

	ptr = fgets(head_table, MAXLINE, fptr);

	if ((ptr = fgets(line, MAXLINE, fptr)) != NULL)
	{
		init_head();
		pNode = head;
		give_data(pNode, ptr);
	}



	while ((ptr = fgets(line, MAXLINE, fptr)) != NULL)
	{
		pNode = init_Node(pNode);
		give_data(pNode, ptr);
	}


	//завершение чтения из файла и заполнения списка
	do
	{

		system("cls");

		printf("[0] Выйти из программы.\n[1] Добавить рецепт.\n[2] Удалить рецепт.\n[3] Поиск рецепта по неполному совпадение.\n[4] Вывод рецептов в алфавитном порядке по названию.\n[5] Вывести все рецепты.\n");
		scanf("%d", &choice);


		switch (choice)
		{
		case 1:
			system("cls");
			print_table(head_table);
			printf("\n");

			printf("Введите номер строки, в которую нужно впихнуть новый рецепт: ");
			scanf("%d", &choice_num);

			pNode = add_recept(choice_num);

			init_new_node(pNode);
			system("pause");

			break;

		case 2:
			system("cls");
			print_table(head_table);
			printf("\n");


			printf("Введите ID рецепта, который хотите удалить: ");
			scanf("%d", &num_delete);
			printf("\n");

			pNode = head;
			while (pNode->id != num_delete)
			{
				pNode = pNode->next;
			}

			delete_node(pNode);

			system("cls");
			print_table(head_table);
			system("pause");

			break;

		case 3:
			system("cls");
			printf("[0] Поиск по названию.\n[1] Поиск по ингредиентам\n ");
			scanf("%d", &find);

			if (find)//Поиск по ингредиентам
			{
				flag = find_ingr();
				
			}
			else//Поиск по названию
			{
				printf("Введите название рецепта: \n");
				getchar();
				gets(line);
				printf("По данному запросу найдены рецепты:\n");
				pNode = head;
				printf("%s", head_table);
				flag = 0;
				while (pNode != NULL)
				{
					if (strcmp(pNode->name, line) == 0)
					{
						print_node(pNode);
						flag = 1;
					}
					pNode = pNode->next;
				}
				system("pause");
				if (flag == 0)
					printf("Таких рецептов нет, иди готовь без кулинарной книги!");
			}

			break;

		case 4:
			count = 0;
			system("cls");
			pNode = head;
			ptr_mn = (Node **)malloc(sizeof(Node*));
			while (pNode != NULL)
			{
				*(ptr_mn + count) = pNode;
				count++;
				ptr_mn = (Node **)realloc(ptr_mn, (count + 1) * sizeof(Node *));
				pNode = pNode->next;
			}
			//cортировка массива от параметра name


			Node *swap;
			// Сортировка пузырьком по name
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < count - 1 - i; j++)
				{
					if (strcmp(ptr_mn[j]->name, ptr_mn[j + 1]->name) > 0)
					{
						swap = ptr_mn[j];
						ptr_mn[j] = ptr_mn[j + 1];
						ptr_mn[j + 1] = swap;
					}
				}
			}

			//Вывод всех узлов отсортированного массива в алфавитном порядке

			for (int i = 0; i < count; i++)
			{
				print_node(*(ptr_mn + i));

			}
			system("pause");

			free(ptr_mn);

			break;

		case 5:
			system("cls");
			print_table(head_table);
			system("pause");
		};


	} while (choice);
	fclose(fptr);

	//перезапись в файл
	fopen_s(&fptr, "Kniga.txt", "wt");
	if (fptr == NULL)
		printf("Ошибка перезаписи в файл, книга остаётся неизменной.");
	fputs( head_table , fptr);

	int len = 0;
	int id;
	pNode = head;
	while (pNode != NULL)
	{
		fputc('|', fptr);

		id = pNode->id;
		count = 0;
		do
		{
			id = id / 10;
			count++;
		} while (id != 0);

		while (6 - count != 0)
		{
			fputc('.', fptr);
			count++;
		}
		fprintf(fptr, "%d", pNode->id);
		fputc('|', fptr);

		len = strlen(pNode->name);
		while (16 - len != 0)
		{
			fputc('.', fptr);
			len++;
		}
		fputs( pNode->name,fptr);
		fputc('|', fptr);

		len = 0;
		len = strlen(pNode->ingr);
		while (44 - len != 0)
		{
			fputc('.', fptr);
			len++;
		}
		fputs( pNode->ingr, fptr);
		fputc('|', fptr);

		len = strlen(pNode->recept);
		while (46 - len != 0)
		{
			fputc('.', fptr);
			len++;
		}
		fputs( pNode->recept, fptr);
		fputc('|', fptr);
		fputc('\n', fptr);

		pNode = pNode->next;
	}
	struct_free();
	
	return 0;
}
