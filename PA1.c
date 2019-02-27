/*********************
  *Eddie Negron
  *PA 1
  *CPSC 1020-002, Sp19
  *eddien@clemson.edu
**********************/
#include "PA1.h"

void readFile( FILE* read , array* readIn){
  fscanf(read , "%d %d\n" , &readIn->row , &readIn->column);
  allocate2D(readIn);
  for(int i = 0; i < readIn->row; i++){
    for(int j = 0; j < readIn->column; j++){
      fscanf(read, "%d " , &readIn->data[i][j]);
    }
  }
}

void allocate2D ( array* readIn ){
  readIn->data = (int**)malloc(sizeof(int) * readIn->row * readIn->row);
  for(int i = 0; i < readIn->row; i++){
    readIn->data[i] = (int*)malloc(sizeof(int) * readIn->column);
  }
}

void free2D ( array readIn){
  for(int i = 0; i < readIn.row; i++){
    free(readIn.data[i]);
  }
  free(readIn.data);
}

void calculateParity( parity* pArray , array readIn1, array readIn2 ){
  pArray->parityRow = malloc(sizeof(int) * 2);
  pArray->parityRow[0] = malloc(sizeof(int) * readIn1.row);
  pArray->parityRow[1] = malloc(sizeof(int) * readIn2.row);
  pArray->parityColumn = malloc(sizeof(int) * 2);
  pArray->parityColumn[0] = malloc(sizeof(int) * readIn1.column);
  pArray->parityColumn[1] = malloc(sizeof(int) * readIn2.column);
  for(int i = 0; i < readIn1.row; i++){
    pArray->parityRow[0][i] = 0;
    pArray->parityRow[1][i] = 0;
  }
  for(int i = 0; i < readIn2.column; i++){
    pArray->parityColumn[0][i] = 0;
    pArray->parityColumn[1][i] = 0;
  }

  for(int i = 0; i < readIn1.row; i++){
    for(int j = 0; j < readIn1.column; j++){
      pArray->parityRow[0][i] += readIn1.data[i][j];
      pArray->parityRow[1][i] += readIn2.data[i][j];
      pArray->parityColumn[0][j] += readIn1.data[i][j];
      pArray->parityColumn[1][j] += readIn2.data[i][j];
    }
  }

  for(int i = 0; i < readIn1.row; i++){
    pArray->parityRow[0][i] = (pArray->parityRow[0][i])%2;
    pArray->parityRow[1][i] = (pArray->parityRow[1][i])%2;
  }
  for(int i = 0; i < readIn1.column; i++){
    pArray->parityColumn[0][i] = (pArray->parityColumn[0][i])%2;
    pArray->parityColumn[1][i] = (pArray->parityColumn[1][i])%2;
  }
}

bool checkArgv(int i){
  if(i != 4){
    printf("Error please enter 4 arguments\n");
    return false;
  }else{
    return true;
  }
}

bool openFiles(FILE** read1, FILE** read2, FILE** write, const char* cmdArgs[]){
  *read1 = fopen(cmdArgs[1],"r");
  *read2 = fopen(cmdArgs[2],"r");
  *write = fopen(cmdArgs[3], "w");
  bool pass = false;
  if(*read1 == NULL) perror ("Error opening read1 file\n");
  else if(*read2 == NULL) perror ("Error opening read2 file\n");
  else if(*write == NULL) perror ("Error opening write file\n");
  else pass = true;
  return pass;
}

void writeFile(FILE* write , array readIn1, array readIn2, parity pArray){
  int pRow, pCol =-1;
  for(int i = 0; i < readIn1.row; i++){
    if (!(pArray.parityRow[0][i]==pArray.parityRow[1][i])) {
      pRow = i;
      break;
    }
  }
  for(int i = 0; i < readIn1.column; i++){
    if (!(pArray.parityColumn[0][i]==pArray.parityColumn[1][i])) {
      pCol = i;
      break;
    }
  }
  fprintf(write, "ORIGINAL MESSAGE\n");
  for(int i = 0; i < readIn2.row; i++){
    for(int j = 0; j < readIn2.column; j++){
      fprintf(write,"%d ",readIn2.data[i][j]);
    }
    fprintf(write," | %d\n", pArray.parityRow[0][i]);
  }
  fprintf(write,"---\n");
  for(int i = 0; i < readIn2.column; i++){
    fprintf(write,"%d ", pArray.parityColumn[0][i]);
  }
  fprintf(write,"\n");

  fprintf(write, "\nMESSAGE AFTER TRANSMISSION\n");
  for(int i = 0; i < readIn2.row; i++){
    for(int j = 0; j < readIn2.column; j++){
      if(i == pRow || j == pCol){
        fprintf(write,"\033[31m");
        fprintf(write,"%d ",readIn2.data[i][j]);
        fprintf(write,"\033[0m");
      }else{
        fprintf(write,"%d ",readIn2.data[i][j]);
      }
    }
    if(i == pRow){
      fprintf(write,"\033[31m");
      fprintf(write," | %d\n", pArray.parityRow[1][i]);
      fprintf(write,"\033[0m");
    }else{
      fprintf(write," | %d\n", pArray.parityRow[1][i]);
    }
  }
  fprintf(write,"---\n");
  for(int i = 0; i < readIn2.column; i++){
    if(i == pCol){
      fprintf(write,"\033[31m");
      fprintf(write,"%d ", pArray.parityColumn[1][i]);
      fprintf(write,"\033[0m");
    }else{
      fprintf(write,"%d ", pArray.parityColumn[1][i]);
    }
  }
  fprintf(write,"\n");
  if(pRow == -1 || pCol == -1){
    fprintf(write, "\nTransmission was a success, no errors were found.\n");
  }else{
    fprintf(write,"\nAn error was found in the file, the error is in Row %d Column %d.\n", pRow, pCol );
  }
}
