#include <stdio.h> 
#include <conio.h> 
#include <locale.h>
#include <iostream>
using namespace std;

void main()

{
	setlocale(LC_ALL, "ru");
	int n;

	// Исходное число

	int r;

	// Остаток от деления числа на основаниесист.счисл.

	// Представление числа в заданной сист.

	char st[5];



	int i;



	/*printf("\nПреобразование десятичного числа" ); 
	printf("в шестнадцатеричное\n"); 
	printf("Введите целое число ->"); 
	scanf_s(" % d", &n);*/

		//делим исходное число на 16 до тех пор,

		//пока остаток от деления больше 16

	/*printf("\nДесятичному числу %d", n); 
	printf(" соответствует шестнадцатеричное "); 
	printf("here1");*/

	cout << "Введите число -> ";
	cin >> n;

	for (int i = 0; i < 5; i++)
		st[i] = '0';

	//printf("here1");

	i = 4; 
	do {

		r = n % 16; // очередная цифра

		n = n / 16; // целая часть рез-та деления 

		if (r < 10)
			st[i--] = r + 48; // (int)'0'==48, (int)'1'==49  
		else 
			st[i--] = r + 55; // (int)'A'==65, (int)'B'==66 
	} while ((n > 0) && (i >= 0));

	// удалим начальные пробелы 
	//i++;

	int j;
	for (j = 0; j < 5 && i < 5; i++ && j++)
		st[j] = st[i];

	/*while (st[i++]) {
		j++;
		st[j] = st[i];
	}*/

	j++;
	if (j < 5) {
		st[j] = '0';
		j++;
	}
	cout << "Ваше число -> ";
	for (int i = 0; i < 5; i++)
		cout << st[i];

	/*printf("%s\n", st);

	printf("\nДля завершения нажмите <Enter>");*/
	//_getch();

}