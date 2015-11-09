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

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <iostream>

using namespace std;

// structure for seperate chain
struct Node
{
 int number;
 Node* next;
};


class Hash
{
 public:
  Hash();
  void manualCreate();
  void randomCreate();

// four collision solution
  void doubleHash(int);
  void linearHash(int);
  void quadraticHash(int);
  void separateHash(int);

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

// desire loadRatio
  double desiredLoad;
  int arraySize;
  double elements;
// delete arraySize is 1009
  int linearArray[811];
  int quadraticArray[811];
  int doubleArray[811];
  Node separateArray[811];

  /* a table is made for statistics, using:
	linear	double	quadratic	separate
20%
40%11
60%
80%
	 to line the outside.
  */
// double Array for displaying the statistics
  double statistics[4][4];
  double comparisons[4];
};

#endif // HASH_H_INCLUDED
