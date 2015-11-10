//
//  Hash.cpp
//  HashTable_Array
//
//  Created by Yue Zhao on 11/9/15.
//  Copyright © 2015 Yue Zhao. All rights reserved.
//
//  the main purpose of this program is to show the comparision
//  among different collision algorithm
/****************************************************************************
 date     : Nov 29 2011,
 coplier  : GCC
 software : Xcode 7.1
 Author   : Yue Zhao
 
 description: Implement a hash table using an array that contains prime(by default 811) elements.
 each element contains only an integer, and the integer is also the key for this element.
 The hashtable is constructed manually or randomly.
 That is, the user could insert the numbers to the hash table.
 
 The program will stop in part 1 when the load ratio is exceeded.
 Use linear probing, double hash, quadratic hash and seperate chaining
 as the collision-resolution scheme.
 
 Then analyze the efficiency through comparing the different times
 of comparisions of different strategies.
 
 ****************************************************************************/


#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include "HashStruc.h"

//create the object with no comparisons and no elements,
//an arraySize of 811, loadlimit 80%
Hash::Hash()

{
    arraySize = 811; // set arraysize
    desiredLoad = 0.8;
    initialization();
}

Hash::Hash(int size, double loadRatio)
{
    arraySize = size;
    desiredLoad = loadRatio;
    initialization();
}

void Hash::initialization()
{
    elements = 0;
    hash2seed = randomPrime();
    for(int i=0; i<4; i++)
    {
        comparisons[i]=0; // set to "0"
    }
    
    linearArray.clear();
    doubleArray.clear();
    quadraticArray.clear();
    separateArray.clear();

    linearArray.resize(arraySize);
    doubleArray.resize(arraySize);
    quadraticArray.resize(arraySize);
    separateArray.resize(arraySize);
    
    
    for(int i=0; i<arraySize; i++) // this loop sets all initial values to -1
    {
        linearArray[i] = -1;
        quadraticArray[i] = -1;
        doubleArray[i] = -1;
        separateArray[i].number = -1;
    }
}

void Hash::manualCreate()
  //this function was used in Part 1
{
    cout<<"\n";
    while((static_cast<double>(elements)/static_cast<double>(arraySize))<desiredLoad)
    {
        int tempnNum;
        cout << "Please enter an element (enter -1 to switch to random and -2 to stop).\n";
        cin >> tempnNum;
        if(tempnNum != -1 && tempnNum != -2) // use four different methods to hash
        {
            linearHash(tempnNum);
            doubleHash(tempnNum);
            quadraticHash(tempnNum);
            separateHash(tempnNum);
            elements++;
        }
        else if (tempnNum == -1)
        {
            randomCreate(); // otherwise, randomGenerate
        }
        else
        {
            break;
        }
    }
}


// insert values to different hashtable until it reaches the limit
// randomly insert items into the arrays
// clear the array first
void Hash::randomCreate()
{
    initialization();
    srand(static_cast<unsigned>(time(0)));
    for(int i=0; i<arraySize && (static_cast<double>(elements)/static_cast<double>(arraySize))<desiredLoad; i++)
    {
        int randInt=rand()% 10000; // randomly generate the numbers
        linearHash(randInt);
        doubleHash(randInt);
        quadraticHash(randInt);
        separateHash(randInt);
        elements++;
    }
    return;
}

// linear hash--linear probing method
// insert the element into the array using linear probing
void Hash::linearHash(int key)

{
    int address = key % arraySize;
    comparisons[0]++; // increment comparisions
    while(true)
    {
        if(linearArray[address] == -1)
        {
            linearArray[address] = key;
            break;
        }
        else
        {
            address++; // move one position down
            if(address == arraySize - 1) // wrap back to Array[0]
            {
                address = 0;
            }
            comparisons[0]++; // collision happens
        }
    }

}

// double hash method
// insert using double hashing
void Hash::doubleHash(int key)
{
    int key2, address, addressTemp;
    address = key % arraySize;
    
    key2 = hash2seed - key % hash2seed + 1; // second key - non zero
    comparisons[1]++;
    addressTemp = address;

    for (int i=1; i < arraySize; i++) // unseccessful insertion when comparisons exceed the arraysize
    {
        if(doubleArray[addressTemp] == -1)
        {
            doubleArray[addressTemp] = key;
            break;
        }
        else
        {
            addressTemp = address + i * key2; // second hash
            comparisons[1]++;
            while(addressTemp >= arraySize ) // wrap back
            {
                addressTemp = addressTemp - arraySize;
            }
        }
    }
}

// quadratic hash method
// insert using quadratic probing
void Hash::quadraticHash(int key)
{
    int address, addressTemp;
    address = key % arraySize;
    comparisons[2]++;
    addressTemp = address;

    for (int i=1; i<arraySize; i++)
    {
        if(quadraticArray[addressTemp] == -1)
        {
            quadraticArray[addressTemp] = key;
        
            break;
        }
        else
        {
            addressTemp = address + i * i; // after each time comparisons, plus square
            comparisons[2]++;
            while(addressTemp >= arraySize ) // wrap back
        {
            addressTemp = addressTemp - arraySize;}
        }
    }

}
// seperate chaining
// insert using separate chaining
void Hash::separateHash(int key)
{
    int address;
    Node* temp = new Node;
    Node* store = new Node;
    comparisons[3]++; // increment the comparision
    address = key % arraySize;
    store->number = key;
    store->next = NULL; // create a node for this
    if(separateArray[address].number == -1)
    {
        separateArray[address].number = key;
    }

    else
    {
        temp = &(separateArray[address]); // find the linked list
        while(temp->next!= NULL)
        {
            temp = temp->next;
            comparisons[3]++;
        }
        temp->next = store; // insert the data
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


//display the linear array
void Hash::displayLinear()
{
    cout<<"\n";
    for(int i=0; i<arraySize; i++)
    {
        cout<<i+1<<": ";
        if(linearArray[i]!=-1)
        {
            cout<<linearArray[i]<<"\n";
        }
        else cout<<"\n";
    }

    return;
}

//display the double hash array
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

//display the quadratic hash array
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
        {
            cout<<i+1<<": ";
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

//the is the control function, using the other
//main functions to find statistics on them
void Hash::findStatistics()
{
    desiredLoad = 0;
    for(int i=0; i<4; i++)
    {
        desiredLoad = desiredLoad+0.2;
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

// this function could generate psuedo random prime number
// for double hashing function as the second key
int Hash::randomPrime()
{
    while(true)
    {
        int r = rand()%100;
        int x = 0;
        for(int i = 2; i < r; i++)
        {
            if(r%i ==0)
                break;
            else
                x++;
        }
        if(x == r-2)
            return r;
    }
}
