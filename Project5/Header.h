#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include<locale.h>
#include <string.h>
#include <stdlib.h>


const char* DIGITS[] = {"ноль" ,"один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};

LPWSTR CBOuput();
void CBInput(LPWSTR);
void ConsoleRead();
wchar_t* convertCharArrayToLPCWSTR(char*);
char* print_as_digits(unsigned);
char* substring(char* string, int position, int length);
void insert_substring(char* , char* , int );