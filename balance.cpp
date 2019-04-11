// Adam Gemperline
// Section 3

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;


struct PERSON
{
  char Name[20];
  float balance;
};



void deposit(char custName[20], PERSON P[],int SIZE)
{
  double deposit;

  for(int i = 0; i < SIZE; i++)
  {
    // strcmp() will compare c_str types
    // function compares lhs with rhs
    // NOTE: strcmp() will return 0 if TRUE, 1 if FALSE
    if (strcmp(custName, P[i].Name) == 0)
    {
      cout << P[i].Name << ", how much would you like to deposit?" << endl;
      cin >> deposit;

      P[i].balance += deposit;
      cout << P[i].Name << "'s new balance is: " << fixed <<setprecision(2) << P[i].balance << endl;

      break;
    }
    else if (i == SIZE - 1)
    {
      cout << "ERROR: name not found." << endl;
    }
  }
}



void findRichest(PERSON P[],int SIZE)
{
  // variable to store ith place of richest
  int richest = 0;

  for(int i = 1; i < SIZE; i++)
  {
    if (P[0].balance < P[i+1].balance)
      richest = i;
  }

  cout << "The customer with the greatest balance is " << P[richest].Name << "\n" << endl;
}



void display(PERSON P[], int SIZE)
{
  cout << " NAME                      BALANCE" << endl;
  cout << "-----------------------------------" << endl;

  // traverse the array, print data
  for(int i = 0; i < SIZE; i++)
  {
    cout << setw(20) << left << P[i].Name << "      " << fixed << setprecision(2) << setw(8) << right << P[i].balance << endl;
  }
  cout << "-----------------------------------" << endl;
}



void newCopy(string fileName, PERSON P[], int SIZE)
{
  ofstream outFile;
  outFile.open(fileName);

  for(int i = 0; i < SIZE; i++)
  {
    outFile << P[i].Name << " " << fixed << setprecision(2) << P[i].balance << endl;
  }

  outFile.close();
}



PERSON * readData(PERSON P[], int & N)
{
  PERSON * tempPtr;

  ifstream inFile;
  inFile.open("data.txt");

  // traverse the array, create new person, read data, store data
  for(int i = 0; i < N; i++)
  {
    string fName;
    string lName;
    string fullName;

    // read name to local members, read balance to struct, then copy name to struct
    inFile >> fName >> lName >> P[i].balance;
    fullName = fName + " " + lName;
    strcpy(P[i].Name, fullName.c_str());
  }
  inFile.close();

  return P;
}



void countRecords(int &numRecords)
{
  // open the data file and read the number of records (1 records per line)
  string line;
  ifstream inFile;

  inFile.open("data.txt");

  if(inFile.is_open())
  {
    cout << "File opened successfully\n" << endl;
  }
    // determine number of records
  while(getline(inFile, line))
  {
    numRecords++;
  }

  numRecords--;
  inFile.close();
}



int main()
{
  string line;
  char custName[20];
  int numRecords = 0;

  // open data file and count records
    countRecords(numRecords);

    // create a dynamic array of type PERSON
    PERSON * P = new PERSON[numRecords];

    // pass array address into read function
    readData(P, numRecords);

    // display the array
    display(P, numRecords);

    // search the array to determine richest person
    findRichest(P, numRecords);

    cout << "Enter your full name to deposit money:" << endl;
    getline(cin, line);
    strcpy(custName, line.c_str());

    deposit(custName, P, numRecords);

    // update the input file with new balance
    newCopy("data.txt", P, numRecords);

  return 0;
}
