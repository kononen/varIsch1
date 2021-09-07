// практика_4_сем_коммивояжёр.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "cmath"

using namespace std;

void printmass (int **mass, int inf)
{
	for (int i = 1; i <= sizeof(mass)+1; i++)
	{
		cout << "\t " << i;
	}
	cout << "\n\n";

	for (int i = 0; i <= sizeof(mass); i++)
	{
		cout << i + 1 << "\t";
		for (int j = 0; j <= sizeof(mass); j++)
		{
			if (mass[i][j] > inf / 2) cout << "inf\t ";
			else cout << mass[i][j] << "\t ";
		}
		cout << endl;
	}
}

// Функция нахождения оценки нулевой клетки, k - столбец, n - строка
int value(int **mass, int i, int j)
{
	int minstr = numeric_limits<int>::max()*0.8;
	int minstb = minstr;
	for (int k = 0; k <= sizeof(mass); k++) // найдём минимум по строке
	{
		if (k != j)
		{
			if (minstr > mass[i][k])
			{
				minstr = mass[i][k];
			}
			else continue;
		}
		else continue;
	}

	for (int n = 0; n <= sizeof(mass); n++) // найдём минимум по столбцу
	{
		if (n != i)
		{
			if (minstb > mass[n][j])
			{
				minstb = mass[n][j];
			}
			else continue;
		}
		else continue;
	}
	return minstr + minstb;
}

//Функция нахождения максимальной оценки
int maxvalue(int **massp, int &maxvi, int &maxvj)
{
	int maxv = 0;
	
	for (int i = 0; i <= sizeof(massp); i++)
	{
		for (int j = 0; j <= sizeof(massp); j++)
			if (maxv < massp[i][j])
			{
				maxv = massp[i][j];
				maxvi = i;
				maxvj = j;
			}
	}

	return maxv;
}


int main()
{
	setlocale(LC_ALL, "rus");
	/*cout << INFINITY << endl;
	cout << numeric_limits<double>::has_infinity << endl;
	cout << numeric_limits<double>::infinity() << endl;
	int inf = static_cast<int>(numeric_limits<double>::infinity());
	cout << inf << endl;
	cout << numeric_limits<int>::infinity << endl;
	*///cout << typedef
	//int mod = \u221E;
	//cout << mod << endl;
	int inf = numeric_limits<int>::max();
	//cout << inf << endl;
	//cout << "Введите количество вершин" << endl;
	/*const*/ int numbercity = 5; // можно ли избавиться от этого действия?
	//cin >> numbercity;// >> endl;

	cout << "Вы ввели " << numbercity << endl << " ";

	//int mass[numbercity][numbercity]; 

	int **mass = new int*[numbercity];
	for (int i = 0; i < numbercity; i++)
	{
		mass[i] = new int[numbercity];
	}
	cout << " Размер массива равен " << sizeof(mass) << endl;
	/*for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			if (i != j)
				mass[i][j] = rand() % 9 + 1;
			else
				mass[i][j] = inf;
		}*/

	mass[0][0] = inf;	mass[0][1] = 20;	mass[0][2] = 18;	mass[0][3] = 12;	mass[0][4] = 8;
	mass[1][0] = 5;		mass[1][1] = inf;	mass[1][2] = 14;	mass[1][3] = 7;		mass[1][4] = 11;
	mass[2][0] = 12;	mass[2][1] = 18;	mass[2][2] = inf;	mass[2][3] = 6;		mass[2][4] = 11;
	mass[3][0] = 11;	mass[3][1] = 17;	mass[3][2] = 11;	mass[3][3] = inf;	mass[3][4] = 12;
	mass[4][0] = 5;		mass[4][1] = 5;		mass[4][2] = 5;		mass[4][3] = 5;		mass[4][4] = inf;

// выводим массив, присваивая его ячейкам случайные значения стоимости пути из пункта (номер строки) в пункт (номер столбца)
	cout << " Вид первоначальной матрицы " << endl;

	printmass(mass, inf);

	/*for (int i = 1; i <= numbercity; i++)
	{
		cout << "\t " << i;
	}
	cout << "\n\n";

	for (int i = 0; i < numbercity; i++)
	{
		cout << i + 1 << "\t";
		for (int j = 0; j < numbercity; j++)
		{
			if (mass[i][j] > inf/2) cout << "inf\t ";
			else cout << mass[i][j] << "\t ";
		}
		cout << endl;
	}*/

	

	//const int cnum = numbercity;

	//2. Нахождение минимумов по строкам 
	int *minstr = new int [numbercity];

	for (int i = 0; i < numbercity; i++)
	{
		minstr[i] = mass[i][0];
	}
	
	for (int i = 0; i < numbercity; i++)
	{
		cout << minstr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			if (minstr[i] > mass[i][j]) 
				minstr[i] = mass[i][j];
		}

	// Вывод столбца, ячейками которого являются минимальные числа в каждой из строк
	cout << " Вывод массива минимумов строк " << endl;
	for (int i = 0; i < numbercity; i++)
	{
		cout << minstr[i] << " ";
	}
	cout << endl;

	//3. Рекурсия строк
	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j<numbercity;j++)
		{
			mass[i][j] = mass[i][j] - minstr[i];
		}
	cout << " Вид матрицы МИНУС минимумы строк" << endl;
	printmass(mass,  inf);
	//for (int i = 1; i <= numbercity; i++)
	//{
	//	cout << "\t " << i;
	//}
	//cout << "\n\n";
	////Вывод изменённой матрицы
	//for (int i = 0; i < numbercity; i++)
	//{
	//	cout << i + 1 << "\t";
	//	for (int j = 0; j < numbercity; j++)
	//	{
	//		if (mass[i][j] > inf / 2) cout << "inf\t ";
	//		else cout << mass[i][j] << "\t ";
	//	}
	//	cout << endl;
	//}



	//4. Нахождение минимумов по столбцам 
	int *mincol = new int[numbercity];

	for (int j = 0; j < numbercity; j++)
	{
		mincol[j] = mass[0][j];
	}

	for (int j = 0; j < numbercity; j++)
	{
		cout << mincol[j] << " ";
	}
	cout << endl;

	for (int j = 0; j < numbercity; j++)
		for (int i = 0; i < numbercity; i++)
		{
			if (mincol[j] > mass[i][j]) mincol[j] = mass[i][j];
		}

	// Вывод столбца, ячейками которого являются минимальные числа в каждом из столбцов
	cout << " Вывод массива минимумов столбцов " << endl;
	for (int j = 0; j < numbercity; j++)
	{
		cout << mincol[j] << " ";
	}
	cout << endl;

	//5. Рекурсия столбцов
	for (int j = 0; j<numbercity; j++)
		for (int i = 0; i < numbercity; i++)
		{
			mass[i][j] = mass[i][j] - mincol[j];
		}
	//Вывод изменённой матрицы
	cout << " Вид матрицы МИНУС минимумы столбцов" << endl;
	printmass(mass, inf);
	/*for (int i = 1; i <= numbercity; i++)
	{
		cout << "\t " << i;
	}
	cout << "\n\n";

	for (int i = 0; i < numbercity; i++)
	{
		cout << i + 1 << "\t";
		for (int j = 0; j < numbercity; j++)
		{
			if (mass[i][j] > inf / 2) cout << "inf\t ";
			else cout << mass[i][j] << "\t ";
		}
		cout << endl;
	}*/

	//6. Нахождение локальной нижней границы.
	int *H = new int[numbercity];
	for (int i = 0; i < numbercity; i++)
	{
		H[i] = 0;
	}
	for (int i = 0; i < numbercity; i++)
	{
		H[0] += minstr[i] + mincol[i];
	}

	int mindl = H[0];

	//7. Вычисление оценок нулевых клеток.
	int **massminp = new int *[numbercity];
	for (int i = 0; i < numbercity; i++)
	{
		massminp[i] = new int[numbercity];
	}

	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			massminp[i][j] = 0;
		}
	
	int maxisminp = 0;	int maxi = 0;	int maxj = 0;

	cout << " Нахождение минимумов по строкам и столбцам для изменённой матрицы " << endl;


	// Нахождение минимумов по строкам и столбцам для изменённой матрицы
	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			if (minstr[i] > mass[i][j])	minstr[i] = mass[i][j];
		}

	for (int j = 0; j < numbercity; j++)
		for (int i = 0; i < numbercity; i++)
		{
			if (mincol[j] > mass[i][j])  mincol[j] = mass[i][j];
		}
	cout << " По строкам";
		for (int i = 0; i < numbercity; i++)
		{
			cout << minstr[i] << " ";
		}
	cout << "\n По столбцам";
		for (int j = 0; j < numbercity; j++)
		{
			cout << mincol[j] << " ";
		}
	cout << endl;
	// вычисление оценок нулевых клеток
	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			if (mass[i][j] == 0)
			{
				massminp[i][j] = value(mass, i, j);
			}
		}
	
	cout << " Оценка нулевой клетки строки 0 столбца 4 " << value(mass, 0, 4) << endl;

	cout << "Максимальная оценка нулевой клетки строки " << maxi << " столбца " << maxj << " = " << maxisminp << endl;
 

	// ОШИБКА В ТОМ, ЧТО МЫ УЧИТЫВАЕМ НУЛЕВУЮ КЛЕТКУ,
	// КОТОРУЮ В МИНИМУМЕ УЧИТЫВАТЬ НЕ ДОЛЖНЫ БЫЛИ
	//for (int i = 0; i < )
	int maxvi = 0;
	int maxvj = 0;

	cout << " Массив оценок: " << endl;
	printmass(massminp, inf);
	cout << " Максимальная оценка " << maxvalue(massminp, maxvi, maxvj);
	cout << " строки " << maxvi << " столбца " << maxvj << endl;

	cin.get();
	cin.get();

	delete[] minstr;
	delete[] mincol;
	delete[] mass;

    return 0;
}

