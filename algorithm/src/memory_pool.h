
#ifndef  _MEMORY_POOL_H
#define  _MEMORY_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MPOOL_SIZE          (64 * 1024)
#define MPOOL_ALIGN_SIZE    (8)

#define MPOOL_MALLOC(p, size)                 \
    do                                        \
    {                                         \
        if (((p) = malloc(size)) == NULL)     \
        {                                     \
            fprintf(stderr, "malloc failed"); \
            exit(-1);                         \
        }                                     \
    } while (0)                               \

#endif
