//
//  main.cpp
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

#include "HashStruc.h" // the header file of hash function

int main()
{
  Hash hashtable(811,0.8); // create a new table

  int menuChoice = 0;
    
  cout<<"Enter keys manually or randomly?\n1: Manually\n2: Randomly\n";
  while(menuChoice!=1 && menuChoice!=2)
  {
	  cin>>menuChoice;
  }
  if(menuChoice==1)
		hashtable.manualCreate();
  else  hashtable.randomCreate();

  while(menuChoice>0 && menuChoice<6)
    {
      cout<<"\nWhat do you want to do?\n"
	  <<"1: Display Linear Hashing Table\n"
	  <<"2: Display Double Hashing Table\n"
	  <<"3: Display Quadratic Hashing Table\n"
	  <<"4: Display Separate Chaining Hashing Table\n"
	  <<"5: Display Statiscs\n"
	  <<"6: End\n";
      cin>>menuChoice;
      switch(menuChoice)
	{
	case 1:
	  hashtable.displayLinear();
	  break;
	case 2:
	  hashtable.displayDouble();
	  break;
	case 3:
	  hashtable.displayQuadratic();
	  break;
	case 4:
	  hashtable.displaySeparate();
	  break;
	case 5:
	  hashtable.findStatistics();
	  hashtable.displayStatistics();
	  break;
	}
    }

  return 0;
}
