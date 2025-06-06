#include "circle.h"
#include <iostream>
#include <error.h>

Circle::Circle() {
	head = nullptr;
	tail = nullptr;
	size = 0;
}

int Circle::length() {
	return size;
}

Circle::Node* Circle::getNode(Node* tmp, int idx) {
	int i = 0;
	while (tmp) {
		if (i == idx) {
			return tmp;
		}
		i++;
		tmp = tmp->next;
	}
	return nullptr;
}

void Circle::insert(int pos, int v) {
	Node* node = new Node();
	node->val = v;
	node->next = nullptr;
	if (size == 0) {
		head = node;
		tail = node;
		head->next = tail; 
		tail->next = head; // redundant
	} else if (pos == 0) {
		node->next = head;
		head = node;
		if (tail) { // extra check
			tail->next = node;
		}
	}
	else {
		int idx = (pos - 1) % size;
		Node* nd = getNode(head, idx);
		node->next = nd->next;
		nd->next = node;
		if (nd == tail) {
			tail = node;
		}
	}
	size++;
}

int Circle::get(int pos) {
	if (pos < 0)error("Invalid idx");
	int idx = pos % size;
	return getNode(head, idx)->val;
}

void Circle::set(int pos, int v) {
	if (pos < 0)error("Invalid idx");
	int idx = pos % size;
	Node* nd = getNode(head, idx);
	nd->val = v;
}

Circle * Circle::subCircle(int start, int end) {
	Node* node = nullptr;
	Node* tail = nullptr;
	if (start > end) {
		cout << "WRONG" << endl;
		error("STOP");
	}
	Node* nd = head;
	int i = 0;
	while (nd) {
		if (i >= end)break;
		if (i >= start && i < end) {
			Node* addable = new Node();
			addable->val = nd->val;
			addable->next = nullptr;
			if (!node) {
				node = addable;
				tail = addable;
			}
			else {
				tail->next = addable;
				tail = addable;
			}
		}
		i++;
		nd = nd->next;
	}
	if (tail) {
		tail->next = head;
	}
	Circle* c = new Circle();
	c->size = end-start;
	c->head = node;
	c->tail = tail;
	return c;
}


int Circle::contains(Circle * c) {
	Node* nd1 = head;
	Node* nd2 = c->head;
	if (!nd2)return -1;
	if (c->size > size)return -1;
	for (int i = 0; i < size; i++) {
		if (nd1->val == nd2->val) {
			Node* node1 = nd1;
			Node* node2 = nd2;
			bool b = true;
			for (int j = 0; j < c->size; j++) {
				if (node1->val != node2->val) {
					b = false;
					break;
				}
				node1 = node1->next;
				node2 = node2->next;
			}
			if (b)return i;
		}
		nd1 = nd1->next;
	}
	return -1;
}
