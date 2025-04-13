#include "../include/common.h"
#include "../include/io.h"
#include "../include/vector.h"
#include  "../include/globals.h"



int load_embeddings(const char *filename, Embedding *embeddings)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LEN];
    int count = 0;
    int dim = 0;

    if (fgets(line, sizeof(line), file))
    {
        int n, d;
        if (sscanf(line, "%d %d", &n, &d) == 2)
        {
            dim = d;
            if (dim != EMBEDDING_DIM)
            {
                fprintf(stderr, "Warning: Embedding dimension mismatch (%d vs %d)\n", dim, EMBEDDING_DIM);
            }
        }
        else
        {
            fseek(file, 0, SEEK_SET);
        }
    }

    while (fgets(line, sizeof(line), file) && count < MAX_WORDS)
    {
        char *token = strtok(line, " ");
        if (!token)
            continue;

        char cleaned[MAX_WORD_LEN] = {0};
        int j = 0;
        for (int i = 0; token[i] && j < MAX_WORD_LEN - 1; i++)
        {
            if (isalpha(token[i]))
            {
                cleaned[j++] = tolower(token[i]);
            }
        }
        if (j == 0)
            continue;

        strncpy(embeddings[count].word, cleaned, MAX_WORD_LEN - 1);
        embeddings[count].word[MAX_WORD_LEN - 1] = '\0';

        int i = 0;
        while (i < EMBEDDING_DIM && (token = strtok(NULL, " \t\n\r")))
        {
            embeddings[count].vector[i++] = atof(token);
        }

        if (i == EMBEDDING_DIM)
        {
            normalize_vector(embeddings[count].vector);
            count++;
        }
        else
        {
            fprintf(stderr, "Warning: Invalid vector dimension for word '%s'\n", embeddings[count].word);
        }
    }

    fclose(file);
    return count;
}

int load_test_pairs(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error opening test file: %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LEN];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_TEST_PAIRS)
    {
        char *en_word = strtok(line, "\t\n ");
        char *fr_word = strtok(NULL, "\t\n ");

        if (en_word && fr_word)
        {
            strncpy(test_pairs[count].source, en_word, MAX_WORD_LEN - 1);
            strncpy(test_pairs[count].target, fr_word, MAX_WORD_LEN - 1);
            test_pairs[count].source[MAX_WORD_LEN - 1] = '\0';
            test_pairs[count].target[MAX_WORD_LEN - 1] = '\0';
            count++;
        }
    }

    fclose(file);
    return count;
}
