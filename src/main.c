#include "../include/common.h"
#include "../include/eval.h"
#include "../include/io.h"
#include "../include/translate.h"
#include "../include/vector.h"
#include "../include/globals.h"


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

    printf("Loading English embeddings...\n");
    en_count = load_embeddings("data/wiki.en.align.vec", en_embeddings);
    printf("Loaded %d English words.\n", en_count);

    printf("Loading French embeddings...\n");
    fr_count = load_embeddings("data/wiki.fr.align.vec", fr_embeddings);
    printf("Loaded %d French words.\n", fr_count);

    if (en_count == 0 || fr_count == 0)
    {
        fprintf(stderr, "Failed to load embeddings.\n");
        return 1;
    }

    printf("Loading test pairs...\n");
    test_count = load_test_pairs("data/test_data.txt.txt");
    if (test_count > 0)
    {
        printf("Loaded %d test pairs.\n", test_count);
        evaluate_accuracy();
    }
    else
    {
        printf("No test pairs loaded. Continuing without evaluation.\n");
    }

    printf("\nInteractive translation (type 'quit' to exit):\n");
    char input[MAX_LINE_LEN];
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    while (1)
    {
        printf("Enter English word or sentence: ");
        if (!fgets(input, sizeof(input), stdin))
        {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0)
        {
            break;
        }

        if (strchr(input, ' '))
        {
            translate_sentence(input);
        }
        else
        {
            const char *translation = translate_word(input, TOP_K, top_indices, top_scores);

            if (strcmp(translation, "<same>") == 0)
            {
                printf("No suitable translation found (best match was same as input)\n");
            }
            else
            {
                printf("Translation: %s\n", translation);
            }

            printf("Top %d candidates:\n", TOP_K);
            for (int i = 0; i < TOP_K && top_indices[i] >= 0; i++)
            {
                printf("%d. %s (score: %.4f)", i + 1, fr_embeddings[top_indices[i]].word, top_scores[i]);
                if (strcmp(fr_embeddings[top_indices[i]].word, input) == 0)
                {
                    printf(" <same as input>");
                }
                printf("\n");
            }
        }
    }

    return 0;
}
