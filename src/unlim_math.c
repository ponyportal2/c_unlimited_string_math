#include "unlim_math.h"

void add_positive_10String(char* a, char* b, char* result) {
  int dotPosLocal = 0;
  char localA[VAS_INPUT_SIZE_MAX + 1] = {0};
  char localB[VAS_INPUT_SIZE_MAX + 1] = {0};
  strcpy(localA, a);
  strcpy(localB, b);

  char** localResult = calloc(VAS_MULTIPLY_SUBPRODUCTS, sizeof(char*));
  for (int i = 0; i < VAS_MULTIPLY_SUBPRODUCTS; i++) {
    localResult[i] = calloc(VAS_MULTIPLY_SUBPRODUCT_SIZE, sizeof(char));
  }

  deDot(localA, localB, &dotPosLocal);

  reverseString(localA);
  reverseString(localB);

  v10StringFirstStep(localA, localB, localResult, true);
  v10StringSecondStepAdd(localResult);
  int resultSize = matrixSizeDetector(localResult);
  reverseCharMatrix(localResult, resultSize);
  char outputString[VAS_OUTPUT_SIZE_MAX] = {0};
  matrixToString(localResult, outputString);

  if (outputString[dotPosLocal - 1] != '\0') {
    reAddZero(outputString, dotPosLocal);
  }

  for (int i = 0; i < VAS_MULTIPLY_SUBPRODUCTS; i++) {
    if (localResult[i]) free(localResult[i]);
  }
  if (localResult) free(localResult);

  cleanUpTrailingZeroes(outputString);

  strcpy(result, outputString);
}

void sub_positive_10String(char* a, char* b, char* result) {
  int dotPosLocal = 0;
  char localA[VAS_INPUT_SIZE_MAX + 1] = {0};
  char localB[VAS_INPUT_SIZE_MAX + 1] = {0};
  strcpy(localA, a);
  strcpy(localB, b);

  char** localResult = calloc(VAS_MULTIPLY_SUBPRODUCTS, sizeof(char*));
  for (int i = 0; i < VAS_MULTIPLY_SUBPRODUCTS; i++) {
    localResult[i] = calloc(VAS_MULTIPLY_SUBPRODUCT_SIZE, sizeof(char));
  }
  deDot(localA, localB, &dotPosLocal);

  reverseString(localA);
  reverseString(localB);

  v10StringFirstStep(localA, localB, localResult, false);
  v10StringSecondStepSub(localResult);
  int resultSize = matrixSizeDetector(localResult);
  reverseCharMatrix(localResult, resultSize);
  char outputString[VAS_OUTPUT_SIZE_MAX] = {0};
  matrixToString(localResult, outputString);

  if (outputString[dotPosLocal - 1] != '\0') {
    reAddZero(outputString, dotPosLocal);
  }

  for (int i = 0; i < VAS_MULTIPLY_SUBPRODUCTS; i++) {
    if (localResult[i]) free(localResult[i]);
  }
  if (localResult) free(localResult);

  cleanUpTrailingZeroes(outputString);

  strcpy(result, outputString);
}

bool isZero(char* inputString) {
  bool isZeroBool = true;
  bool whileBreak = false;
  int i = 0;
  while (whileBreak == false) {
    if (inputString[i] == '\0') {
      whileBreak = true;
    } else if (inputString[i] != '0' && inputString[i] != '.' &&
               inputString[i] != '-') {
      whileBreak = true;
      isZeroBool = false;
    }
    i++;
  }
  return isZeroBool;
}

void v10StringFirstStep(char* a, char* b, char** localResult, bool isAddition) {
  bool AEnded = false;
  bool BEnded = false;
  int i = 0;
  int j = 0;
  char* tempForItoa = calloc(VAS_ATOMS_MAX, sizeof(char));
  bool whileBreak = false;
  while (whileBreak == false) {
    if (a[i] == '\0') AEnded = true;
    if (b[i] == '\0') BEnded = true;
    if (AEnded == true && BEnded == true) {
      whileBreak = true;
    }
    int current = 0;
    if (AEnded != true && BEnded != true) {
      if (isAddition) current = (a[i] - '0') + (b[i] - '0');
      if (isAddition == false) current = (a[i] - '0') - (b[i] - '0');
      place(current, localResult, tempForItoa, j);
    } else if (AEnded) {
      current = (b[i] - '0');
      place(current, localResult, tempForItoa, j);
    } else if (BEnded) {
      current = (a[i] - '0');
      place(current, localResult, tempForItoa, j);
    }
    j++;
    i++;
  }
  if (tempForItoa) free(tempForItoa);
}

void v10StringSecondStepAdd(char** localResult) {
  int i = 0;
  char* tempForItoa = calloc(VAS_ATOMS_MAX, sizeof(char));
  while (vas_strlen(localResult[i]) > 0) {
    if (atoi(localResult[i]) > 9) {
      if (localResult[i + 1][0] != '\0') {
        itoa(atoi(localResult[i + 1]) + 1, tempForItoa);
        strcpy(localResult[i + 1], tempForItoa);
      } else {
        localResult[i + 1][0] = '1';
      }
      minusTen(localResult[i]);
    }
    i++;
  }
  if (tempForItoa) free(tempForItoa);
}

void v10StringSecondStepSub(char** localResult) {
  int i = 0;
  char* tempForItoa = calloc(VAS_ATOMS_MAX, sizeof(char));
  while (vas_strlen(localResult[i]) > 0) {
    if (atoi(localResult[i]) < 0) {
      if (vas_strlen(localResult[i + 1]) > 0) {
        itoa(atoi(localResult[i + 1]) - 1, tempForItoa);
        strcpy(localResult[i + 1], tempForItoa);
        itoa(10 + atoi(localResult[i]), tempForItoa);
        strcpy(localResult[i], tempForItoa);
      }
    }
    i++;
  }
  if (tempForItoa) free(tempForItoa);
}

void mult_positive_10String(const char* a, const char* b, char* result) {
  char*** subProducts = threeDMatrixCallocSub();
  char*** nonZeroSubProducts = threeDMatrixCallocNonZeroSub();
  char* tempForItoa = calloc(VAS_ATOMS_MAX, sizeof(char));
  char aCpy[VAS_ATOMS_MAX] = {0};
  strcpy(aCpy, a);
  char bCpy[VAS_ATOMS_MAX] = {0};
  strcpy(bCpy, b);

  int localDotPos = 0;
  deDot(aCpy, bCpy, &localDotPos);

  reverseString(aCpy);
  reverseString(bCpy);

  int aLen = vas_strlen(aCpy);
  int bLen = vas_strlen(bCpy);

  for (int ai = 0; ai < aLen; ai++) {
    for (int bi = 0; bi < bLen; bi++) {
      int current = (aCpy[ai] - '0') * (bCpy[bi] - '0');
      place(current, subProducts[bi], tempForItoa, ai);
    }
  }
  if (tempForItoa) free(tempForItoa);

  int j = 0;
  for (size_t i = 0; i < VAS_ATOMS_MAX; i++) {
    if (subProducts[i][0][0] != '\0') {
      matrixCopy(nonZeroSubProducts[j], subProducts[i]);
      j++;
    }
  }

  for (size_t i = 0; i < VAS_ATOMS_MAX; i++) {
    if (nonZeroSubProducts[i][0][0] != '\0') {
      multMatrixAddOstatok(nonZeroSubProducts[i]);
    }
  }

  threeDMatrixReverse(nonZeroSubProducts);

  char sum[VAS_OUTPUT_SIZE_MAX] = {0};
  for (size_t i = 0; i < VAS_ATOMS_MAX; i++) {
    if (nonZeroSubProducts[i][0][0] != '\0') {
      char currentStr[VAS_ATOMS_MAX] = {0};
      matrixToString(nonZeroSubProducts[i], currentStr);
      for (size_t j = 0; j < i; j++) {
        strcat(currentStr, "0");
      }
      add_positive_10String(sum, currentStr, sum);
    }
  }

  reAddZero(sum, localDotPos * 2);

  if (sum[0] == '0' && sum[1] != '.') {
    char nzSum[VAS_OUTPUT_SIZE_MAX] = {0};
    cleanupLeftZeros(sum, nzSum);
    cleanUpTrailingZeroes(nzSum);
    strcpy(result, nzSum);
  } else {
    cleanUpTrailingZeroes(sum);
    strcpy(result, sum);
  }

  threeDMatrixFree(subProducts);
  threeDMatrixFree(nonZeroSubProducts);
}

void place(int current, char** inputMatrix, char* tempForItoa, int j) {
  if (current < 0) {
    itoa(current, tempForItoa);
  } else {
    itoa(current, tempForItoa);
  }
  if (strcmp(tempForItoa, "-48") == 0) {
    strcpy(inputMatrix[j], "\0");
  } else {
    strcpy(inputMatrix[j], tempForItoa);
  }
}

void cleanupLeftZeros(char* before, char* after) {
  if ((before[0] == '0') && before[1] != '.') {
    int i = 0;
    bool whileBreak = false;
    while (whileBreak != true) {
      if (before[i] == '\0') {
        whileBreak = true;
      } else if (before[i] == '.') {
        strcpy(after, "0");
        strcat(after, (char*)before + i);
        whileBreak = true;
      } else if (before[i] != '0') {
        strcpy(after, (char*)before + i);
        whileBreak = true;
      }
      i++;
    }
  }
}

char*** threeDMatrixCallocSub() {
  char*** input = calloc(VAS_ATOMS_MAX, sizeof(char**));
  for (int i = 0; i < VAS_ATOMS_MAX; i++) {
    input[i] = calloc(VAS_ATOMS_MAX, sizeof(char*));
    for (int j = 0; j < VAS_ATOMS_MAX; j++) {
      input[i][j] = calloc(VAS_ATOM_SIZE, sizeof(char));
    }
  }
  return input;
}

char*** threeDMatrixCallocNonZeroSub() {
  char*** input = calloc(VAS_ATOMS_MAX, sizeof(char**));
  for (int i = 0; i < VAS_ATOMS_MAX; i++) {
    input[i] = calloc(VAS_ATOMS_MAX, sizeof(char*));
    for (int j = 0; j < VAS_ATOMS_MAX; j++) {
      input[i][j] = calloc(VAS_ATOM_SIZE, sizeof(char));
    }
  }
  return input;
}

void threeDMatrixFree(char*** input) {
  for (int i = 0; i < VAS_ATOMS_MAX; i++) {
    for (int j = 0; j < VAS_ATOMS_MAX; j++) {
      if (input[i][j]) free(input[i][j]);
    }
    if (input[i]) free(input[i]);
  }
  if (input) free(input);
}

void minusTen(char* input) {
  input[0] = input[1];
  input[1] = '\0';
}

void matrixToString(char** input, char* output) {
  int i = 0;
  while (vas_strlen(input[i]) > 0) {
    strcat(output, input[i]);
    i++;
  }
}

void itoa(long long num, char* src) {
  int i = 0, j = 0;
  int digit;
  int radix;
  radix = 10;
  while ((num >= pow(radix, i) && num > 0) ||
         (num <= -pow(radix, i) && num < 0)) {
    digit = (int)(num / pow(radix, i++)) % radix;
    if (num < 0) digit = -digit;
    src[j++] =
        (digit >= 0 && digit <= 9) ? (char)(digit + 48) : (char)(digit + 65);
  }
  if (num == 0) src[j++] = 48;
  if (num < 0) src[j++] = '-';
  src[j] = '\0';
  reverseString(src);
}

void reverseString(char* string) {
  char temp[VAS_REVERSE_MAXLINE];
  strcpy(temp, string);
  int length = vas_strlen(string);
  int i;
  for (i = 0; i < length; i++) string[i] = temp[length - i - 1];
  string[i] = '\0';
}

void reverseCharMatrix(char** inputArr, int n) {
  int i = 0;
  while (((n - i - 1) - i) > 0) {
    char tempStr[VAS_ATOMS_MAX] = {0};
    strcpy(tempStr, inputArr[i]);
    strcpy(inputArr[i], inputArr[n - i - 1]);
    strcpy(inputArr[n - i - 1], tempStr);
    i++;
  }
}

void reverseStringAlt(char* inputArr) {
  int i = 0;
  int n = vas_strlen(inputArr);
  while (inputArr[i] != '\0') {
    char tempChar = inputArr[i];
    inputArr[i] = inputArr[n - i - 1];
    inputArr[n - i - 1] = tempChar;
  }
}

int matrixSizeDetector(char** localResult) {
  int i = 0;
  while (vas_strlen(localResult[i]) > 0) {
    i++;
  }
  return i;
}

void matrixPrinter(char** localResult) {
  int i = 0;
  printf("out: [");
  do {
    if (i == 0) {
      printf("%2s", localResult[i]);
    } else {
      printf(",%2s", localResult[i]);
    }
    i++;
  } while (vas_strlen(localResult[i]) > 0);
  printf("]\n");
}

void threeDMatrixPrinter(char*** input) {
  for (size_t i = 0; i < VAS_ATOMS_MAX; i++) {
    if (input[i][0][0] != '\0') {
      matrixPrinter(input[i]);
    }
  }
}

void threeDMatrixReverse(char*** input) {
  for (size_t i = 0; i < VAS_ATOMS_MAX; i++) {
    if (input[i][0][0] != '\0') {
      reverseCharMatrix(input[i], matrixSizeDetector(input[i]));
    }
  }
}

void matrixCopy(char** outputMatrixLine, char** inputMatrixLine) {
  int i = 0;
  while (vas_strlen(inputMatrixLine[i]) > 0) {
    strcpy(outputMatrixLine[i], inputMatrixLine[i]);
    i++;
  }
}

void multMatrixAddOstatok(char** input) {
  int i = 0;
  char temp[VAS_ATOMS_MAX] = {0};
  while (vas_strlen(input[i]) > 0) {
    if (vas_strlen(input[i]) > 1) {
      int des = input[i][0] - '0';
      itoa(atoi(input[i + 1]) + des, temp);
      strcpy(input[i + 1], temp);
      input[i][0] = input[i][1];
      input[i][1] = '\0';
    }
    i++;
  }
}

void deDot(char* a, char* b, int* dotPos) {
  char aCpy[VAS_INPUT_SIZE_MAX + 1] = {0};
  strcpy(aCpy, a);

  char bCpy[VAS_INPUT_SIZE_MAX + 1] = {0};
  strcpy(bCpy, b);
  // -----------------------WHAT IS NEEDED:--------------------------------
  // char a[TEST_VALUE_SIZE] = "        875.84758623475897345878784953789";
  // char b[TEST_VALUE_SIZE] = "46237647823.64762374000000000000000000000";
  // ----------------------------------------------------------------------
  bool AEnded = false, BEnded = false;
  bool ADotFound = false, BDotFound = false;
  bool ADotParsed = false, BDotParsed = false;
  char ALeftPart[VAS_INPUT_SIZE_MAX * 2] = {0};
  char BLeftPart[VAS_INPUT_SIZE_MAX * 2] = {0};
  char ARightPart[VAS_INPUT_SIZE_MAX + 1] = {0};
  char BRightPart[VAS_INPUT_SIZE_MAX + 1] = {0};
  int i = 0, j = 0;
  bool whileBreak = false;
  while (whileBreak == false) {
    if (AEnded == false || ADotFound == false) {
      if (a[i] == '\0') {
        AEnded = true;
      } else if (a[i] == '.') {
        ADotFound = true;
      }
    }

    if (BEnded == false || BDotFound == false) {
      if (b[j] == '\0') {
        BEnded = true;
      } else if (b[j] == '.') {
        BDotFound = true;
      }
    }

    if (ADotFound == true && ADotParsed == false) {
      strcpy(ALeftPart, strtok(aCpy, "."));
      strcpy(ARightPart, strtok(NULL, "."));
      ADotParsed = true;
    }

    if (BDotFound == true && BDotParsed == false) {
      strcpy(BLeftPart, strtok(bCpy, "."));
      strcpy(BRightPart, strtok(NULL, "."));
      BDotParsed = true;
    }

    if ((AEnded == true && BEnded == true) ||
        (AEnded == true && BDotParsed == true) ||
        (ADotParsed == true && BDotParsed == true) ||
        (ADotParsed == true && BEnded == true)) {
      whileBreak = true;
    }

    if (AEnded == false && ADotFound == false) i++;
    if (BEnded == false && BDotFound == false) j++;
  }

  if (ADotFound == false) {
    *dotPos = addZerosAndReturnDotPos(ARightPart, BRightPart);
    strcat(a, ARightPart);
  } else {
    *dotPos = addZerosAndReturnDotPos(ARightPart, BRightPart);
    strcat(ALeftPart, ARightPart);
    strcpy(a, ALeftPart);
  }

  if (BDotFound == false) {
    *dotPos = addZerosAndReturnDotPos(ARightPart, BRightPart);
    strcat(b, BRightPart);
  } else {
    *dotPos = addZerosAndReturnDotPos(ARightPart, BRightPart);
    strcat(BLeftPart, BRightPart);
    strcpy(b, BLeftPart);
  }
}

int addZerosAndReturnDotPos(char* a, char* b) {
  int dotPos = -1;
  int i = 0;
  size_t biggerStrlen =
      vas_strlen(a) > vas_strlen(b) ? vas_strlen(a) : vas_strlen(b);
  while (vas_strlen(a) < biggerStrlen || vas_strlen(b) < biggerStrlen) {
    if (vas_strlen(a) < vas_strlen(b)) {
      a[vas_strlen(a) + i] = '0';
    } else {
      b[vas_strlen(b) + i] = '0';
    }
  }
  dotPos = vas_strlen(a);
  return dotPos;
}

void reAddZero(char* input, int dotPos) {
  char tempStr[VAS_ATOMS_MAX] = {0};
  if (dotPos == 0) strcat(tempStr, "0");
  strncat(tempStr, input, vas_strlen(input) - dotPos);
  strcat(tempStr, ".");
  strcat(tempStr, (char*)input + vas_strlen(input) - dotPos);
  if (tempStr[strlen(tempStr) - 1] == '.') tempStr[strlen(tempStr) - 1] = '\0';
  strcpy(input, tempStr);
}

void reAddZeroMult(char* input, int dotPos) {
  char tempStr[VAS_ATOMS_MAX] = {0};
  if (dotPos == 0) strcat(tempStr, "0");
  strncat(tempStr, input, dotPos);
  strcat(tempStr, ".");
  strcat(tempStr, (char*)input + dotPos);
  if (tempStr[strlen(tempStr) - 1] == '.') tempStr[strlen(tempStr) - 1] = '\0';
  strcpy(input, tempStr);
}

bool vas_match(const char* inputCharArr, char inputChar) {
  int match = false;
  int i = 0;
  while (inputCharArr[i] != '\0') {
    if (inputCharArr[i] == inputChar) {
      match = true;
    }
    i++;
  }
  return match;
}

size_t vas_strlen(const char* str) {
  size_t len = 0;
  while (*str != '\0') {
    str++;
    len++;
  }
  return (size_t)len;
}

void cleanUpTrailingZeroes(char* inputStr) {
  int i = strlen(inputStr) - 1;
  bool whileBreak = false;
  if (charMatch(inputStr, '.') == true) {
    while (whileBreak == false && i > -1) {
      if ((i - 1 > 0) && inputStr[i] == '0' && inputStr[i - 1] != '.') {
        inputStr[i] = '\0';
      } else {
        whileBreak = true;
      }
      i--;
    }
  }
}

bool charMatch(const char* inputCharArr, char inputChar) {
  int match = false;
  int i = 0;
  while (inputCharArr[i] != '\0') {
    if (inputCharArr[i] == inputChar) {
      match = true;
    }
    i++;
  }
  return match;
}