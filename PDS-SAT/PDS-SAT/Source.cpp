#include <iostream>
#include <fstream>

using namespace std;

void exct_one_or(int**, int, int);
int get_nextstate(int**, int, int);
int get_output(int**, int, int);
void imply(int, int, int, bool = false);
void initilize_CNF();
void PDS_Checking(int**, int, int);



void main(int argc, char* argv[])
{
	int L, n, o, ns, p, q, var_no = 1;

	//create file input stream
	//create file output stream
	//open file streams

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
	for (int i = 0; i < L; i++)
	{
		x[i] = new int[p];
		for (int j = 0; j < p; j++)
		{
			x[i][j] = var_no++;   //xl={1,2,3,..,p*L}
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

	//allocate memory for (p*n)*4 transition variables
	int ** t = new int*[p*n];
	for (int i = 0; i < (p*n); i++)
		t[i] = new int[4];

	//inserting transitions
	cout << "enter the transitions:\n";
	for (int i = 0; i < (p*n); i++)
		for (int j = 0; j < 4; j++)
			cin >> t[i][j];

	//allocate memory for (n*(n-1)/2)*L comparison variables
	int ** E = new int*[n*(n - 1) / 2];
	for (int i = 0; i < n; i++)
	{
		E[i] = new int[L];
		for (int l = 0; l < L; l++)
		{
			E[i][l] = var_no++;
		}
	}
	initilize_CNF();
	cout << "/---------------------------------------------\n";
	//generating clauses for Q1
	exct_one_or(x, L, p);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q2
	for (int i = 0; i < n; i++)
		cout << s[i][0][i] << " 0\n";

	cout << "/---------------------------------------------\n";
	//generating clauses for Q3
	for (int i = 0; i < n; i++)
		exct_one_or(s[i], L, n);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q4
	for (int i = 0; i < n; i++)
		for (int l = 0; l < (L - 1); l++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < p; k++)
				{
					ns = get_nextstate(t, j, k);
					imply(s[i][l][j], x[l][k], s[i][l + 1][ns]);
				}

	cout << "/---------------------------------------------\n";
	//generating clauses for Q5
	for (int i = 0; i < n; i++)
		exct_one_or(y[i], L, q);

	cout << "/---------------------------------------------\n";
	//generating clauses for Q6
	for (int i = 0; i < n; i++)
		for (int l = 0; l < L; l++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < p; k++)
				{
					o = get_output(t, j, k);
					imply(s[i][l][j], x[l][k], y[i][l][o]);
				}

	cout << "/---------------------------------------------\n";
	//generating clauses for Q7
	int ec1 = 0;
	for (int i = 0; i < (n - 1); i++)
		for (int j = i + 1; j < n; j++)
		{
			for (int l = 0; l < L; l++)
				for (int k = 0; k < q; k++)
					imply(y[i][l][k], y[j][l][k], E[ec1][l]);
			ec1++;
		}

	cout << "/---------------------------------------------\n";
	//generating clauses for Q8 (NOT TESTED)
	int ec2 = 0;
	for (int i = 0; i < (n - 1); i++)
		for (int j = i + 1; j < n; j++)
		{
			for (int l = 0; l < L; l++)
				for (int k = 0; k < q; k++)
					for (int m = 0; m < q; m++)
						if (m != k) imply(y[i][l][k], y[j][l][m], E[ec2][l], true);
			ec2++;
		}

	cout << "/---------------------------------------------\n";
	//generating clauses for Q9 (NOT TESTED)
	PDS_Checking(E, L, n);

	cout << "/---------------------------------------------\n";


	//Close file streams 

	system("PAUSE");
}


void initilize_CNF() {
	cout << "P CNF " << "#Var #Sums\n";
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
int get_nextstate(int** t, int j, int k)
{
	return t[(2 * j + k)][2];
}

//get the output from the correct transition
int get_output(int** t, int j, int k)
{
	return t[(2 * j + k)][3];
}

//output clause to screen
void imply(int s, int k, int ns, bool flag)
{
	if (!flag)
		cout << -s << " " << -k << " " << ns << " 0\n";
	else
		cout << -s << " " << -k << " " << -ns << " 0\n";
}

void PDS_Checking(int** E, int L, int n) {
	for (int i = 0; i < n; i++) {
		for (int l = 0; l < L; l++)
			cout << -E[i][l] << " 0/n";
	}

}