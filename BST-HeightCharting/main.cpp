/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 * Now also doing testing & height calculations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *  * Also doing height calculations
 *
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <cmath>
#include "BST.h"
#include "TestData.h"

using namespace std;

/*
 *  Interface to run all tests if --test is passed on command line
 */
void runTests() {
  cout << " [x] Running tests. " << endl;
  TestData *testing = new TestData();			// Create object with testing data and interfaces
  
  BST<int> *bst_test = new BST<int>;

	/* Should make a tree like this:
              10
         5          14
     1      7           17
                            19
                          18

   */
  int testval = testing->get_next_minitest();

  while( testval >= 0 ){
    bst_test->add( testval );
    testval = testing->get_next_minitest();
  }

  cout << " [x] Should print out in pre order: 10 5 1 7 14 17 19 18 " << endl;
  cout << " [x] Resulting print out test:      " << endl;
  bst_test->printPreOrder();
  cout << endl;

  cout << " [x] Should print a tree height of  : 5" << endl;
  cout << " [x] Currently calculating height of: ";
  cout << bst_test->height();
  cout << endl;
}


/*
 * Generate the CSV file for the project output here
 */
void genCSV() {
    
  ofstream mOutputData;

  mOutputData.open("OutputData-BST.csv", ios::in);
  
  BST<int> *bst_sorted = new BST<int>;
  BST<int> *bst_balanced = new BST<int>;
  BST<int> *bst_scrambled_0 = new BST<int>;
  BST<int> *bst_scrambled_1 = new BST<int>;
  BST<int> *bst_scrambled_2 = new BST<int>;
  BST<int> *bst_scrambled_3 = new BST<int>;
  BST<int> *bst_scrambled_4 = new BST<int>;

  int incr = 0;
  
  TestData *testing = new TestData();
  TestData *b_testing = new TestData();
  TestData *s0_testing = new TestData();
  TestData *s1_testing = new TestData();
  TestData *s2_testing = new TestData();
  TestData *s3_testing = new TestData();
  TestData *s4_testing = new TestData();

  int sorted = testing->get_next_sorted();
  int b_sorted = b_testing->get_next_balanced();
  int s0_sorted = s0_testing->get_next_scrambled(0);
  int s1_sorted = s1_testing->get_next_scrambled(1);
  int s2_sorted = s2_testing->get_next_scrambled(2);
  int s3_sorted = s3_testing->get_next_scrambled(3);
  int s4_sorted = s4_testing->get_next_scrambled(4);

  while (s0_sorted >= 0 &&
  	 s1_sorted >= 0 &&
  	 s2_sorted >= 0 &&
  	 s3_sorted >= 0 &&
  	 s4_sorted >= 0 &&
	 sorted >= 0 &&
  	 b_sorted >= 0)
    {

      if (s0_sorted >= 0)
	{
	  bst_scrambled_0->add(s0_sorted);
	  s0_sorted = s0_testing->get_next_scrambled(0);
	}
      

      if (s1_sorted >= 0)
	{
	  bst_scrambled_1->add(s1_sorted);
	  s1_sorted = s1_testing->get_next_scrambled(1);
	}
      
      if (s2_sorted >= 0)
	{
	  bst_scrambled_2->add(s2_sorted);
	  s2_sorted = s2_testing->get_next_scrambled(2);
	}
      
      if (s3_sorted >= 0)
	{
	  bst_scrambled_3->add(s3_sorted);
	  s3_sorted = s3_testing->get_next_scrambled(3);
	}
      
      if (s4_sorted >= 0)
	{
	  bst_scrambled_4->add(s4_sorted);
	  s4_sorted = s4_testing->get_next_scrambled(4);
	}
      
      if (b_sorted >= 0)
	{
	  bst_balanced->add(b_sorted);
	  b_sorted = b_testing->get_next_balanced();
	}
            
      if (sorted >= 0)
      	{
      	  bst_sorted->add(sorted);
      	  sorted = testing->get_next_sorted();
      	}

      incr++;
      
      mOutputData << bst_sorted->getNodeCount() << ","
		  << (int) log(incr) << ","
  		  << incr << "," // bst_sorted->height()
		  << bst_balanced->height() << ","
	
		  << bst_scrambled_0->height() << ","
		  << bst_scrambled_1->height() << ","
		  << bst_scrambled_2->height() << ","
		  << bst_scrambled_3->height() << ","
		  << bst_scrambled_4->height() << endl;
    }            

  cout << "Sorted height: " << bst_sorted->height() << endl;
  cout << "Balanced height: " << bst_balanced->height() << endl;
      
  cout << "Scrambled 0 height: " << bst_scrambled_0->height() << endl;

  cout << "Scrambled 1 height: " << bst_scrambled_1->height() << endl;
  cout << "Scrambled 2 height: " << bst_scrambled_2->height() << endl;
  cout << "Scrambled 3 height: " << bst_scrambled_3->height() << endl;
  cout << "Scrambled 4 height: " << bst_scrambled_4->height() << endl;
	  
  mOutputData.close();    
}

/*
 *   Main function for execution
 */
int main( int argc, char* argv[] ) {

  if( argc > 1 && !strcmp(argv[1], "--test") )
    {
      cout << " [x] Program in test mode, doing simple tests. " << endl;
      runTests();  // testing should just do a simple tree insert set and search
    }

  else
    {	
      cout << " [x] Program built and running in full CSV generation mode. " << endl;

      genCSV();
    }

  return 0;
}
