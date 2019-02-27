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



/*Parameters: read - FILE pointer that hold the address of the read file
*             readIn - array pointer that all the data gets passed to
*return: none
* This function reads the data from the input file and stores it
* into the array struct. Inside this function there is a call to allocate2D
* to allocate memory for the array struct. The data scanned in is passed
* by pointer back to the main.
*/
void readFile( FILE* read , array* readIn);



/*Parameters: readIn - array pointer for all the data
*return: none
* allocates memory for all the data; uses for loop since it is 2d
* pass by pointer
*/
void allocate2D ( array* readIn );



/*Parameters: readIn - array type that has all the data
*return: none
* frees memory for all the data; uses for loop since it is 2d
*/
void free2D ( array readIn);



/*Parameters: pArray - parity pointer that stores all 4 parities
*             readIn1 - array type that has all the data from the
*             first input file stored in.
*             readIn2 - array type that has all the data from the
*             second input file stored in.
*return: none
*des
*/
void calculateParity( parity* pArray , array readIn1, array readIn2 );



/*Parameters: i - an int that represents the number of arguments from
*             the command line
*return: true or false
*returns true or false depending if i is equal to 4
*/
bool checkArgv(int i);



/*Parameters: read1 - FILE double pointer that is used to open the first
*             input file.
*             read2 - FILE double pointer that is used to open the second
*             input file.
*             write - FILE double pointer that is used to open the output file.
*return: true or false
* opens all three files, then checks if they were successfully opened. If they
* weren't opened, it will print which one was not opened and return false.
* Otherwise, it will return true. passes the opened files by pointer
*/
bool openFiles(FILE** read1, FILE** read2, FILE** write, const char* cmdArgs[]);



/*Parameters: write - FILE pointer thats stores the address of the output file
*             readIn1 - array type that has all the data from the first
*             input file
*             readIn2 - array type that has all the data from the second
*             input file
*             pArray - parity type that has all four parities stored.
*return: none
* prints the first input file formated. Then prints the second input
* file formated with the row and column with the error colored red.
* frees the allocated memory for pArray.
*/
void writeFile(FILE* write , array readIn1,  array readIn2, parity pArray);

#endif
