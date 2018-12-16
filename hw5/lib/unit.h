#include <cstring>

class Unit {
  
  int num_;

public:
  
  enum Type {
    PLUS,
    MINUS,
    MUL,
    DIV,
    SIN,
    COS,
    NUM,
    VAR
  } type_;
  
  Unit(Type type) : type_(type) {}
  Unit() {}

  int getNumber() const {
    return num_;
  }

  void setNumber(int num) {
    num_ = num;
  }

  Type getType() const {
    return type_;
  }

  void setType(Type type) {
    type_ = type;
  }
  
  std::string toString() const {
    if (type_ == NUM) {
      return std::to_string(num_);
    }
    switch (type_) {
    	case MUL:
     	  return " * ";
      case PLUS:
        return " + ";
      case MINUS:
        return " - ";
      case DIV:
        return " / ";
      case VAR:
        return "x";
      case SIN:
        return "sin";
      case COS:
        return "cos";
    }
  }
};

