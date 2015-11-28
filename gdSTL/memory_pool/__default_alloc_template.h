/* the interface writed by SGI¡¡STL*/
#ifndef __DEFAULT_ALLOC_TEMPLATE__
#define __DEFAULT_ALLOC_TEMPLATE__
#ifndef __MALLOC_ALLOC_TEMPLATE__
#include "__malloc_alloc_template.h"
#endif
enum{ALIGN = 8};
enum{ MAX_BYTE = 128 };
enum{N_FREELIST = MAX_BYTE / ALIGN};
template<bool threads,int n>//here the thread to insist mutithread
class __default_alloc_template{
private:
	union object{
		union object* next = 0;
		char data[0];
	};

private:
	static size_t ROUND_UP(size_t bytes){
		return (((bytes) + ALIGN - 1)&~(ALIGN - 1));
	}
	static size_t index(size_t bytes){
		return (((bytes) + ALIGN - 1) / ALIGN - 1);
	}
	static object* volatile freelist[N_FREELIST];
	static void* refill(size_t);
	static char* chunk_alloc(size_t, int&);
public:
	static void* allocate(size_t);
	static void* reallocate(void*, size_t);
	static void deallocate(void*, size_t);
	static char* start_free;
	static char* end_free;
	static size_t heap_size;
	
};
template<bool threads, int n>char* __default_alloc_template<threads, n>::start_free = 0;
template<bool threads, int n>char* __default_alloc_template<threads, n>::end_free = 0;
template<bool threads, int n>size_t __default_alloc_template<threads, n>::heap_size = 0;
template<bool threads, int n>
typename __default_alloc_template<threads, n>::object* volatile __default_alloc_template<threads, n>::freelist[16] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

template<bool threads, int n>
void* __default_alloc_template<threads, n>::allocate(size_t t){
	object *result;
	object* volatile* myfreelist;
	if (t > size_t(MAX_BYTE)){
		return malloc_alloc::allocate(t);
	}
	myfreelist = freelist + index(t);
	result = *myfreelist;//here to get really memory
	if(0 == result){
		void* r = refill(ROUND_UP(t));
		return r;
	}
	*myfreelist =result->next;
	return static_cast<void*>(result);
}
//here  the key point
//static char* chunk_alloc(size_t, int&);
template<bool threads,int n>
char* __default_alloc_template<threads, n>::chunk_alloc(size_t N, int& node){
	size_t end_storage = end_free - start_free;
	size_t total_alloc = N * node;
	char* result = nullptr;
	object *curobj = nullptr;
	object* volatile * my_free_list;
	if (end_storage >= total_alloc){
		result = start_free;
		start_free += total_alloc;
		return static_cast<char*>(result);
	}
	else if (end_storage >= N){
		node = end_storage / N;//the left can be used by how many chunks
		total_alloc = node * N;//here distribution the left memory
		result = start_free;
		start_free += total_alloc;
		return static_cast<char*>(result);
	}
	else{//here to deal to cannot distibution one chunk
		if(end_storage > 0){
			my_free_list = freelist + index(end_storage);
			((object*)(start_free))->next = *my_free_list;
			*my_free_list = (object*)(start_free);
		}
		size_t get_bytes = 2 * total_alloc + ROUND_UP(heap_size >> 4);

		start_free = static_cast<char*>(malloc(get_bytes));
		object* p = nullptr;
		if (start_free == 0){//here it cannot to distibution anything
			for (int i = N; i < MAX_BYTE; i += ALIGN){
				my_free_list = freelist + index(i);
				p = *my_free_list;
				if (p){
					(*my_free_list) = (p->next);
					start_free = (char*)p;
					end_free = start_free + i;
					return chunk_alloc(N, node);
				}
			}
			end_free = 0;
			start_free = static_cast<char*>(malloc_alloc::allocate(get_bytes));
		}
		heap_size += get_bytes;
		end_free = start_free + get_bytes;
		return chunk_alloc(N, node);
	}
}
// here to find N byte in memory pool  
template<bool threads,int n>
void* __default_alloc_template<threads, n>::refill(size_t N){
	int node = 20;//here node = 20 but I donot think it's reasonable;
	char* pchunk= chunk_alloc(N, node);//here is to use the chunk alloc to get more than N bytes
	object* volatile* my_free_list;
	object* result = 0;
	if (1 == node){
		return (void*)(pchunk);//here illustrate the only one chunk
	}
	else{
		my_free_list = freelist + index(N);
		result = (object*)(pchunk);
		//here It's customed memory
		//here now the the chunk which result point to must be used now
		// so *freelist pointer the second chunk  

		object* next_object = (object*)(pchunk + N);
		*my_free_list = next_object;
		object* cur_obj = 0;
		for (int i = 1;; ++i){
			cur_obj = next_object;
			next_object = (object*)((char*)(cur_obj) + N);
			if (node - 1 == i){
				cur_obj ->next = 0;
				break;
			}
			else{
				cur_obj->next = next_object;
			}
		}
	}
	return (void*)(result);
}

template<bool threads,int n>
void __default_alloc_template<threads, n>::deallocate(void* p,size_t t){
	object* volatile* my_free_list = freelist + index(t);
	object* result = *my_free_list;
	if (t > (size_t)MAX_BYTE){
		malloc_alloc::deallocate(p, t);
		return;
	}
	*my_free_list = static_cast<object*>(p);
	((object*)(p))->next = result;
}








typedef __default_alloc_template<false, 0> default_alloc;










#endif