// Selection sort

#include <stdio.h>
#include <string.h>

void selection_sort(char* arr)
{
    int len = strlen(arr);
    int i, j;
    printf("Input : %s len %d\n", arr, len);
    for (i = 0; i < len; i++)
    {
        int selected = i;
        for (j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[selected])
            {
                selected = j;
            }
        }
        if (selected != i)
        {
            char third = arr[selected];
            arr[selected] = arr[i];
            arr[i] = third;
        }

    }
    printf("Output: %s\n", arr);
}

int main()
{
    {
        char arr[] = "ZABCRTYUPO";
        selection_sort(arr);
    }
    {
        char arr[] = "ZYXVUWTSNMPO";
        selection_sort(arr);
    }
    {
        char arr[] = "ABCDEFHGJILK";
        selection_sort(arr);
    }
    return 0;
}
