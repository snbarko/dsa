// Bubble sort

#include <stdio.h>
#include <string.h>

void bubble_sort(char* arr)
{
    int len = strlen(arr);
    int i, j;
    printf("Input : %s len %d\n", arr, len);
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[i])
            {
                char third = arr[j];
                arr[j] = arr[i];
                arr[i] = third;
            }
        }   
    }
    printf("Output: %s\n", arr);
}

int main()
{
    {
        char arr[] = "ZABCRTYUPO";
        bubble_sort(arr);
    }
    {
        char arr[] = "ZYXVUWTSNMPO";
        bubble_sort(arr);
    }
    {
        char arr[] = "ABCDEFHGJILK";
        bubble_sort(arr);
    }
    return 0;
}
