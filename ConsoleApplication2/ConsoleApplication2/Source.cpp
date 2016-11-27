#include <iostream>
#include <fstream>

using namespace std;

void main(int argc, char* argv[])
{
	int L;
	ifstream fin(argv[2]);
	ofstream fout(argv[3]);

	int ** t = new int*[3*3];
	for (int i = 0; i < (3*3); i++)
		t[i] = new int[4];

	//int i = 0, j = 0;
	//
	//while (fin >> t[i][j] && j<4 &&) {
	//	i++;
	//	j++;
	//}

	for (int i = 0; !fin.eof(); i++)
		for (int j = 0; j < 4; j++)
			fin >> t[i][j];

	L = atoi(argv[1]);
	fout << "THIS LINE WORKS\nargc: " << argc << "\nargv[1]: " << argv[1] << "\nargv[2]: " << argv[2] << "\nargv[3]: " << argv[3] << "\nTest: L= " << L << '\n';

	for (int i = 0; i < (2 * 3)+1; i++) {
		for (int j = 0; j < 4; j++)
			fout << t[i][j] << " ";
		fout << '\n';
	}


	fin.close();
	fout.close();

}