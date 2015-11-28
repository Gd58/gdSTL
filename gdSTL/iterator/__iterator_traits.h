// write on 2015-10-31
#pragma once
#ifndef __ITERATOR_TRAITS__
#define __ITERATOR_TRAITS__


#ifndef __G_FUNC__
#include "g_func.h"
#endif



extern struct __true_type;
extern struct __false_type;

template<class _catagory,class T, class reference = T&, class pointer = T*, class distance = diffptr_t>
struct iterator{
	typedef T value_type;
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef distance different_type;
	typedef _catagory catagory;
};


/* iterator tags */
struct __input_iterator_tag{};
struct __output_iterator_tag{};
struct __forward_iterator_tag :__input_iterator_tag{};
struct __bidirection_iterator_tag:__forward_iterator_tag{};
struct __random_access_iterator_tag :__bidirection_iterator_tag{};


template<class T>
class __iterator_traits_impl;

template <class iterator>
class __iterator_traits_impl{
public:
	typedef typename iterator::value_type value_type;
	typedef typename iterator::pointer pointer;
	typedef typename iterator::reference reference;
	typedef typename iterator::different_type different_type;
	typedef typename iterator::catagory catagory;
	};
template<> class __iterator_traits_impl<int>{
public:
	typedef int value_type;
	typedef int* pointer;
	typedef int& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<unsigned int>{
public:
	typedef unsigned int value_type;
	typedef unsigned int* pointer;
	typedef unsigned int& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<char>{
public:
	typedef char value_type;
	typedef char* pointer;
	typedef char& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};

template<> class __iterator_traits_impl<unsigned char>{
public:
	typedef unsigned char value_type;
	typedef unsigned char* pointer;
	typedef unsigned char& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<signed char>{
public:
	typedef signed char value_type;
	typedef signed char* pointer;
	typedef signed char& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<short>{
public:
	typedef short value_type;
	typedef short* pointer; 
	typedef short& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<unsigned short>{
public:
	typedef unsigned short value_type;
	typedef unsigned short* pointer;
	typedef unsigned short& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<float>{
public:
	typedef float value_type;
	typedef float* pointer;
	typedef float& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<double>{
public:
	typedef double value_type;
	typedef double* pointer;
	typedef double& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<long>{
public:
	typedef long value_type;
	typedef long* pointer;
	typedef long& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<unsigned long>{
public:
	typedef unsigned long value_type;
	typedef unsigned long* pointer;
	typedef unsigned long& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template<> class __iterator_traits_impl<long double>{
public:
	typedef long double value_type;
	typedef long double* pointer;
	typedef long double& reference;
	typedef ptrdiff_t different_type;
	typedef __random_access_iterator_tag catagory;
};
template <class T>
class __iterator_traits_impl<T*>{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef __random_access_iterator_tag catagory;
	typedef ptrdiff_t different_type;
};

template <class T>
class __iterator_traits_impl<const T*>{
public:
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef __random_access_iterator_tag catagory;
	typedef ptrdiff_t different_type;
};





template<class Element>
class __iterator_traits:public __iterator_traits_impl<Element>{
public:
	typedef __true_type dummy_member_must_be_first;
	typedef __false_type has_trival_default_constructor;
	typedef __false_type has_trival_copy_constructor;
	typedef __false_type has_trival_assignment_operator;
	typedef __false_type has_trival_destructor;
	typedef __false_type is_pod_type;
};
template<> class  __iterator_traits<int>:public __iterator_traits_impl<int>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<char>:public __iterator_traits_impl<char>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};
template<> class __iterator_traits<unsigned int>:public __iterator_traits_impl<unsigned int>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<float>:public __iterator_traits_impl<float>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<double>:public __iterator_traits_impl<double>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<unsigned char>:public __iterator_traits_impl<unsigned char>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<signed char>:public __iterator_traits_impl<signed char>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<short>:public __iterator_traits_impl<short>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<unsigned short>:public __iterator_traits_impl<unsigned short>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<long>:public __iterator_traits_impl<long>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template<> class __iterator_traits<unsigned long>:public __iterator_traits_impl<unsigned long>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};
template<> class __iterator_traits<long double>:public __iterator_traits_impl<long double>{
public:
	typedef __true_type has_trival_default_constructor;
	typedef __true_type has_trival_copy_constructor;
	typedef __true_type has_trival_assignment_operator;
	typedef __true_type has_trival_destructor;
	typedef __true_type is_pod_type;
};

template <class iterator>
inline typename __iterator_traits<iterator>::catagory iterator_catagory(const iterator&){
	typedef typename __iterator_traits<iterator>::catagory catagory;
	return catagory();
}

template <class iterator>
inline typename __iterator_traits<iterator>::value_type* value_type(const iterator&){
	return static_cast<typename __iterator_traits<iterator>::value_type*>(0);
}

template <class iterator>
inline typename __iterator_traits<iterator>::different_type* different_type(const iterator&){
	return static_cast<typename __iterator_traits<iterator>::different_type*>(0);
}
template <class iterator>
inline typename __iterator_traits<iterator>::different_type __distance(iterator first, iterator last, __input_iterator_tag){
	typename __iterator_traits<iterator>::different_type n = 0;
	while (first++ != last)++n;//there use first++ because first is input_iterator
	return n;
}

template <class iterator>
inline typename __iterator_traits<iterator>::different_type __distance(iterator first, iterator last, __random_access_iterator_tag){
	return last - first;
}

template <class iterator>
inline typename __iterator_traits<iterator>::different_type distance(iterator first, iterator last){
	typename __iterator_traits<iterator>::catagory catagory;
	return __distance(first, last, catagory());
}

template <class iterator,class distance>
inline void __advance(iterator& lhs, distance n,__input_iterator_tag){
	_ASSERT(n >= 0);//here use ASSERT to avoid n < 0 because iterator is input_iterator in debug
	if (n >= 0){//here to avoid n < 0 in release
		while (n--)  ++lhs;
	}
}

template <class iterator,class distance>
inline void __advance(iterator& lhs, distance n, __bidirection_iterator_tag){
	if (n >= 0)  while (n--) ++lhs;
	else         while (n++) ++lhs;
}

template <class iterator,class distance>
inline void __advance(iterator& lhs, distance n, __random_access_iterator_tag){
	lhs += n;
}

template<class iterator,class distance>
inline void advance(iterator& lhs, distance n){
	/*
	
	typedef typename __iterator_traits<iterator>::catagory;
	return __advance(lhs, n, catagory());
	*/
	return __advance(lhs, n, iterator_catagory(lhs));
}
#endif