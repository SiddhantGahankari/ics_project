#include "../include/common.h"
#include  "../include/globals.h"

Embedding en_embeddings[MAX_WORDS];
Embedding es_embeddings[MAX_WORDS];
Embedding fr_embeddings[MAX_WORDS];
TranslationPair test_pairs[MAX_TEST_PAIRS];
int en_count = 0;
int es_count = 0;
int fr_count = 0;
int test_count = 0;
int lang = 0;