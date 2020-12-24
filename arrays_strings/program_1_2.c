// Check permutation: Given two string, write a method to decide if one is a permutation of the other

#define TEST_CASE(A, B, C, D) { if(A(B, C) != D) { printf("TEST CASE FAILED %s(%s, %s) != %s\n", #A, #B, #C, #D); } else printf ("Test Case %s(%s, %s) == %s passed\n", #A, #B, #C, #D);}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void merge(char* arr, char* newArr, int low, int mid, int high)
{
    int i;
    for(i = low; i <= high; i++)
    {
        newArr[i] = arr[i];
    }
    int lowH = low;
    int highH = mid + 1;
    int slot = low;
    while ((lowH <= mid) && (highH <= high))
    {
        if (newArr[lowH] <= newArr[highH])
        {
            arr[slot] = newArr[lowH];
            lowH++;
        }
        else
        {
            arr[slot] = newArr[highH];
            highH++;
        }
        slot++;
    }

    int remaining = mid - lowH;
    for (i = 0; i <= remaining; i++)
    {
        arr[slot + i] = newArr[lowH++];
    }
}

void merge_sort_internal(char* arr, char* newArr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort_internal(arr, newArr, low, mid);
        merge_sort_internal(arr, newArr, mid + 1, high);
        merge(arr, newArr, low, mid, high);
    }
}

void merge_sort(char* arr)
{
    int len = strlen(arr);
    char* newArr = (char*)malloc(len);
    merge_sort_internal(arr, newArr, 0, len - 1);
    free(newArr);
}

// O(nlogn)
int check_permutation_Onlogn(char* masterString, char* subString)
{
    int lenM = strlen(masterString);
    int lenS = strlen(subString);

    if (!lenM || !lenS)
        return 0;

    if (lenM != lenS)
        return 0;

    if (!strcmp(masterString, subString))
        return 1;

    char* newMaster = (char*)malloc(lenM + 1);
    strncpy(newMaster, masterString, lenM);
    merge_sort(newMaster);
    char* newsub = (char*)malloc(lenS + 1);
    strncpy(newsub, subString, lenS);
    merge_sort(newMaster);
    merge_sort(newsub);

    int status = 0;
    if (!strcmp(newMaster, newsub))
        status = 1;

    free(newMaster);
    free(newsub);
    return status;
}

struct hashTable
{
    int count;
};

// O(n)
int check_permutation_On(char* masterString, char* subString)
{
    int lenM = strlen(masterString);
    int lenS = strlen(subString);

    if (!lenM || !lenS)
        return 0;

    if (lenM != lenS)
        return 0;

    if (!strcmp(masterString, subString))
        return 1;

    int i;
    struct hashTable hashT[256] = {0};
    int visited[256] = {0};
    for (i = 0; i < lenM; i++)
    {
        int key = masterString[i] % 256;
        hashT[key].count++;
    }

    for (i = 0; i < lenS; i++)
    {
        int key = subString[i] % 256;

        if (hashT[key].count == 0)
            return 0;

        if (visited[key] == hashT[key].count)
            return 0;

        visited[key]++;
    }
    return 1;
}

int check_permutation(char* masterString, char* subString)
{
    //return check_permutation_On(masterString, subString);
    return check_permutation_Onlogn(masterString, subString);
}

void run_all_testcases()
{
    TEST_CASE(check_permutation, "", "", 0);
    TEST_CASE(check_permutation, "", "a", 0);
    TEST_CASE(check_permutation, "a", "", 0);
    TEST_CASE(check_permutation, " ", "", 0);
    TEST_CASE(check_permutation, "abc", "ab", 0);
    TEST_CASE(check_permutation, "abc ", "a ", 0);
    TEST_CASE(check_permutation, "abc", "ba", 0);
    TEST_CASE(check_permutation, "abc", "abc", 1);
    TEST_CASE(check_permutation, "abc", "bac", 1);
    TEST_CASE(check_permutation, "aab", "baa", 1);
    TEST_CASE(check_permutation, "abc ", "ca b", 1);
}

int main()
{
    run_all_testcases();
    return 0;
}
