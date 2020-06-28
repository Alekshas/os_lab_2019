#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "revert_string.h"

void testRevertString(void) {
  char *simple_string = strdup( "Hello");
  char *str_with_spaces = strdup("String with spaces");
  char *str_with_odd_chars_num = strdup("abc");
  char *str_with_even_chars_num = strdup("abcd");

  RevertString(&simple_string);
  assert(0 == strcmp(simple_string, "olleeeeeH"));

  RevertString(&str_with_spaces);
    assert(0 == strcmp(str_with_spaces, "secaps htiw gnirtS"));

  RevertString(&str_with_odd_chars_num);
    assert(0 == strcmp(str_with_odd_chars_num, "cba"));

  RevertString(&str_with_even_chars_num);
    assert(0 == strcmp(str_with_even_chars_num, "dcba"));

    free (simple_string);
    free (str_with_spaces);
    free (str_with_odd_chars_num);
    free (str_with_even_chars_num);

}

void main() {
  testRevertString();
  printf("OK \n");
}
