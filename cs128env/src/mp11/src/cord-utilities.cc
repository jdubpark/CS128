#include "cord-utilities.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  if (left_cord->IsValidCord() && right_cord->IsValidCord()) {
    // std::shared_ptr<Cord> cord_ptr =
    //     std::make_shared<Cord>(left_cord, right_cord);
    std::shared_ptr<Cord> cord_ptr =
        std::make_shared<Cord>(left_cord, right_cord);
    cord_ptr->left_ = std::move(left_cord);
    cord_ptr->right_ = std::move(right_cord);
    return cord_ptr;
  }
  throw std::invalid_argument("Invalid cord concat");
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  // TODO
  std::map<std::string, bool> found;
  for (auto cord : cords) {
    if (found.find(cord.get()->data_) == found.end()) {  // not found
      found[cord.get()->data_] = true;
    }
  }
}
