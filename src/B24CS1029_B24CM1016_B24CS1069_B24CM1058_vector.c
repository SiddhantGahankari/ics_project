#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_common.h"
#include "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_vector.h"
#include  "../include/B24CS1029_B24CM1016_B24CS1069_B24CM1058_globals.h"



//cosine similarity to measure how close each output word is to the input
float cosine_similarity(float *a, float *b)
{
    float dot = 0.0;
    for (int i = 0; i < EMBEDDING_DIM; i++)
    {
        dot += a[i] * b[i];
    }
    return dot;
}

// normalize the input vector to unit length.if its below the threshold value of 1e-6 make it a unit vector.
void normalize_vector(float *vec)
{
    float norm = 0.0;   
    for (int i = 0; i < EMBEDDING_DIM; i++)
    {
        norm += vec[i] * vec[i];
    }
    norm = sqrt(norm);
    if (norm < 1e-6)
    {
        for (int i = 0; i < EMBEDDING_DIM; i++)
        {
            vec[i] = 1.0 / sqrt(EMBEDDING_DIM);
        }
        return;
    }
    for (int i = 0; i < EMBEDDING_DIM; i++)
    {
        vec[i] /= norm;
    }
}