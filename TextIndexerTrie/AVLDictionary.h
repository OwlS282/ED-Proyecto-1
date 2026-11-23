#pragma once

#include <stdexcept>
#include "AVLTree.h"
#include "Pair.h"
#include "Dictionary.h"
#include "DLinkedList.h"

using std::runtime_error;

template <typename K, typename V>
class AVLDictionary : public Dictionary<K, V> {
private:
	AVLTree<Pair<K, V>>* pairs;

public:
	AVLDictionary() {
		pairs = new AVLTree<Pair<K, V>>();
	}
	~AVLDictionary() {
		delete pairs;
	}
	void insert(K key, V value) {
		Pair<K, V> p(key, value);
		pairs->insert(p);
	}
	V remove(K key) {
		Pair<K, V> p(key);
		p = pairs->remove(p);
		return p.value;
	}
	V getValue(K key) {
		Pair<K, V> p(key);
		p = pairs->find(p);
		return p.value;
	}
	void setValue(K key, V value) {
		remove(key);
		insert(key, value);
	}
	bool contains(K key) {
		Pair<K, V> p(key);
		return pairs->contains(p);
	}
	void clear() {
		pairs->clear();
	}
	bool isEmpty() {
		return pairs->isEmpty();
	}
	List<K>* getKeys() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<K>* keys = new DLinkedList<K>();
		elements->goToStart();
		while (!elements->atEnd()) {
			Pair<K, V> p = elements->getElement();
			keys->append(p.key);
			elements->next();
		}
		delete elements;
		return keys;
	}
	List<V>* getValues() {
		List<Pair<K, V>>* elements = pairs->getElements();
		List<V>* values = new DLinkedList<V>();
		elements->goToStart();
		while (!elements->atEnd()) {
			Pair<K, V> p = elements->getElement();
			values->append(p.value);
			elements->next();
		}
		delete elements;
		return values;
	}
	int getSize() {
		return pairs->getSize();
	}
	void print() {
		pairs->print();
	}
};


