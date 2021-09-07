// ��������_4_���_����������.cpp: ���������� ����� ����� ��� ����������� ����������.
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

// ������� ���������� ������ ������� ������, k - �������, n - ������
int value(int **mass, int i, int j)
{
	int minstr = numeric_limits<int>::max()*0.8;
	int minstb = minstr;
	for (int k = 0; k <= sizeof(mass); k++) // ����� ������� �� ������
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

	for (int n = 0; n <= sizeof(mass); n++) // ����� ������� �� �������
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

//������� ���������� ������������ ������
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
	//cout << "������� ���������� ������" << endl;
	/*const*/ int numbercity = 5; // ����� �� ���������� �� ����� ��������?
	//cin >> numbercity;// >> endl;

	cout << "�� ����� " << numbercity << endl << " ";

	//int mass[numbercity][numbercity]; 

	int **mass = new int*[numbercity];
	for (int i = 0; i < numbercity; i++)
	{
		mass[i] = new int[numbercity];
	}
	cout << " ������ ������� ����� " << sizeof(mass) << endl;
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

// ������� ������, ���������� ��� ������� ��������� �������� ��������� ���� �� ������ (����� ������) � ����� (����� �������)
	cout << " ��� �������������� ������� " << endl;

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

	//2. ���������� ��������� �� ������� 
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

	// ����� �������, �������� �������� �������� ����������� ����� � ������ �� �����
	cout << " ����� ������� ��������� ����� " << endl;
	for (int i = 0; i < numbercity; i++)
	{
		cout << minstr[i] << " ";
	}
	cout << endl;

	//3. �������� �����
	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j<numbercity;j++)
		{
			mass[i][j] = mass[i][j] - minstr[i];
		}
	cout << " ��� ������� ����� �������� �����" << endl;
	printmass(mass,  inf);
	//for (int i = 1; i <= numbercity; i++)
	//{
	//	cout << "\t " << i;
	//}
	//cout << "\n\n";
	////����� ��������� �������
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



	//4. ���������� ��������� �� �������� 
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

	// ����� �������, �������� �������� �������� ����������� ����� � ������ �� ��������
	cout << " ����� ������� ��������� �������� " << endl;
	for (int j = 0; j < numbercity; j++)
	{
		cout << mincol[j] << " ";
	}
	cout << endl;

	//5. �������� ��������
	for (int j = 0; j<numbercity; j++)
		for (int i = 0; i < numbercity; i++)
		{
			mass[i][j] = mass[i][j] - mincol[j];
		}
	//����� ��������� �������
	cout << " ��� ������� ����� �������� ��������" << endl;
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

	//6. ���������� ��������� ������ �������.
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

	//7. ���������� ������ ������� ������.
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

	cout << " ���������� ��������� �� ������� � �������� ��� ��������� ������� " << endl;


	// ���������� ��������� �� ������� � �������� ��� ��������� �������
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
	cout << " �� �������";
		for (int i = 0; i < numbercity; i++)
		{
			cout << minstr[i] << " ";
		}
	cout << "\n �� ��������";
		for (int j = 0; j < numbercity; j++)
		{
			cout << mincol[j] << " ";
		}
	cout << endl;
	// ���������� ������ ������� ������
	for (int i = 0; i < numbercity; i++)
		for (int j = 0; j < numbercity; j++)
		{
			if (mass[i][j] == 0)
			{
				massminp[i][j] = value(mass, i, j);
			}
		}
	
	cout << " ������ ������� ������ ������ 0 ������� 4 " << value(mass, 0, 4) << endl;

	cout << "������������ ������ ������� ������ ������ " << maxi << " ������� " << maxj << " = " << maxisminp << endl;
 

	// ������ � ���, ��� �� ��������� ������� ������,
	// ������� � �������� ��������� �� ������ ����
	//for (int i = 0; i < )
	int maxvi = 0;
	int maxvj = 0;

	cout << " ������ ������: " << endl;
	printmass(massminp, inf);
	cout << " ������������ ������ " << maxvalue(massminp, maxvi, maxvj);
	cout << " ������ " << maxvi << " ������� " << maxvj << endl;

	cin.get();
	cin.get();

	delete[] minstr;
	delete[] mincol;
	delete[] mass;

    return 0;
}

