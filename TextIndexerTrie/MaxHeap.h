#pragma once

#include <stdexcept>

using std::runtime_error;


template <typename E>
class MaxHeap {
private:
	E* elements;
	int capacity;
	int size;

	int parent(int pos) {
		return (pos - 1) / 2;
	}

	int leftChild(int pos) {
		return 2 * pos + 1;
	}

	int rightChild(int pos) {
		return 2 * pos + 2;
	}

	void swap(int i, int j) {
		E temp = elements[i];
		elements[i] = elements[j];
		elements[j] = temp;
	}

	void grow() {
		int newCapacity = capacity * 2;
		E* newElements = new E[newCapacity];
		for (int i = 0; i < size; i++)
			newElements[i] = elements[i];
		delete[] elements;
		elements = newElements;
		capacity = newCapacity;
	}

	void siftUp(int pos) {
		while (pos > 0 && elements[parent(pos)] < elements[pos]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}

	void siftDown(int pos) {
		while (leftChild(pos) < size) {
			int biggest = leftChild(pos);
			int right = rightChild(pos);
			if (right < size && elements[biggest] < elements[right])
				biggest = right;
			if (!(elements[pos] < elements[biggest]))
				return;
			swap(pos, biggest);
			pos = biggest;
		}
	}

public:
	MaxHeap(int initialCapacity = 1024) {
		if (initialCapacity < 1)
			initialCapacity = 1;
		capacity = initialCapacity;
		elements = new E[capacity];
		size = 0;
	}

	MaxHeap(const MaxHeap<E>&) = delete;
	
	void operator=(const MaxHeap<E>&) = delete;
	~MaxHeap() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == capacity)
			grow();
		elements[size] = element;
		siftUp(size);
		size++;
	}

	// Retorna el elemento sin eliminarlo
	E getMax() {
		if (size == 0) {
			throw runtime_error("Error, Heap is empty.");
		}
		return elements[0];
	}

	// Retorna y elimina el elemento mayor
	E removeMax() {
		if (size == 0) {
			throw runtime_error("Error, Heap is empty.");
		}
		E result = elements[0];
		size--;
		elements[0] = elements[size];
		siftDown(0);
		return result;
	}

	void clear() {
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}
};