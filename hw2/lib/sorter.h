#include <algorithm>

//-----------------------------------------------------------------------------
//! Compare two strings
//!
//! @params [in] c1 Pointer to start of first string
//! @params [in] c2 Pointer to start of second string
//!
//! @return bool
//-----------------------------------------------------------------------------

bool stringComparator(char* c1, char* c2) {
  while (*c1 != '\0' && *c2 != '\0') {
    char cur_c1 = *c1;
    char cur_c2 = *c2;
    if ('A' <= cur_c1 && cur_c1 <= 'Z')
      cur_c1 = cur_c1 - 'A' + 'a';
    if ('A' <= cur_c2 && cur_c2 <= 'Z')
      cur_c2 = cur_c2 - 'A' + 'a';
    if (cur_c1 != cur_c2)
      return (cur_c1 < cur_c2);
    ++c1;
    ++c2;
  }
  return (*c1 == '\0' && *c2 != '\0');
}

//-----------------------------------------------------------------------------
//! Compares two strings in reverse order
//!
//! @params [in] c1 Pointer to start of first string
//! @params [in] c2 Pointer to start of second string
//!
//! @return void
//-----------------------------------------------------------------------------

bool reverseStringComparator(char* c1, char* c2) {
  char* start1 = c1;
  char* start2 = c2;
  while (*c1 != '\0')
    ++c1;
  while (*c2 != '\0')
    ++c2;

  while (c1 != start1 && c2 != start2) {
    char cur_c1 = *c1;
    char cur_c2 = *c2;
    if ('A' <= cur_c1 && cur_c1 <= 'Z')
      cur_c1 = cur_c1 - 'A' + 'a';
    if ('A' <= cur_c2 && cur_c2 <= 'Z')
      cur_c2 = cur_c2 - 'A' + 'a';
    if (cur_c1 != cur_c2)
      return (cur_c1 < cur_c2);
    --c1;
    --c2;
  }
  return (c1 == start1 && c2 != start2);
}
