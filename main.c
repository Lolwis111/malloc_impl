#include <stdlib.h>
#include "stdbool.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "c_malloc.h"

int HEAP_SIZE = 8192, TEST_SIZE = 100;

void shuffle(void *array, size_t n, size_t size);

void test1()
{
    void* p1 = c_realloc(NULL, 200);

    void* p2 = c_realloc(NULL, 100);

    // printBlocks();

    c_free(p1);

    // printBlocks();

    p1 = c_realloc(NULL, 50);

    // printBlocks();

    p1 = c_realloc(p1, 100);

    // printBlocks();

    p1 = c_realloc(p1, 150);

    p2 = c_realloc(p2, 10);

    // printBlocks();

    c_free(p1);
    c_free(p2);

    printBlocks();
}

void test2()
{
    void** ptr[TEST_SIZE + BLOCK_SIZE];

    for(int i = 0; i < TEST_SIZE; i++)
    {
        ptr[i] = NULL;
    }

    for(int i = 0; i < (TEST_SIZE / 10); i++)
    {
        size_t size = rand() % (HEAP_SIZE/10);
        ptr[i] = c_malloc(size);
    }

    shuffle(ptr, TEST_SIZE, sizeof(void*));

    for(int i = 0; i < TEST_SIZE; i++)
    {
        if(ptr[i] != NULL)
        {
            if(rand() % 20 > 3)
            {
                c_free(ptr[i]);
                ptr[i] = NULL;
            }
        }
        else
        {
            if(rand() % 20 > 5)
            {
                size_t size = rand() % (HEAP_SIZE / 10);
                ptr[i] = c_malloc(size);
            }
        }
    }

    shuffle(ptr, TEST_SIZE, sizeof(void*));

    for(int i = 0; i < TEST_SIZE; i++)
    {
        c_free(ptr[i]);
    }

    printBlocks();
}

void test3()
{
    struct test_struct {
        int a;
        int b;
        char c;
    };

    const int calloc_test = 24;

    struct test_struct* array = c_calloc(calloc_test, sizeof(struct test_struct));

    printBlocks();

    for(int i = 0; i < calloc_test; i++)
    {
        if(array[i].a != 0 || array[i].b != 0 || array[i].c != 0)
        {
            fputs("CALLOC ERROR\r\n", stderr);
        }
    }

    c_free(array);

    printBlocks();
}

void test4()
{
    void* p = c_malloc(2 * HEAP_SIZE);

    if(p != NULL)
    {
        fputs("MALLOC ERROR\r\n", stderr);
    }

    printBlocks();
}

int main(int argc, char** argv)
{
    if(argc >= 3)
    {
        HEAP_SIZE = atoi(argv[1]);
        TEST_SIZE = atoi(argv[2]);
    }
    
    printf("Using TEST_SIZE = %d and HEAP_SIZE = %d\r\n", TEST_SIZE, HEAP_SIZE);

    srand(time(NULL));
    
    init_c_malloc(HEAP_SIZE);

    puts("\r\nRunning test1()");

    test1();

    puts("\r\nRunning test2()");

    test2();

    puts("\r\nRunning test3()");

    test3();

    puts("\r\nRunning test4()");

    test4();
    

    free_c_malloc();
}

void shuffle(void *array, size_t n, size_t size)
{
    if (n > 1)
    {
        char* arr = array;
        char tmp[size];
        size_t stride = size * sizeof(char);
        
        size_t i;
        for (i = 0; i < n - 1; ++i)
        {
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}