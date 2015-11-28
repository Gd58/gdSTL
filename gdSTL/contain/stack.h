#ifndef __STACK__
#define __STACK__
#ifndef __LIST__
#include "list.h"
#endif
template<class Element,class T = list<typename Element>>
class stack{
public:
	typedef Element value_type;
private:
	T contain;
public:
	stack(){}
	void push(value_type lhs){ contain.push_back(lhs); }
	void pop(){ 
		if (contain.empty())
			throw std::logic_error("empty");
		else
		contain.pop_back(); }
	value_type top(){ 
		if (contain.empty())
			throw std::logic_error("empty");
		else
		return *(--contain.end()); }
	void clear(){ contain.clear(); }


};
#endif