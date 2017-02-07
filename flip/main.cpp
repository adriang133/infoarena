#include <fstream>
#include <cstring>
using namespace std;
int N, M, A[20][20], B[20][20], i, j, k, indexx, sol = 0, tempSum, maxSol = - (1<<30);
void copyMatrix()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j] = B[i][j];
		}
	}
}
void flip(int column)
{
	for (int i = 0; i < N; i++)
	{
		A[i][column] *= -1;
	}
}
int totalSum()
{
	int s = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			s += A[i][j];
		}
	}
	return s;
}
int sum(int line)
{
	int s = 0;
	for (int i = 0; i < M; i++)
	{
		s += A[line][i];
	}
	return s;
}
int main()
{

	ifstream fin("flip.in");
	fin >> N >> M;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			fin >> A[i][j];
			B[i][j] = A[i][j];
		}
	}
	fin.close();
	indexx = 0;
	for (k = 0; k < (1 << M) - 1; k++)
	{
		copyMatrix();
		int k2 = k;
		indexx = 0;
		while (k2 > 0)
		{
			if (k2 & 1 == 1)
			{
				flip(indexx);
			}
			indexx++;
			k2 = k2 >> 1;
		}
		sol = totalSum();
		for (i = 0; i < N; i++)
		{
			tempSum = sum(i);
			if (tempSum < 0)
			{
				sol += 2 * (-tempSum);
			}
		}
		if (sol > maxSol)
		{
			maxSol = sol;
		}
	}


	ofstream fout("flip.out");
	fout << maxSol;
	fout.close();
	return 0;
}
