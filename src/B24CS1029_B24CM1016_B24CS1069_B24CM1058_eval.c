#include "../include/common.h"
#include "../include/translate.h"
#include "../include/eval.h"
#include  "../include/globals.h"

//function to evaluate accuracy, here we also calcalute top-5 accuracy since for a translator, more than one word may be right translation for a givne word...
void evaluate_accuracy_fr()
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
    
    //to show runtime of evealuation
    clock_t start = clock(); // start of runtime

    for (int i = 0; i < test_count; i++)
    {
        const char *translation = translate_word_fr(test_pairs[i].source, TOP_K, top_indices, top_scores);
        //we use strcmp to compare given output with accurate output..
        if (strcmp(translation, "<same>") != 0 && strcmp(translation, test_pairs[i].target) == 0)
        {
            correct_top1++;
        }

        //still correct if it result is similar to any word among top 5.
        for (int j = 0; j < TOP_K && top_indices[j] >= 0; j++)
        {
            //compare among the top 5 most similar words to the input word....we use strcmp
            if (strcmp(fr_embeddings[top_indices[j]].word, test_pairs[i].target) == 0)
            {
                correct_top5++;
                break;
            }
        }

        total_processed++;
    }

    //end of runtime.
    clock_t end = clock();

    //formulated runtime and converted it to secs.
    double elapsed = (double)((end - start) / CLOCKS_PER_SEC);

    printf("\nEvaluation Results:\n");
    printf("Test pairs processed: %d\n", total_processed);

    //accuracy%
    printf("Top-1 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top1 / total_processed, correct_top1, total_processed); 
    printf("Top-5 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top5 / total_processed, correct_top5, total_processed);

    //display processing time
    printf("Processing time: %.2f seconds (%.0f pairs/sec)\n", elapsed, total_processed / elapsed);
}

void evaluate_accuracy_es()
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
    
    //to show runtime of evealuation
    clock_t start = clock(); // start of runtime

    for (int i = 0; i < test_count; i++)
    {
        const char *translation = translate_word_es(test_pairs[i].source, TOP_K, top_indices, top_scores);
        //we use strcmp to compare given output with accurate output..
        if (strcmp(translation, "<same>") != 0 && strcmp(translation, test_pairs[i].target) == 0)
        {
            correct_top1++;
        }

        //still correct if it result is similar to any word among top 5.
        for (int j = 0; j < TOP_K && top_indices[j] >= 0; j++)
        {
            //compare among the top 5 most similar words to the input word....we use strcmp
            if (strcmp(fr_embeddings[top_indices[j]].word, test_pairs[i].target) == 0)
            {
                correct_top5++;
                break;
            }
        }

        total_processed++;
    }

    //end of runtime.
    clock_t end = clock();

    //formulated runtime and converted it to secs.
    double elapsed = (double)((end - start) / CLOCKS_PER_SEC);

    printf("\nEvaluation Results:\n");
    printf("Test pairs processed: %d\n", total_processed);

    //accuracy%
    printf("Top-1 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top1 / total_processed, correct_top1, total_processed); 
    printf("Top-5 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top5 / total_processed, correct_top5, total_processed);

    //display processing time
    printf("Processing time: %.2f seconds (%.0f pairs/sec)\n", elapsed, total_processed / elapsed);
}
