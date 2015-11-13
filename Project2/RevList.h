//
// Name :         RevList.h
// Description :  Simple doubly linked list with reversing feature.
//

#ifndef REVLIST_H
#define REVLIST_H

//#include <iostream>

template<class T> class CRevList
{

public:
  // Constructor.  Sets to an empty list.
  CRevList() 
  {
  }

  // Destructor.  Deletes everything in the list.
  ~CRevList()
  {
  }

  // Copy constructor.  Copies another list.
  CRevList(const CRevList &b)
  {
  }

  // Assignment operator.  Copies another list.
  void operator=(const CRevList &b);

  // Clear the list.
  void Clear()
  {
  }


  //
  // class Node
  // The nested node class for objects in our linked list.
  //
  // YOU MAY NOT MODIFY THIS CLASS!
  class Node 
  {
  public:
    friend class CRevList;
  
    Node() {m_next = 0;  m_prev = 0;}
    Node(const T &t) {m_payload = t;  m_next = 0;  m_prev = 0;}
  
    T Data() {return m_payload;}
    const T Data() const {return m_payload;}
  
  private:
    Node    *m_next;
    Node    *m_prev;
    T       m_payload;
  };
  
  // Determines if the list is empty
  bool IsEmpty() const {}

  //methods to add data to the front or the back of the list
  void PushFront(const T &t) {}
  void PushBack(const T &t) {}
  void PopFront() {}
  void PopBack() {}

  //Get a pointer to the first node in the list
  const Node *Begin() const {}
  Node *Begin() {}

  //get a pointer to the last node in the list
  const Node *End() const {}
  Node *End() {}

  //get a pointer to node next in the list
  const Node *Next(const Node *n) const {  }
  Node *Next(const Node *n) {}

  //Find a node with the specified key
  const Node *Find(const T &t) const {  }
  Node *Find(const T &t) {}

  //Delete the given node
  void Delete(Node *n){}

  //Reverse the list in O(1) time
  void Reverse() {}

  

private:

  //NOTE: you may add any private member variables or 
  //      methods you need to complete the implementation

  Node    m_head;             // Head node
};

// Assignment operator.  Copies another list.
template<class T> void CRevList<T>::operator=(const CRevList<T> &b)
{}

//template<class T> (CRevList<T>::Node *) CRevList<T>::Begin1() {return m_reverse ? m_head.m_prev : m_head.m_next;}


#endif
