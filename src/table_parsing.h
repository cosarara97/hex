#ifndef TABLE_PARSING_H_
#define TABLE_PARSING_H_

void load_table(const char* file_name, char output[0x100]);
int parse_table(char* table, char output[0x100]);

#endif // TABLE_PARSING_H_
