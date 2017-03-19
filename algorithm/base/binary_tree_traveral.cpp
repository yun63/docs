/// =====================================================================================
/// 
///    @filename         :  binary_tree_traveral.cpp
/// 
///    @description      :  二叉树的先序，中序，后序及层序遍历算法
/// 
///    @version          :  1.0
///    @created          :  2013年07月29日 22时52分54秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @company          :  
/// 
/// =====================================================================================

#include <iostream>
#include "queue.h"
#include "btnode.h"
#include "exceptions.h"

using namespace std;

template <typename T>
void visit(CBTNode<T> *bn)
{
	cout << bn->data() << " ";
}

template <typename T>
void preorder(CBTNode<T> *t)
{
	if (t != NULL)
	{
		visit(t);
		preorder(t->lchild());
		preorder(t->rchild());
	}
}

template <typename T>
void inorder(CBTNode<T> *t)
{
	if (t != NULL)
	{
		inorder(t->lchild());
		visit(t);
		inorder(t->rchild_);
	}
}

template <typename T>
void postorder(CBTNode<T> *t)
{
	if (t != NULL)
	{
		postorder(t->lchild());
		postorder(t->rchild());
		visit(t);
	}
}

template <typename T>
void levelorder(CBTNode<T> *t)
{
	CSqueue< CBTNode<T> * > q;
	while (t != NULL)
	{
		visit(t);
		// put t's children on queue
		if (t->lchild_ != NULL)
		{
			q.push(t->lchild());
		}
		if (t->rchild_ != NULL)
		{
			q.push(t->rchild());
		}

		// get next node to visit
		try
		{
			t = q.front();
		}
		catch (CSqueueEmpty &e)
		{
			return;
		}
		q.pop();
	}
}

int main( )
{
	// create a binary tree with root x
	CBTNode<int> *x, *y, *z;
	y = new CBTNode<int>(2);
	z = new CBTNode<int>(3);
	x = new CBTNode<int>(1, y, z);
	
	// traverse x in all ways
	cout << "Inorder sequence is : ";
	inorder(x);
	cout << endl;
	cout << "Preorder sequence is : ";
	preorder(x);
	cout << endl;
	cout << "Postorder sequence is : ";
	postorder(x);
	cout << endl;
	cout << "Level order sequence is : ";
	levelorder(x);
	cout << endl;

	return 0;
}
