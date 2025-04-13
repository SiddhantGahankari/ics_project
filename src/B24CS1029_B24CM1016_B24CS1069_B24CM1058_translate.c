#include "../include/common.h"
#include "../include/translate.h"
#include "../include/vector.h"
#include  "../include/globals.h"

void find_top_k(const float *source_vector, int k, int *top_indices, float *top_scores)
{
    for (int i = 0; i < k; i++)
    {
        top_indices[i] = -1;
        top_scores[i] = -2.0f;
    }

    for (int i = 0; i < fr_count; i++)
    {
        float sim = cosine_similarity(source_vector, fr_embeddings[i].vector);

        for (int j = 0; j < k; j++)
        {
            if (sim > top_scores[j])
            {
                for (int l = k - 1; l > j; l--)
                {
                    top_indices[l] = top_indices[l - 1];
                    top_scores[l] = top_scores[l - 1];
                }
                top_indices[j] = i;
                top_scores[j] = sim;
                break;
            }
        }
    }   
}

const char* translate_word(const char* english_word, int top_k, int* top_indices, float* top_scores) {
    static char return_buffer[MAX_WORD_LEN];

    if (isupper(english_word[0])) {
        strncpy(return_buffer, english_word, MAX_WORD_LEN - 1);
        return_buffer[MAX_WORD_LEN - 1] = '\0';
        return return_buffer;
    }

    char cleaned[MAX_WORD_LEN] = {0};
    int j = 0;
    for (int i = 0; english_word[i] && j < MAX_WORD_LEN - 1; i++) {
        if (isalpha(english_word[i])) {
            cleaned[j++] = tolower(english_word[i]);
        }
    }
    if (j == 0) return "<unk>";

    float* source_vector = NULL;
    for (int i = 0; i < en_count; i++) {
        if (strcmp(en_embeddings[i].word, cleaned) == 0) {
            source_vector = en_embeddings[i].vector;
            break;
        }
    }
    if (!source_vector) return "<unk>";

    find_top_k(source_vector, top_k, top_indices, top_scores);

    for (int i = 0; i < top_k && top_indices[i] >= 0; i++) {
        if (strcmp(fr_embeddings[top_indices[i]].word, cleaned) != 0 &&
            top_scores[i] >= MIN_SIMILARITY) {
            return fr_embeddings[top_indices[i]].word;
        }
    }

    if (top_indices[0] >= 0) {
        if (strcmp(fr_embeddings[top_indices[0]].word, cleaned) == 0) {
            return "<same>";
        }
        return fr_embeddings[top_indices[0]].word;
    }

    return "<unk>";
}

void translate_sentence(const char *input)
{
    char sentence_copy[MAX_LINE_LEN];
    strncpy(sentence_copy, input, MAX_LINE_LEN - 1);
    sentence_copy[MAX_LINE_LEN - 1] = '\0';

    char *token = strtok(sentence_copy, " \t\n\r");
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    printf("Translation: ");
    while (token)
    {
        const char *translation = translate_word(token, TOP_K, top_indices, top_scores);
        if (strcmp(translation, "<unk>") == 0 || strcmp(translation, "<same>") == 0)
        {
            printf("%s ", token);
        }
        else
        {
            printf("%s ", translation);
        }
        token = strtok(NULL, " \t\n\r");
    }
    printf("\n");
}
