#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_common.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_translate.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_eval.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_globals.h"

// this function evaluates the accuracy for French translations
void evaluate_accuracy_fr() {
    if (test_count == 0) {
        printf("No test pairs loaded for evaluation.\n");
        return;
    }

    int correct_top1 = 0, correct_top5 = 0, total_processed = 0;
    int top_indices[TOP_K];
    float top_scores[TOP_K];
    

    // here we process each test pair
    for (int i = 0; i < test_count; i++) {
        const char *translation = translate_word_fr(test_pairs[i].source, TOP_K, top_indices, top_scores);
        
        if (strcmp(translation, "<same>") == 0) {
            if (strcmp(test_pairs[i].source, test_pairs[i].target) == 0) {
                correct_top1++;
            }
        }
        else if (strcmp(translation, test_pairs[i].target) == 0) {
            correct_top1++;
        }

        // now we check if target is in top-5
        for (int j = 0; j < TOP_K && top_indices[j] >= 0; j++) {
            if (strcmp(fr_embeddings[top_indices[j]].word, test_pairs[i].target) == 0) {
                correct_top5++;
                break;
            }
        }

        total_processed++;
    }


    printf("\nEvaluation Results:\n");
    printf("Test pairs processed: %d\n", total_processed);
    printf("Top-1 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top1 / total_processed, correct_top1, total_processed);
    printf("Top-5 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top5 / total_processed, correct_top5, total_processed);

}

// similar function as the above function
void evaluate_accuracy_es() {
    if (test_count == 0) {
        printf("No test pairs loaded for evaluation.\n");
        return;
    }

    int correct_top1 = 0, correct_top5 = 0, total_processed = 0;
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    // here we process each test pair
    for (int i = 0; i < test_count; i++) {
        const char *translation = translate_word_es(test_pairs[i].source, TOP_K, top_indices, top_scores);
        
        if (strcmp(translation, "<same>") == 0) {
            if (strcmp(test_pairs[i].source, test_pairs[i].target) == 0) {
                correct_top1++;
            }
        }
        else if (strcmp(translation, test_pairs[i].target) == 0) {
            correct_top1++;
        }

        // check if target is in top-5
        for (int j = 0; j < TOP_K && top_indices[j] >= 0; j++) {
            if (strcmp(es_embeddings[top_indices[j]].word, test_pairs[i].target) == 0) {
                correct_top5++;
                break;
            }
        }

        total_processed++;
    }


    printf("\nEvaluation Results:\n");
    printf("Test pairs processed: %d\n", total_processed);
    printf("Top-1 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top1 / total_processed, correct_top1, total_processed);
    printf("Top-5 Accuracy: %.2f%% (%d/%d)\n", 100.0 * correct_top5 / total_processed, correct_top5, total_processed);

}
