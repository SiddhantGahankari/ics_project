#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_common.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_translate.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_vector.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_globals.h"

char buffer[MAX_WORD_LEN]; // buffer for whenever required in the code


// find top-k similar French words based on cosine similarity
void find_top_k_fr(float *source_vector,int k, int *top_indices , float *top_scores)
{
    for (int i = 0; i < k; i++)
    {
        top_indices[i] = -1;
        top_scores[i] = -2.0;
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


// find top-k similar Spanish words
void find_top_k_es(float *source_vector, int k, int *top_indices, float *top_scores)
{
    for (int i = 0; i < k; i++)
    {
        top_indices[i] = -1;
        top_scores[i] = -2.0;
    }

    for (int i = 0; i < es_count; i++)
    {
        float sim = cosine_similarity(source_vector, es_embeddings[i].vector);

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


// translate a single English word to French
char *translate_word_fr(char *english_word , int top_k,int *top_indices , float *top_scores)
{
    if (isupper(english_word[0]))
    {
        return english_word;
    }

    // clean the word, i.e basically lowercase the word and check if there are any non-alphabetical characters
    char word_c[MAX_WORD_LEN] = {0};
    int j = 0;
    for (int i = 0; english_word[i] && j < MAX_WORD_LEN - 1; i++)
    {
        if (isalpha(english_word[i]))
        {
            word_c[j] = tolower(english_word[i]);
            j++;
        }
    }

    // find the embedding from the dataset
    float *source_vector = NULL;
    for (int i = 0; i < en_count; i++)
    {
        if (strcmp(en_embeddings[i].word, word_c) == 0)
        {
            source_vector = en_embeddings[i].vector;
            break;
        }
    }


    // if it is not found then return unknown 
    if (!source_vector) return "<unk>";

    find_top_k_fr(source_vector, top_k, top_indices, top_scores);

    for (int i = 0; i < top_k && top_indices[i] >= 0; i++)
    {
        if (strcmp(fr_embeddings[top_indices[i]].word, word_c) != 0 && top_scores[i] >= MIN_SIMILARITY)
        {
            return fr_embeddings[top_indices[i]].word;
        }
    }

    if (top_indices[0] >= 0)
    {
        if (strcmp(fr_embeddings[top_indices[0]].word, word_c) == 0)
        {
            return "<same>";
        }
        return fr_embeddings[top_indices[0]].word;
    }

    return "<unk>";
}


// Translate a single English word to Spanish
char *translate_word_es(char *english_word,int top_k ,int *top_indices, float *top_scores)
{
    if (isupper(english_word[0]))
    {
        return english_word;
    }

    char word_c[MAX_WORD_LEN] = {0};
    int j = 0;
    for (int i = 0; english_word[i] && j < MAX_WORD_LEN - 1; i++)
    {
        if (isalpha(english_word[i]))
        {
            word_c[j] = tolower(english_word[i]);
            j++;
        }
    }

    float *source_vector = NULL;
    for (int i = 0; i < en_count; i++)
    {
        if (strcmp(en_embeddings[i].word, word_c) == 0)
        {
            source_vector = en_embeddings[i].vector;
            break;
        }
     }

    // if it is not found then return unknown
    if (!source_vector) return "<unk>";

    find_top_k_es(source_vector, top_k, top_indices, top_scores);

    for (int i = 0; i < top_k && top_indices[i] >= 0; i++)
    {
        if (strcmp(es_embeddings[top_indices[i]].word, word_c) != 0 && top_scores[i] >= MIN_SIMILARITY)
        {

            return es_embeddings[top_indices[i]].word;
        }
    }

    if (top_indices[0] >= 0)
    {
        if (strcmp(es_embeddings[top_indices[0]].word, word_c) == 0)
        {
            return "<same>";
        }

        return es_embeddings[top_indices[0]].word;
    }

    return "<unk>";
}


// translate a sentence to French word by word
void translate_sentence_fr(char *input)
{
    char *token = strtok(input, " \t\n\r");
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    char full_output[MAX_LINE_LEN];
    full_output[0] = '\0';
    
    strcat(full_output, "Translation: ");
    while (token) {
        char *translation = translate_word_fr(token, TOP_K, top_indices, top_scores);
        if (strcmp(translation, "<unk>") == 0 || strcmp(translation, "<same>") == 0) {
            
            strcat(full_output, token);
        } else {

            
            strcat(full_output, translation);
        }
        strcat(full_output, " ");
        token = strtok(NULL, " \t\n\r");
    }
    strcat(full_output, "\n");

    printf("%s", full_output);
}


// translate a sentence to Spanish word by word
void translate_sentence_es(char *input)
{
    char *token = strtok(input, " \t\n\r");
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    char full_output[MAX_LINE_LEN];
    full_output[0] = '\0';
    
    strcat(full_output, "Translation: ");
    while (token) {
        char *translation = translate_word_es(token, TOP_K, top_indices, top_scores);
        if (strcmp(translation, "<unk>") == 0 || strcmp(translation, "<same>") == 0) {
            
            strcat(full_output, token);
        } else {

            
            strcat(full_output, translation);
        }
        strcat(full_output, " ");
        token = strtok(NULL, " \t\n\r");
    }
    strcat(full_output, "\n");

    printf("%s", full_output);
}
