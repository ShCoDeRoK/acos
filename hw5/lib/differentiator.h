#include <fstream>
#include <cstring>
#include "node.h"

class Differentiator {

  Node* head_;
  std::string expr_;

  enum Type {
    SIGN,
    FUNC,
    NUM,
    VAR,
    OPEN_BR,
    CLOSE_BR
  } type_;
  
  void build(size_t& node_index, Node* node) {
    Type type = getType(expr_[node_index]);
    Unit unit;
    Node* left, *right;
    switch (type) {

      case VAR:
        unit = Unit(Unit::VAR);
        node->setUnit(unit);
        ++node_index;
        break;

      case OPEN_BR:
        left = new Node();

        ++node_index;
        build(node_index, left);
        ++node_index;

        node->setLeft(left);

        if (node_index + 1 == expr_.size()) {
          break;
        }

        unit.setType(getSign(node_index));
        node->setUnit(unit);

        right = new Node();

        ++node_index;
        build(node_index, right);
        ++node_index;

        node->setRight(right);
        break;
  
      case FUNC: 
        unit.setType(getFunc(node_index));
        node->setUnit(unit);

        left = new Node();
            
	      ++node_index;
        build(node_index, left);
        ++node_index;
        
        node->setLeft(left);
        break;
      
      case NUM:
        unit = Unit(Unit::NUM);
        unit.setNumber(getNumber(node_index));
        node->setUnit(unit);
        break;
    }
  }

  Type getType(char& c) {
    switch (c) {
      case 's':
        return FUNC;
      case 'c':
        return FUNC;
      case '+':
	      return SIGN;
      case '-':
	      return SIGN;
      case '*':
	      return SIGN;
      case '/':
        return SIGN;
      case 'x':
        return VAR;
      case '(':
        return OPEN_BR;
      case ')':
        return CLOSE_BR;
      default:
        return NUM;
    }
  }

  int getNumber(size_t& index) {
    int num = 0;
    while (expr_[index] >= '0' && expr_[index] <= '9') {
        num = num * 10 + (expr_[index++] - '0');
    }
    return num;
  }

  Unit::Type getSign(size_t& index) {
    char sign = expr_[index++];
    switch (sign) {
        case '+':
            return Unit::PLUS;
        case '-':
            return Unit::MINUS;
        case '*':
            return Unit::MUL;
        case '/':
            return Unit::DIV;
    }
  }

  Unit::Type getFunc(size_t& index) {
    char func = expr_[index];
    index += 3;
    switch (func) {
      case 's':
        return Unit::SIN;
      case 'c':
        return Unit::COS;
    }
  }

  void makeDerivative(Node* der_node, Node* node, std::ofstream& out) {
    Unit unit;
    Node* left, *right;
    Node* left_der_node, *right_der_node;
    switch (node->getUnit().getType()) {
      
      case Unit::VAR:
        unit = Unit(Unit::NUM);
        unit.setNumber(1);
        der_node->setUnit(unit);
        break;
      
      case Unit::NUM:
        unit = Unit(Unit::NUM);
        unit.setNumber(0);
        der_node->setUnit(unit);
        break;
      
      case Unit::PLUS:
      case Unit::MINUS:
        unit = Unit(node->getUnit().getType());
        der_node->setUnit(unit);

        left_der_node = new Node();
        makeDerivative(left_der_node, node->getLeft(), out);
        der_node->setLeft(left_der_node);

        right_der_node = new Node();
        makeDerivative(right_der_node, node->getRight(), out);
        der_node->setRight(right_der_node);
        break;
      
      case Unit::MUL:
        unit = Unit(Unit::PLUS);
        der_node->setUnit(unit);
        mulDerivative(der_node, node, out);
        break;
      
      case Unit::DIV:
        unit = Unit(Unit::DIV);
        der_node->setUnit(unit);

        divDerivative(der_node, node, out);
        break;
      
      case Unit::SIN:
        unit = Unit(Unit::MUL);
        der_node->setUnit(unit);

        left = new Node(Unit::COS);
        der_node->setLeft(left);

        left->setLeft(new Node(node->getLeft()));

        right = new Node();
        der_node->setRight(right);

        makeDerivative(right, node->getLeft(), out);
        break;
        
      case Unit::COS:
        unit = Unit(Unit::MUL);
        der_node->setUnit(unit);

        left = new Node(Unit::MUL);
        der_node->setLeft(left);

        unit = Unit(Unit::NUM);
        unit.setNumber(-1);
        left->setLeft(new Node(unit));

        Node* left_right = new Node(Unit::SIN);
        left->setRight(left_right);

        left_right->setLeft(new Node(node->getLeft()));

        right = new Node();
        der_node->setRight(right);

        makeDerivative(right, node->getLeft(), out);
        break;
    }
  }

  void mulDerivative(Node* der_node, Node* node, std::ofstream &out) {
    
    Node* left = new Node(Unit::MUL);
    der_node->setLeft(left);

    Node* left_der_node = new Node();
    makeDerivative(left_der_node, node->getLeft(), out);

    Node* copy = new Node(node->getRight());

    left->setLeft(left_der_node);
    left->setRight(new Node(node->getRight()));
	
    Node* right = new Node(Unit::MUL);
    der_node->setRight(right);

    Node* right_der_node = new Node();
    makeDerivative(right_der_node, node->getRight(), out);

    right->setLeft(right_der_node);
    right->setRight(new Node(node->getLeft()));
  }

  void divDerivative(Node* der_node, Node* node, std::ofstream &out) {
    
    Node* left = new Node();
    der_node->setLeft(left);

    Unit unit(Unit::PLUS);
    left->setUnit(unit);

    mulDerivative(left, node, out);

    Node* right = new Node(Unit::MUL);

    der_node->setRight(right);

    right->setLeft(new Node(node->getRight()));
    right->setRight(new Node(node->getRight()));
  }

  void showTree(Node* node, std::ofstream &out) {
    if(node == nullptr) {
        return;
    }

    if (node->getLeft() != nullptr) {
      
      if (node->getUnit().getType() == Unit::SIN 
          || node->getUnit().getType() == Unit::COS) {
        out << node->getUnit().toString();
      }
      
      out << "(";
      showTree(node->getLeft(), out);
      out << ")";
    }

    if (!(node->getUnit().getType() == Unit::SIN 
        || node->getUnit().getType() == Unit::COS )) {
      out << node->getUnit().toString();
    }

    if (node->getRight() != nullptr) {
      
      out << "(";
      showTree(node->getRight(), out);
      out << ")";
    } 
  }

public:
  
  Differentiator(std::string expr) {
    expr_ = expr;
    head_ = new Node();
    size_t node_index = 1;
    build(node_index, head_);
    ++node_index;
  }
  
  void differentiate(std::string name) { 
    std::ofstream out;
    out.open(name);

    Node* head_derivative = new Node();
    makeDerivative(head_derivative, head_, out);

    out << "(";
    showTree(head_, out);
    out << ")'" << " = ";
    
    out << "("; 
    showTree(head_derivative, out);
    out << ")";
  }

  ~Differentiator() {}
};

