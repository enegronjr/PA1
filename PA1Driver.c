/**********************
  *Eddie Negron
  *PA 1
  *CPSC 1020-002, Sp19
  *eddien@clemson.edu
***********************/
#include "PA1.h"

int main(int argc, const char* argv[]){
  FILE* read1 = NULL;
  FILE* read2 = NULL;
  FILE* write = NULL;
  array readIn1;
  array readIn2;
  parity pArray;

  if(!(checkArgv(argc)) || !(openFiles(&read1, &read2 ,&write, argv))){
    return 1;
  }

  readFile(read1, &readIn1);
  readFile(read2, &readIn2);

  calculateParity(&pArray, readIn1, readIn2);

  writeFile(write, readIn1, readIn2, pArray);

  free2D(readIn1);
  free2D(readIn2);

}
