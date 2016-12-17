#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#pragma warning(disable : 4996)
ifstream fin;
ofstream fout;

void exct_one_or(int**, int, int);
int get_nextstate(int**, int, int, int);
int get_output(int**, int, int, int);
void imply(int, int, int, bool = false);
void initilize_CNF(int, int, int, int);
void PDS_Checking(int**, int, int);
int Calculate_Variables(int, int, int, int);
int Calculate_Clauses(int, int, int, int);



void main(int argc, char* argv[])
{
	int start_s = clock();

	int L, n, o, ns, p, q, var_no = 1;
	char* outputfile = new char[52];
	char length[2];
	L = atoi(argv[1]);

	sprintf(length, "%d%c", L, '-'); // put the int into a string

	fin.open(argv[2]);
	strcpy(outputfile, "CNF-L");
	strcat(outputfile, length);
	strcat(outputfile, argv[2]);

	fout.open(outputfile);


	L = atoi(argv[1]);


	fin.ignore(100, ' ');
	fin >> p;
	fin.ignore(100, ' ');
	fin >> q;
	fin.ignore(100, 's');
	fin.ignore(100, ' ');
	fin >> n;
	fin.ignore(6, '\0');

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
	for (int i = 0; i < (p*n); i++)
		for (int j = 0; j < 4; j++)
			fin >> t[i][j];

	//allocate memory for (n*(n-1)/2)*L comparison variables
	int ** E = new int*[n*(n - 1) / 2];
	for (int i = 0; i < (n*(n - 1) / 2); i++)
	{
		E[i] = new int[L];
		for (int l = 0; l < L; l++)
		{
			E[i][l] = var_no++;
		}
	}



	initilize_CNF(L, n, p, q);
	//cout << "/---------------------------------------------\n";
	//generating clauses for Q1
	exct_one_or(x, L, p);

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q2
	for (int i = 0; i < n; i++)
		fout << s[i][0][i] << " 0\n";

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q3
	for (int i = 0; i < n; i++)
		exct_one_or(s[i], L, n);

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q4
	for (int i = 0; i < n; i++)
		for (int l = 0; l < (L - 1); l++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < p; k++)
				{
					ns = get_nextstate(t, j, k, p);
					imply(s[i][l][j], x[l][k], s[i][l + 1][ns]);
				}

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q5
	for (int i = 0; i < n; i++)
		exct_one_or(y[i], L, q);

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q6
	for (int i = 0; i < n; i++)
		for (int l = 0; l < L; l++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < p; k++)
				{
					o = get_output(t, j, k, p);
					imply(s[i][l][j], x[l][k], y[i][l][o]);
				}

	//cout << "/---------------------------------------------\n";
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

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q8
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

	//cout << "/---------------------------------------------\n";
	//generating clauses for Q9
	PDS_Checking(E, L, n);

	//cout << "/---------------------------------------------\n";




	fin.close();
	fout.close();


	//Deallocating memory
	//Deallocating Outputfile
	delete[] outputfile;

	//Deallocating x
	for (int i = 0; i < L; i++) {
		delete[] x[i];
	}
	delete[] x;

	//Deallocating t
	for (int i = 0; i < p*n; i++) {
		delete[] t[i];
	}
	delete[] t;
	//Deallocating E
	for (int i = 0; i < (n*(n - 1) / 2); i++) {
		delete[] E[i];
	}
	delete[] E;

	//Deallocating s & y
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < L; j++) {
			delete[] s[i][j];
			delete[] y[i][j];
		}
		delete[] s[i];
		delete[] y[i];
	}
	delete[] s;
	delete[] y;

	int stop_s = clock();
	cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

	//system("PAUSE");
}


void initilize_CNF(int L, int N, int P, int Q) {
	fout << "p cnf " << Calculate_Variables(L, N, P, Q) << ' ' << Calculate_Clauses(L, N, P, Q) << '\n';
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
				fout << -z[i][k] << " " << -z[i][j + 1] << " 0\n";
			}
		}
		for (j = 0; j < y; j++) //or all variables
			fout << z[i][j] << " ";
		fout << " 0\n";
	}
}

//get the next state from the correct transition
int get_nextstate(int** t, int j, int k, int p)
{
	return t[(p* j + k)][2];
}

//get the output from the correct transition
int get_output(int** t, int j, int k, int p)
{
	return t[(p * j + k)][3];
}

//output clause to screen
void imply(int s, int k, int ns, bool flag)
{
	if (!flag)
		fout << -s << " " << -k << " " << ns << " 0\n";
	else
		fout << -s << " " << -k << " " << -ns << " 0\n";
}

void PDS_Checking(int** E, int L, int n)
{
	for (int i = 0; i < (n*(n - 1) / 2); i++)
	{
		for (int l = 0; l < L; l++)
			fout << -E[i][l] << " ";
		fout << "0\n";
	}

}

int Calculate_Variables(int L, int N, int P, int Q) {
	return ((P*L) +
		(L*N*N) +
		(N*L*Q) +
		(L*N*(N - 1) / 2)
		);
}

int Calculate_Clauses(int L, int N, int P, int Q) {
	return ((P*(P - 1) / 2 + 1) +
		(N)+
		(N*L*(N*(N - 1) / 2 + 1)) +
		(N*N*(L - 1)*P) +
		(N*L*(Q*(Q - 1) / 2 + 1)) +
		(N*N*L*P) +
		(Q*Q*L*N*(N - 1) / 2) +
		(N*(N - 1) / 2)
		);
}