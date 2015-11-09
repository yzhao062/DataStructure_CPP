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

#include "Hash.cpp" // the head file

int main()
{
  Hash table; // create a new table

  int answer=0;
  cout<<"\nWhat is the desired decimal value for load ratio?\n";

  cin>>table.desiredLoad;
  cout<<"Enter keys manually or randomly?\n1: Manually\n2: Randomly\n";
  while(answer!=1 && answer!=2)
  {
	  cin>>answer;
  }
  if(answer==1)
		table.manualCreate();
  else  table.randomCreate();

  while(answer>0 && answer<6)
    {
      cout<<"\nWhat do you want to do?\n"
	  <<"1: Display Linear Hashing Table\n"
	  <<"2: Display Double Hashing Table\n"
	  <<"3: Display Quadratic Hashing Table\n"
	  <<"4: Display Separate Chaining Hashing Table\n"
	  <<"5: Display Statiscs\n"
	  <<"6: End\n";
      cin>>answer;
      switch(answer)
	{
	case 1:
	  table.displayLinear();
	  break;
	case 2:
	  table.displayDouble();
	  break;
	case 3:
	  table.displayQuadratic();
	  break;
	case 4:
	  table.displaySeparate();
	  break;
	case 5:
	  table.findStatistics();
	  table.displayStatistics();
	  break;
	}
    }

  return 0;
}
