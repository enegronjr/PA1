/**********************
  *Eddie Negron
  *PA 1
  *CPSC 1020-002, Sp19
  *eddien@clemson.edu
***********************/
#ifndef PA1_H
#define PA1_H value

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int** data;
  int row;
  int column;
}array;

typedef struct{
  int** parityRow;
  int** parityColumn;
}parity;

/*Parameters:
*return:
*des
*/
array* readFile( FILE* read , array* readIn);

array* allocate2D ( array* readIn );

void free2D ( array readIn);

parity* calculateParity( parity* pArray , array readIn1, array readIn2 );

bool checkArgv(int i);

bool openFiles(FILE** read1, FILE** read2, FILE** write, const char* cmdArgs[]);

void writeFile(FILE* write , array readIn1,  array readIn2, parity pArray);

#endif
