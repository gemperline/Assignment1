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



void deposit(char custName[20], PERSON P[],int SIZE, double amount)
{
  for(int i = 0; i < SIZE; i++)
  {
    // strcmp() will compare c_str types
    // function compares lhs with rhs
    // NOTE: strcmp() will return 0 if TRUE, 1 if FALSE
    if (strcmp(custName, P[i].Name) == 0)
    {
      P[i].balance += amount;
      cout << P[i].Name << "'s new balance is: " << fixed <<setprecision(2) << P[i].balance << endl;
    }
  }
}



void findRichest(PERSON P[],int SIZE)
{
  // variable to store ith place of richest
  int richest = 0;

  for(int i = 1; i < SIZE; i++)
  {
    if (P[richest].balance < P[i].balance)
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



PERSON * readData(PERSON P[], int N)
{
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

    fullName = fName.substr(0,8) + " " +  lName.substr(0,9);

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

    while(getline(inFile, line))
    {
      numRecords++;
    }
    inFile.close();
  }
  else
    cout << "ERROR: could not open file" << endl;
}



int main()
{
  string fname, lname, fullName;
  char custName[20];
  int numRecords = 0;
  double depositAmt;

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
    cin >> setw(9) >> fname;
    cin >> setw(10) >> lname;
    fullName = fname + " " + lname;

    // convert fullName string to custName c_string
    strcpy(custName, fullName.c_str());

    for(int i = 0; i < numRecords; i++)
    {
      // strcmp() will compare c_str types
      // function compares lhs with rhs
      // NOTE: strcmp() will return 0 if TRUE, 1 if FALSE
      if (strcmp(custName, P[i].Name) == 0)
      {
        cout << custName << ", how much would you like to deposit?" << endl;
        cin >> depositAmt;

        deposit(custName, P, numRecords, depositAmt);
      }
      else if (i == numRecords-1)
      {
        cout << "ERROR: name not found." << endl;
      }
    }

    // update the input file with new balance
    newCopy("data.txt", P, numRecords);

  delete [] PERSON;
  return 0;
}
