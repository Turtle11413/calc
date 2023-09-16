#include "calc.h"

int validateStr(char* str) {
  int status = OK;
  if (strlen(str) == 0 || strlen(str) > 255) {
    status = INCORRECT_INPUT;
  }
  if (validateBrackets(str) || validateDots(str) || validateOperators(str) ||
      validateTrig(str) || validateOtherFuncs(str) || validateX(str)) {
    status = INCORRECT_INPUT;
  }
  return status;
}

int validateBrackets(char* str) {
  int leftBracket = 0;
  int rightBracket = 0;
  int status = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      leftBracket++;
      if (str[i + 1] == ')') {
        status = INCORRECT_INPUT;
      }
    }
    if (str[i] == ')') {
      rightBracket++;
      if (rightBracket > leftBracket) {
        status = INCORRECT_INPUT;
      }
    }
  }
  if (rightBracket != leftBracket) {
    status = INCORRECT_INPUT;
  }
  if (status == OK) {
    status = validateBracketsPosition(str);
  }
  return status;
}

int validateBracketsPosition(char* str) {
  int len = strlen(str);
  int status = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (i == 0 && str[i] == ')') {
      status = INCORRECT_INPUT;
    }
    if (i == len - 1 && str[i] == '(') {
      status = INCORRECT_INPUT;
    }
    if (str[i] == '(' && i != 0) {
      if (str[i - 1] == ')' || isdigit(str[i - 1])) {
        status = INCORRECT_INPUT;
      }
      if (str[i + 1] == ')') {
        status = INCORRECT_INPUT;
      }
    }
    if (str[i] == ')' && i != 0) {
      if (str[i + 1] == '(' || isdigit(str[i + 1])) {
        status = INCORRECT_INPUT;
      }
      if (str[i - 1] == '(') {
        status = INCORRECT_INPUT;
      }
    }
  }
  return status;
}

int validateDots(char* str) {
  int status = OK;
  char* ptr = str;
  while (*ptr != '\0' && status == OK) {
    int dotsCount = 0;
    if (isdigit(*ptr) || (*ptr == '.')) {
      while (isdigit(*ptr) || *ptr == '.') {
        if (*ptr == '.') {
          dotsCount++;
          if (!isdigit(*(ptr - 1))) {
            status = INCORRECT_INPUT;
          }
        }
        ptr++;
      }
      ptr--;
    }
    if (dotsCount > 1) {
      status = INCORRECT_INPUT;
    }
    ptr++;
  }
  return status;
}

int validateOperators(char* str) {
  int status = OK;
  int len = (int)strlen(str);
  for (int i = 0; i < len && status == OK; i++) {
    if (strchr("+-", str[i])) {
      if (i == len - 1) status = INCORRECT_INPUT;
      if (i != 0 && i != len - 1) {
        if (i > 0 &&
            (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1])))
          status = INCORRECT_INPUT;
      }
    }

    if (strchr("/*^", str[i])) {
      if (i == 0 || i == len - 1) status = INCORRECT_INPUT;
      if (i != 0 && i != len - 1) {
        if (i > 0 &&
            (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1])))
          status = INCORRECT_INPUT;
      }
    }
    if (str[i] == 'm') {
      if (i == 0 || i > len - 4) status = INCORRECT_INPUT;
      if (i != 0 || i < len - 4) {
        if (i > 0 && !isdigit(str[i - 1]) && (strchr(")x", str[i - 1]) == NULL))
          status = INCORRECT_INPUT;
        if (i > 0 && !isdigit(str[i + 3]) && (strchr("(x", str[i + 3]) == NULL))
          status = INCORRECT_INPUT;
      }
      i += 2;
    }
  }
  return status;
}

int validateTrig(char* str) {
  int status = OK;
  int len = (int)strlen(str);
  for (int i = 0; i < len && status == OK; i++) {
    // sin cos tan
    if (str[i] == 'c' || (str[i] == 't' && str[i - 1] != 'r') ||
        (str[i] == 's' && str[i + 1] == 'i')) {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }
      if (i != 0 || i < len - 6) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          status = INCORRECT_INPUT;
      }
      i += 2;
    }
    //  asin acos atan
    if (str[i] == 'a') {
      if (i > len - 7) {
        status = INCORRECT_INPUT;
      }
      if (i != 0 || i < len - 7) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          status = INCORRECT_INPUT;
      }
      i += 3;
    }
  }
  return status;
}

int validateOtherFuncs(char* str) {
  int status = OK;
  int len = (int)strlen(str);
  // ln
  for (int i = 0; i < len && status == OK; i++) {
    if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i > len - 5) {
        status = INCORRECT_INPUT;
      }
      if (i != 0 || i < len - 5) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          status = INCORRECT_INPUT;
      }
      i++;
    }
    // sqrt
    if (str[i] == 's' && str[i + 1] == 'q') {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }
      if (i != 0 || i < len - 7) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          status = INCORRECT_INPUT;
      }
      if (str[i + 5] == '-') {
        status = INCORRECT_INPUT;
      }
      i += 3;
    }
    // log
    if (str[i] == 'l' && str[i + 1] == 'o') {
      if (i > len - 6) {
        status = INCORRECT_INPUT;
      }
      if (i != 0 || i < len - 6) {
        if (i > 0 && (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          status = INCORRECT_INPUT;
      }
      i += 2;
    }
  }
  return status;
}

int validateX(char* str) {
  int status = OK;
  int len = (int)strlen(str);
  for (int i = 0; i < len && status == OK; i++) {
    if (str[i] == 'x' && len != 1) {
      if (i == 0 && (isdigit(str[i + 1]) || strchr(")x", str[i + 1]))) {
        status = INCORRECT_INPUT;
      }
      if (i == len - 1 && (isdigit(str[i - 1]) || strchr(")x", str[i - 1]))) {
        status = INCORRECT_INPUT;
      }
      if (i > 0 && i < len - 1 &&
          (isdigit(str[i + 1]) || str[i + 1] == '(' || str[i + 1] == 'x')) {
        status = INCORRECT_INPUT;
      }
      if (i > 0 && i < len - 1 &&
          (isdigit(str[i - 1]) || str[i - 1] == ')' || str[i - 1] == 'x')) {
        status = INCORRECT_INPUT;
      }
    }
  }
  return status;
}
