//
//  HashStruc.h
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
#ifndef HashStruc_h
#define HashStruc_h

#include <iostream>
#include <vector>
using namespace std;

// structure for seperate chain algorithm
struct Node
{
    int number = -1;
    Node* next;
};


class Hash
{
public:
    Hash();
    Hash(int,double);
    void initialization();
    void manualCreate();
    void randomCreate();
    
    int randomPrime();
    // four collision algrithms
    void doubleHash(int);
    void linearHash(int);
    void quadraticHash(int);
    void separateHash(int); // seperate chain
    
    // display functions
    void displayLinear();
    void displayDouble();
    void displayQuadratic();
    void displaySeparate();
    
    // show the statistics
    void findStatistics();
    void displayStatistics();
    
    // statistics for four different methods
    double averageLinear();
    double averageQuadratic();
    double averageDouble();
    double averageSeparate();
    
    

    
    /* a table is made for statistics, using:
     linear	double	quadratic	separate
     20%
     40%11
     60%
     80%
     to line the outside.
     */
    // double Array for displaying the statistics
    
private:
    // desire loadRatio
    double desiredLoad; // the threshold of the percentage in the hashtable
    int arraySize; // size of the hash table
    double elements;
    int hash2seed;
    
    double statistics[4][4];
    double comparisons[4];
    // comparisions[1] - linear hash
    // comparisions[2] - double hash
    // comparisions[3] - quadratic hash
    // comparisions[4] - seperate chain

    
    vector<int> linearArray;
    vector<int> quadraticArray;
    vector<int> doubleArray;
    vector<Node> separateArray;
    
};

#endif /* HashStruc_h */
