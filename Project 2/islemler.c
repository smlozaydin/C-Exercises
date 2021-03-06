/*
* @file islemler.c
* @description This program make summation and substraction with big numbers.
* @assignment Project 2
* @date 23.01.2021
* @author Samil Bilal OZAYDIN samilbilal.ozaydin@stu.fsm.edu.tr
*/
#include <stdio.h>
#include "islemler.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t *readFile(char *des, int *numSize)
{
    FILE *file;
    uint8_t *num = NULL;
    if ((file = fopen(des, "r+")) == NULL)
    {
        printf("File cannot be opened so num is send as NULL");
    }
    else
    {
        *numSize = sizeFile(file); //sayinin kac basamakli oldugu bulunur.
        num = createArray(*numSize);
        int i = 0;
        while (!(feof(file)))
        {
            char temp = fgetc(file);
            if (temp >= 48 && temp <= 57)
            {
                *(num + i) = (uint8_t)(temp - 48);
                i++;
            }
        }
    }
    fclose(file);
    return num;
}
int sizeFile(FILE *file)
{
    int size = 0;
    char temp;
    while (!((temp = fgetc(file)) == EOF))
    {
        if (temp >= 48 && temp <= 57)
            size++;
    }
    rewind(file);
    return size;
}
uint8_t *createArray(int size)
{
    uint8_t *arr = (uint8_t *)malloc(size * sizeof(uint8_t));
    return arr;
}
uint8_t *sumFile(uint8_t *num1, uint8_t *num2, int num1Size, int num2Size, int *sumSize)
{
    uint8_t *sum;
    uint8_t *big;
    uint8_t *low;

    int size;
    int diff;

    if (num1Size > num2Size) // toplamada dongu icinde hata olmaması icin buyuk basamakli sayi belirlenir.
    {
        size = num1Size;
        diff = num1Size - num2Size;
        big = num1;
        low = num2;
    }
    else
    {
        size = num2Size;
        diff = num2Size - num1Size;
        big = num2;
        low = num1;
    }
    *sumSize = size + 1;
    sum = createArray(size + 1);

    int i;
    int get = 0;
    for (i = size - 1; i >= 0; i--)
    {
        if (i >= diff)
        {
            *(sum + i + 1) = (*(big + i) + *(low + i - diff) + get) % 10;
            get = (*(big + i) + *(low + i - diff) + get) / 10;
        }
        else
        {
            *(sum + i + 1) = (*(big + i) + get) % 10;
            get = 0;
        }
    }
    if (get == 1)
    {
        *(sum) = 1;
    }
    else
    {
        *sum = 0;
    }

    return sum;
}
uint8_t *substractFile(uint8_t *num1, uint8_t *num2, int num1Size, int num2Size, int *substractSize, char *notation)
{
    uint8_t *substruct;
    uint8_t *big;
    uint8_t *low;

    int size;
    int diff;

    if (num1Size > num2Size)
    {
        size = num1Size;
        diff = num1Size - num2Size;
        big = num1;
        low = num2;
    }
    else if (num2Size == num1Size) //sayi icerikleri kontrol edilir. Buyuk olan basa gecirilir.
    {
        int i;
        for (i = 0; i < num1Size; i++)
        {
            if (*(num1 + i) > *(num2 + i))
            {
                size = num1Size;
                diff = num1Size - num2Size;
                big = num1;
                low = num2;
                break;
            }
            else if (*(num1 + i) == *(num2 + i))
            {
                continue;
            }
            else
            {
                size = num2Size;
                diff = num2Size - num1Size;
                big = num2;
                low = num1;
                *notation = '-';
                break;
            }
        }
    }
    else
    {
        size = num2Size;
        diff = num2Size - num1Size;
        big = num2;
        low = num1;
        *notation = '-';
    }
    *substractSize = size;
    substruct = createArray(size);

    int i;
    int debt = 0;
    for (i = size - 1; i >= 0; i--)
    {
        if (i >= diff)
        {
            *(substruct + i) = (*(big + i) - *(low + i - diff) - debt);
            debt = 0;
            if (*(substruct + i) > 10)
            {
                debt = 1;
                *(substruct + i) += 10;
            }
        }
        else
        {
            *(substruct + i) = (*(big + i) - debt);
            debt = 0;
        }
    }
    return substruct;
}

uint8_t *removeZeros(uint8_t *arr, int *arrSize)
{
    int i;
    uint8_t *newArr;
    for (i = 0; i < *arrSize; i++)
    {
        if (*(arr + i) != 0)
        {
            newArr = (arr + i);
            *arrSize = *arrSize - i;
            break;
        }
    }
    return newArr;
}
void displayNumber(uint8_t *num, int numSize)
{
    int i;
    for (i = 0; i < numSize; i++)
    {
        printf("%d", *(num + i));
    }
}
void printIntoFile(uint8_t *result, int resultSize, char notation)
{
    FILE *file;
    int i = 0;
    if ((file = fopen("sonuclar.txt", "w+")) == NULL)
    {
        printf("sonuclar.txt olusturulamadi.");
    }
    else
    {
        if (notation == '-')
        {
            fprintf(file, "%c", notation);
        }
        while (i != resultSize)
        {
            fprintf(file, "%u", *(result + i));
            i++;
        }
    }
    fclose(file);
}
void readResult()
{
    FILE *file;
    int i = 0;
    char num;
    if ((file = fopen("sonuclar.txt", "r")) == NULL)
    {
        printf("sonuclar.txt olusturulamadi.");
    }
    else
    {
        while (!(feof(file)))
        {
            num = fgetc(file);
            printf("%c", num);
        }
    }
    fclose(file);
}
