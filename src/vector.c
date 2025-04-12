#include "../include/common.h"
#include "../include/vector.h"
#include "../include/globals.h"


float cosine_similarity(const float *a, const float *b)
{
    float dot = 0.0;
    for (int i = 0; i < EMBEDDING_DIM; i++)
    {
        dot += a[i] * b[i];
    }
    return dot;
}


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