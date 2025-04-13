#include "../include/common.h"
#include "../include/translate.h"
#include "../include/eval.h"
#include  "../include/globals.h"


void evaluate_accuracy()
{
    if (test_count == 0)
    {
        printf("No test pairs loaded for evaluation.\n");
        return;
    }

    int correct_top1 = 0;
    int correct_top5 = 0;
    int total_processed = 0;
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    clock_t start = clock();

    for (int i = 0; i < test_count; i++)
    {
        const char *translation = translate_word(test_pairs[i].source, TOP_K, top_indices, top_scores);

        if (strcmp(translation, "<same>") != 0 &&
            strcmp(translation, test_pairs[i].target) == 0)
        {
            correct_top1++;
        }

        for (int j = 0; j < TOP_K && top_indices[j] >= 0; j++)
        {
            if (strcmp(fr_embeddings[top_indices[j]].word, test_pairs[i].target) == 0)
            {
                correct_top5++;
                break;
            }
        }

        total_processed++;
    }

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nEvaluation Results:\n");
    printf("Test pairs processed: %d\n", total_processed);
    printf("Top-1 Accuracy: %.2f%% (%d/%d)\n",
           100.0 * correct_top1 / total_processed, correct_top1, total_processed);
    printf("Top-5 Accuracy: %.2f%% (%d/%d)\n",
           100.0 * correct_top5 / total_processed, correct_top5, total_processed);
    printf("Processing time: %.2f seconds (%.0f pairs/sec)\n",
           elapsed, total_processed / elapsed);
}

