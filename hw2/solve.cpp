#include <cstring>
#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include "lib/sorter.h"

//------------------------------------------------------------------------------
//! Input name of file
//!
//! @params [in]  s string which will be printed
//! @return char*
//------------------------------------------------------------------------------

char* inputFile(std::string s) {
  printf("%s", s.c_str());
  char* name = (char*)malloc((FILENAME_MAX + 1) * sizeof(char));
  scanf("%s", name);
  return name;
}

//------------------------------------------------------------------------------
//! Read text from file
//!
//! @params [in]  file_pointer  Pointer to file
//! @params [out]  file_size    Size of file
//!
//! @return char*
//------------------------------------------------------------------------------

char* getText(FILE* file_pointer, size_t* file_size) {
  struct stat buffer;
  fstat(fileno(file_pointer), &buffer);
  *file_size = buffer.st_size;
  char* chars = (char*)malloc((buffer.st_size + 1) * sizeof(char));
  fread(chars, sizeof(char), buffer.st_size, file_pointer);
  return chars;
}

//------------------------------------------------------------------------------
//! Return array of pointers to beginnings of all words
//!
//! @params [in]  chars Pointer to array of characters from a file
//! @params [in]  file_size Size of file
//! @params [out] word_counter Number of words
//!
//! @return char**
//------------------------------------------------------------------------------

char** getIndices(char* chars, size_t file_size, size_t& word_counter) {
  word_counter = 0;
  for (size_t i = 0; i < file_size; ++i) {
    if (chars[i] == '\n' || chars[i] == '\0') {
      ++word_counter;
      chars[i] = '\0';
    }
  }
  char** indices = (char**)malloc(word_counter * sizeof(char*));
  size_t id = 0;
  size_t prev = 0;
  for (size_t i = 0; i < file_size; ++i) {
    if (chars[i] == '\0') {
      indices[id++] = chars + prev;
      prev = i + 1;
    }

  }
  return indices;
}

//------------------------------------------------------------------------------
//! Print sorted text
//!
//! @params [in]  chars         Pointer to array of characters from a file
//! @params [in]  indices       Pointer to array of pointers to words from text
//! @params [in]  word_counter  Number of words
//! @params [in]  file_pointer  Pointer to file
//!
//! @return void
//------------------------------------------------------------------------------

void out(char* chars, char** indices, size_t word_counter, FILE* file_pointer) {
  char* c = new char('\n');
  for (size_t i = 0; i < word_counter; ++i) {
    fwrite(indices[i], sizeof(char), strlen(indices[i]), file_pointer);
    fwrite(c, sizeof(char), 1, file_pointer);
  }
}

int main() {
  char* file = inputFile("Enter the name of file with text: ");
  FILE* file_pointer = fopen(file, "r");
  if (file_pointer == nullptr) {
    printf("Can't open a file %s\n", file);
    exit(1);
  }
  size_t file_size;
  char* chars = getText(file_pointer, &file_size);
  fclose(file_pointer);
  
  size_t word_counter;
  char** indices = getIndices(chars, file_size, word_counter);
  
  file = inputFile("Enter the name of file where output text will be printed: ");
  file_pointer = fopen(file, "w");
  if (file_pointer == nullptr) {
    printf("Can't open a file %s\n", file);
    exit(1);
  }
  
  std::sort(indices, indices + word_counter, stringComparator);
  fwrite("\n\nSorted text:\n\n", sizeof(char), 14, file_pointer);
  out(chars, indices, word_counter, file_pointer);
  
  std::sort(indices, indices + word_counter, reverseStringComparator);
  fwrite("\n\nReverse Sorted text:\n\n", sizeof(char), 22, file_pointer);
  out(chars, indices, word_counter, file_pointer);

  fclose(file_pointer);
  return 0;
}
