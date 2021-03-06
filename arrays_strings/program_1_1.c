// Implement an algorithm to determine if a string has all unique characters. What if you cannot use additional data structures?

#include <stdio.h>
#include <string.h>

#define TEST_CASE(A, B, C) { if(A(B) != C) { printf("Test Case failure -> %s(%s) != %s.\n", #A, #B, #C); /*return;*/ } }

// O(n^2)
int brute_force_method(char* string)
{
    int len = strlen(string);
    if (len == 0)
        return 0;
    if (len == 1)
        return 1;
    int ref_index, j;
    int diff = 'a' - 'A';
    for (ref_index = 1; ref_index < len; ref_index++)
    {
        for (j = 0; j < ref_index; j++)
        {
            if (string[j] == string[ref_index])
                return 0;
            if ((((string[j] >= 'a') && (string[j] <= 'z')) && (string[ref_index] == (string[j] - diff))) ||
                (((string[j] >= 'A') && (string[j] <= 'Z')) && (string[ref_index] == (string[j] + diff))))
                return 0;
        }
    }
    return 1;
}

// O(n)
int my_optimized_method_hash_table(char* string)
{
    int len = strlen(string);
    if (len == 0)
        return 0;
    if (len == 1)
        return 1;
    int j;
    int diff = 'a' - 'A';
    int hash[256] = {0};
    for (j = 0; j < len; j++)
    {
        int key = string[j] % 256;

        if ((string[j] >= 'a') && (string[j] <= 'z'))
            key-=diff;

        if (hash[key] == 1)
            return 0;
        hash[key] = 1;
    }
    return 1;
}

int is_unique(char* string)
{
    /* return brute_force_method(string); */
    return optimized_method_hash_table(string);
}

void run_test_cases()
{
    TEST_CASE(is_unique, "a", 1);
    TEST_CASE(is_unique, "", 0);
    TEST_CASE(is_unique, "abc", 1);
    TEST_CASE(is_unique, "abbc", 0);
    TEST_CASE(is_unique, "aabc", 0);
    TEST_CASE(is_unique, "abcc", 0);
    TEST_CASE(is_unique, "abc ", 1);
    TEST_CASE(is_unique, "abc  ", 0);
    TEST_CASE(is_unique, "ab  c", 0);
    TEST_CASE(is_unique, "  abc", 0);
    TEST_CASE(is_unique, "Arunima", 0);
}

int main()
{
    run_test_cases();
    return 0;
}

