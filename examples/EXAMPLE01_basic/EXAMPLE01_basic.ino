/*
 * FILENAME: EXAMPLE01_basic.ino
 * AUTHOR:   Orlando S. Hoilett
 * CONTACT:  orlandohoilett@gmail.com
 * VERSION:  1.0.0
 * 
 * 
 * AFFILIATIONS
 * Linnes Lab, Weldon School of Biomedical Engineering,
 * Purdue University, West Lafayette, IN 47907
 * 
 * 
 * DESCRIPTION
 * Basic test of the MatrixMath library.
 * 
 * 
 * UPDATES
 * Version 1.0.0
 * 2020/08/31:1411>
 *           - Initialized
 * 
 */


#include <MatrixMath.h>


const uint16_t N = 2;
const uint16_t M = 3;

uint16_t A[N][N];
uint16_t B[N][N];
uint16_t C[N][N];

uint16_t D[M][M];
uint16_t E[M][M];


void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0)); //initialize random number generator


  //Initialize matrix "A"
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;
  Serial.println("Initializing matrix, A...");
  MatrixMath<uint16_t>::print((uint16_t*)A, N, N, "A =");
  Serial.println();


  //Scale matrix "A"
  Serial.println("Scaling matrix, A...");
  MatrixMath<uint16_t>::scale((uint16_t*)A, N, N, 3);
  MatrixMath<uint16_t>::print((uint16_t*)A, N, N, "A = ");
  Serial.println();


  //Transpose matrix "A"
  Serial.println("Transposing matrix, A into matrix, C...");
  MatrixMath<uint16_t>::transpose((uint16_t*)A, N, N, (uint16_t*)C);
  MatrixMath<uint16_t>::print((uint16_t*)C, N, N, "C =");
  Serial.println();


  //Initialize matrix "D"
  for(uint16_t i = 0; i < M; i++)
  {
    for(uint16_t j = 0; j < M; j++)
    {
      D[i][j] = random(0,10);
    }
  }
  Serial.println("Initializing matrix, D...");
  MatrixMath<uint16_t>::print((uint16_t*)D, N, N, "D = ");
  Serial.println();

  
  //Transposing matrix, D into matrix, E
  Serial.println("Transposing matrix, D into matrix, E...");
  MatrixMath<uint16_t>::transpose((uint16_t*)D, N, N, (uint16_t*)E);
  MatrixMath<uint16_t>::print((uint16_t*)E, N, N, "E =");
  Serial.println();


  //Scaling matrix, A into matrix, B
  Serial.println("Scale matrix, A into matrix, B...");
  MatrixMath<uint16_t>::scale((uint16_t*)A, N, N, 10, (uint16_t*)B);
  MatrixMath<uint16_t>::print((uint16_t*)A, N, N, "A = ");
  Serial.println();
  MatrixMath<uint16_t>::print((uint16_t*)B, N, N, "B = ");
  Serial.println();
}

void loop()
{
}
