#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lookup_table.h"

Linux_Keys * get_value(int key) {
    // Get the starting point into the lookup table to start looping at.
    Linux_Keys key_stroke[1] = {{key}};
    // Use bsearch algorithm to find the correct key that was pressed in the lookup table.
    Linux_Keys * lookup_key = bsearch(key_stroke, linux_lookup_table, sizeof(linux_lookup_table) / sizeof(linux_lookup_table[0]), sizeof(linux_lookup_table[0]), compare_keys);
    // Return the lookup key.
    return lookup_key ? lookup_key : NULL;
}

int main(void) {
  char * value = calloc(10, sizeof(char));

  // Partial test: verify we can look up all the valid keys.
  for (int i = 0; i < sizeof linux_lookup_table / sizeof linux_lookup_table[0]; ++i) {
    Linux_Keys * lookup_key = get_value(linux_lookup_table[i].key_code);
    printf("%d -> %s\n", lookup_key->key_code, lookup_key->key_name);
  }

  free(value);

  return 0;
}