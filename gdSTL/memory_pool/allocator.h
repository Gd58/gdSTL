/* note
	__malloc_alloc_template and __default_alloc_template  can be encapsulated
*/
/*
#ifndef __DEFAULT_ALLOC_TEMPLATE__
#include "__default_alloc_template.h"
#endif
*/
#ifndef __ALLOCATOR__
#define __ALLOCATOR__
template<class T,class Alloc = default_alloc>
class __allocator{
public:
	static void *allocate(size_t n){ return Alloc::allocate(n * sizeof(T)); }
	static void *reallocate(void *p, size_t n){ return Alloc::reallocate(p, n * sizeof(T)); }
	static void deallocate(void *p, size_t n){ Alloc::deallocate(p, n * sizeof(T)); }
	static void* allocate(){ return Alloc::allocate(sizeof(T));  }
	static void  deallocate(void *p){ Alloc::deallocate(p,sizeof(T)); }
	static void* reallocate(void* p){ return Alloc::reallocate(p, sizeof(T)); }
};
#endif