// =====================================================================================
// 
//    @filename    :  binary_tree.h
// 
//    @description :  二叉树的定义
// 
// -------------------------------------------------------------------------------------
//    @version     :  1.0
//    @created     :  2013年10月15日 15时55分23秒
//    @revision    :  none
//    @compiler    :  g++
// 
//    @author      :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company     :  
// 
// =====================================================================================

#ifndef  H_BINARY_TREE_H_
#define  H_BINARY_TREE_H_

template<typename T>
class BinaryNode
{
	public:
		BinaryNode(T &data); 
		inline T *data() const { return &_data; }
		inline BinaryNode *lchild() { return _left; }
		inline BinaryNode *rchild() { return _right; }

	protected:
		T _data;
		BinaryNode *_left;
		BinaryNode *_right;
};


template<typename T>
class BinaryTree
{
	public:
		BinaryTree();
		~BinaryTree();
		/**
		 * @brief  PreOrder 
		 * @param  vist
		 */
		void PreOrder(void (*vist)(T &data));
		/**
		 * @brief  InOrder 
		 * @param  visit
		 */
		void InOrder(void (*visit)(T &data));
		/**
		 * @brief  PostOrder 
		 * @param  visit
		 */
		void PostOrder(void (*visit)(T &data));
		/**
		 * @brief  empty 
		 * @return  
		 */
		bool empty() const;

		/**
		 * @brief  clear 
		 */
		void clear();

		/**
		 * @brief  size 
		 * @return  
		 */
		size_t size() const;

		/**
		 * @brief  height 
		 * @return  
		 */
		size_t height() const;

		/**
		 * @brief  GetSize 
		 * @param  pt
		 * @return  
		 */
		size_t GetSize(BinaryNode<T> *pt);

		/**
		 * @brief  GetHeight 
		 * @param  pt
		 * @return  
		 */
		size_t GetHeight(BinaryNode<T> *pt);

		/**
		 * @brief  search 
		 * @param  data
		 * @param  parent
		 * @param  x
		 * @return  
		 */
		virtual bool Search(T &data, BinaryNode<t> *&parent, BinaryNode<T> *&x);
		/**
		 * @brief  Insert 
		 * @param  data
		 * @return  
		 */
		virtual bool Insert(T &data);

		/**
		 * @brief  Delete 
		 * @param  data
		 * @return  
		 */
		virtual bool Delete(T &data);

	protected:
		/**
		 * @brief  RecursivePreOrder 
		 * @param  
		 * @param  visit
		 */
		void RecursivePreOrder(BinaryNode<T> *, void (*visit)(T &data));
		/**
		 * @brief  RecursiveInOrder 
		 * @param  
		 * @param  visit
		 */
		void RecursiveInOrder(BinaryNode<T> *, void (*visit)(T &data));
		/**
		 * @brief  RecursivePostOrder 
		 * @param  
		 * @param  visit
		 */
		void RecursivePostOrder(BinaryNode<T> *, void (*visit)(T &data));

	protected:
		BinaryNode<T> 	_root;
};

#endif   // ----- #ifndef H_BINARY_TREE_H_  -----
