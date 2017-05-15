/*
 * Binary Search Tree implementation - heavily lifted from https://gist.github.com/mgechev/5911348
 *
 * Simple integer keys and basic operations
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 *
 */

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
using namespace std;

/*
 *  Node datastructure for single tree node
 */ 
template <class T>
struct Node {
  
public:
  Node(T newData, Node *newLeft = nullptr, Node *newRight = nullptr)
  {
    mData = newData;
    mpLeft = newLeft;
    mpRight = newRight;
  }
  ~Node()
  {
    //Inside Destructor
  }

  void setData(T newData)
  {
    mData = newData;
  }
  void setLeft(Node *newData)
  {
    mpLeft = newData;
  }
  void setRight(Node *newData)
  {
    mpRight = newData;
  }
  
  T getData()
  {
    return mData;
  }
  Node *& getLeft()
  {
    return mpLeft;
  }
  Node *& getRight()
  {
    return mpRight;
  }

    
private:
  T mData;
  Node *mpLeft;
  Node *mpRight;
};


/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

 private:
  Node<T> *root;
  int NodeCount, HeightCount, LeftHeight, RightHeight;
  int Height[100];
  
  void destroyTree(Node<T> *pTree)
  {
    if (pTree == nullptr)
      {
	return;
      }
    else
      {
	destroyTree(pTree->getLeft());
	destroyTree(pTree->getRight());
	delete pTree;
      }
  }
  
  void add(Node<T> *& pTree, T val)
  {
    if (pTree == nullptr)
      {
	pTree = new Node<T>(val);
	NodeCount++;
      }
    
    else if (val > pTree->getData())
      {
	add(pTree->getRight(), val);
      }

    else if (val < pTree->getData())
      {
	add(pTree->getLeft(), val);
      }

    else
      {
	cout << "Tried to insert a duplicate" << endl;
	cout << "Duplicate was: " << val << endl;
      }
  }
  
  void printPreOrder(Node<T> *pTree)
  {
    if (pTree == nullptr)
      {
	return;
      }

    else
      {
	cout <<  pTree->getData() << " ";
	printPreOrder(pTree->getLeft());
	printPreOrder(pTree->getRight());
      }
  }
  
  void FindHeight(Node<T> *pTree)
  { 
    RightHeight = 0;
    LeftHeight = 0;
    
    if (pTree->getRight() != nullptr)
      {
	HeightOfSubtree(pTree, "RIGHT");	
      }

    if (pTree->getLeft() != nullptr)
      {
	HeightOfSubtree(pTree, "LEFT");
      }

    if (RightHeight > LeftHeight)
      {
	Height[HeightCount]++;
	FindHeight(pTree->getRight());
      }
    
    else if (RightHeight < LeftHeight)
      {	
	Height[HeightCount]++;
	FindHeight(pTree->getLeft());
      }

    else if ((RightHeight == LeftHeight) && (RightHeight != 0))
      {
	Height[HeightCount]++;
	FindHeight(pTree->getLeft());
      }
    
    else if (RightHeight == 0 && LeftHeight == 0)
      {
	Height[HeightCount]++;
	return;
      }
  }

  void HeightOfSubtree(Node<T> *pTree, string LeftOrRight)
  {
    if (pTree == nullptr)
      {
	return;
      }

    else if (LeftOrRight == "LEFT")
      {
	HeightOfSubtree(pTree->getLeft(), "LEFT");
	LeftHeight++;
      }

    else if (LeftOrRight == "RIGHT")
      {
	HeightOfSubtree(pTree->getRight(), "RIGHT");
       	RightHeight++;
      }
  }

  
 public:
  BST()
    {
      root = nullptr;
    }
  
  ~BST()
    {
      destroyTree(root);
    }

  int getNodeCount()
  {
    return NodeCount;
  }
    
  void add(T val)
  {
    add(root, val);
  }
  
  void setRoot(Node<T> *newData)
  {
    root = newData;
  }
  
  Node<T> *& getRoot()
    {
      return root;
    }

  void printPreOrder()
  {
    printPreOrder(root);

    int num = nodesCount();
    cout << endl << "Number of Nodes: " << num;
  }

  int nodesCount()
  {
    return NodeCount;
  }

  int height()
  {
    Height[0] = 0;
    
    FindHeight(root);
    
    if (root != nullptr)
      {
	return Height[0];
      }
    
    return( -1 );
  }
};

#endif
