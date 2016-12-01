#include <iostream>
#include <fstream>
#include<string>

using namespace std;

void main(int argc, char* argv[])
{
	int L,p=0,q=0,n=0,test=0;
	ifstream fin(argv[2]);
	ofstream fout(argv[3]);
	fin.ignore(3,' ');
	fin >> p;
	fin.ignore(3,' ');
	fin >> q;
	fin.ignore(5, 's');
	fin.ignore(3,' ');
	fin >> n;
	fin.ignore(6, '\0');
	cout << test << endl;
	cout << p << endl;
	cout << q << endl;
	cout << n << endl;

	fout << "p: " << p << "\nq: " << q << "\nn: " << n << "\ntest: " << test;

	int ** t = new int*[3 * 3];
	for (int i = 0; i < (3 * 3); i++)
		t[i] = new int[4];

	for (int i = 0; !fin.eof(); i++)
		for (int j = 0; j < 4; j++)
			fin >> t[i][j];

	L = atoi(argv[1]);
	fout << "THIS LINE WORKS\nargc: " << argc << "\nargv[1]: " << argv[1] << "\nargv[2]: " << argv[2] << "\nargv[3]: " << argv[3] << "\nTest: L= " << L << '\n';

	for (int i = 0; i < (2 * 3); i++) {
		for (int j = 0; j < 4; j++)
			fout << t[i][j] << " ";
		fout << '\n';
	}


	fin.close();
	fout.close();

}