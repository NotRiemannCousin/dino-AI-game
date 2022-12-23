#include <array>
#include <iostream>
#include <algorithm>

using std::array;
using std::cout;
using std::ostream;
using std::max;
using std::string;

template <int i, int j>
class matrix
{
	array<array<float, j>, i> M{};

  public:
	matrix() {}
	//	matrix(array<int, i * j> B) {
	//		for(int m = 0; m < i; m++)
	//			for(int n = 0; n < j; n++)
	//				M[m][n] = B[m*j + n];
	//	};
	matrix(array<array<float, j>, i> A) { M = A; }

	array<float, j> &operator[](int a)
	{
		return M[a];
	}

	string print()
	{
		string str = "\n";
		for (int m = 0; m < i; m++)
		{
			for (int n = 0; n < j; n++)
				str.append(std::to_string(M[m][n]) + " ");
			str.append("\n");
		}
		return str;
	}
	void boolean()
	{
		for (int a = 0; a < i; a++)
			for (int b = 0; b < j; b++)
				M[a][b] = (M[a][b] > 0 ? 1 : 0);

	}
	void ReLu()
	{
		for (int a = 0; a < i; a++)
			for (int b = 0; b < j; b++)
				M[a][b] = max(M[a][b], 0.0f);
	}
	
	void compare(float x)
	{
		
	}

	matrix<j, i> transpose()
	{
		array<array<float, i>, j> A;
		for (int a = 0; a < i; a++)
			for (int b = 0; b < j; b++)
				A[b][a] = M[a][b];
		return matrix<j, i>(A);
	}

	template <int k>
	matrix<i, k> operator*(matrix<j, k> &B)
	{
		matrix<i, k> C;
		for (int x = 0; x < i; x++)
			for (int y = 0; y < k; y++)
				for (int z = 0; z < j; z++)
					C[x][y] += M[x][z] * B[z][y];

		return C;
	}
	operator array<array<float, j>, i>() { return M; }
};