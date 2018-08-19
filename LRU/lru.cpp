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
template <class K, class T>
struct Node {
	K key;
	T data;
	Node *prev, *next;
};

template<class K, class T>
class LRUcache {
public:
	LRUcache(size_t size) {
		entries_ = new Node<K, T>[size];
		for (int i = 0; i < size; ++i) {
			free_entries_.push_back(entries_ + i);
		}
		head_ = new Node<K, T>;
		tail_ = new Node<K, T>;
		head_->prev = NULL;
		head_->next = tail_;
		tail_->prev = head_;
		tail_->next = NULL;
	}
	~LRUcache() {
		delete head_;
		delete tail_;
		delete[] entries_;
	}
	void put(K key, T data) {
		Node<K, T> *node = hashmap_[key];
		if (node) {
			detach(node);
			node->data = data;
			attach(node);
		} else if (free_entries_.empty()) {
			node = tail_->prev;
			detach(node);
			hashmap_.erase(node->key);
		} else {
			node = free_entries_.back();
			free_entries_.pop_back();
		}
		node->key = key;
		node->data = data;
		hashmap_[key] = node;
		attach(node);
	}
	T get(K key) {
		Node<K, T> *node = hashmap_[key];
		if (node) {
			detach(node);
			attach(node);
			return node->data;
		} else {
			return T();
		}
	}
private:
	void detach(Node<K, T> *node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	void attach(Node<K, T> *node) {
		node->prev = head_;
		node->next = head_->next;
		head_->next = node;
		node->next->prev = node;
	}
private:
	// __gnu_cxx::hash_map
	__gnu_cxx::hash_map<K, Node<K, T>* > hashmap_;
	vector<Node<K, T> *>free_entries_;
	Node<K, T> *head_, *tail_;
	Node<K, T> *entries_;
};

int main() {
	LRUcache<int, string> lru_cache(100);
	lru_cache.put(1, "dushuai");
	lru_cache.put(2, "Yokile");
	cout << lru_cache.get(1) << endl;
	cout << lru_cache.get(4) << endl;
}