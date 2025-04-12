#ifndef IO_H
#define IO_H
#include "common.h"

int load_embeddings(const char *filename, Embedding *embeddings);
int load_test_pairs(const char *filename);

#endif