#ifndef TRANSLATE_H
#define TRANSLATE_H

void find_top_k_es(float *source_vector, int k, int *top_indices, float *top_scores);
char *translate_word_fr(char *english_word, int top_k, int *top_indices, float *top_scores);
char *translate_word_es(char *english_word, int top_k, int *top_indices, float *top_scores);
void find_top_k_fr(float *source_vector, int k, int *top_indices, float *top_scores);
void translate_sentence_fr(char *input);
void translate_sentence_es(char *input);

#endif