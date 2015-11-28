#ifndef __QUEUE__
#define __QUEUE__
#ifndef __LIST__
#include "list.h"
#endif
template<class Element,class T = list<typename Element>>
class queue{
public:
	typedef Element value_type;
	queue(){};
	
	void push(value_type lhs){ contain.push_back(lhs); }
	void pop(){
		if (contain.empty())
			throw std::logic_error("Empty");
		else
			contain.pop_front();
	}
	bool empty(){ return contain.empty(); }
	bool size(){ return contain.size(); }
	value_type front(){ return *contain.begin(); }
private:
	T contain;
};
#endif