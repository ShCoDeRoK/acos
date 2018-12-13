#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include "assembler.h"
#include "stack.h"

class Processor {

  const float EPS = 1e-8;
  const size_t COMMAND_LENGTH = 3;

  enum {
      PUSH,
      POP,
      ADD,
      SUB,
      MUL,
      DIV,
      SIN,
      COS,
      SQRT,
      IN,
      OUT,
      JMP,
      JE,
      JNE,
      JA,
      JAE,
      JB,
      JBE,
      PUSH_REG,
      POP_REG,
      PUSH_RAM_REG,
      PUSH_RAM_NUM,
      POP_RAM_REG,
      POP_RAM_NUM
  };

  Assembler assembler_;
  Stack<float> stack_ = Stack<float>(false);
  int* program_;
  size_t num_commands_;
  int registers_[26];
  int ram_[(1 << 16)];

  void jump(int command, int& ip) {
    float a = stack_.pop();
    float b = stack_.pop();
    
    

    if (command == JMP)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JE && abs(a - b) < EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JNE && abs(a - b) > EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JA && a - b > EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JAE && b - a < EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JB && b - a > EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;
    if (command == JBE && a - b < EPS)
      ip = program_[COMMAND_LENGTH * ip + 1] - 1;

    stack_.push(b);
    stack_.push(a);
  }

  void processProgram() {
    int ip = 0;
    while (ip < num_commands_) {
      if (ip < 0) {
        printf("ERROR.\n");
        printf("ip < 0\n");
        exit(1);
      }
      float res;
      
      switch (program_[COMMAND_LENGTH * ip]) {
        case PUSH:
          stack_.push(program_[COMMAND_LENGTH * ip + 1]);
          break;
        case POP:
          stack_.pop();
          break;
        case ADD:
          res = stack_.pop();
          res += stack_.pop();
          stack_.push(res);
          break;
        case SUB:
          res = -stack_.pop();
          res += stack_.pop();
          stack_.push(res);
          break;
        case MUL:
          res = stack_.pop();
          res *= stack_.pop();
          stack_.push(res);
          break;
        case DIV:
          res = stack_.pop();
          res /= stack_.pop();
          stack_.push(res);
          break;
        case SIN:
          res = stack_.pop();
          stack_.push(sin(res));
          break;
        case COS:
          res = stack_.pop();
          stack_.push(cos(res));
          break;
        case SQRT:
          res = stack_.pop();
          stack_.push(sqrt(res));
          break;
        case IN:
          res;
          scanf("%f", &res);
          stack_.push(res);
          break;
        case OUT:
          res = stack_.pop();
          printf("%.2f\n", res);
          stack_.push(res);
          break;
        case JMP:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JE:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JNE:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JA:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JAE:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JB:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case JBE:
          jump(program_[COMMAND_LENGTH * ip], ip);
          break;
        case PUSH_REG:
          stack_.push(registers_[program_[COMMAND_LENGTH * ip + 1]]);
          break;
        case POP_REG:
          registers_[program_[COMMAND_LENGTH * ip + 1]] = stack_.pop();
          break;
        case PUSH_RAM_REG:
          stack_.push(ram_[registers_[program_[COMMAND_LENGTH * ip + 1]]]);
          break;
        case PUSH_RAM_NUM:
          stack_.push(ram_[program_[COMMAND_LENGTH * ip + 1]]);
          break;
        case POP_RAM_REG:
          ram_[registers_[program_[COMMAND_LENGTH * ip + 1]]] = stack_.pop();
          break;
        case POP_RAM_NUM:
          ram_[program_[COMMAND_LENGTH * ip + 1]] = stack_.pop();
          break;
        default:
          printf("Something went wrong:(\n");
      }
      ++ip;
    }
  }
public:
  
  Processor() {
    memset(registers_, 0, sizeof(registers_));
    memset(ram_, 0, sizeof(ram_));
  }
  ~Processor() {}

  void process(const char* text) {
    std::pair<int*, size_t> result = assembler_.getProgram(text);
    program_ = result.first;
    num_commands_ = result.second;
    processProgram();
  }
};
