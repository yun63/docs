/// =====================================================================================
/// 
///    @filename         :  tree.h
/// 
///    @description      :  树型结构的定义及实现，主要涉及到二叉树的算法
/// 
/// -------------------------------------------------------------------------------------
///    @version          :  1.0
///    @created          :  2013年07月06日 01时40分30秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @Company          :  
/// 
/// =====================================================================================

#ifndef  H_TREE_INC
#define  H_TREE_INC

using namespace std;

// 前置声明
template <class T>
class CBTNode;

/// 模板类友元函数声明

// 先序遍历
template <class T>
void preorder(CBTNode<T> *t);

// 中序遍历
template <class T>
void inorder(CBTNode<T> *t);

// 后序遍历
template <class T>
void postorder(CBTNode<T> *t);

// 层序遍历
template <class T>
void levelorder(CBTNode<T> *t);

/// ===========================================================================
///  @class      :  CBTNode
///  @description:  二叉树结点定义
/// ===========================================================================
template<class T>
class CBTNode
{
//	friend CBSTree<T>;
	public:
		friend void preorder<T>(CBTNode<T> *t);
		friend void inorder<T>(CBTNode<T> *t);
		friend void postorder<T>(CBTNode<T> *t);
		friend void levelorder<T>(CBTNode<T> *t);

	public:
		CBTNode( ) { lchild_ = rchild_ = NULL; }
		CBTNode(const T &element) 
			: data_(element), lchild_(NULL), rchild_(NULL) { }
		CBTNode(const T &element, CBTNode *left, CBTNode *right)
			: data_(element), lchild_(left), rchild_(right) { }
		T data( ) const { return data_; }
		CBTNode *lchild( ) const { return lchild_; }
		CBTNode *rchild( ) const { return rchild_; }

	protected:
		T 				data_;                  // 数据域
        CBTNode<T>    *lchild_;                 // 左子树
        CBTNode<T>    *rchild_;                 // 右子树
};
#endif   // ----- #ifndef TREE_INC  -----
