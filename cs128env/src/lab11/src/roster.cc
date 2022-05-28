#include "roster.hpp"

#include <iostream>

Roster::Roster(const Student& student) {
  head_ = make_unique<RosterEntry>(student, nullptr);
}

void Roster::AddStudent(const Student& student) {
  auto* iter = head_.get();
  if (head_ == nullptr) {
    head_ = make_unique<RosterEntry>(student, nullptr);
    return;
  }

  if (iter->student.compare(student) > 0) {
    std::unique_ptr<RosterEntry> newnode =
        make_unique<RosterEntry>(student, head_.release());
    head_.reset(newnode.release());
    return;
  }

  while (iter->next != nullptr) {
    if (iter->next->student.compare(student) < 0) {
      iter = iter->next.get();
    } else {
      break;
    }
  }
  if (iter->next == nullptr) {
    std::unique_ptr<RosterEntry> newnode =
        make_unique<RosterEntry>(student, nullptr);
    iter->next.reset(newnode.release());
  } else {
    std::unique_ptr<RosterEntry> newnode =
        make_unique<RosterEntry>(student, iter->next.release());
    iter->next.reset(newnode.release());
  }
}

Roster::Iterator Roster::begin() const { return Iterator(head_.get()); }

Roster::Iterator Roster::end() const { return Iterator(); }
