// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <iostream>
#include <string>

#include "circular-linked-list.hpp"
#include "node.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("Empty List", "[node-0]") {
//   auto* cll = new CircularLinkedList<int>();
//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("One Node List", "[node-1]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(16);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Two Node List 1", "[node-2-1]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(32);  // NOLINT
//   cll->InsertInOrder(10);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Two Node List 2", "[node-2-2]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(16);  // NOLINT
//   cll->InsertInOrder(95);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Two Node List 3", "[node-2-3]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(10);  // NOLINT
//   cll->InsertInOrder(10);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Three Node List 1", "[node-3-1]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(3);  // NOLINT
//   cll->InsertInOrder(9);  // NOLINT
//   cll->InsertInOrder(6);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Four Node List 1", "[node-4-1]") {
//   CircularLinkedList<int> cll;
//   cll.InsertInOrder(3);   // NOLINT
//   cll.InsertInOrder(12);  // NOLINT
//   cll.InsertInOrder(9);   // NOLINT
//   cll.InsertInOrder(6);   // NOLINT

//   std::cout << cll << std::endl;
//   cll.Reverse();
//   std::cout << cll << std::endl;
// }

// TEST_CASE("Four Node List 2", "[node-4-2]") {
//   auto* cll = new CircularLinkedList<int>();
//   cll->InsertInOrder(3);   // NOLINT
//   cll->InsertInOrder(12);  // NOLINT
//   cll->InsertInOrder(6);   // NOLINT
//   cll->InsertInOrder(77);  // NOLINT

//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Four Node List 3", "[node-4-3]") {
//   CircularLinkedList<int> cll;
//   cll.Reverse();
//   cll.InsertInOrder(47);  // NOLINT
//   cll.InsertInOrder(98);  // NOLINT
//   cll.InsertInOrder(56);  // NOLINT
//   cll.InsertInOrder(12);  // NOLINT

//   std::cout << cll << std::endl;
//   cll.Reverse();
//   std::cout << cll << std::endl;
// }

// // TEST_CASE("Destruct manual", "[destruct-1]") {
// //   CircularLinkedList<int> cll;
// //   cll.InsertInOrder(47);  // NOLINT
// //   cll.InsertInOrder(98);  // NOLINT
// //   cll.InsertInOrder(56);  // NOLINT
// //   cll.InsertInOrder(12);  // NOLINT
// //   cll.DestructCLL();
// //   std::cout << cll << std::endl;
// // }

// TEST_CASE("3 node string", "[3-node-string]") {
//   auto* cll = new CircularLinkedList<std::string>();
//   cll->Reverse();
//   cll->InsertInOrder("hello");    // NOLINT
//   cll->InsertInOrder("welcome");  // NOLINT
//   cll->InsertInOrder("bye");      // NOLINT
//   std::cout << *cll << std::endl;
//   cll->Reverse();
//   std::cout << *cll << std::endl;
// }

// TEST_CASE("Copy operator", "[copy-1]") {
//   CircularLinkedList<int> cll;
//   cll.InsertInOrder(47);  // NOLINT
//   cll.InsertInOrder(98);  // NOLINT
//   cll.InsertInOrder(56);  // NOLINT
//   cll.InsertInOrder(12);  // NOLINT

//   CircularLinkedList<int> cll2;
//   cll2 = cll;
//   std::cout << cll2 << std::endl;
// }

// TEST_CASE("Default constructor", "[constructor-1]") {
//   CircularLinkedList<int> cll;
//   std::cout << cll << std::endl;
// }

// TEST_CASE("Copy constructor", "[constructor-2]") {
//   CircularLinkedList<int> cll;
//   cll.InsertInOrder(47);

//   CircularLinkedList<int> cll2 = CircularLinkedList<int>(cll);

//   std::cout << cll2 << std::endl;
// }

/////////////////////////////////////////////////////////////////////////////////////////////