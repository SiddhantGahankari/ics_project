#ifndef IO_H
#define IO_H
#include "B24CS1029_B24CM1016_B24CS1069_B24CM1058_common.h"

int load_embeddings(char *filename, Embedding *embeddings); // function to load embeddings
int load_test_pairs(char *filename); // function to load the test pairs

#endif