#include <iostream>
#include <fstream>

using namespace std;

void main(int argc, char* argv[])
{
	int L;
	ifstream fin(argv[2]);
	ofstream fout(argv[3]);


	L = atoi(argv[1]);
	fout << "THIS LINE WORKS\nargc: " << argc << "\nargv[1]: " << argv[1] << "\nargv[2]: " << argv[2] << "\nargv[3]: " << argv[3] << "\nTest: L= " << L << '\n';

	fin.close();
	fout.close();

}