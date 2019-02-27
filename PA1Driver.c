/**********************
  *Eddie Negron
  *PA 1
  *CPSC 1020-002, Sp19
  *eddien@clemson.edu
***********************/
#include "PA1.h"

int main(int argc, const char* argv[]){
  //declare file pointers
  FILE* read1 = NULL;
  FILE* read2 = NULL;
  FILE* write = NULL;
  //declare user-defined variables for data
  array readIn1;
  array readIn2;
  //declare user-defined variable for parity
  parity pArray;

  //checks if correct ammount of arguments were entered and
  //if all files were opened correctly
  if(!(checkArgv(argc)) || !(openFiles(&read1, &read2 ,&write, argv))){
    return 1;
  }
  //reads the data into the variables
  readFile(read1, &readIn1);
  readFile(read2, &readIn2);

  //calculates the parities
  calculateParity(&pArray, readIn1, readIn2);

  //writes to the output
  writeFile(write, readIn1, readIn2, pArray);

  //frees the 2d arrays
  free2D(readIn1);
  free2D(readIn2);

  //closes all the files
  fclose(read1);
  fclose(read2);
  fclose(write);

}
