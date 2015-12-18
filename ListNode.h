
#define Posi(T)  ListNode<T>*
#include <iostream>
using namespace std;
typedef int Rank;
template <typename T> struct ListNode {

	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) :data(e), pred(p), succ(s) {}
	Posi(T) insertAsPred(T const& e) {
		Posi(T) x = new ListNode(e, pred, this);
		pred->succ = x;
		pred = x;
		return x;
	};
	Posi(T) insertAsSucc(T const& e) {
		Posi(T) x = new ListNode(e, this, succ);
		succ->pred = x;
		succ = x;
		return x;
	};

};
template <typename T> class List {
private:
	int _size;
	Posi(T) header;
	Posi(T) trailer;
protected:

public:
	void init() {
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer;
		trailer->pred = header;
		_size = 0;
	}
	List() { init(); }
	~List() {
		Clear();
		delete header;
		delete trailer;

	}
	Posi(T) find(T const& e, int n, Posi(T) p)const {
		while (0 < n--) {
			if (e == (p = p->pred)->data)
			{
				return p;
			}
		}
		return NULL;
	}
	void insert(int m, T n) {
		int i = -1;
		Posi(T) pt = header;
		while (i++<m)
		{
			pt = pt->succ;
		}
		insertBefore(pt, n);
	}

	void show() {
		Posi(T) pt = header->succ;
		if (pt == trailer)
		{
			cout << "-" << endl;
		}
		else
		{
			for (; pt != trailer; pt = pt->succ)
			{
				cout << pt->data;
			}
			cout << endl;
		}

	}
	Posi(T) first() { return header->succ; }
	T firstData() { return header->succ->data; }
	Posi(T) insertAsFirst(T const& e) {
		_size++;
		return header->insertAsSucc(e);
	}
	Posi(T) insertAsLast(T const& e) {
		_size++;
		return trailer->insertAsPred(e);
	}
	Posi(T) insertBefore(Posi(T) p, T const& e) {
		_size++;
		return p->insertAsPred(e);
	}
	Posi(T) insertAfter(Posi(T) p, T const& e) {
		_size++;
		return p->insertAsSucc(e);
	}
	void copyNodes(Posi(T) p, int n) {
		init();
		while (n--)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}
	List(Posi(T) p, int n) { // 从P开始复制n个节点
		copyNodes(p, n);
	}
	List(List<T> const& L) {//整体复制一个列表
		copyNodes(L.first(), L._size);
	}
	//List(List<T> const& L,int r,int n){  //循秩复制
	//	copyNodes(L[r],n);
	//}
	T remove(Posi(T) p) {
		T e = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return e;
	}
	int Clear() {
		int oldsize = _size;
		while (0<_size)
		{
			remove(header->succ);
			_size--;
		}
		return oldsize;
	}
	int deduplicate() {
		if (_size < 2) return 0;
		int oldsize = _size;
		Posi(T) p = first();
		Rank r = 1;
		while (trailer != p->succ)
		{
			Posi(T) q = find(p->data, r, p);
			q ? remove(q) : r++;
			p = p->succ;
		}
		return oldsize - _size;
	}
	int uniquify() {
		if (_size < 2)
		{
			return 0;
		}
		int oldsize = _size;
		Posi(T) p = first();
		Posi(T) q;
		while (trailer != (q = p->succ))
		{
			if (p->data != q->data) { p = q; }
			else { remove(q); }
		}
		return oldsize - _size;
	}
	void del(int m) {
		Posi(T) p1;
		Posi(T) p2;
		Posi(T) p3;
		Posi(T) p4;
		Posi(T) pt = header;
		Posi(T) begin = header;
		Posi(T) end = trailer;
		bool boo = true;
		int repeat, i = -1;
		while (i++ < m - 2)pt = pt->succ;
		begin = pt; end = pt; i = 0;

		while (i++<4 && end->succ != trailer)
		{
			end = end->succ;
		}
		while (boo && pt != trailer)
		{
			boo = false; repeat = 1;
			while (pt != end)
			{
				pt = pt->succ;
				if (pt->pred->data == pt->data) repeat++;
				else repeat = 1;
				if (repeat == 3)
				{
					boo = true;
					if (pt->data == pt->succ->data)
					{
						repeat++;
						pt = pt->succ;
					}
					if (repeat == 3) //三个连续的
					{
						p3 = pt; p2 = p3->pred; p1 = p2->pred;
						p1->pred->succ = p3->succ;
						p3->succ->pred = p1->pred;
						pt = pt->succ;
						delete p1; delete p2; delete p3;
						_size -= 3;
					}
					else //四个连续的
					{
						p4 = pt; p3 = p4->pred; p2 = p3->pred; p1 = p2->pred;
						p1->pred->succ = p4->succ;
						p4->succ->pred = p1->pred;
						pt = pt->succ;
						delete p1; delete p2; delete p3; delete p4;
						_size -= 4;
					}

					break;
				}
			}
			if (boo && pt != trailer)
			{
				begin = pt; i = 0;
				while (i++ < 2 && begin->pred != header) begin = begin->pred;//begin向前移动两位
				end = pt; i = 0;
				if (i++ < 1 && end->succ != trailer) end = end->succ;//end向后移动一位
				pt = begin;
			}
		}


	}
	Posi(T) search(T const &e, int n, Posi(T) p) {
		while (0 <= n--)
		{
			p = p->pred;
			if (p->data <= e)break;
		}
		return p;
	}
	void ZumaCreate(T *a, int n) {
		header->data = '-';
		trailer->data = '-';
		for (int i = 0; i < n; i++)
		{
			insertAsLast(a[i]);
		}
	}
	void selectionSort(Posi(T) p, int n) {
		Posi(T) head = p->pred;
		Posi(T) tail = p;
		for (int i = 0; i < n; i++) { tail = tail->succ; }
		while (1<n)
		{
			insertBefore(tail, remove(selectMax(head->succ, n)));
			tail = tail->pred;
			n--;
		}
	}
	Posi(T) selectMax(Posi(T) p, int n) {
		Posi(T) max = p;
		for (Posi(T) current = p; n>1; n--)
		{
			if (current->data >= max->data)
			{
				max = current;  //画家算法：max只增加不减少
			}
			current = current->succ;
		}
		return max;
	}
	T selectMaxData() {
		Posi(T) max = selectMax(header->succ, _size);
		return max->data;
	}
	void insertionSort(Posi(T) p, int n) {
		for (int r = 0; r < n; r++) {
			insertAfter(search(p->data, r, p), p->data);  //搜索不大于p.data的最大节点，在其后插入p.data
			p = p->succ;
			remove(p->pred);         //移动到下一个节点，删除原来的p
		}
	}
};

