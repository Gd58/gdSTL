////////////////////////////////////
/*
#ifndef __ITERATOR_TRAITS__        
#include "__iterator_traits.h"      
#endif

#ifndef __MALLOC_ALLOC_TEMPLATE__
#include"__malloc_alloc_template.h"
#endif


#ifndef __DEFAULT_ALLOC_TEMPLATE__
#include "__default_alloc_template.h"
#endif
#include<excpt.h>


template<typename T>
struct t{
	typedef typename std::conditional<std::is_array<T>::value, typename std::remove_all_extents<T>::type,
	typename std::conditional<std::is_pointer<T>::value, typename std::remove_pointer<T>::type, typename T>::type>::type type;
	type x;
};
template<typename T>
struct m{
	typedef typename std::enable_if<std::is_member_function_pointer<T>::value,bool>::type type;
	type x;
};
template<>
struct m<int>{
	int x;
};

struct f{
	void foo(){};
};

t<int*> x;
std::cout << typeid(x.x).name() << std::endl;
f w;
typedef void(f::*pfun)();
m<pfun> a;
cout << typeid(a.x).name() << endl;
m<int> b;
cout << typeid(b.x).name() << endl;
#include "Vector.h"
template<typename T>
struct m{
	typedef typename std::enable_if<std::is_integral<T>::value||std::is_floating_point<T>::value, typename std::add_pointer<T>::type>::type type;
	type f;
};
int main(){
	using std::cout;
	using std::endl;
	/*
	malloc_alloc alloc;
	int* p = static_cast<int*>(alloc.allocate(4*sizeof(int)));
	for (auto i = 0; i < 4; ++i){
		p[i] = i;
	}
	std::cout << p[0] << p[1] << p[2] << p[3] << endl;
	cout << *p << endl;
	alloc.deallocate(static_cast<void*>(p));
	std::cout << p[2] << endl;
	__iterator_traits<int>::value_type x = 1;
	__iterator_traits<int>::reference jh = x;
	using type = __iterator_traits<int>::pointer;
	__iterator_traits<int>::pointer pint = static_cast<int*>(alloc.allocate(sizeof(int)* 10));
	int i;
	for (i = 0; i < 10; ++i){
		pint[i] = i;
	}
	while (--i >= 0)cout << pint[i] << endl;
	int* px = pint+6;
	advance(px, -3);
	cout<<"*px="<<*px << endl;
	cout << x <<"   jh = "<<jh<< endl;
	char mk = char();
	cout <<"mk是"<< mk << endl;
	int mn;
	default_alloc default_allocate;
	int *pn = static_cast<int*>(default_allocate.allocate(10));
	for (int i = 0; i < 10; ++i){
		pn[i] = i;
	}

	for (int j = 0; j < 10; ++j){
		cout << "p[" << j << "]=" << j << endl;
	}
	Ve
}
*/
/*
template<typename T>
class ty :public tn;
template<typename T>
class ty<T*>{

}
*/
/*
#include "Vector.h"
#ifndef __ITERATOR_TRAITS__        
#include "__iterator_traits.h"      
#endif
#include <iostream>
using namespace std;
int main(){
	Vector<int,default_alloc> v;
	for (int i = 0; i < 8; ++i)v.push_back(i);
	Vector<int,default_alloc>::iterator it = v.begin_();
	while (it != v.end_())
	{
		cout << *it << endl;
		++it;
	}
	Vector<int, default_alloc> v1;
	for (int i = 0; i < 10; ++i)v1.push_back(i);

	cout << v.front() << endl;
	cout << v.back() << endl;
	cout << "第二次" << endl;
	Vector<int, default_alloc>::iterator t = v.begin_();
	Vector<int, default_alloc>::iterator t1 = t;
	++t1; ++t1; ++t1;
	v.erase(t, t1);
	while (t != v.end_()){
		cout << *t << endl;
		++t;
	}
	v =  v1;
	cout << "Third Times" << endl;
	Vector<int, default_alloc>::iterator Iter = v.begin_();
	while (Iter != v.end_())
	{
		cout << *Iter << endl;
		++Iter;
	}
	Vector<int, default_alloc>::iterator ih = v.begin_();
	Vector<int, default_alloc>::iterator ix = ih;
	Vector<int, default_alloc>::iterator ik = ih;
	while (ik != v.end_())
	{
		cout << *ik << endl;
		++ik;
	}
	++ix; ++ix; ++ix;
	++ix; ++ix; ++ix;
	cout << "*IX = "<<*ix << endl;
	v.insert(ix, 10, 34);
	Vector<int, default_alloc>::iterator Ih = v.begin_();
	

	while (Ih != v.end_()){
		cout << *Ih << endl;
		++Ih;
	}

	cin.get();

	return 0;
}
*/
/*
#include <iostream>
#include "slist.h"
int main(){
	slist<int> mylist;
	for (size_t i = 0; i < 9; ++i)
		mylist.push_front(i);
	slist<int>::iterator iter = mylist.begin();
	while (iter != mylist.end()) {

	
		std::cout << *iter << std::endl;
		++iter;
	}
	std::cin.get();
	return 0;
}
*/
#include "list.h"
#include <iostream>
int main(){
	list<int> l;
	for (auto i = 0; i < 10; ++i)
		l.push_back(i);
	list<int>::iterator iter = l.begin();
	while (iter != l.end()){
		std::cout << *iter << std::endl;
		++iter;
	}
	for (auto i = 11; i < 20; ++i)
		l.push_front(i);
	
	/*
	for (auto i = 0; i < 12; ++i)
		l.pop_back();
		*/
	/*
	l.erase(++l.begin());
	l.remove(8);
	*/
	list<int> ml;
	for (auto i = 0; i < 10; ++i)
		ml.push_back(i + 20);
	
	list<int>::iterator as = l.begin();
	//l.transfer(++(++as), ml.begin(), ml.end());
	/*
	l.clear();
	if (l.empty())std::cout << "empty" << std::endl;
	else  std::cout << "no empty and size =" << l.size() << std::endl;
	*/
	l.splice(++as, ml);
	

	list<int> p;
	p.push_back(1);
	p.push_back(1);
	p.push_back(1);
	p.push_back(2);
	p.push_back(2);
	p.push_back(3);
	p.unique();
	std::cout << "原数列" << std::endl;
	list<int>::iterator it = l.begin();
	while (it != l.end()){
		std::cout << *it << std::endl;
		++it;
	}
	
	std::cout << "现数列" << std::endl;
	l.reserve();
	list<int>::iterator Iter = l.begin();
	while (Iter != l.end()){
		std::cout << "*Iter = " << *Iter << std::endl;
		++Iter;
	}
	std::cin.get();
	return 0;
}