// #####################################################################################
// 
//    @filename         :  link_node.h
// 
//    @description      :  
// 
// -------------------------------------------------------------------------------------
//    @version          :  1.0
//    @created          :  05/26/13 23:04:50
//    @revision         :  none
//    @compiler         :  g++
// 
//    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
//    @Company          :  
// 
// #####################################################################################

#ifndef  H_LINK_NODE_INC
#define  H_LINK_NODE_INC

template<class T>
class CLinkNode
{
	public:
		CLinkNode( ) : next_(NULL) { }
		~CLinkNode( ) { }
		CLinkNode(const T &element)	
		{ 
			this->element_ = element; 
			this->next_ = NULL;
		}
		CLinkNode(const T &element, CLinkNode<T> *next)
		{
			this->element_ = element;
			this->next_ = next;
		}

	public:
		T element_;
		CLinkNode<T> *next_;
};
#endif   // ----- #ifndef LINK_NODE_INC  -----
