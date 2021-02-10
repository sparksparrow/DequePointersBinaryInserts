#include <iostream>
#include <windows.h>
#include "dequePointers.h"
#include <time.h>


using namespace std;

void BIsort(Deque exp);

extern long long int nOperations;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	Deque example;

	int countSort = 0;

	int choice = 1;
	cout << "0 - Выход\n1 - Добавить в конец\n2 - Удалить в конце\n3 - Добавить в начало\n4 - Удалить в начале\n5 - Показать дек\n6 - Проверка на отсутствие\n7 - Сортировка бинарными вставками\n8 - Очистка дека\n9 - Показать первый элемент\n10 - Показать последний элемент\n11 - Заполнить дек случаными числами" << endl;;
	while (choice != 0)
	{
		
		int i;
		cin >> choice;
		switch (choice) {
		case 1:			
			cout << "Добавить: ";
			cin >> i;
			example.pushBack(i);
			cout << endl;
			break;
		case 2:			
			example.popBack();
			cout << endl;
			break;
		case 3:
			cout << "Добавить: ";
			cin >> i;
			example.pushFront(i);
			cout << endl;
			break;
		case 4:
			example.popFront();
			cout << endl;
			break;
		case 5:
			cout << "Дек - ";
			example.show();
			cout << endl;
			break;
		case 6:
			cout<< "1 - пусто, 0 - есть элементы: " << example.isEmpty() << endl;
			break;
		case 7:
			unsigned int tS, tF;
			tS = GetTickCount();
			BIsort(example);
			tF = GetTickCount();
			countSort++;
			cout << "Дек отсортирован!" << endl;
			cout << "Сортировка: №"<< countSort <<". Количество элементов: "<<example.getSize()<<". Время сортировки: "<<tF-tS<< "ms."<<" Количество операций: "<<::nOperations<<"."<< endl;
			nOperations = 0;
			break;
		case 8:
			example.clear();
			cout << "Дек очищен!"<< endl;
			break;
		case 9:
			cout << "Первый элемент "<< example.head() << endl;
			break;
		case 10:
			cout << "Последний элемент "<< example.tail() << endl;
			break;
		case 11:
			cout<<"Количество элементов:";
			cin >> i;
			example.fill(i);
			cout << endl;
			break;		
		}
	}

	return;
}

void BIsort(Deque exp)                           //1+64n+104n²+n*log₂(n)*(18+13n)
{	
	nOperations++;
	for (int i = 2; i < exp.getSize(); i++)		 //1+n(19+52n+10+26n+1+2+log₂(n)*(17+13n)+22+52n+10+26n)	         
		if (exp[i - 1] > exp[i])				 //1+1+9+26n+9+26n		    //Сравниваем новое значение с последним значение сортированного массива
		{
			nOperations++;

			int current = exp[i];				 //1+9+26n				    //Берем новое значения для сортировки
			int left = 0;						 //1		    //Левая сторона проверяемого массива
			int right = i - 1;	
			nOperations += 4;                    //2			//Правая сторона проверяемого массива

			do
			{
				int mid = (left + right) / 2;	 //3			//Центр проверяемого массива
				nOperations += 3;

				nOperations++;
				if (exp[mid] < current)			 //1+9+13n		    //Сравниваем новое значение с центральным значением массива
					left = mid + 1;				 //2		    //Отрезаем от массива левую часть
				else
					right = mid - 1;			 //2			//Отрезаем от массива правую часть
				nOperations+=2;

				nOperations++;
			} while (left <= right);             //(1+3+1+9+13n+2+2)*log₂(n)

			nOperations+=2;
			for (int j = i - 1; j >= left; j--)	 //2+9+26n+9+26n+1+1			//Сдвигаем все элементы вправо
			{
				exp[j + 1] = exp[j];             //9+26n+9+26n+1+1
				nOperations++;
			}

			exp[left] = current;				 //9+26n+1	 	    //Присваевываем нужное место новому элементу
			nOperations++;
		}
}