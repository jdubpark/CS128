#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;

  CircularLinkedList(const CircularLinkedList<T>& source);

  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

  void InsertInOrder(const T& data);
  void Reverse();
  void ClearLL();

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (&source == this || source.head_ == nullptr || source.tail_ == nullptr) {
    return;
  }
  node_order_ = source.node_order_;  // copy order
  Node<T>* src_node = source.head_;  // start at head
  auto* dest_node = new Node<T>(src_node->data);
  head_ = dest_node;

  if (source.head_->next != source.head_) {
    // only if there's more than one node (next != head)
    src_node = src_node->next;
    while (src_node != source.head_) {
      dest_node->next = new Node<T>(src_node->data);
      dest_node = dest_node->next;
      src_node = src_node->next;
    }
  }
  dest_node->next = head_;
  tail_ = dest_node;
  // cleanup
  src_node = dest_node = nullptr;
  delete src_node;
  delete dest_node;
}

template <typename T>
void CircularLinkedList<T>::ClearLL() {
  Node<T>* tmp = head_;
  tail_->next = nullptr;  // single LL
  while (head_ != nullptr) {
    tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  head_ = tail_ = nullptr;
  delete tmp;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;  // copy order
  if (&source == this) {
    return *this;
  }
  if (source.head_ == nullptr || source.tail_ == nullptr) {
    head_ = tail_ = nullptr;
    return *this;
  }

  // clear the current linked list
  if (head_ != nullptr) {
    ClearLL();
  }

  // ** same as the parameterized constructor **
  Node<T>* src_node = source.head_;  // start at head
  auto* dest_node = new Node<T>(src_node->data);
  head_ = dest_node;
  if (source.head_->next != source.head_) {
    // only if there's more than one node (next != head)
    src_node = src_node->next;
    while (src_node != source.head_) {
      dest_node->next = new Node<T>(src_node->data);
      dest_node = dest_node->next;
      src_node = src_node->next;
    }
  }
  dest_node->next = head_;
  tail_ = dest_node;
  // cleanup
  src_node = dest_node = nullptr;
  delete src_node;
  delete dest_node;
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr || tail_ == nullptr) {
    return;  // empty list check
  }
  Node<T>* tmp = head_;
  tail_->next = nullptr;  // single LL
  while (head_ != nullptr) {
    tmp = head_->next;
    delete head_;
    head_ = tmp;
  }
  head_ = tail_ = nullptr;
  delete tmp;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  auto* new_node = new Node<T>(data);
  if (head_ == nullptr) {
    new_node->next = new_node;
    head_ = tail_ = new_node;
    return;
  }
  tail_->next = nullptr;  // make it singly LL
  if ((node_order_ == Order::kASC && data <= head_->data) ||
      (node_order_ == Order::kDESC && data >= head_->data)) {
    // insert as first node
    new_node->next = head_;
    head_ = new_node;
  } else if (head_->next == nullptr) {
    new_node->next = head_;
    tail_ = new_node;
    head_->next = tail_;
  } else {
    // somewhere in the middle?
    Node<T>* insert = head_;  // node (point of insertion)
    while (insert->next != nullptr &&
           ((node_order_ == Order::kASC && data >= insert->next->data) ||
            (node_order_ == Order::kDESC && data <= insert->next->data))) {
      insert = insert->next;
    }
    if (insert->next == nullptr) {  // insert as the last node (new tail)
      new_node->next = head_;
      insert->next = new_node;
      tail_ = new_node;
    } else {
      new_node->next = insert->next;
      insert->next = new_node;
    }
  }
  tail_->next = head_;  // redo circular LL
  new_node = nullptr;
  delete new_node;
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  // always flip node order
  node_order_ = node_order_ == Order::kASC ? Order::kDESC : Order::kASC;
  if (head_ == nullptr || tail_ == nullptr || head_->next == head_) {
    return;
  }
  if (head_->next == tail_) {  // just switch head and tail (2 nodes)
    Node<T>* tmp = head_;
    head_ = tail_;
    tail_ = tmp;
    return;
  }
  // 3 node or more
  tail_->next = nullptr;  // cut off last pointer, now a singly linked list
  Node<T>*prev = nullptr, *cur = head_;
  while (cur != nullptr) {
    Node<T>* next = cur->next;  // save node t+1
    cur->next = prev;           // link to node t-1 (reversing the next to prev)
    prev = cur;                 // node t-1 is now node t
    cur = next;                 // node t is now node t+1
  }
  tail_ = head_;        // head becomes the new tail
  head_ = prev;         // Point head to the last node (new head)
  tail_->next = head_;  // Route tail's next to the new head
  // cleanup
  prev = cur = nullptr;
  delete prev;
  delete cur;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif