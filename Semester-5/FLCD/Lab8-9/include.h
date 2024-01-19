struct row_entry {
  struct row_entry* first_child;
  struct row_entry* next_sibling;
  char* name;
};