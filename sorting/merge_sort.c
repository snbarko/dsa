// Merge sort

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void merge(char* arr, char* newArr, int low, int mid, int high)
{
    // printf ("merge low %d %c mid %d %c high %d %c\n", low, arr[low], mid, arr[mid], high, arr[high]);
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
        // printf ("lowH %d %c highH %d %c slot %d\n", lowH, newArr[lowH], highH, newArr[highH], slot);
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
        //printf ("end lowH %d highH %d slot %d\n", lowH, highH, slot);
        slot++;
    }

    int remaining = mid - lowH;
    for (i = 0; i <= remaining; i++)
    {
        //printf ("remaining i %d remaining %d lowH %d slot %d\n", i, remaining, lowH, slot);
        arr[slot + i] = newArr[lowH++];
    }
    //printf ("End of merge low %d %c mid %d %c high %d %c\n", low, arr[low], mid, arr[mid], high, arr[high]);
}

void merge_sort_internal(char* arr, char* newArr, int low, int high)
{
    //printf ("merge sort internal %c %c\n", arr[low], arr[high]);
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
    printf("Input : %s len %d\n", arr, len);
    char* newArr = (char*)malloc(len);

    merge_sort_internal(arr, newArr, 0, len - 1);
    printf("Output: %s %s\n", arr, newArr);
    free(newArr);
}

int main()
{
    {
        //char arr[] = "CAB";
        char arr[] = "ZABCRTYUPO";
        merge_sort(arr);
    }
    {
        char arr[] = "ZYXVUWTSNMPO";
        merge_sort(arr);
    }
    {
        char arr[] = "ABCDEFHGJILK";
        merge_sort(arr);
    }
    return 0;
}
