#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <iostream>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand();
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  Node* Head();
  Node* Tail();
  void PushBack(char ch);
  Node* Match(const char* pattern);  // returns prev node of matching sequence

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif