#include <iostream>
#include <fstream>

using namespace std;

void exct_one_or(int**, int, int);
int get_transition(int**, int, int);
void imply(int, int, int);

int main()
{
	int i, j, k, l, L, n, ns, p, q, var_no = 1;

	cout << "enter the length of DS: ";
	cin >> L;//Read from file
	cout << "enter number of inputs: ";
	cin >> p;//Read from file
	cout << "enter number of outputs: ";
	cin >> q;//Read from file
	cout << "enter number of states: ";
	cin >> n;//Read from file

	//allocate memory for p*L input variables
	int ** x = new int*[L];
	for (i = 0; i<L; i++)
	{
		x[i] = new int[p];
		for (j = 0; j < p; j++)
		{
			x[i][j] = var_no++;   //xl={1,2,3,..,p*L}
		}
	}

	//allocate memory for n*L*n state variables
	int *** s = new int**[n];
	for (i = 0; i<n; i++)
	{
		s[i] = new int*[L];
		for (j = 0; j < L; j++)
		{
			s[i][j] = new int[n];
			for (k = 0; k < n; k++)
				s[i][j][k] = var_no++;
		}
	}

	//allocate memory for n*L*q output variables
	int *** y = new int**[n];
	for (i = 0; i<n; i++)
	{
		y[i] = new int*[L];
		for (j = 0; j < L; j++)
		{
			y[i][j] = new int[q];
			for (k = 0; k < q; k++)
				y[i][j][k] = var_no++;
		}
	}

	//allocate memory for (p*n)*4 transition variables
	int ** t = new int*[p*n];
	for (i = 0; i<(p*n); i++)
		t[i] = new int[4];

	//inserting transitions
	for (i = 0; i < (p*n); i++)
		for (j = 0; j < 4; j++)
			cin >> t[i][j];

	//generating clauses for Q1
	exct_one_or(x, L, p);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q2
	for (i = 0; i < n; i++)
		cout << s[i][0][i] << " 0\n";

	cout << "/---------------------------------------------\n";
	//generating clauses for Q3
	for (i = 0; i < n; i++)
		exct_one_or(s[i], L, n);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q4
	for (i = 0; i < n; i++)
		for (l = 0; l < (L - 1); l++)
			for (j = 0; j < n; j++)
				for (k = 0; k < p; k++)
				{
					ns = get_transition(t, j, k);
					imply(s[i][l][j], x[l][k], s[i][l + 1][ns]);
				}
	cout << "/---------------------------------------------\n";
	//generating clauses for Q5
	for (i = 0; i < n; i++)
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
	cin >> p; //to stop the screen
	return 0;
}


//exactly one or for two dimensions array
void exct_one_or(int ** z, int x, int y)
{
	int i, j, k;
	for (i = 0; i < x; i++)
	{
		for (k = 0; k < y; k++)
		{
			for (j = k; j < (y - 1); j++) //negating every two variables
			{
				cout << -z[i][k] << " " << -z[i][j + 1] << " 0\n";
			}
		}
		for (j = 0; j < y; j++) //or all variables
			cout << z[i][j] << " ";
		cout << " 0\n";
	}
}

//get the next state from the correct transition
int get_transition(int** t, int j, int k)
{
	return t[(2 * j + k)][2];
}

//output clause to screen
void imply(int s, int k, int ns)
{
	cout << -s << " " << -k << " " << ns << " 0\n";
}