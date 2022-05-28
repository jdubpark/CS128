#include "cord.hpp"

#include "cord-utilities.hpp"

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord,
           const std::shared_ptr<Cord>& right_cord) {
  //  std::make_shared<T>
  left_ = left_cord != nullptr ? left_cord : nullptr;
  right_ = right_cord != nullptr ? right_cord : nullptr;
  length_ = (left_cord != nullptr ? left_cord->Length() : 0) +
            (right_cord != nullptr ? right_cord->Length() : 0);
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  // std::string str = data_;
  if (left_ == nullptr && right_ == nullptr) return data_;
  return left_->ToString() + right_->ToString();
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  size_t left = lower_idx;
  size_t right = upper_idx;
  if (upper_idx == Length() && lower_idx == 0) {
    return std::make_shared<Cord>(left_, right_);
  }
  if (left_ == nullptr && right_ == nullptr &&
      upper_idx - lower_idx < length_) {
    right = upper_idx - lower_idx;
    return std::make_shared<Cord>(data_.substr(left, right));
  }

  if (lower_idx >= left_->Length() && upper_idx > left_->Length()) {
    left = lower_idx - left_->Length();
    right = upper_idx - left_->Length();
    return GetRight()->SubString(left, right);
  }

  if (lower_idx < left_->Length() && upper_idx <= left_->Length())
    return GetLeft()->SubString(left, right);

  if (lower_idx < left_->Length() && upper_idx > left_->Length())
    return std::make_shared<Cord>(
        left_->SubString(lower_idx, left_->Length()),
        right_->SubString(0, upper_idx - left_->Length()));

  return nullptr;
}

char Cord::At(size_t idx) const {
  if (idx >= length_) throw std::invalid_argument("Index OOR");
  return left_ == nullptr && right_ == nullptr
             ? data_.at(idx)
             : left_->length_ > idx ? left_->At(idx)
                                    : right_->At(idx - left_->length_);
}

bool Cord::IsValidCord() const {
  if (left_ == nullptr && right_ == nullptr) return data_.length() == length_;

  if (left_ != nullptr || right_ != nullptr) {  // has children
    return (left_ != nullptr ? left_->length_ : 0) +
               (right_ != nullptr ? right_->length_ : 0) ==
           length_;
  }

  return false;
}
