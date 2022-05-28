#include "branched-linked-list.hpp"

void BLL::Clear() {
  Node* cur = head_;
  while (cur != nullptr) {
    if (cur->next_bll_ != nullptr) {
      cur->next_bll_->~BLL();    // use recursive destructor
      delete cur->next_bll_;     // delete from heap space
      cur->next_bll_ = nullptr;  // set to nullptr
    }
    Node* next = cur->next_node_;
    delete cur;
    cur = next;
  }
  cur = head_ = nullptr;
}

void BLL::DeepClone(const BLL& to_copy) {
  if (&to_copy == this) {
    return;
  }
  if ((&to_copy)->head_ == nullptr) {
    return;
  }
  Node* copy_cur = to_copy.head_;
  Node* cur = new Node(copy_cur->data_);
  // special case: head
  if (copy_cur->next_bll_ != nullptr) {
    cur->next_bll_ = new BLL(*copy_cur->next_bll_);
  }
  head_ = cur;
  // from next node of head
  copy_cur = copy_cur->next_node_;
  while (copy_cur != nullptr) {
    cur->next_node_ = new Node(copy_cur->data_);
    if (copy_cur->next_bll_ != nullptr) {
      cur->next_node_->next_bll_ = new BLL(*(copy_cur->next_bll_));
    }
    cur = cur->next_node_;
    copy_cur = copy_cur->next_node_;
  }
}

void DeepCloneSrcToTarget(BLL* src, const BLL& to_copy) {
  if ((&to_copy)->GetHead() == nullptr) {
    return;
  }
  Node* copy_cur = to_copy.GetHead();
  Node* cur = new Node(copy_cur->data_);
  // special case: head
  if (copy_cur->next_bll_ != nullptr) {
    cur->next_bll_ = new BLL(*copy_cur->next_bll_);
  }
  src->SetHead(cur);
  // from next node of head
  copy_cur = copy_cur->next_node_;
  while (copy_cur != nullptr) {
    cur->next_node_ = new Node(copy_cur->data_);
    if (copy_cur->next_bll_ != nullptr) {
      cur->next_node_->next_bll_ = new BLL(*(copy_cur->next_bll_));
    }
    cur = cur->next_node_;
    copy_cur = copy_cur->next_node_;
  }
}

BLL::BLL(const BLL& to_copy) {
  if (&to_copy == this) {
    return;
  }
  head_ = nullptr;  // must init before cloing
  DeepClone(to_copy);
}

BLL::~BLL() { Clear(); }

BLL& BLL::operator=(const BLL& rhs) {
  if (&rhs == this) {
    return *this;
  }
  Clear();
  if ((&rhs)->head_ != nullptr) {
    DeepClone(rhs);
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* new_node = new Node(dat);
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    Node* tmp = head_;
    while (tmp->next_node_ != nullptr) {
      tmp = tmp->next_node_;
    }
    tmp->next_node_ = new_node;
  }
  return new_node;
}

void BLL::PushNode(Node* new_node) {
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    Node* tmp = head_;
    while (tmp->next_node_ != nullptr) {
      tmp = tmp->next_node_;
    }
    tmp->next_node_ = new_node;
  }
}

Node* BLL::PopNode() {
  if (head_ == nullptr) {
    // throw std::runtime_error("Nothing to pop");
    return nullptr;
  }
  if (head_->next_node_ == nullptr) {
    Node* tmp = head_;
    head_ = nullptr;  // NOTE: Can we use delete, and will it work? Since it
                      // deletes before returning the pointer to that node.
    return tmp;
  }
  Node* prev = nullptr;
  Node* tmp = head_;
  while (tmp->next_node_ != nullptr) {
    prev = tmp;
    tmp = tmp->next_node_;
  }
  prev->next_node_ = nullptr;
  return tmp;
}

char BLL::GetAt(size_t idx) const {
  if (head_ == nullptr) {
    throw std::runtime_error("GetAt: No head found");
  }
  if (idx > Size() - 1) {
    throw std::runtime_error("GetAt: OOB");
  }
  std::string full_str = ToString();
  return full_str.at(idx);
}

Node* BLL::GetNodeAt(size_t idx) const {
  if (head_ == nullptr) {
    throw std::runtime_error("GetNodeAt: No head found");
  }
  if (idx > Size() - 1) {
    throw std::runtime_error("GetNodeAt: OOB");
  }
  Node* cur = head_;
  size_t count = idx;
  while (cur != nullptr) {
    if (count == 0) {
      break;
    }
    if (cur->next_bll_ != nullptr) {
      // child bll exists, get its size and check if:
      // count - size > 0 -- means next bll doesn't hit the required idx
      //  thus move to the next node (skip current node's next bll)
      size_t next_bll_size = cur->next_bll_->Size();
      if (count > next_bll_size) {
        count--;
        cur = cur->next_node_;
      } else {
        // count hits 0 is within the next bll
        return cur->next_bll_->GetNodeAt(count - 1);
      }
    } else {
      count--;
      cur = cur->next_node_;
    }
  }
  return cur;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx > Size() - 1 || head_ == nullptr) {
    throw std::runtime_error("SetAt: OOB");
  }
  Node* cur = head_;
  size_t count = idx;
  while (cur != nullptr) {
    if (count == 0) {  // base case
      cur->data_ = dat;
      return;
    }
    if (cur->next_bll_ != nullptr) {
      // child bll exists, get its size and check if:
      // count - size > 0 -- means next bll doesn't hit the required idx
      //  thus move to the next node (skip current node's next bll)
      size_t next_bll_size = cur->next_bll_->Size();
      if (count > next_bll_size) {
        count--;
        cur = cur->next_node_;
      } else {
        // count hits 0 is within the next bll
        return cur->next_bll_->SetAt(count - 1, dat);
      }
    } else {
      count--;
      cur = cur->next_node_;
    }
  }
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx > Size() - 1) {
    throw std::runtime_error("Join: OOB");
  }
  Node* cur = head_;
  size_t count = idx;
  while (cur != nullptr) {
    if (count == 0) {  // base case, join
      if (cur->next_bll_ != nullptr) {
        throw std::runtime_error("BLL for the node already exists");
      }
      cur->next_bll_ = list;
      break;
    }
    if (cur->next_bll_ != nullptr) {
      size_t next_bll_size = cur->next_bll_->Size();
      if (count > next_bll_size) {
        count--;
        cur = cur->next_node_;
      } else {
        cur->next_bll_->Join(count - 1, list);
        break;
      }
    } else {
      count--;
      cur = cur->next_node_;
    }
  }
  // check if acyclic
  if (!IsBLLAcyclic()) {
    throw std::runtime_error("BLL is cyclic now!");
  }
}

std::string BLL::ToString() const {
  if (head_ == nullptr) {
    return "";
  }
  std::string str;
  Node* cur = head_;
  while (cur != nullptr) {
    str.push_back(cur->data_);
    if (cur->next_bll_ != nullptr) {
      std::string next_bll_str = cur->next_bll_->ToString();
      str += next_bll_str;
    }
    cur = cur->next_node_;
  }
  return str;
}

size_t BLL::Size() const {
  if (head_ == nullptr) {
    return 0;
  }
  size_t size = 0;
  Node* cur = head_;
  while (cur != nullptr) {
    if (cur->next_bll_ != nullptr) {
      size_t next_bll_size = cur->next_bll_->Size();
      size += next_bll_size;
    }
    size++;
    cur = cur->next_node_;
  }
  return size;
}

Node* BLL::GetHead() const { return head_; }

BLL* Flatten(BLL* bll, Node* chain_node) {
  Node* prev = nullptr;
  Node* cur = bll->GetHead();
  // std::cout << "flatten" << std::endl;
  while (cur != nullptr) {
    if (cur->next_bll_ != nullptr) {
      // std::cout << "flatten child bll" << std::endl;
      Node* next = cur->next_node_;
      BLL* child_bll = Flatten(cur->next_bll_, next);
      cur->next_node_ = child_bll->GetHead();
    }
    prev = cur;
    cur = cur->next_node_;
  }
  if (prev != nullptr) {
    // std::cout << "flatten child bll connect" << std::endl;
    prev->next_node_ = chain_node;
  }
  return bll;
}

// two-pointer (slow turtoise & fast hare) method
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  bool is_acyclic = true;  // acyclic by default
  // std::cout << "acyclic" << std::endl;
  BLL* flat_bll = new BLL();
  DeepCloneSrcToTarget(flat_bll, *this);
  Flatten(flat_bll, nullptr);
  Node* slow = flat_bll->head_;
  Node* fast = flat_bll->head_->next_node_;
  while (slow != nullptr && fast != nullptr && fast->next_node_ != nullptr) {
    if (slow == fast) {
      is_acyclic = false;  // bll is cyclic
      break;
    }
    // std::cout << "next" << std::endl;
    slow = slow->next_node_;
    fast = fast->next_node_->next_node_;
  }
  // flat_bll->~BLL();
  // delete flat_bll;
  slow = fast = nullptr;
  return is_acyclic;
}

// two-pointer (slow turtoise & fast hare) method
// if (head_ == nullptr) {
//   return true;
// }
// Node* slow = head_;
// Node* fast = head_->next_node_;
// while (slow != nullptr && fast != nullptr && fast->next_node_ != nullptr) {
//   if (slow == fast) {
//     return false;  // bll is cyclic
//   }

//   slow = slow->next_node_;
//   fast = fast->next_node_->next_node_;
// }
// return true;  // bll is acyclic
