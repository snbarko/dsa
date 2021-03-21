// Palindrome permutation: Given a string, write a function to check if it is a permutation of a palindrome, A palindrome is a word or phrase that is the same
// forwards and backwards. A permutation is a rearrangement of letters. The palindrome does not need to be limited to just dictionary words.

#include <stdio.h>
#include <string.h>

struct hashTable
{
    int count;
};

int isPermutationOfPalindrome(char* string)
{
    int len = strlen(string);

    printf("Input: %s\n", string);
    struct hashTable hashT[256];
    int i;
    int oddno = 0;
    for (i = 0; i < len; i++)
    {
        if ((string[i] == ' ') ||
            (string[i] < 'A') ||
            (string[i] > 'z'))
            continue;

        int key = string[i] % 256;

        if ((string[i] >= 'A') && (string[i] <= 'Z'))
            key = key + ('a' - 'A');
        hashT[key].count++;

        if (hashT[key].count % 2)
        {
            oddno++;
        }
        else if(hashT[key].count >= 2)
        {
            oddno--;
        }
    }

    if (oddno > 1)
        return 0;

    return 1;
}

int main()
{
    printf("Is permutation of palindrome : %d\n", isPermutationOfPalindrome("Tact Coa"));
    printf("Is permutation of palindrome : %d\n", isPermutationOfPalindrome("Ma mdap"));
    return 0;
}
