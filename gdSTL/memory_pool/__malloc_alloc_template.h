#ifndef __MALLOC_ALLOC_TEMPLATE__
#define __MALLOC_ALLOC_TEMPLATE__


//the is usefuless

template<int n>
class __malloc_alloc_template{
protected:
	static void* __out_of_memory_alloc(size_t t);
	static void* __out_of_memory_reallocate(void* p, size_t t);
	static void(*__out_of_memory_handle)();
public:

	static void* allocate(size_t t){
		void* result = malloc(t);
		if (0 == result){
			result = __out_of_memory_alloc(t);
		}
		return result;
	}

	static void deallocate(void* p,size_t){
		free(p);
	}

	static void* reallocate(void* p, size_t t){
		void* result = realloc(p, t);
		if (0 == result){
			result = __out_of_memory_realloc(p, t);
		}
		return result;
	}
	/*here to set the out of memory handle*/
	typedef void(*_pfun_out_of_handle)();
	static _pfun_out_of_handle set_out_of_handle(_pfun_out_of_handle f){
		_pfun_out_of_handle old_handle = __out_of_memory_alloc;
		__out_of_memory_handle = f;
		return old_handle;
	}

};

#define THROW_BAD_ALLOCATE throw"NO MEMORY TO USE";
template<int n>
void(*__malloc_alloc_template<n>::__out_of_memory_handle)() = 0;



template<int n>
void* __malloc_alloc_template<n>::__out_of_memory_alloc(size_t t){
	_pfun_out_of_handle __observe_handle;
	void* result = nullptr;
	for (;;){
		__observe_handle = __out_of_memory_handle;
		if (0 == __observe_handle)	THROW_BAD_ALLOCATE
			__observe_handle();
		result = malloc(n);
		if (result)		return result;
	}
}


template<int n>
void* __malloc_alloc_template<n>::__out_of_memory_reallocate(void* p, size_t t){
	void* result = nullptr;
	_pfun_out_of_handle __observe_handle;
	for (;;){
		__observe_handle = __out_of_memory_handle;
		if (0 == __observe_handle)	THROW_BAD_ALLOCATE
			__observe_handle();
		result = realloc(p, t);
		if (result)		return result;
	}
}
typedef __malloc_alloc_template<0> malloc_alloc;
#endif