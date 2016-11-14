//#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

void initilize_CNF(int num_var, int num_sum) {
	cout << "P CNF " << num_var << ' ' << num_sum << endl;//writes to file
	cout << "/---------------------------------------------\n";
}

void exct_one_or(int **, int, int);

//exactly one or for two dimensions array
void exct_one_or(int ** z, int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int k = 0; k < y; k++)
		{
			for (int j = k; j < (y - 1); j++) //negating every two variables
			{
				cout << -z[i][k] << " " << -z[i][j + 1] << " 0\n";//writes to file
			}
		}
		for (int j = 0; j < y; j++) //or all variables
			cout << z[i][j] << " ";
		cout << " 0\n";
	}
}



void main()
{
	int L, n, p, q, var_no = 1;
	ofstream output;

	cout << "enter the length of DS: ";
	cin >> L;//given as argh[]
	cout << "enter number of inputs: ";
	cin >> p;//read from file
	cout << "enter number of outputs: ";
	cin >> q;//read from file
	cout << "enter number of states: ";
	cin >> n;// read from file

	cout << "/---------------------------------------------\n";

	initilize_CNF(5, 7);

	//allocate memory for p*L input variables
	int ** xl = new int*[L];
	for (int i = 0; i < L; i++)
	{
		xl[i] = new int[p];
		for (int j = 0; j < p; j++)
		{//must read variables from file
			xl[i][j] = var_no++;   //xl={1,2,3,..,p*L}
		}
	}

	//allocate memory for n*L*n state variables
	int *** s = new int**[n];
	for (int i = 0; i < n; i++)
	{
		s[i] = new int*[L];
		for (int j = 0; j < L; j++)
		{
			s[i][j] = new int[n];
			for (int k = 0; k < n; k++)
				s[i][j][k] = var_no++;
		}
	}

	//allocate memory for n*L*q output variables
	int *** y = new int**[n];
	for (int i = 0; i < n; i++)
	{
		y[i] = new int*[L];
		for (int j = 0; j < L; j++)
		{
			y[i][j] = new int[q];
			for (int k = 0; k < q; k++)
				y[i][j][k] = var_no++;
		}
	}

	//generating clauses for Q1
	exct_one_or(xl, L, p);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q2
	for (int i = 0; i < n; i++)
		cout << s[i][0][i] << " 0\n";

	cout << "/---------------------------------------------\n";
	//generating clauses for Q3
	for (int i = 0; i < n; i++)
		exct_one_or(s[i], L, n);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q5
	for (int i = 0; i < n; i++)
		exct_one_or(y[i], L, q);

	cout << "/---------------------------------------------\n";
	//checking s, or y
	//for (i = 0; i < n; i++)
	//{
	//	for (j = 0; j < L; j++)
	//	{
	//		for (k = 0; k < q; k++)
	//			cout << y[i][j][k] << " ";
	//		cout << "\n";
	//	}
	//	cout << "\n";
	//}
	//cin >> p; //to stop the screen
}