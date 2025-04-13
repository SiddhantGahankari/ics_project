#include "../include/common.h"
#include "../include/eval.h"
#include "../include/io.h"
#include "../include/translate.h"
#include "../include/vector.h"
#include "../include/globals.h"
// #include <gtk/gtk.h>



// static void on_translate_clicked(GtkButton *button, gpointer user_data)
// {
//     (void)button;
//     (void)user_data;
//     const char *input = gtk_entry_get_text(GTK_ENTRY(entry));
//     int top_indices[TOP_K];
//     float top_scores[TOP_K];

//     GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
//     gtk_text_buffer_set_text(buffer, "", -1);

//     if (strchr(input, ' ')) {
//         char output[MAX_LINE_LEN] = "Translation: ";
//         char sentence_copy[MAX_LINE_LEN];
//         strncpy(sentence_copy, input, MAX_LINE_LEN - 1);
//         sentence_copy[MAX_LINE_LEN - 1] = '\0';

//         char *token = strtok(sentence_copy, " \t\n\r");
//         while (token) {
//             const char *translation = translate_word(token, TOP_K, top_indices, top_scores);
//             strcat(output, translation);
//             strcat(output, " ");
//             token = strtok(NULL, " \t\n\r");
//         }
//         gtk_text_buffer_set_text(buffer, output, -1);
//     } else {
//         const char *translation = translate_word(input, TOP_K, top_indices, top_scores);
//         char output[MAX_LINE_LEN];
//         snprintf(output, sizeof(output), "Translation: %s\nTop %d candidates:\n", translation, TOP_K);

//         for (int i = 0; i < TOP_K && top_indices[i] >= 0; i++) {
//             char line[256];
//             snprintf(line, sizeof(line), "%d. %s (score: %.4f)%s\n",
//                      i + 1, fr_embeddings[top_indices[i]].word, top_scores[i],
//                      strcmp(fr_embeddings[top_indices[i]].word, input) == 0 ? " <same as input>" : "");
//             strcat(output, line);
//         }
//         gtk_text_buffer_set_text(buffer, output, -1);
//     }
// }

// int main(int argc, char *argv[])
// {
//     gtk_init(&argc, &argv);
//     setlocale(LC_ALL, "en_US.UTF-8");

//     en_count = load_embeddings("wiki.en.align.vec", en_embeddings);
//     fr_count = load_embeddings("wiki.fr.align.vec", fr_embeddings);
//     test_count = load_test_pairs("test_data.txt");

//     GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_title(GTK_WINDOW(window), "Bilingual Word Translator");
//     gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

//     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

//     GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
//     gtk_container_add(GTK_CONTAINER(window), vbox);

//     entry = gtk_entry_new();
//     gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

//     GtkWidget *button = gtk_button_new_with_label("Translate");
//     gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);
//     g_signal_connect(button, "clicked", G_CALLBACK(on_translate_clicked), NULL);

//     textview = gtk_text_view_new();
//     gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
//     gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);

//     gtk_widget_show_all(window);
//     gtk_main();

//     return 0;
// }


int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    printf("Loading English embeddings...\n");
    en_count = load_embeddings("data/wiki.en.align.vec", en_embeddings);
    printf("Loaded %d English words.\n", en_count);

    printf("Loading French embeddings...\n");
    fr_count = load_embeddings("data/wiki.fr.align.vec", fr_embeddings);
    printf("Loaded %d French words.\n", fr_count);

    if (en_count == 0 || fr_count == 0) {
        fprintf(stderr, "Failed to load embeddings.\n");
        return 1;
    }

    printf("Loading test pairs...\n");
    test_count = load_test_pairs("data/test_data.txt");
    if (test_count > 0) {
        printf("Loaded %d test pairs.\n", test_count);
        evaluate_accuracy();
    } else {
        printf("No test pairs loaded. Continuing without evaluation.\n");
    }

    printf("\nInteractive translation (type 'quit' to exit):\n");
    char input[MAX_LINE_LEN];
    int top_indices[TOP_K];
    float top_scores[TOP_K];

    while (1) {
        printf("Enter English word or sentence: ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0) {
            break;
        }

        if (strchr(input, ' ')) {
            translate_sentence(input);
        } else {
            const char *translation = translate_word(input, TOP_K, top_indices, top_scores);

            if (strcmp(translation, "<same>") == 0) {
                printf("No suitable translation found (best match was same as input)\n");
            } else {
                printf("Translation: %s\n", translation);
            }

            printf("Top %d candidates:\n", TOP_K);
            for (int i = 0; i < TOP_K && top_indices[i] >= 0; i++) {
                printf("%d. %s (score: %.4f)", i + 1, fr_embeddings[top_indices[i]].word, top_scores[i]);
                if (strcmp(fr_embeddings[top_indices[i]].word, input) == 0) {
                    printf(" <same as input>");
                }
                printf("\n");
            }
        }
    }

    return 0;
}

