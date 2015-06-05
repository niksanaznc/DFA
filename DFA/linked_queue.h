#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

template <typename T>
struct LinkedNode {
	T data;
	LinkedNode<T> *next;
	LinkedNode(T data = 0, LinkedNode<T> *next = NULL);
};

template <typename T>
class LinkedQueue {
private:
	LinkedNode<T> *frontNode;
	LinkedNode<T> *backNode;

	void copy(const LinkedQueue<T> &other);
	void destroy();

public:
	LinkedQueue<T>();
	LinkedQueue<T>(T el);
	LinkedQueue<T>(const LinkedQueue<T> &other);
	LinkedQueue<T> &operator=(const LinkedQueue<T> &other);
	~LinkedQueue<T>();

	bool isEmpty() const;
	T front() const;
	T getSize() const;

	void push(T el);
	T pop();
};

#endif
