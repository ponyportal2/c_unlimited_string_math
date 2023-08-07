#ifndef SRC_UNLIM_MATH_H_
#define SRC_UNLIM_MATH_H_

#define VAS_ATOM_SIZE 4
#define VAS_MULTIPLY_SUBPRODUCT_SIZE 128
#define VAS_REVERSE_MAXLINE 2048
#define VAS_INPUT_SIZE_MAX 128
#define VAS_ATOMS_MAX 64
#define VAS_OUTPUT_SIZE_MAX 16000
#define VAS_MULTIPLY_SUBPRODUCTS 128

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matrixCopy(char** outputMatrixLine, char** inputMatrixLine);
void threeDMatrixPrinter(char*** input);
void multMatrixAddOstatok(char** input);
void threeDMatrixReverse(char*** input);
char*** threeDMatrixCallocSub();
char*** threeDMatrixCallocNonZeroSub();
void threeDMatrixFree(char*** input);
bool isZero(char* inputString);

void cleanUpTrailingZeroes(char* inputStr);
bool charMatch(const char* inputCharArr, char inputChar);

void cleanupLeftZeros(char* before, char* after);
void reAddZeroMult(char* input, int dotPos);
size_t vas_strlen(const char* str);
void cleanUpTrailingZeroes(char* inputStr);
void add_positive_10String(char* a, char* b, char* result);
void sub_positive_10String(char* a, char* b, char* result);
void mult_positive_10String(const char* a, const char* b, char* result);
void decimFirstStepMulti(char* a, char* b, char** result);
void reAddZero(char* input, int dotPos);
void matrixToString(char** input, char* output);
void deDot(char* a, char* b, int* dotPos);
int addZerosAndReturnDotPos(char* a, char* b);
size_t vas_strlen(const char* str);
void minusTen(char* input);
void reverseString(char* inputArr);
void v10StringFirstStep(char* a, char* b, char** result, bool isSubtraction);
void v10StringSecondStepAdd(char** result);
void reverseString(char* string);
void itoa(long long num, char* src);
char* get(char** input, int i);
void matrixPrinter(char** result);
int matrixSizeDetector(char** result);
void reverseCharMatrix(char** inputArr, int n);
void place(int current, char** result, char* tempForItoa, int j);
void decimSubFirstStep(char* a, char* b, char** result);
void v10StringSecondStepSub(char** result);
void reverseStringAlt(char* inputArr);
#endif  // SRC_UNLIM_MATH_H_
