#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>


#define EMBEDDING_DIM 300
#define MAX_WORDS 200000
#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 4096
#define MAX_TEST_PAIRS 10000
#define TOP_K 5
#define MIN_SIMILARITY 0.6

typedef struct
{
    char word[MAX_WORD_LEN];
    float vector[EMBEDDING_DIM];
} Embedding;

typedef struct
{
    char source[MAX_WORD_LEN];
    char target[MAX_WORD_LEN];
} TranslationPair;

extern Embedding en_embeddings[MAX_WORDS];
extern Embedding fr_embeddings[MAX_WORDS];
extern TranslationPair test_pairs[MAX_TEST_PAIRS];
extern int en_count;
extern int fr_count;
extern int test_count;

#endif
