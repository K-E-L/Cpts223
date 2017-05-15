#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <iostream>    // For NULL
#include <queue>  // For level order printout
#include <vector>
#include <algorithm> // For max() function
using namespace std;

// AvlTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (null == -1)
// void insert( x )       --> Insert x
// void insert( vector<T> ) --> Insert whole vector of values
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted (in) order
// void printPreOrder( )  --> Print tree in pre order
// void printPostOrder( ) --> Print tree in post order
// void printInOrder( )   --> Print tree in *in* order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
 public:
 AvlTree( ) : root( NULL )
    { }

 AvlTree( const AvlTree & rhs ) : root( NULL )
    {
      *this = rhs;
      
      //root = clone(rhs.root);
    }

  ~AvlTree( )
    {
      makeEmpty();
    }  
  
  /**
   * Find the smallest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMin( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException( );
    return findMin( root )->element;
  }

  /**
   * Find the largest item in the tree.
   * Throw UnderflowException if empty.
   */
  const Comparable & findMax( ) const
  {
    if( isEmpty( ) )
      throw UnderflowException( );
    return findMax( root )->element;
  }

  /**
   * Returns true if x is found in the tree.
   */
  bool contains( const Comparable & x ) const
  {
    return contains( x, root );
  }

  /**
   * Test if the tree is logically empty.
   * Return true if empty, false otherwise.
   */
  bool isEmpty( ) const
  {
    if (root == nullptr) {
      return true;
    }

    else {
      return false;
    }
  }

  /**
   * Return number of elements in tree.
   */
  int size( )
  {
    int count = 0;
    count = size( root, count ); 
    
    return count; 
  }

  /**
   * Return height of tree.
   *  Null nodes are height -1
   */
  int height( )
  {
    return height( root );
  }

  /**
   * Print the tree contents in sorted order.
   */
  void printTree( ) const
  {
    if( isEmpty( ) )
      cout << "Empty tree" << endl;
    else
      printInOrder( root );
  }

  /**
   * Print the tree contents in sorted order.
   */
  void printInOrder( ) const
  {
    if( isEmpty( ) )
      cout << "Empty tree" << endl;
    else
      printInOrder( root );
  }

  /**
   * Print the tree contents in pre order.
   */
  void printPreOrder( ) const
  {
    if( isEmpty( ) )
      cout << "Empty tree" << endl;
    else
      printPreOrder( root );
  }

  /**
   * Print the tree contents in post order.
   */
  void printPostOrder( ) const
  {
    if( isEmpty( ) )
      cout << "Empty tree" << endl;
    else
      printPostOrder( root );
  }

  /**
   * Make the tree logically empty.
   */
  void makeEmpty( )
  {
    makeEmpty( root );
  }

  /**
   * Insert x into the tree; duplicates are ignored.
   */
  void insert( const Comparable & x )
  {
    insert( x, root );
  }

  /**
   * Insert vector of x's into the tree; duplicates are ignored.
   */
  void insert( vector<Comparable> vals)
  {
    for( auto x : vals ) {
      insert( x, root );
    }
  }
     

  /**
   * Remove x from the tree. Nothing is done if x is not found.
   */
  void remove( const Comparable & x )
  {
    remove( x, root);
  }


  /**
   * Deep copy. - or copy assignment operator
   *  Will be in part II
   */
  const AvlTree & operator=( const AvlTree & rhs )
    {
      cout << " [!] Copy *assignment* operator called." << endl;
      return *this;
    }


  /*****************************************************************************/
 private:
  struct AvlNode
  {
    Comparable element;
    AvlNode   *left;
    AvlNode   *right;
    int       height;

  AvlNode( const Comparable & theElement, AvlNode *lt,
	   AvlNode *rt, int h = 0 )
  : element( theElement ), left( lt ), right( rt ), height( h ) { }
  };

  void remove( const Comparable & x, AvlNode *& t)
  {
    if (t == nullptr)
      return;

    if (x < t->element)
      remove(x, t->left);
    
    else if (t->element < x)
      remove(x, t->right);

    else if (t->left != nullptr && t->right != nullptr) {
      t->element = findMin(t->right)->element;
      remove(t->element, t->right);
    }

    else {
      AvlNode *oldNode = t;
      t = (t->left != nullptr) ? t->left : t->right;
      delete oldNode;
    }

    balance(t);
  }

  AvlNode *root;

  /**
   * Internal method to count nodes in tree
   */
  int size( AvlNode * & t, int & count )
  {
    if (t != nullptr) {
      size(t->left, count);
      count++;
      size(t->right, count);
    }

    return count;
  }

  /**
   * Internal method to insert into a subtree.
   * x is the item to insert.
   * t is the node that roots the subtree.
   * Set the new root of the subtree.
   */

  void insert( const Comparable & x, AvlNode * & t )
  {
    if (t == nullptr)
      t = new AvlNode{ x, nullptr, nullptr};

    else if (x < t->element)
      insert(x, t->left);

    else if (t->element < x)
      insert(x, t->right);

    else
      cout << "Tried to insert a duplicate" << endl;

    balance(t);
  }

  /**
   * Internal method to find the smallest item in a subtree t.
   * Return node containing the smallest item.
   *  You'll need this for deletes
   */

  AvlNode * findMin( AvlNode *t ) const
  {
    if (t == nullptr)
      return nullptr;

    if (t->left == nullptr)
      return t;

    return findMin(t->left);
  }

  /**
   * Internal method to find the largest item in a subtree t.
   * Return node containing the largest item.
   */

  AvlNode * findMax( AvlNode *t ) const
  {
    if (t != nullptr)
      while (t->right != nullptr)
	t = t->right;

    return t;
  }


  /**
   * Internal method to test if an item is in a subtree.
   * x is item to search for.
   * t is the node that roots the tree.
   */

  bool contains( const Comparable & x, AvlNode *t ) const
  {
    if(t == nullptr)
      return false;
    else if (x < t->element)
      return contains(x, t->left);
    else if (t->element < x)
      return contains(x, t->right);
    else
      return true;
  }

  /******************************************************/

  /**
   * Internal method make subtree empty.
   * 
   */

  void makeEmpty( AvlNode * & t )
  {
    if (t != nullptr) {
      makeEmpty(t->left);
      makeEmpty(t->right);
      delete t;
    }
    t = nullptr;
  }

  /**
   * Internal method to print a subtree rooted at t in sorted order.
   */

  void printInOrder( AvlNode *t ) const
  {
    if (t != nullptr) {
      printInOrder(t->left);
      cout << t->element << " ";
      printInOrder(t->right);
    }
  }

  /**
   * Internal method to print a subtree rooted at t in pre order.
   */

  void printPreOrder( AvlNode *t ) const
  {
    if (t != nullptr) {
      cout << t->element << " ";
      printPreOrder(t->left);
      printPreOrder(t->right);
    }
  }

  /**
   * Internal method to print a subtree rooted at t in post order.
   */
  void printPostOrder( AvlNode *t ) const
  {
    if (t != nullptr) {
      printPostOrder(t->left);
      printPostOrder(t->right);
      cout << t->element << " ";
    }
  }

  /**
   * Internal method to clone subtree.
   */
  AvlNode * clone( AvlNode *t ) const
  {
    if( t == NULL )
      return NULL;
    else
      return new AvlNode( t->element, clone( t->left ), clone( t->right ), t->height );
  }

  /**
   * Return the height of node t or -1 if NULL.
   */

  int height( AvlNode *t ) const
  {
    return t == nullptr ? -1 : t->height;
  }

  int max( int lhs, int rhs ) const
  {
    return lhs > rhs ? lhs : rhs;
  }

  static const int ALLOWED_IMBALANCE = 1;

  void balance(AvlNode *& t)
  {
    if (t == nullptr)
      return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
      if (height(t->left->left) >= height(t->left->right))
	rotateWithLeftChild(t);
      else
	doubleWithLeftChild(t);

    else
      if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
	if(height(t->right->right) >= height(t->right->left))
	  rotateWithRightChild(t);
	else
	  doubleWithRightChild(t);

    t->height = max(height(t->left), height(t->right)) + 1;
  }
  
  /**
   * Rotate binary tree node with left child.
   * For AVL trees, this is a single rotation for case 1.
   * Update heights, then set new root.
   */

  void rotateWithLeftChild( AvlNode * & k2 )
  {
    AvlNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
  }

  /**
   * Rotate binary tree node with right child.
   * For AVL trees, this is a single rotation for case 4.
   * Update heights, then set new root.
   */

  void rotateWithRightChild( AvlNode * & k1 )
  {
    AvlNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
  }

  /**
   * Double rotate binary tree node: first left child.
   * with its right child; then node k3 with new left child.
   * For AVL trees, this is a double rotation for case 2.
   * Update heights, then set new root.
   */

  void doubleWithLeftChild( AvlNode * & k3 )
  {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
  }

  /**
   * Double rotate binary tree node: first right child.
   * with its left child; then node k1 with new right child.
   * For AVL trees, this is a double rotation for case 3.
   * Update heights, then set new root.
   */

  void doubleWithRightChild( AvlNode * & k1 )
  {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
  }
};

#endif
