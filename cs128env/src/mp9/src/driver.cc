#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << " (hi)" << std::endl;  // hi
  std::cout << first->Size() << " (2)" << std::endl;       // 2
  std::cout << first->GetAt(0) << " (h)" << std::endl;     // h

  try {
    std::cout << first->GetAt(6) << " (?)" << std::endl;
  } catch (const std::runtime_error& error) {
    std::cout << "[Caught] GetAt(6) OOB" << std::endl;
  }

  BLL* first_cons = new BLL(*first);
  std::cout << first_cons->ToString() << " (hi)" << std::endl;  // hi
  std::cout << first->Size() << " (2)" << std::endl;            // 2
  std::cout << first->GetAt(0) << " (h)" << std::endl;          // h

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << " (i!@)" << std::endl;  // i!@
  std::cout << second->Size() << " (3)" << std::endl;        // 3
  std::cout << second->GetAt(1) << " (!)" << std::endl;      // !

  // /////////////////////////////////////

  first->Join(1, second);
  try {
    first->Join(1, second);
  } catch (const std::runtime_error& error) {
    std::cout << "[Caught] Joining on node that already has bll" << std::endl;
  }

  std::cout << first->ToString() << " (hii!@)" << std::endl;  // hii!@
  std::cout << first->Size() << " (5)" << std::endl;          // 5
  std::cout << first->GetAt(2) << first->GetAt(4) << " (i@)"
            << std::endl;  // i@

  std::cout << second->ToString() << " (i!@)" << std::endl;  // i!@
  std::cout << second->Size() << " (3)" << std::endl;        // 3

  // /////////////////////////////////////

  first->PushBack('?');
  first->PushBack('p');
  std::cout << first->ToString() << " (hii!@?p)" << std::endl;
  std::cout << first->GetAt(5) << " (?)" << std::endl;

  // /////////////////////////////////////

  BLL* first_clone = new BLL();
  *first_clone = *first;

  std::cout << first_clone->ToString() << " (hii!@?p)" << std::endl;
  std::cout << first_clone->Size() << " (7)" << std::endl;

  // /////////////////////////////////////

  // BLL* third = new BLL();
  // third->PushBack('x');
  // third->PushBack('y');
  // third->PushBack('z');
  // third->PushNode(first->GetNodeAt(1));

  // std::cout << third->ToString() << " (xyzii!@?p)" << std::endl;
  // std::cout << third->Size() << " (9)" << std::endl;

  try {
    first->Join(0, first);
  } catch (const std::runtime_error& error) {
    std::cout << "[Caught] Joining makes it cyclic" << std::endl;
  }

  // first->~BLL();
  // first_cons->~BLL();

  return 0;
}
