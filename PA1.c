/*********************
  *Eddie Negron
  *PA 1
  *CPSC 1020-002, Sp19
  *eddien@clemson.edu
**********************/
#include "PA1.h"

void readFile( FILE* read , array* readIn){
  //scans in the dimensions of the data table
  fscanf(read , "%d %d\n" , &readIn->row , &readIn->column);
  //calls function to allocate
  allocate2D(readIn);
  //for amount of rows
  for(int i = 0; i < readIn->row; i++){
    //for amount of columns
    for(int j = 0; j < readIn->column; j++){
      //scans in every number in the table
      fscanf(read, "%d " , &readIn->data[i][j]);
    }
  }
}

void allocate2D ( array* readIn ){
  //allocates the memory for the first dimension
  readIn->data = (int**)malloc(sizeof(int) * readIn->row * readIn->row);
  for(int i = 0; i < readIn->row; i++){
    //allocates the memory for the second dimension
    readIn->data[i] = (int*)malloc(sizeof(int) * readIn->column);
  }
}

void free2D ( array readIn){
  for(int i = 0; i < readIn.row; i++){
    //frees the memory for the second dimension
    free(readIn.data[i]);
  }
  //frees the memory for the first dimension
  free(readIn.data);
}

void calculateParity( parity* pArray , array readIn1, array readIn2 ){
  //allocates memory for pArray
  pArray->parityRow = (int**)malloc(sizeof(int) * 8);
  pArray->parityRow[0] = (int*)malloc(sizeof(int) * readIn1.row);
  pArray->parityRow[1] = (int*)malloc(sizeof(int) * readIn2.row);
  pArray->parityColumn = (int**)malloc(sizeof(int) * 8);
  pArray->parityColumn[0] = (int*)malloc(sizeof(int) * readIn1.column);
  pArray->parityColumn[1] = (int*)malloc(sizeof(int) * readIn2.column);

  //sets pArray to zero
  for(int i = 0; i < readIn1.row; i++){
    pArray->parityRow[0][i] = 0;
    pArray->parityRow[1][i] = 0;
  }
  for(int i = 0; i < readIn2.column; i++){
    pArray->parityColumn[0][i] = 0;
    pArray->parityColumn[1][i] = 0;
  }

  //totals all the data to their respective parities
  for(int i = 0; i < readIn1.row; i++){
    for(int j = 0; j < readIn1.column; j++){
      pArray->parityRow[0][i] += readIn1.data[i][j];
      pArray->parityRow[1][i] += readIn2.data[i][j];
      pArray->parityColumn[0][j] += readIn1.data[i][j];
      pArray->parityColumn[1][j] += readIn2.data[i][j];
    }
  }
  //calculates the parities for the rows
  for(int i = 0; i < readIn1.row; i++){
    pArray->parityRow[0][i] = (pArray->parityRow[0][i])%2;
    pArray->parityRow[1][i] = (pArray->parityRow[1][i])%2;
  }
  //calculates the parities for the columns
  for(int i = 0; i < readIn1.column; i++){
    pArray->parityColumn[0][i] = (pArray->parityColumn[0][i])%2;
    pArray->parityColumn[1][i] = (pArray->parityColumn[1][i])%2;
  }
}

bool checkArgv(int i){
  //there should be 4 arguments so if theres not it will print error
  if(i != 4){
    printf("Error please enter 4 arguments\n");
    return false;
  }else{
    return true;
  }
}

bool openFiles(FILE** read1, FILE** read2, FILE** write, const char* cmdArgs[]){
  //opens the files
  *read1 = fopen(cmdArgs[1],"r");
  *read2 = fopen(cmdArgs[2],"r");
  *write = fopen(cmdArgs[3], "w");
  //initialize pass to false
  bool pass = false;

  //if all the files were opened correctly pass will be set to true, otherwise
  //pass will not change and it will print which file was not opened
  if(*read1 == NULL) perror ("Error opening read1 file\n");
  else if(*read2 == NULL) perror ("Error opening read2 file\n");
  else if(*write == NULL) perror ("Error opening write file\n");
  else pass = true;

  return pass;
}

void writeFile(FILE* write , array readIn1, array readIn2, parity pArray){
  //declares variable to store where error is
  int pRow, pCol =-1;

  //if the parities are not equal, it stores where and breaks
  for(int i = 0; i < readIn1.row; i++){
    if (!(pArray.parityRow[0][i]==pArray.parityRow[1][i])) {
      pRow = i;
      break;
    }
  }

  //if the parities are not equal, it stores where and breaks
  for(int i = 0; i < readIn1.column; i++){
    if (!(pArray.parityColumn[0][i]==pArray.parityColumn[1][i])) {
      pCol = i;
      break;
    }
  }
  //prints header
  fprintf(write, "ORIGINAL MESSAGE\n");

  //print the entire first table
  for(int i = 0; i < readIn2.row; i++){
    for(int j = 0; j < readIn2.column; j++){
      //print data
      fprintf(write,"%d ",readIn2.data[i][j]);
    }
    //print row parity
    fprintf(write," | %d\n", pArray.parityRow[0][i]);
  }
  //seperates the data from parity
  fprintf(write,"---\n");

  for(int i = 0; i < readIn2.column; i++){
    //print column parity
    fprintf(write,"%d ", pArray.parityColumn[0][i]);
  }
  fprintf(write,"\n");

  //print header
  fprintf(write, "\nMESSAGE AFTER TRANSMISSION\n");

  //print second table
  for(int i = 0; i < readIn2.row; i++){
    for(int j = 0; j < readIn2.column; j++){
      //if its the error print data red
      if(i == pRow || j == pCol){
        fprintf(write,"\033[31m");
        fprintf(write,"%d ",readIn2.data[i][j]);
        fprintf(write,"\033[0m");
      }else{
        //just print data regulary
        fprintf(write,"%d ",readIn2.data[i][j]);
      }
    }
    //if error print parity red
    if(i == pRow){
      fprintf(write,"\033[31m");
      fprintf(write," | %d\n", pArray.parityRow[1][i]);
      fprintf(write,"\033[0m");
    }else{
      //just print parity regulary
      fprintf(write," | %d\n", pArray.parityRow[1][i]);
    }
  }
  //seperates the data from parity
  fprintf(write,"---\n");
  //print parity
  for(int i = 0; i < readIn2.column; i++){
    //if error print parity red
    if(i == pCol){
      fprintf(write,"\033[31m");
      fprintf(write,"%d ", pArray.parityColumn[1][i]);
      fprintf(write,"\033[0m");
    }else{
      //just print regulary
      fprintf(write,"%d ", pArray.parityColumn[1][i]);
    }
  }
  fprintf(write,"\n");
  //determines if there was a parity or not
  if(pRow == -1 || pCol == -1){
    fprintf(write, "\nTransmission was a success, no errors were found.\n");
  }else{
    fprintf(write,"\nAn error was found in the file, the error is in Row %d Column %d.\n", pRow, pCol );
  }
  //free all of pArray
  for(int i = 0; i < 2; i++){
    free(pArray.parityColumn[i]);
    free(pArray.parityRow[i]);
  }
  free(pArray.parityColumn);
  free(pArray.parityRow);
}
