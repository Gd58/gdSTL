#ifndef __SLIST__
#define __SLIST__
#ifndef __ALLOCATOR__
#include "allocator.h"
#endif
#ifndef __ITERATOR_TRAITS__
#include "__iterator_traits.h"
#endif
#ifndef __DEFAULT_ALLOC_TEMPLATE__
#include "__default_alloc_template.h"
#endif
#ifndef __G_FUN__
#include "g_func.h"
#endif
struct slist_node_base{
	slist_node_base *next;
};
template<typename T>
struct slist_node:slist_node_base{
	T data;
};
template<typename T,typename Ref,typename Distance>
struct slist_iterator{
	typedef T value_type;
	typedef Ref reference;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef Distance different_type;
	typedef slist_iterator<T, T&, different_type> self;
	typedef slist_iterator<T, T&, ptrdiff_t> iterator;
	typedef __forward_iterator_tag catagory;
	self& operator++(){ node_base = node_base->next; return *this; }
	self& operator++(int){ slist_node_base tmp = node_base; ++(*this); return tmp; }
	value_type operator*(){ return ((slist_node<T>*)(node_base))->data; }
	pointer operator->(){ return &*this; }
	bool operator==(const iterator lhs){ return lhs.node_base == node_base; }
	bool operator!=(const iterator lhs){ return lhs.node_base != node_base; }

	
	slist_node_base *node_base;
	explicit slist_iterator(slist_node_base* lhs){ node_base = lhs; }
	slist_iterator() :node_base(0){}
	slist_iterator(const slist_iterator& lhs){ node_base = lhs.node_base; }

	//slist_iterator(slist_node lhs){ node_base = lhs.next; }
};
inline slist_node_base* _slist_make_link(slist_node_base* prev, slist_node_base* cur){
	cur->next = prev->next;
	prev->next = cur;
	return cur;
}
inline size_t _slist_size(slist_node_base* node){
	size_t result = 0;
	while (node){
		result++;
		node = node->next;
	}
	return result;
}
template<typename T,typename Alloc = default_alloc>
class slist{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef value_type& reference;
	typedef slist_iterator<T, T&, ptrdiff_t> iterator;
	typedef slist_iterator<const T, const T&, ptrdiff_t> const_iterator;
private:
	typedef slist_node_base node_base;
	typedef slist_node<T> node;
	typedef typename __allocator<slist_node<T>, typename Alloc> allocator_t;
private:
	slist_node_base _front;
	slist_node_base* _back;/*here left a interface to meet to insert from back */
	static node* create_node(value_type lhs)
	{
		node* tmp =(node*)allocator_t::allocate();
		construct(&tmp->data, lhs);
		tmp->next = 0;
		return tmp;
	}
	static void destory_node(node * lhs)
	{
		destory(lhs->data);
		allocator_t::deallocator(lhs);
	}
public:
	slist() :_back(0){ _front.next = 0; }

	iterator begin(){ return iterator(_front.next); }

	iterator end() { return iterator(); }

	value_type front()
	{ 
		static_assert(_front.next != 0);
		return ((slist_node*)(_front.next))->data; 
	}

	/*
	value_type back(){
		static_assert(_back != 0);
		return ((slist_node*)(_front.next))->data;
	}
	*/
	size_t size(){
		return _slist_size(_front);
	}
	bool empty(){
		//return 0 == size();
		//the others way
		return _front->next == 0;
	}

	void push_front(value_type lhs)
	{

		_slist_make_link(&_front, create_node(lhs));

	}
	void pop_front(){
		node_base* tmp = _front.next;
		_front.next = tmp->next;
		destory_node((node*)tmp);
	}
	/*
	here we also can use back_insert
	but we can use only one way
	void push_back(value_type lhs){
	_slist_make_link(_back,create_node(lhs));
	}

	and   we can use pop_back
	void pop_back(){
	iterator iter = _front + size() -1;
	node_base* tmp = _back;
	_back = iter.node_base;
	destory_node(tmp);
	}
	*/
	
};
#endif