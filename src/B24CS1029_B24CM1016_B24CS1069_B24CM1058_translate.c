#include "../include/common.h"
#include "../include/translate.h"
#include "../include/vector.h"
#include  "../include/globals.h"

//to show top 5 words similar to the input word..cause more than one word might be a right transaltion
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

    // If the word is capitalized ie probably a name or something so just return it and dont find anything similar to it
    if (isupper(english_word[0])) {
        strncpy(return_buffer, english_word, MAX_WORD_LEN - 1);
        return_buffer[MAX_WORD_LEN - 1] = '\0';
        return return_buffer;
    }

    //clean the word, make it lowercase cause embedding have smallcased words
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

    //no match, so return unknown
    return "<unk>";
}

void translate_sentence(const char *input)
{
    char sentence_copy[MAX_LINE_LEN];
    strncpy(sentence_copy, input, MAX_LINE_LEN - 1);
    sentence_copy[MAX_LINE_LEN - 1] = '\0';

    //tokenize the sentence, separate it into words so that we can load embeddings for each
    char *token = strtok(sentence_copy, " \t\n\r");
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    printf("Translation: ");
    
    //go word by word...
    while (token)
    {
        const char *translation = translate_word(token, TOP_K, top_indices, top_scores);
        if (strcmp(translation, "<unk>") == 0 || strcmp(translation, "<same>") == 0)
        {
            //word is unknown or same as english word so we return as it is
            printf("%s ", token);
        }
        else
        {
            //if not so, return its correspoding translatioin
            printf("%s ", translation);
        }
        token = strtok(NULL, " \t\n\r"); //move to next, one done
    }
    printf("\n");
}
