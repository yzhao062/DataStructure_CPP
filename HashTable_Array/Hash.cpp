/****************************************************************************

 date     : Nov 29 2011,
 coplier  : GCC
 software : Xcode 4.2 & Codeblocks 10.5
 Author   : Yue Zhao

 description: Implement a hash table using an array that contains 1009 (prime) elements. 
              each element contains only an integer, and the integer is also the key for this element. 
              Also, allow the user to input (i.e., insert) the numbers to the hash table. 
              the program will stop in part 1 when the load ratio is exceeded. 
              Use linear probing, double hash, quadratic hash and seperate chaining 
              as the collision-resolution scheme.

              Then analyze the efficiency through comparing the different times of comparisions of different strategies.

 ***************************************************************************/


#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include "Hash.h"

Hash::Hash()
  //create the object with no comparisons and no elements,
  //an arraySize of 11
{
  for(int i=0; i<4; i++)
  comparisons[i]=0; // set to "0"
  elements=0;
  arraySize=811; // set arraysize
  for(int i=0; i<arraySize; i++) // this loop sets all initial values to -1
  {
   linearArray[i] = -1;
   quadraticArray[i] = -1;
   doubleArray[i] = -1;
   separateArray[i].number = -1;
   separateArray[i].next = NULL;
  }

}

void Hash::manualCreate()
  //this function was used in Part 1
{
  cout<<"\n";
  while((static_cast<double>(elements)/static_cast<double>(arraySize))<desiredLoad)
    {
      int element;
      cout<<"Please enter an element (enter -1 to switch to random).\n";
      cin>>element;
      if(element!=-1) // use four different methods to hash
	{
	  linearHash(element);
     doubleHash(element);
	 quadraticHash(element);
      separateHash(element);
	  elements++;
	}
      else randomCreate(); // otherwise, randomGenerate
   }
}



void Hash::randomCreate()
  //randomly insert items into the arrays
  //first clear the arrays, reset elements and comparisons
{

  srand(static_cast<unsigned>(time(0)));

  for(int i=0; i<arraySize && (static_cast<double>(elements)/static_cast<double>(arraySize))<desiredLoad; i++)
    {
      int randInt=rand(); // randomly generate the numbers
      linearHash(randInt);
      doubleHash(randInt);
      quadraticHash(randInt);
      separateHash(randInt);
      elements++;
    }
  return;
}

/*linear hash--linear probing method*/
void Hash::linearHash(int key)
  //insert the element into the array using linear probing
{
    int address;
    address = key % arraySize;
    comparisons[0]++; // increment comparisions
     for (int i=1; i<arraySize; i++)
    {
    if(linearArray[address] == -1)
       {linearArray[address] = key;
       break;}
    else
    {
    address++;
    if(address == arraySize-1) // wrap back to Array[0]
    {address = 0;}
    comparisons[0]++;
   }
   }

}

/*double hash method*/
void Hash::doubleHash(int key)
  //insert using double hashing
{
   int address, key2, addressTemp;
   address = key % arraySize;
   key2 = 50 - key % 50; // second key
   comparisons[1]++;
   addressTemp = address;

  for (int i=1; i<arraySize; i++) // unseccessful insertion when comparisons exceed the arraysize
  {
     if(doubleArray[addressTemp] == -1)
      { doubleArray[addressTemp] = key;
      break;
      }
    else
    {
     addressTemp = address + i*key2; // second hash
     comparisons[1]++;
     while(addressTemp >= arraySize ) // wrap back
     {addressTemp = addressTemp - arraySize;}
    }
  }
}

/*quadratic hash method*/
void Hash::quadraticHash(int key)
  //insert using quadratic probing
{
    int address, addressTemp;
    address = key % arraySize;
    comparisons[2]++;
    addressTemp = address;

  for (int i=1; i<arraySize; i++)
  {
     if(quadraticArray[addressTemp] == -1)
      {quadraticArray[addressTemp] = key;
      break;
      }
    else
    {
     addressTemp = address + i*i; // after each time comparisons, plus square 
     comparisons[2]++;
     while(addressTemp >= arraySize ) // wrap back
     {addressTemp = addressTemp - arraySize;}
    }
  }

}
/*Seperate chaining*/
void Hash::separateHash(int key)
  //insert using separate chaining
{
  int address;
  Node* temp = new Node;
  Node* store = new Node;
  comparisons[3]++; // increment the comparision
  address = key % arraySize;
  store->number = key;
  store->next = NULL; // create a node for this
  if(separateArray[address].number == -1)
  {separateArray[address].number = key;}

  else
  {
   temp = &(separateArray[address]); // find the linked list
	while(temp->next!= NULL)
	{
	temp = temp->next;
	comparisons[3]++;
	}
	temp-> next = store; // insert the data
  }
}

double Hash::averageLinear()
{

  return (comparisons[0]/elements);
}

double Hash::averageDouble()
{
  return (comparisons[1]/elements);
}

double Hash::averageQuadratic()
{
  return (comparisons[2]/elements);
}

double Hash::averageSeparate()
{
  return (comparisons[3]/elements);
}



void Hash::displayLinear()
  //display the linear array
{
  cout<<"\n";
  for(int i=0; i<arraySize; i++)
    {
      cout<<i+1<<": ";
      if(linearArray[i]!=-1)
	cout<<linearArray[i]<<"\n";
      else cout<<"\n";
    }

  return;
}

void Hash::displayDouble()
{
  cout<<"\n";
  for(int i=0; i<arraySize; i++)
    {
      cout<<i+1<<": ";
      if(doubleArray[i]==-1)
	cout<<" \n";
      else
	cout<<doubleArray[i]<<"\n";
    }

  return;
}

void Hash::displayQuadratic()
{
  cout<<"\n";
  for(int i=0; i<arraySize; i++)
    {
      cout<<i+1<<": ";
      if(quadraticArray[i]==-1)
	cout<<"\n";
      else
	cout<<quadraticArray[i]<<"\n";
    }

  return;
}

void Hash::displaySeparate()
{
  Node* temp = new Node; // temp node
  cout<<"\n";
  for(int i=0; i<arraySize; i++)
{
    if(separateArray[i].number == -1) // no data inserted, skip
    {cout<<i+1<<": ";
     cout<<"\n";
     }
    else

    {
     temp = &(separateArray[i]);
     cout<<i+1<<": "; // display every data
     while(temp->next!=NULL)
    {
      cout<<temp->number<<" ";
      temp = temp->next;
    }
	 cout << temp->number; // display the data
	 cout<<"\n";
    }

}
  return;
}
void Hash::findStatistics()
  //the is the control function, using the other
  //main functions to find statistics on them
{
  desiredLoad=0;
  for(int i=0; i<4; i++)
    {
      desiredLoad= desiredLoad+0.2;
      randomCreate();
      statistics[i][0]=averageLinear();
      statistics[i][1]=averageDouble();
      statistics[i][2]=averageQuadratic();
      statistics[i][3]=averageSeparate();
    }

}

void Hash::displayStatistics()
  //displays the statistics in a table format
{
  cout<<"\nThe number displayed is the average number of comparisons"
      <<" per entry.\nLoad\tLinear\tDouble\tQuad\tSeparate";
  double tempLoad=0;
  for(int i=0; i<4; i++)
    {
      cout<<showpoint<<setprecision(2);
      tempLoad=tempLoad+20;
      cout<<"\n"<<tempLoad<<"%\t";
	  for(int n=0; n<4; n++)
	    cout<<statistics[i][n]<<"   "<<"\t";
    }
}
