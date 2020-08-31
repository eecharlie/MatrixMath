/*
 *  MatrixMath.h Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 *  Modified to work with Arduino 1.0/1.5 by randomvibe & robtillaart
 *  Made into a real library on GitHub by Vasilis Georgitzikis (tzikis)
 *  so that it's easy to use and install (March 2015)
 */


/*
 *  MatrixMath.cpp Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 */


#ifndef MatrixMath_h
#define MatrixMath_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#if defined(ARDUINO_ARCH_SAMD)
	#define MatrixMathSerial SerialUSB
#else
	#define MatrixMathSerial Serial
#endif


template<typename Type>

class MatrixMath
{
	
public:
	//MatrixMath();
	static void print(Type* A, int m, int n);
	static void print(Type* A, int m, int n, String label);
	
	static void copy(Type* A, int n, int m, Type* B);
	
	static void multiply(Type* A, Type* B, int m, int p, int n, Type* C);
	static void add(Type* A, Type* B, int m, int n, Type* C);
	static void subtract(Type* A, Type* B, int m, int n, Type* C);
	
	static void transpose(Type* A, int m, int n, Type* C);
	static void scale(Type* A, int m, int n, Type k);
	static void scale(Type* A, int m, int n, Type k, Type* C);
	
	static int invert(float* A, int n);
	
};


// Matrix Printing Routine
// Uses tabs to separate numbers under assumption printed float width won't cause problems
template<typename Type>
void MatrixMath<Type>::print(Type* A, int m, int n)
{
	// A = input matrix (m x n)
	int i, j;

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			MatrixMathSerial.print(A[n * i + j]);
			MatrixMathSerial.print("\t");
		}
		MatrixMathSerial.println();
	}
}

// Matrix Printing Routine
// Uses tabs to separate numbers under assumption printed float width won't cause problems
template<typename Type>
void MatrixMath<Type>::print(Type* A, int m, int n, String label)
{
	// A = input matrix (m x n)
	int i, j;
	
	MatrixMathSerial.println(label);
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			MatrixMathSerial.print(A[n * i + j]);
			MatrixMathSerial.print("\t");
		}
		MatrixMathSerial.println();
	}
}

template<typename Type>
void MatrixMath<Type>::copy(Type* A, int n, int m, Type* B)
{
	int i, j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
		{
			B[n * i + j] = A[n * i + j];
		}
}

//Matrix Multiplication Routine
// C = A*B
template<typename Type>
void MatrixMath<Type>::multiply(Type* A, Type* B, int m, int p, int n, Type* C)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// C = output matrix = A*B (m x n)
	int i, j, k;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
		{
			C[n * i + j] = 0;
			for (k = 0; k < p; k++)
				C[n * i + j] = C[n * i + j] + A[p * i + k] * B[n * k + j];
		}
}


//Matrix Addition Routine
template<typename Type>
void MatrixMath<Type>::add(Type* A, Type* B, int m, int n, Type* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			C[n * i + j] = A[n * i + j] + B[n * i + j];
}


//Matrix Subtraction Routine
template<typename Type>
void MatrixMath<Type>::subtract(Type* A, Type* B, int m, int n, Type* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			C[n * i + j] = A[n * i + j] - B[n * i + j];
}


//Matrix Transpose Routine
template<typename Type>
void MatrixMath<Type>::transpose(Type* A, int m, int n, Type* C)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
			C[m * j + i] = A[n * i + j];
}

template<typename Type>
void MatrixMath<Type>::scale(Type* A, int m, int n, Type k)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[n * i + j] = A[n * i + j] * k;
}


template<typename Type>
void MatrixMath<Type>::scale(Type* A, int m, int n, Type k, Type* C)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			C[n * i + j] = A[n * i + j] * k;
}


//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
template<typename Type>
int MatrixMath<Type>::invert(float* A, int n)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k, i, j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	float tmp;		// used for finding max value and making column swaps
	
	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i * n + k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i * n + k]);
				pivrow = i;
			}
		}
		
		// check for singular matrix
		if (A[pivrow * n + k] == 0.0f)
		{
			Serial.println("Inversion failed due to singular matrix");
			return 0;
		}
		
		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k * n + j];
				A[k * n + j] = A[pivrow * n + j];
				A[pivrow * n + j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)
		
		tmp = 1.0f / A[k * n + k];	// invert pivot element
		A[k * n + k] = 1.0f;		// This element of input matrix becomes result matrix
		
		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k * n + j] = A[k * n + j] * tmp;
		}
		
		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i * n + k];
				A[i * n + k] = 0.0f; // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i * n + j] = A[i * n + j] - A[k * n + j] * tmp;
				}
			}
		}
	}
	
	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n - 1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = A[i * n + k];
				A[i * n + k] = A[i * n + pivrows[k]];
				A[i * n + pivrows[k]] = tmp;
			}
		}
	}
	return 1;
}


#endif
