/****************
  Eddie Negron
  eddien
  Lab 7
  CPSC 1021-001
  Nushrat Humaira
****************/
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, const char* argv[]){
  //open input and output files
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  //declare necessary variables
  string title;
  int id;
  long double price;
  double sum = 0;
  int count = 0;

  //enables the reading of US currency
  input.imbue(locale("en_US.UTF-8"));
  output.imbue(locale("en_US.UTF-8"));

  //outputs the "header"
  output << "ID\t" << setw(25) << right << "Title" <<
  setw(12) << right << "Price" << endl;

  //while there's an ID
  while(input >> id){
    //while there's a price
    while(input >> get_money(price)){
      //counts the amount of prices and totals them
      count++;
      sum += price;
    }
    //clears the input
    input.clear();
    //reads in the title
    getline(input,title);
    //format the title if length is greater than 25
    if(title.length() > 25){
      title.erase(25, string::npos);
      title.replace(22, string::npos, 3 , '.');
    }
    //output the read in and calulated data
    output << setw(2) << id << setw(27) <<
    title << setw(12) << put_money(sum/count) << endl;
    //resets the sum and count
    sum = 0.0;
    count = 0;
  }
}
