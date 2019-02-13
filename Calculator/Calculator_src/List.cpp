#pragma once
#include <iostream>
#include <string>
using namespace std;



template <class T> class List
{
protected:
	struct Node
	{
		Node(const T& elem, Node *head0);
		T data; Node *next; //односвязный список
	};
	Node *head;
	int size;
public:
	class Iterator
	{
	public:
		Iterator(Node *c=NULL);
		T& operator*() const;
		Iterator& operator++();
		bool OK() const;
		operator bool() const;
	protected:
		Node *current;
	};
	List();
	~List();
	int getSize() const;
	T top() const;
	T bottom() const;
	T* push(const T&);
	T* push_back(const T&);
	bool pop();
	bool pop_back();
	bool remove(const T&);
	T* find(const T&) const;
	bool empty() const;
	void clear();
	bool operator==(const List &other) const;
	Iterator begin() const;
private:
	List(const List&);
	List& operator=(const List&);
};

template <class T> List<T>::Node::Node(const T& elem, Node *head0): data(elem), next(head0) {}

template <class T> List<T>::List(): head(NULL), size(0) {}

template <class T> List<T>::~List() {clear();}

template <class T> List<T>::Iterator::Iterator(Node *c): current(c) {}

template <class T> T& List<T>::Iterator::operator *() const {return current->data;}

template <class T> typename List<T>::Iterator& List<T>::Iterator::operator ++()
{if(current) current=current->next; return *this;}

template <class T> bool List<T>::Iterator::OK() const {return (current!=NULL);}

template <class T> List<T>::Iterator::operator bool() const {return OK();}

template <class T> typename List<T>::Iterator List<T>::begin() const {return Iterator(head);}

template <class T> /* typename */ T List<T>::top() const {return head->data;}

template <class T> /* typename */ T List<T>::bottom() const
{
	Iterator cur=begin(),prev=begin();
	++cur;
	while(cur) {++cur; ++prev;}
	return (*prev);
}

template <class T> /* typename */ T* List<T>::push(const T& elem) //добавление элем вначало
{
	Node *tmp=new Node(elem,head);
	head=tmp;
	size++;
	return &(tmp->data);
}

template <class T> /* typename */ T* List<T>::push_back(const T& elem) // добавление элем вконец
{
	if(head==NULL) return push(elem);
	Node *cur=head->next, *prev=head;
	while(cur!=NULL) {cur=cur->next; prev=prev->next;}
	cur=new Node(elem,NULL);
	prev->next=cur;
	++size;
	return &(cur->data);
}

template <class T> bool List<T>::pop()
{
	if(head==NULL) return false;
	Node *tmp=head;
	head=head->next;
	delete tmp;
	--size;
	return true;
}

template <class T> bool List<T>::pop_back()
{
	if(head==NULL) return false;
	Node *cur=head->next, *prev=head;
	if(cur==NULL) {delete head; head=NULL; --size; return true;}
	while(cur->next!=NULL) {cur=cur->next; prev=prev->next;}
	prev->next=NULL;
	delete cur;
	--size;
	return true;
}

template <class T> bool List<T>::remove(const T& t)
{
	T *p=find(t);
	if(p==NULL) return false;
	Iterator i=begin();
	int k=0;
	while(!((*i)==*p)) {++i; ++k;}
	if(k==0) {Node *tmp=head->next; delete head; head=tmp; return true;}
	Node *cur=head->next, *prev=head;
	for(int l=1; l<k; ++l) {cur=cur->next; prev=prev->next;}
	prev->next=cur->next;
	delete cur;
	return true;
}

template <class T> /* typename */ T* List<T>::find(const T& elem) const
{
	Iterator i=begin();
	while(i && !((*i)==elem)) ++i;
	return &(*i);
}

template <class T> int List<T>::getSize() const {return size;}

template <class T> bool List<T>::empty() const {return size==0;}

template <class T> void List<T>::clear()
{
	Node *tmp;
	while(head!=NULL)
	{
		tmp=head->next;
		delete head;
		head=tmp;
	}
	size=0;
}

template <class T> bool List<T>::operator==(const List<T> &other) const
{
	if(getSize()!=other.getSize()) return false;
	int n=getSize();
	Iterator i1=begin(), i2=other.begin();
	bool flag=true;
	while(i1 && i2 && flag)
	{
		if(!((*i1)==(*i2))) flag=false;
		++i1; ++i2;
	}
	return flag;
}