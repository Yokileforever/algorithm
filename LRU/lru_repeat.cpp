#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

#if defined __GNUC__ || defined __APPLE__
#include <ext/hash_map>
#else
#include <hash_map>
#endif


using namespace std;

template<class K, class T>
struct Node {
	K key;
	T data;
	Node *prev, *next;
};

template<class K, class T>
class LRUcache {
public:
	LRUcache(size_t size) {
		_entries = new Node<K, T>[size];
		for (int i = 0; i < size; ++i) {
			_freeNode.push_back(_entries + i);
		}
		_tail = new Node<K, T>;
		_head = new Node<K, T>;
		_tail->prev = _head;
		_tail->next = NULL;
		_head->next = _tail;
		_head->prev = NULL;
	}
	~LRUcache() {
		delete _head;
		delete _tail;
		delete[] _entries;
	}
	void put(K key, T data) {
		Node<K, T> *node = _hashmap[key];
		if (node) {
			detach(node);
			node->data = data;
			attach(node);
		} else {
			if (_freeNode.empty()) {
				node = _tail->prev;
				detach(node);
				_hashmap.erase(key);
			} else {
				node = _freeNode.back();
				_freeNode.pop_back();
			}
			node->key = key;
			node->data = data;
			_hashmap[key] = node;
			attach(node);
		}
	}
	T get(K key) {
		Node<K, T> *node = _hashmap[key];
		if (node) {
			detach(node);
			attach(node);
			return node->data;
		} else {
			return T();
		}
	}
private:
	__gnu_cxx::hash_map<K, Node<K, T>* > _hashmap;
	vector<Node<K, T> *> _freeNode;
	Node<K, T> *_head, *_tail;
	Node<K, T> *_entries;
private:
	void detach(Node<K, T> *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	void attach(Node<K, T> *node) {
		node->next = _head->next;
		node->prev = _head;
		_head->next->prev = node;
		_head->next = node;

	}
};

int main() {
	LRUcache<int, string> lru_cache(100);
	lru_cache.put(1, "dushuai");
	lru_cache.put(2, "Yokile");
	cout << lru_cache.get(2) << endl;
	cout << lru_cache.get(4) << endl;
}