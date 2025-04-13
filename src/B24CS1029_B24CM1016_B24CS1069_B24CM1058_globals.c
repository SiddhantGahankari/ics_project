#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_common.h"
#include  "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_globals.h"

Embedding en_embeddings[MAX_WORDS]; //english embeddings
Embedding es_embeddings[MAX_WORDS]; //spanish embeddings
Embedding fr_embeddings[MAX_WORDS]; //french embeddings
TranslationPair test_pairs[MAX_TEST_PAIRS]; //test pairs 
int en_count = 0; //english word count
int es_count = 0; // spanish word count
int fr_count = 0; // french word count
int test_count = 0; // test words count
char lang[100]; // which language have they chosen