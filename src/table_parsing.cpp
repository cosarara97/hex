#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "table_parsing.h"

void load_table(const char* file_name, char output[0x100]) {
  FILE* f = fopen(file_name, "r");
  if (f == NULL) {
    std::cerr << "Error opening table file, exiting" << std::endl;
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  int length = ftell(f);
  fseek (f, 0, SEEK_SET);
  char* buffer = (char*)malloc(length);
  if (buffer == NULL) {
    std::cerr << "Error opening table file (malloc), exiting" << std::endl;
    exit(1);
  }
  fread(buffer, length, 1, f);
  fclose(f);

  if (parse_table(buffer, output) != 0) {
    std::cerr << "Error parsing table, exiting" << std::endl;
    free(buffer);
    exit(1);
  }
  free(buffer);
}

int parse_table(char* table, char output[0x100]) {
  // TODO: utf8
  char c;
  char tmp[20];
  char* cursor;
  for (int i=0; i<0xFE; i++) {
    sprintf(tmp, "%02X", i);
    cursor = strstr(table, tmp);
    if (cursor != NULL && cursor[2] == '=') {
      c = cursor[3];
      if (c < 32 || c == 0xFF)
        c = '.';
    } else {
      c = '.';
    }
    output[i] = c;
    //table = strchr(table, '\n') + 1;
  }
  return 0;
}

