#ifndef _BINARY_TREE_PRIVATE_INCLUDE
#define _BINARY_TREE_PRIVATE_INCLUDE

#include "binaryTreePublic.h"

typedef struct node node_t;
struct node
{
  long int code;
  char *name;
  char *date;
  char *course;
  int year;
  node_t *left_N;
  node_t *right_N;
  node_t *left_ID;
  node_t *right_ID;
};

#endif
