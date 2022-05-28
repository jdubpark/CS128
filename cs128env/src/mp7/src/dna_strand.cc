#include "dna_strand.hpp"

#include <stdexcept>

#define MAXC 1024

// Returns string length for const char*
int StringLength(const char* str) {
  int len = 0;
  while (str[len] != '\0') len++;
  return len;
}

DNAstrand::DNAstrand() { head_ = tail_ = nullptr; }

// Something something deallocate
DNAstrand::~DNAstrand() {
  Node* next = head_;
  while (next != nullptr) {
    next = head_->next;
    delete head_;
    head_ = next;
  }
  head_ = tail_ = nullptr;
}

void DNAstrand::PushBack(char ch) {
  Node* node = new Node(ch);
  if (head_ == nullptr) {
    head_ = tail_ = node;
  } else {
    tail_->next = node;
    tail_ = node;
  }
}

Node* DNAstrand::Head() { return head_; }
Node* DNAstrand::Tail() { return tail_; }

Node* DNAstrand::Match(const char* pattern) {
  Node *match = nullptr, *start = nullptr, *prev = head_, *cur = head_;
  int idx = 0, len = StringLength(pattern);
  while (cur != nullptr) {
    if (cur->data == pattern[idx]) {
      if (idx == 0) {
        start = prev;
      }
      if (idx + 1 == len) {
        match = start;  // full match
        idx = -1;       // ++ later
      }
      idx++;
    } else {
      idx = 0;  // no match, reset
    }
    prev = cur;
    cur = cur->next;
  }
  delete cur;
  return match;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  // empty pattern and/or empty to_splice_in object are/is passed
  if (pattern == nullptr || to_splice_in.head_ == nullptr ||
      &to_splice_in == this || to_splice_in.head_->data == '\0') {
    return;
  }

  Node* start = Match(pattern);  // one node before the (next) cleave
  if (start == nullptr) {
    delete start;
    throw std::runtime_error("no match");
  }

  Node* end = nullptr;
  if (end != head_) {
    end = start->next;
  } else {
    end = start;
  }

  for (int i = 0; i < StringLength(pattern); i++) {
    // remove all cleaved nodes
    Node* tmp = end->next;
    delete end;
    end = tmp;
  }

  if (start == head_) {
    head_ = to_splice_in.head_;
  } else {
    start->next = to_splice_in.head_;
  }

  if (end != nullptr) {
    to_splice_in.tail_->next = end;
  } else {
    tail_ = to_splice_in.tail_;
  }

  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}