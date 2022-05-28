#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() { head_ = nullptr; };
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

  // custom
  void Clear();
  void DeepClone(const BLL& to_copy);
  void PushNode(Node* new_node);
  Node* PopNode();
  Node* GetNodeAt(size_t idx) const;
  Node* GetHead() const;
  void SetHead(Node* new_head) { head_ = new_head; };

private:
  Node* head_;
  bool IsBLLAcyclic() const;
};

#endif
