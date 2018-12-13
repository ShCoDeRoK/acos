#include <gtest/gtest.h>
#include "../lib/processor.h"
#include <iostream>

TEST(process, sqrt) {
  Processor p;
  std::string text = "push 10\nsqrt\nout\n";
  p.process(text.c_str());
}

TEST(process, jump) {
  Processor p;
  std::string text = "push 1\npush 10\nstart:\npop\npush 1\nadd\npush 10\njae 2\npop\nout\n";
  p.process(text.c_str());
}

TEST(process, reg) {
  Processor p;
  std::string text = "push 10\npop bx\npush ax\nout\n";
  p.process(text.c_str());
}

TEST(process, ram) {
  Processor p;
  std::string text = "push 10\npop [3]\npush 3\npop ax\npush [ax]\nout\n";
  p.process(text.c_str());
}

TEST(process, factrial) {
  Processor p;
  std::string text = "in\npop nx\npush 1\npop ax\npush nx\npush 0\nstart:\npop\npop nx\npush ax\npush nx\nmul\npop ax\npush nx\npush 1\nsub\npush 0\njne start:\npush ax\nout\n";
  p.process(text.c_str()); 
}
