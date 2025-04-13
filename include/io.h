#ifndef IO_H
#define IO_H
#include "common.h"

int load_embeddings(char *filename, Embedding *embeddings);
int load_test_pairs(char *filename);

#endif