// Write a method to replace all spaces in a string with '%20'. You may assume that the string has sufficient space at the end to hold the additional characters,
// and that you are given the "true" length of the string.

#include <stdio.h>

void replace_spaces(char* string, int len)
{
    int spaces = 0;
    int i;
    int table[len];
    for (i = 0; i < len; i++)
    {
        if (string[i] == ' ')
            spaces++;
    }

    int j = len - 1;
    i = ((spaces * 2) + len);
    string[i--] = '\0';
    for (; i > 0 && spaces; i-- && j--)
    {
        if (string[j] == ' ')
        {
            string[i--] = '0';
            string[i--] = '2';
            string[i] = '%';
            spaces--;
        }
        else
        {
            string[i] = string[j];
        }
    }
}

int main()
{
    {
        char a[] = "Mr John Smith         ";
        printf("Input: %s<-\n", a);
        replace_spaces(a, 13);
        printf("Output: %s<-\n", a);
    }
    {
        char a[] = "Snehasish Banerjee    ";
        printf("Input: %s<-\n", a);
        replace_spaces(a, 18);
        printf("Output: %s<-\n", a);   
    }
    {
        char a[] = "SnehasishBanerjee    ";
        printf("Input: %s<-\n", a);
        replace_spaces(a, 17);
        printf("Output: %s<-\n", a);   
    }
    return 0;
}
