/*
 *  AvlTreeTesting.h - Testing our AVL implementation
 *   Aaron Crandall - 2017
 */


#include "AvlTree.h"
#include <iostream>
#include <string.h>


/*****************************************************************************/
// Do lots of random inserts and deletes. This is a fuzzing test
void test_BigTreeFuzzing() {
  /* BIGGER test of your AVL tree! */
	cout << "  [t] Big Tree Fuzzing test."; 
  vector<int> incVals;
  AvlTree<int> bigTree;
  srand (time(NULL));
  for( int i = 0; i < 3000; i++ ) {
    int newVal = rand() % 900000; // Generate new integer to insert into tree
    bool skip = false;
    for( int j = 0; j < incVals.size(); j++ ){ // Very dumb search!
      if( incVals[j] == newVal ){
        skip = true;
        j = incVals.size();
      }
    }
    if( !skip ){
      bigTree.insert(newVal);
      incVals.push_back(newVal);
    }

    if( i % 3 == 0 ){   // Delete a random element every 3 inserts
      int remIndex = rand() % incVals.size();
      bigTree.remove( incVals[remIndex] );
      incVals.erase(incVals.begin() + remIndex);
    }
  }
	cout << " - fuzzing test complete. " << endl;
}


void test_empty() {
  AvlTree<int> myTree;
	cout << "  [t] Testing empty() interface";
	if( myTree.empty() ) {
		cout << " - Pass" << endl;
	} else {
		cout << " - Fail" << endl;
	}
}


void test_size() {
	AvlTree<int> myTree;
	cout << "  [t] Testing size() interface..." << endl;;
	cout << "   [t] size() when empty: " << myTree.size() << " - ";
	(myTree.size() == 0) ? cout << "Pass" : cout << "Fail";
	cout << endl;

	vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
	myTree.insert( vals ); 
	cout << "   [t] size() with " << vals.size() << " values: " << myTree.size() << " - ";
	(vals.size() == myTree.size()) ? cout << "Pass" : cout << "Fail";
	cout << endl;

	myTree.remove( 10 );    // Remove the root, what about now?
	cout << "   [t] size() with " << vals.size() - 1<< " values: " << myTree.size() << " - ";
	(vals.size() - 1  == myTree.size()) ? cout << "Pass" : cout << "Fail";
	cout << endl;
}


void test_height() {
	AvlTree<int> myTree;
	vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
	cout << "  [t] Testing tree heights" << endl;
	cout << "   [t] Height of empty: " << myTree.height() << " - ";
	(myTree.height() == -1) ? cout << "Pass" : cout << "Fail";    cout << endl;

	myTree.insert(vals);
	cout << "   [t] Height of filled (3): " << myTree.height() << " - ";
	(myTree.height() == 3) ? cout << "Pass" : cout << "Fail";    cout << endl;
}

/*
 *  Test printing tree in pre-, post-, and in- orders
 */
void test_prints() {
	AvlTree<int> myTree;
	vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
	myTree.insert(vals);
	cout << "  [t] Testing tree print orders: " << endl;

	cout << "   [t] In Order Target: \t1 3 5 7 10 23 30" << endl;
  cout << "   [x] Tree In- Output: \t";
	myTree.printInOrder();
	cout << endl;

	cout << "   [t] Pre Order Target:\t10 5 3 1 7 23 30" << endl;
  cout << "   [x] Tree Pre- Output:\t";
	myTree.printPreOrder();
	cout << endl;

	cout << "   [t] Post Order Target:\t1 3 7 5 30 23 10" << endl;
  cout << "   [x] Tree Post- Output:\t";
	myTree.printPostOrder();
	cout << endl;
}


void test_insert()
{
	AvlTree<int> myTree;
	cout << "  [t] Testing tree basic inserts: " << endl;
	myTree.insert(20);
	myTree.insert(10);
	myTree.insert(5);      // Forces right rotate
	cout << "   [t] Should be: \t10 5 20" << endl;
	cout << "   [t] Pre Order: \t";
	myTree.printPreOrder();
	cout << endl;

  myTree.insert(30);
  myTree.insert(40);     // Forces left rotate
	cout << "   [t] Should be: \t10 5 30 20 40" << endl;
	cout << "   [t] Pre Order: \t";
	myTree.printPreOrder();
	cout << endl;

  myTree.insert(15);     // Forces Right-Left double rotate
	cout << "   [t] Should be: \t20 10 5 15 30 40" << endl;
	cout << "   [t] Pre Order: \t";
	myTree.printPreOrder();
	cout << endl;

	myTree.insert(13);
	myTree.insert(14);     // Forces Left-Right double rotate
	cout << "   [t] Should be: \t20 10 5 14 13 15 30 40" << endl;
	cout << "   [t] Pre Order: \t";
	myTree.printPreOrder();
	cout << endl;
}


void test_contains() {
	AvlTree<int> myTree;
	vector<int> vals = { 10, 5, 23, 3, 7, 30, 1 };   // Give us some data!
	myTree.insert( vals );
	cout << "  [t] Testing contains:" << endl;
	cout << "   [t] Searching for: 7 (is in tree)";
	(myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

	cout << "   [t] Searching for: 15 (not in tree)";
	(!myTree.contains(15)) ? cout << " - pass" : cout << " - fail"; cout << endl;
}

/**
 *  Testing the remove() function
 */
void test_remove() {
	AvlTree<int> myTree{ vector<int>{ 20, 10, 30, 5, 15, 25, 35, 1, 7, 13, 28, 3 } };
	cout << "  [t] Testing remove():" << endl;
	cout << "   [x] Searching for: 7 (is in tree)";
	(myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

	cout << "   [t] Pre order tree:   "; myTree.printPreOrder(); cout << endl;

	cout << "   [t] Removing 7 from tree. " << endl;
	myTree.remove(7);

	cout << "   [x] Searching for: 7 (is not in tree)";
	(!myTree.contains(7)) ? cout << " - pass" : cout << " - fail"; cout << endl;

	cout << "   [t] Pre order target: 20 10 3 1 5 15 13 30 25 28 35" << endl;
	cout << "   [x] Pre order tree:   "; myTree.printPreOrder(); cout << endl;

	cout << "   [t] Removing 20 from tree. " << endl;
	myTree.remove(20);
	cout << "   [t] Pre order target: 25 10 3 1 5 15 13 30 28 35" << endl;
	cout << "   [x] Pre order tree:   "; myTree.printPreOrder(); cout << endl;

	cout << "   [t] Removing 30 and 28 from tree. " << endl;
	myTree.remove(30);
	myTree.remove(28);
	cout << "   [t] Pre order target: 10 3 1 5 25 15 13 35" << endl;
	cout << "   [x] Pre order tree:   "; myTree.printPreOrder(); cout << endl;
}


/**
 *  Testing the copy constructor
 */
void test_copy_constructor() {
	AvlTree<int> myTree{ vector<int>{ 10, 5, 23, 3, 7, 30, 1 } };
	cout << "  [t] Testing copy constructor:" << endl;
  AvlTree<int> treeCopy{ myTree };   // Calls copy constructor

  cout << "   [x] Source tree pre order: ";
  myTree.printPreOrder();
  cout << endl;
  cout << "   [x] Tree COPY pre order:   ";
  treeCopy.printPreOrder();
  cout << endl;
}

/**
 *  Testing the move constructor
 */
void test_move_constructor() {
	AvlTree<int> myTree{ vector<int>{ 10, 5, 23, 3, 7, 30, 1 } };
	cout << "  [t] Testing move constructor:" << endl;
  cout << "   [x] Source tree pre order (before move): ";
  myTree.printPreOrder();
  cout << endl;

  AvlTree<int> treeMove = std::move( myTree ); // Calls move constructor

  cout << "   [x] Source tree pre order (after move):  ";
  myTree.printPreOrder();
  cout << endl;

  cout << "   [x] Tree MOVE pre order:                 ";
  treeMove.printPreOrder();
  cout << endl;
}

/*
 *  Testing the copy *assignment* operator (copy=)
 */
void test_copy_assignment_op()
{
	AvlTree<int> myTree{ vector<int>{ 10, 5, 23, 3, 7, 30, 1 } };
	cout << "  [t] Testing copy assignment operator:" << endl;
	AvlTree<int> copy2;
  copy2 = myTree;      // Calls copy assignment operator
  cout << "   [x] Source tree pre order: ";
  myTree.printPreOrder();
  cout << endl;
  cout << "   [x] Dest tree pre order:   ";
  copy2.printPreOrder();
  cout << endl;
}

/*
 *  Testing the move *assignment* operator (move=)
 */
void test_move_assignment_op() {
	vector<int> vals = { 10, 5, 23, 3, 7, 30, 22 };   // Give us some data!
	cout << "  [t] Testing move assignment operator:" << endl;

  AvlTree<int> treeMove;
  treeMove = AvlTree<int>{ vals }; // Calls move assignment operator
  cout << "   [x] Temp tree (rval) data (rotated):  10 5 3 7 23 22 30" << endl;;

  cout << "   [x] New tree pre order (after move=): ";
  treeMove.printPreOrder();
  cout << endl;
}

/*
 *  Print tree out in level order. Tree should be:
 *                20
 *         10            30
 *    5        15     25     35
 *  3   7        18     28
 * 1
 */
void test_print_level_order()
{
	AvlTree<int> myTree{ vector<int>{ 20, 10, 30, 5, 15, 25, 35, 3, 7, 18, 28, 1 } };
	cout << "  [t] Testing printing in level order:" << endl;
  cout << "   [t] Level Should be:   20 10 30 5 15 25 35 3 7 18 28 1" << endl;
	cout << "   [x] Print Level Order: ";
	myTree.printLevelOrder();
	cout << endl;
}


/*
 *  Testing features of your AVL Tree implementation
 */
int avlTreeTests( bool fuzzing )
{
  cout << " [x] Starting AVL tree test. " << endl;
	test_empty();            // empty() interface working?
	test_size();             // size() interface working properly?
	test_height();           // height() working properly?
	test_prints();           // Print: preorder, postorder, inorder, levelorder
	test_insert();           // Insert test - all 4 types of rotates
	test_contains();         // Testing contains interface
	test_remove();           // Test of removing nodes via remove()
	if( fuzzing ) test_BigTreeFuzzing();   //Big tree fuzzing test

	cout << " [x] Starting PART II tree tests. ----------------" << endl;
	test_copy_constructor(); // Copy constructor tests
	test_move_constructor(); // Move constructor tests
  test_copy_assignment_op(); // Copy= operator tests
  test_move_assignment_op(); // Move= operator tests
	test_print_level_order();  // Print tree in LEVEL order

	return(0);
}
