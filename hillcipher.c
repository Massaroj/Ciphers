#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Encrypts the plaintext with the key.
char *encrypt(int **key, int keyRandC, char plainText[])
{
    //Initialize all the variables.
    int i = 0, j = 0, r = 0, c = 0, letterOut = 0, letterIn = 0, letterCount = 0;
    int *plainTextMatrix;
    int result;

    char cipherText[10000];

    //Create plaintext matrix.
    plainTextMatrix = malloc(sizeof(int) * keyRandC);

    letterCount = strlen(plainText);
    printf("Original letter count = %d\n", letterCount);

    while(letterCount > 0)
    {
        //Fill plaintext matrix.
        for(i = 0; i < keyRandC; i++)
        {
            if(letterCount < 1)
            {
                plainTextMatrix[i] = 23;
                printf("%d ", plainTextMatrix[i]);
            }
            else
            {
                plainTextMatrix[i] = plainText[letterOut] - 'a';
                printf("%d ", plainTextMatrix[i]);
                letterOut++;
                letterCount--;
            }
        }
        printf("\n");

        //Do dot product;
        for(i = 0; i < keyRandC ; i++)
        {
            result = 0;

            for(j = 0; j < keyRandC ; j++)
                result += key[i][j] * plainTextMatrix[j];

            cipherText[letterIn] = (result % 26) + 'a';
            letterIn++;
        }
    }

    return cipherText;
}

//This function takes in a string and returns the integer that the string is.
int stringToInt(char *s, int len)
{
    int i, total = 0;

    for(i = 0; i < len; i++)
    {
        if(i > 0)
            total = total * 10;

        total += s[i] - '0';
    }

    return total;
}


int main(void)
{
    //Matrix, index, index, size of key matrix
    int **matrix, i, j = 0, keyLen;

    //File name for plaintext, File name for key
    char fileName[100], keyName[100];

    //Plaintext, ciphertext, check for space or \n character, check for space or \n character.
    char plainText[10000], cipherText[10000], completeCipherText[10000], garbage[5000], *Ct, k[5];

    //text file pointer, key file pointer
    FILE *txtPtr, *keyPtr;

    keyName = argv[1];
    //Open file and read in the size of the matrix.
    keyPtr = fopen(keyName, "r");
    if(keyPtr == NULL)
    {
        printf("Cannot open input file.\n");
        exit(1);
    }

    keyLen = fgetc(keyPtr) - '0';

    //Dynamically create the key matrix.
    matrix = malloc(sizeof(int *) * keyLen);
    for(i = 0; i < keyLen; i++)
        matrix[i] = malloc(sizeof(int) * keyLen);

    //Fill matrix.
    for(i = 0; i < keyLen; i++)
    {
        for(j = 0; j < keyLen; j++)
        {
            fscanf(keyPtr, "%s", k);
            matrix[i][j] = stringToInt(k, strlen(k));
        }
    }

    //Close file when done with it.
    fclose(keyPtr);

    //Open file
    fileName = argv[2];

    txtPtr = fopen(fileName, "r");
    if(txtPtr == NULL)
    {
        printf("Cannot open input file.\n");
        exit(1);
    }

    //Read in string from file.
    for(i = 0; i < 1; i++)
    {
        fscanf(txtPtr, "%s", plainText);
        strcat(cipherText, plainText);
    }

    printf("Plaintext: %s\n", cipherText);

    //Take out all the special characters, and convert everything to lower case.
    for(i = 0; i < strlen(cipherText); i++)
    {
        //Checks for upper case, changes case, then adds to string.
        if(cipherText[i] >= 'A' && cipherText[i] <= 'Z')
        {
            cipherText[i] = cipherText[i] - 'A' + 'a';
            strncat(completeCipherText, &cipherText[i], 1);
        }
        //Checks for lower case, then adds to string.
        else if(cipherText[i] >= 'a' && cipherText[i] <= 'z')
            strncat(completeCipherText, &cipherText[i], 1);
        //Checks for special characters, then skips them.
        else
            ;
    }

    //Close file.
    fclose(txtPtr);

    printf("New plaintext: %s\n", completeCipherText);

    Ct = encrypt(matrix, keyLen, completeCipherText);

    printf("Encrypted text: %s\n", Ct);

    return 0;
}
