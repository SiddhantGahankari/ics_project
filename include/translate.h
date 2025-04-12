#ifndef TRANSLATE_H
#define TRANSLATE_H

void find_top_k(const float *source_vector, int k, int *top_indices, float *top_scores);
const char *translate_word(const char *english_word, int top_k, int *top_indices, float *top_scores);
void translate_sentence(const char *input);

#endif