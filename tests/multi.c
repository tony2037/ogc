#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "gc.h"

void *sample(void *h)
{
    void **ptr = gc_alloc(10);
    *ptr = gc_alloc(11);
    *ptr += 3;
    gc_dump_internals();
    return NULL;
}

void *hello(void *ptr)
{
    printf("Hello world");
    return  ptr;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3;
    gc_init(&argc, 1);

    int ret = 0;

    if((ret = pthread_create(&t1, NULL, *hello, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if((ret = pthread_create(&t2, NULL, *sample, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if ((ret = pthread_join(t2, NULL))) {
        fprintf(stderr,"Error - pthread_join() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if((ret = pthread_create(&t3, NULL, *hello, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if ((ret = pthread_join(t1, NULL))) {
        fprintf(stderr,"Error - pthread_join() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if ((ret = pthread_join(t2, NULL))) {
        fprintf(stderr,"Error - pthread_join() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    if ((ret = pthread_join(t3, NULL))) {
        fprintf(stderr,"Error - pthread_join() return code: %d\n",ret);
        exit(EXIT_FAILURE);
    }

    gc_destroy();
    return 0;
}
