#pragma once
#define THROW_ERROR throw"ERROR";
#ifndef __G_FUN__
#define __G_FUN__
#ifndef __ITERATOR_TRAITS__
#include "__iterator_traits.h"
#endif
extern struct __input_iterator_tag input_iterator_tag;
extern struct __output_iterator_tag out_iterator_tag;
extern struct __forward_iterator_tag forward_iterator_tag;
extern struct __bidirection_iterator_tag bidirection_iterator_tag;
extern struct __random_access_iterator_tag random_access_iterator_tag;
	struct __true_type{};
	struct __false_type{};
	template<class Bidirectional_iterator1,class Bidirectional_iterator2>
	Bidirectional_iterator2 copy_backward(Bidirectional_iterator1 first, Bidirectional_iterator1 last, Bidirectional_iterator2 result){
		while (last != first)*(--result) = *(--last);
		return result;
	}
	template<class T1,class T2>
	inline void construct(T1* p, const T2& value){
		new(p) T1(value);
	}
	inline void destory(char*, char*){}
	inline void destory(wchar_t*, wchar_t*){}

	template<class T>
	inline void destory(T* p){
		p->~T();
	}
	template<class Forward_iterator>
	inline void __destory_aux(Forward_iterator first, Forward_iterator last, __false_type){
		while (first != last){
			destory(&*first);
			++first;
		}
	}
	template<class Forward_iterator>
	inline void __destory_aux(Forward_iterator first, Forward_iterator last, __true_type){

	}
	template<class Forward_iterator,class T>
	inline void __destory(Forward_iterator first, Forward_iterator last, T*){
		typedef typename __iterator_traits<T>::has_trival_copy_constructor has_trival_copy_constructor;
		__destory_aux(first, last, has_trival_copy_constructor());
	}
	template<class Forward_iterator>
	inline void destory(Forward_iterator first, Forward_iterator last){
		__destory(first, last, value_type(first));
	}
	inline char*  unitialized_copy(const char* first, const char* last, char* result){
		std::memmove(result, first, last - first);
		return result + (last - first);
	}
	inline wchar_t* unitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result){
		std::memmove(result, first, sizeof(wchar_t)*(last - first));
		return result + (last - first);
	}
	template<class Input_iterator,class Forward_iterator>
	inline Forward_iterator __uninitialized_copy_aux(Input_iterator first, Input_iterator last, Forward_iterator result, __false_type){
		for (; first != last; ++first, ++result){
			construct(&*result,*first);
			return result;
		}
	}
	template<class T>
	T* __copy_t(const T* first,const T* last, T* result, __true_type){
		std::memmove(result, first, sizeof(T)*(last - first));
		return result +(last - first);
	}

	template<class T>
	T* __copy_t(const T* first, const T* last, T* result, __false_type){
		return __copy_d(first, last, result, result, ptrdiff_t*(0));
	}

	template<class Random_iterator, class Output_iterator, class Different>
	Output_iterator __copy_d(Random_iterator first, Random_iterator last, Output_iterator result, Different*){
		Different n = last - first;
		for (; n > 0; --n, ++first, ++result){
			*result = *first;
		}
		return result;
	}
	
	template<class Input_iterator,class Output_iterator>
	Output_iterator __copy(Input_iterator first, Input_iterator last, Output_iterator result,__input_iterator_tag){
		while (first != last){
			*result = *first;
			++result;
			++first;
		}
		return result;
	}
	template<class Random_iterator,class Output_iterator>
	Output_iterator __copy(Random_iterator first, Random_iterator last, Output_iterator result, __random_access_iterator_tag){
		return __copy_d(first, last, result, different_type(first));
	}
	
	template<class Input_iterator,class Output_iterator>
	struct __copy_dispatch{
		Output_iterator operator()(Input_iterator first, Input_iterator last, Output_iterator result){
			return __copy(first, last, result, iterator_catagory(result));
		}
	};

	template<class T>
	struct __copy_dispatch<const T*, T*>{
		T* operator()(const T* first, const T* last, T* result){
			typedef typename __iterator_traits<T>::has_trival_assignment_operator has_trival_assignment_operator;
			return __copy_t(first, last, result, has_trival_assignment_operator());
		}
	};
	template<class T>
	struct __copy_dispatch<T*, T*>{
		T* operator()(T* first, T* last, T* result){
			typedef typename __iterator_traits<T>::has_trival_assignment_operator has_trival_assignment_operator;
			return __copy_t(first, last, result, has_trival_assignment_operator());
		}
	};
	

	
	template<class Input_iterator,class Output_iterator>
	inline Output_iterator copy__t(Input_iterator first, Input_iterator last, Output_iterator result){
		return __copy_dispatch<Input_iterator, Output_iterator>()(first, last, result);
	}
	
	template<class Input_iterator,class Forward_iterator>
	inline Forward_iterator __uninitialized__copy_aux(Input_iterator first, Input_iterator last, Forward_iterator result, __true_type){
		return copy__t(first, last, result);
	}

	template<class Input_iterator,class Forward_iterator,class T>
	inline Forward_iterator __uninitialized_copy(Input_iterator first, Input_iterator last, Forward_iterator result, T*){
		typedef typename __iterator_traits<T>::is_pod_type is_pod_type;
		return __uninitialized__copy_aux(first, last, result, is_pod_type());
	}
	template<class Input_iterator,class Forward_iterator>
	inline Forward_iterator uninitialized_copy_x(Input_iterator first, Input_iterator last, Forward_iterator result){
		return __uninitialized_copy(first, last, result, value_type(result));
	}
	template<class Forward_iterator,class T>
	inline Forward_iterator fill_n(Forward_iterator begin, size_t N, const T& x){
		for (; N > 0; --N, ++begin)
			*begin = x;
		return begin;
	}
	template<class Forward_iterator, class T>
	inline Forward_iterator __uninitialized_fill_aux(Forward_iterator begin, size_t N, const T& x, __true_type){
		return fill_n(begin, N, x);
	}
	/*Here can distinguish the difference of the pod and non-pod*/
	/*
	If it has tirval ctor;
	*/
	template<class Forward_iterator, class T>
	inline Forward_iterator __uninitialized_fill_aux(Forward_iterator begin, size_t N, const T& x, __false_type){
		Forward_iterator t = begin;
		try{
			while (N--){
				static_assert(begin);
				if (!begin) THROW_ERROR
					construct(&*begin, x);
				++begin;
			}
		}
		return t;
	}
	template<class Forward_iterator, class T, class T1>
	inline Forward_iterator __uninitialized_fill_n(Forward_iterator begin, size_t N, const T& x, T1*){
		typedef typename __iterator_traits<T1>::is_pod_type is_pod_type;
		return __uninitialized_fill_aux(begin, N, x, is_pod_type());
	}

	template<class Forward_iterator, class T>
	inline Forward_iterator uninitialized_fill_n(Forward_iterator begin, size_t N, const T& x){
		return __uninitialized_fill_n(begin, N, x, value_type(begin));
	}
	
	template<class Input_iterator,class Random_iterator>
	Random_iterator __copy_backward(Input_iterator first, Input_iterator last, Random_iterator result, __random_access_iterator_tag){
		while (first != last){
			*--result = *--last;
		}
		return result;
	}
	
	struct Scalar_ptr{};
	struct Nonscalar_ptr{};
	
	template<class Ty>
	struct is_scalar{
		typedef typename std::conditional <std::is_arithmetic<Ty>::value
		|| std::is_enum<Ty>::value
		|| std::is_pointer<Ty>::value
		|| std::is_member_pointer<Ty>::value
		|| std::_Is_nullptr_t<Ty>::value,typename std::integral_constant<bool,true>::type,typename std::integral_constant<bool,false>>::type type;
		bool value = type::value;
	};
	template<class T1,class T2>
	struct Ptr_helper{
		typedef typename Nonscalar_ptr type;
	};
	template<class T>
	struct Ptr_helper<T,T>{
		typedef typename std::conditional<is_scalar<T>::value, Scalar_ptr, Nonscalar_ptr>::type type;

	};
	template<class T>
	struct Ptr_helper<T*, const T*>{
		typedef typename Scalar_ptr type;
	};
	template<class T1,class T2>
	typename Ptr_helper<T1, T2>::type Ptr(T1*, T2*){
		typedef typename Ptr_helper<T1, T2>::type type;
		return type();
	}
	template<class T1,class T2>
	typename Ptr_helper<T1, T2>::type Ptr(const T1*,T2*){
		typedef typename Ptr_helper<T1, T2>::type type;
		return type();
	}
	template<class Forward_iterator,class T>
	inline void __uninitialized_fill_x(Forward_iterator first, Forward_iterator last, const T& value, __false_type){
		while (first != last){
			construct(&*first, value);
			++first;
		}
	}
	template<class Forward_iterator, class T>
	inline void __uninitialized_fill_x(Forward_iterator first, Forward_iterator last, const T& value, __true_type){
		while (first != last){
			*first++ = value;
		}
	}
	template<class Forward_iterator,class T,class T1>
	inline void __uninitialized_fill(Forward_iterator first, Forward_iterator last, const T& value, T1*){
		typedef typename __iterator_traits<T1>::is_pod is_pod;
		__uninitialized_fill_x(first, last, value, is_pod());
	}
	template<class Forward_iterator,class T>
	inline void uninitialized_fill(Forward_iterator first, Forward_iterator last, const T& value){
		__uninitialized_fill(first, last, value, value_type(first));
	}
#endif