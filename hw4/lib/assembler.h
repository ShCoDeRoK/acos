#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

class Assembler {
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

  int* program_;
  std::map<std::string, int> types_of_commands_;
  std::map<std::string, int> label_;

  int getNum(const char* text, size_t& id) {
    int num = 0;
    bool minus = false;
    if (text[id] == '-') {
      minus = true;
      ++id;
    }
    while (text[id] != ' ' && text[id] != '\n') {
      if (text[id] < '0' || text[id] > '9') {
        printf("ERROR.\n");
        printf("Wrong symbol in programm: %c\n", text[id]);
        exit(1);
      }
      num = num * 10 + text[id] - '0';
      ++id;
    }
    if (minus)
      num *= -1;
    return num;
  }

  std::string getCommand(const char* text, size_t& id) {
    std::string command = "";
    while (text[id] != ' ' && text[id] != '\n')
      command.push_back(text[id++]);
    return command;
  }

  void checkNumArgs(const std::string& command, int given, int expected) {
    if (given != expected) {
      printf("ERROR.\n");
      printf("Wrong number of arguments of command \'%s\'.\n", command.c_str());
      printf("Expected: %d\n", expected);
      printf("Given: %d\n", given);
      exit(1);
    }
  }

  int getNumOfCommands(const char* text) {
    size_t num = 0;
    size_t size = strlen(text);
    for (size_t i = 0; i < size; ++i) {
      if (text[i] == '\n')
        ++num;
      
      if (text[i] == ':') {
        size_t cur_id = i;
        std::string label = "";
        bool is_label = true;
        while (cur_id >= 0 && text[cur_id] != '\n') {
          if (text[cur_id] == ' ') {
            is_label = false;
          }
          label.push_back(text[cur_id--]);
        }
        if (!is_label)
          continue;
        std::reverse(label.begin(), label.end());
        label_[label] = num;
        --num;
      }
    }
    return num;
  }

  void add(size_t num_command, size_t type, size_t num_args, 
        size_t a = 0, size_t b = 0) {
    program_[3 * num_command] = type;
    if (num_args >= 1)
      program_[3 * num_command + 1] = a;
    if (num_args == 2)
      program_[3 * num_command + 2] = b;
  }

  void translate(const char* text) {
    size_t text_size = strlen(text);
    size_t id = 0;
    size_t num_command = 0;
    while (id < text_size) {
      std::string command = getCommand(text, id);
      
      if (command.back() == ':') {
        ++id;
        continue;
      }

      if (!types_of_commands_.count(command)) {
        printf("ERROR.\n");
        printf("Unknown command \'%s\'\n", command.c_str());
        exit(1);
      }

      if (command[0] == 'j') {
        program_[3 * num_command] = types_of_commands_[command];
        if (text[id] == '\n') {
          printf("ERROR!\n");
          printf("No label for jump.\n");
          exit(1);
        }
        ++id;
        std::string label = getCommand(text, id);
        int jump_num;
        if (label.back() == ':') {
          jump_num = label_[label];
        } else {
          jump_num = atoi(label.c_str());
        }
        program_[3 * num_command + 1] = jump_num;

        if (text[id] != '\n') {
          printf("ERROR.\n");
          printf("Line break is absent\n");
          exit(0);
        }
        ++num_command;
        ++id;
        
        continue;
      }
      
      int a;
      size_t num_args = 0;
      
      if (text[id] != '\n') {
        std::string arg = getCommand(text, ++id);
      
        if (arg.back() == 'x') {
          if (arg.size() != 2 || !(arg[0] >= 'a' && arg[0] <= 'z')) {
            printf("ERROR.\n");
            printf("Wrong name for register\n");
            exit(1);
          }

          if (command != "push" && command != "pop") {
            printf("ERROR.\n");
            printf("Only 'push' and 'pop' are operations with registers\n");
            exit(1);
          }
          command += " reg";
          a = arg[0] - 'a';
        } else if (arg[0] == '[') {
          
          if (command != "push" && command != "pop") {
            printf("ERROR.\n");
            printf("Only 'push' and 'pop' are operations with RAM\n");
            exit(1);
          }        
          
          arg = arg.substr(1, arg.size() - 2);
          if (arg.back() == 'x') {
            if (arg.size() != 2 || !(arg[0] >= 'a' && arg[0] <= 'z')) {
              printf("ERROR.\n");
              printf("Wrong name for register\n");
              exit(1);
            }
            command += " ram reg";
            a = arg[0] - 'a';
          } else {
            command += " ram num";
            a = atoi(arg.c_str());
          }
        } else {
          a = atoi(arg.c_str());
        }
        ++num_args;
      }

      if (text[id] != '\n') {
        printf("ERROR.\n");
        printf("Line break is absent\n");
        exit(0);
      }

      int type = types_of_commands_[command];

      switch (type) {
        case PUSH:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case POP:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
        case ADD:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case SUB:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case MUL:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case DIV:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case SIN:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case COS:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0);
          break;
        case SQRT:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0); 
          break;
        case IN:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0); 
          break;
        case OUT:
          checkNumArgs(command, num_args, 0);
          add(num_command, type, 0); 
          break;
        case PUSH_REG:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case POP_REG:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case PUSH_RAM_REG:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case PUSH_RAM_NUM:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case POP_RAM_REG:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;
        case POP_RAM_NUM:
          checkNumArgs(command, num_args, 1);
          add(num_command, type, 1, a);
          break;

        default:
          printf("ERROR.\n");
          printf("Unknown command: %s\n", command.c_str());
          exit(1);
      }
      ++id;
      ++num_command;
    }
  
  }

public:
  Assembler() {
    types_of_commands_["push"] = PUSH;
    types_of_commands_["pop"] = POP;
    types_of_commands_["add"] = ADD;
    types_of_commands_["sub"] = SUB;
    types_of_commands_["mul"] = MUL;
    types_of_commands_["div"] = DIV;
    types_of_commands_["sin"] = SIN;
    types_of_commands_["cos"] = COS;
    types_of_commands_["sqrt"] = SQRT;
    types_of_commands_["in"] = IN;
    types_of_commands_["out"] = OUT;
    types_of_commands_["jmp"] = JMP;
    types_of_commands_["je"] = JE;
    types_of_commands_["jne"] = JNE;
    types_of_commands_["ja"] = JA;
    types_of_commands_["jae"] = JAE;
    types_of_commands_["jb"] = JB;
    types_of_commands_["jbe"] = JBE;
    types_of_commands_["push reg"] = PUSH_REG;
    types_of_commands_["pop reg"] = POP_REG;
    types_of_commands_["push ram reg"] = PUSH_RAM_REG;
    types_of_commands_["push ram num"] = PUSH_RAM_NUM;
    types_of_commands_["pop ram reg"] = POP_RAM_REG;
    types_of_commands_["pop ram num"] = POP_RAM_NUM;
  }
  ~Assembler() {}
  
  std::pair<int*, size_t> getProgram(const char* text) {
    size_t num_commands = getNumOfCommands(text);
    program_ = new int[3 * num_commands]();
    translate(text);
    return std::make_pair(program_, num_commands);
  }
};

