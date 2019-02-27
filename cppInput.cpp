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



void readArray(PERSON p[], int SIZE)
{
  ifstream inFile;
  inFile.open("data.txt");

  // traverse the array, create new person, read data, store data
  for(int i = 0; i < SIZE; i++)
  {
    string fName;
    string lName;
    string fullName;

    // read name to local members, read balance to struct, then copy name to struct
    inFile >> fName >> lName >> p[i].balance;
    fullName = fName + " " + lName;
    strcpy(p[i].Name, fullName.c_str());
  }
  inFile.close();
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


int main()
{
  ifstream inFile;
  char custName[20];
  string line;
  int numRecords = 0;
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
    inFile.close();

    // create array of type PERSON
    PERSON P[numRecords];

    readArray(P, numRecords);
    display(P, numRecords);
    findRichest(P, numRecords);

    cout << "Enter your full name to deposit money:" << endl;
    getline(cin, line);
    strcpy(custName, line.c_str());
    deposit(custName, P, numRecords);

    newCopy("data.txt", P, numRecords);

  return 0;
}
