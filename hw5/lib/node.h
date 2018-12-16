#include "unit.h"

class Node {
  Node* left_ = nullptr;
  Node* right_ = nullptr;
  Unit unit_;
public:
  
  Node() {};
  Node(Node* node) {
    
    if (node == nullptr) {
      return;
    }
    unit_ = node->getUnit();
    if (node->getLeft() != nullptr) {
      left_ = new Node(node->getLeft());
    }

    if (node->getRight() != nullptr) {
      right_ = new Node(node->getRight());
    }
  }

  Node(Unit::Type type) {
    unit_ = Unit(type);
  }

  Node(const Unit& unit) : unit_(unit) {}
  
  Node* getLeft() const {
    return left_;
  }

  void setLeft(Node* left) {
    left_ = left;
  }
  
  Node* getRight() const {
    return right_;
  }

  void setRight(Node* right) {
    right_ = right;
  }

  const Unit& getUnit() const {
    return unit_;
  }

  void setUnit(const Unit& unit) {
    unit_ = unit;
  }


  void copy(Node* parent_node) {
    unit_ = parent_node->getUnit();
    left_ = parent_node->getLeft();
    right_ = parent_node->getRight();
  }

  int getPrior() {
    switch (unit_.getType()) {
      case Unit::PLUS:
	return 1;
      case Unit::MINUS:
        return 1;
      case Unit::MUL:
	return 2;
      case Unit::DIV:
        return 2;
      case Unit::SIN:
	return 3;
      case Unit::COS:
        return 3;
      case Unit::NUM:
	return 0;
      case Unit::VAR:
        return 0;
    }
  }
};
