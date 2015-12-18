#include "ListNode.h"
template<typename T>
class Queue :public List<T> {
public:
	Queue() { size = 0; };
	~Queue() {};
	void enqueue(T const& e) { size++; this->insertAsLast(e); }
	T dequeue() { size--; return this->remove(this->first()); }
	T & front() { return this->first()->data; }
	int size;
	bool empty() {
		if (size != 0) {
			return false;
		}
		else {
			return true;
		}
	}
};


