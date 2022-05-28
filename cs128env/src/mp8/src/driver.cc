#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  // Insert nodes in ascending order (1, 2, 3, 4)
  CircularLinkedList<int> cll1;
  cll1.InsertInOrder(1);  // NOLINT
  cll1.InsertInOrder(2);  // NOLINT
  cll1.InsertInOrder(3);  // NOLINT
  cll1.InsertInOrder(4);  // NOLINT
  std::cout << cll1 << std::endl;

  // Insert nodes in descending order (4, 3, 2, 1)
  CircularLinkedList<int> cll2;
  cll2.InsertInOrder(4);  // NOLINT
  cll2.InsertInOrder(3);  // NOLINT
  cll2.InsertInOrder(2);  // NOLINT
  cll2.InsertInOrder(1);  // NOLINT
  std::cout << cll2 << std::endl;

  // Insert the same value consequtively (1, 1, 1, 1)
  CircularLinkedList<int> cll3;
  cll3.InsertInOrder(1);  // NOLINT
  cll3.InsertInOrder(1);  // NOLINT
  cll3.InsertInOrder(1);  // NOLINT
  cll3.InsertInOrder(1);  // NOLINT
  std::cout << cll3 << std::endl;

  // Insert only negative (-1, -2, -3, -4)
  CircularLinkedList<int> cll4;
  cll4.InsertInOrder(-1);  // NOLINT
  cll4.InsertInOrder(-2);  // NOLINT
  cll4.InsertInOrder(-3);  // NOLINT
  cll4.InsertInOrder(-4);  // NOLINT
  std::cout << cll4 << std::endl;

  // Insert only 0 (0, 0, 0, 0)
  CircularLinkedList<int> cll5;
  cll5.InsertInOrder(0);  // NOLINT
  cll5.InsertInOrder(0);  // NOLINT
  cll5.InsertInOrder(0);  // NOLINT
  cll5.InsertInOrder(0);  // NOLINT
  std::cout << cll5 << std::endl;

  // Insert the same value at least once (1, 2, 3, 1)
  CircularLinkedList<int> cll6;
  cll6.InsertInOrder(1);  // NOLINT
  cll6.InsertInOrder(2);  // NOLINT
  cll6.InsertInOrder(3);  // NOLINT
  cll6.InsertInOrder(1);  // NOLINT
  std::cout << cll6 << std::endl;

  CircularLinkedList<int> cll7;
  cll7.InsertInOrder(4);
  cll7 = cll1;
  std::cout << cll7 << std::endl;
  cll7 = cll2;
  std::cout << cll7 << std::endl;
  cll7 = cll3;
  std::cout << cll7 << std::endl;
  cll7 = cll4;
  std::cout << cll7 << std::endl;
  cll7 = cll5;
  std::cout << cll7 << std::endl;
  cll7 = cll6;
  std::cout << cll7 << std::endl;
}
