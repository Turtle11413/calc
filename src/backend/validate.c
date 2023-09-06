#include "calc.h"

int validateStr(char* str) {
  int res = OK;
  if (validateBrackets(str) && checkDots(str) && validateOperators(str) && validateTrig(str)) {
    res = OK;
  } else {
    res = ERROR;
  }
  return res;
}

int validateBrackets(char* str) {
  int leftBracket = 0;
  int rightBracket = 0;
  int res = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') {
      leftBracket++;
      if (str[i + 1] == ')') {
        res = ERROR;
      }
    }
    if (str[i] == ')') {
      rightBracket++;
      if (rightBracket > leftBracket) {
        res = ERROR;
      }
    }
  }
  if (rightBracket != leftBracket) {
    res = ERROR;
  }
  if (res == OK) {
    res = validateBracketsPosition(str);
  }
  return res;
}

int validateBracketsPosition(char* str) {
  int strLength = strlen(str);
  int res = OK;
  for (int i = 0; str[i] != '\0'; i++) {
    if (i == 0 && str[i] == ')') {
      res = ERROR;
    }
    if (i == strLength - 1 && str[i] == '(') {
      res = ERROR;
    }
    if (str[i] == '(' && i != 0) {
      if (str[i - 1] == ')' || isdigit(str[i - 1])) {
        res = ERROR;
      }
      if (str[i + 1] == ')') {
        res = ERROR;
      }
    }
    if (str[i] == ')' && i != 0) {
      if (str[i + 1] == '(' || isdigit(str[i + 1])) {
        res = ERROR;
      }
      if (str[i - 1] == '(') {
        res = ERROR;
      }
    }
  }
  return res;
}

int checkDots(char* str) {
  int res = OK;
  char* ptr = str;
  while (*ptr != '\0' && res == OK) {
    int dotsCount = 0;
    if (isdigit(*ptr)) {
      while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') {
        if (*ptr == '.') dotsCount++;
        ptr++;
      }
      ptr--;
    }
    if (dotsCount > 1 || *ptr == '.') res = ERROR;
    ptr++;
  }
  return res;
}

int validateOperators(char* str) {
  int res = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && res == OK; i++) {
    if (strchr("+-", str[i])) {
      if (i == strLength - 1) res = ERROR;
      if (i != 0 && i != strLength - 1) {
        if (i > 0 && (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1])))
          res = ERROR;
      }
    }

    if (strchr("/*^", str[i])) {
      if (i == 0 || i == strLength - 1) res = ERROR;
      if (i != 0 && i != strLength - 1) {
        if (i > 0 && (strchr(")/*^", str[i + 1]) || strchr("/*^+-", str[i - 1])))
          res = ERROR;
      }
    }
    if (str[i] == 'm') {
      if (i == 0 || i > strLength - 4) res = ERROR;
      if (i != 0 || i < strLength - 4) {
        if (i > 0 && !isdigit(str[i - 1]) && (strchr(")x", str[i - 1]) == NULL))
          res = ERROR;
        if (i > 0 && !isdigit(str[i + 3]) && (strchr("(x", str[i + 3]) == NULL))
          res = ERROR;
      }
      i += 2;
    }
  }
  return res;
}

int validateTrig(char* str) {
  int res = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && res == OK; i++) {
    // sin cos tan
    if (str[i] == 'c' || str[i] == 't' ||
        (str[i] == 's' && str[i + 1] == 'i')) {
      if (i > strLength - 6) {
        res = ERROR;
      }
      if (i != 0 || i < strLength - 6) {
        if (i > 0 &&
            (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          res = ERROR;
      }
      i += 2;
    }
    //  asin acos atan
    if (str[i] == 'a') {
      if (i > strLength - 7) {
        res = ERROR;
      }
      if (i != 0 || i < strLength - 7) {
        if (i > 0 &&
            (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          res = ERROR;
      }
      i += 3;
    }
  }
  return res;
}

int validateOtherFuncs(char* str) {
  int res = OK;
  int strLength = (int)strlen(str);
  // ln
  for (int i = 0; i < strLength && res == OK; i++) {
    if (str[i] == 'l' && str[i + 1] == 'n') {
      if (i > strLength - 5) {
        res = ERROR;
      }
      if (i != 0 || i < strLength - 5) {
        if (i > 0 &&
            (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          res = ERROR;
      }
      i++;
    }
    // sqrt
    if (str[i] == 's' && str[i + 1] == 'q') {
      if (i > strLength - 7) {
        res = ERROR;
      }
      if (i != 0 || i < strLength - 7) {
        if (i > 0 &&
            (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          res = ERROR;
      }
      if (str[i + 5] == '-') {
        res = ERROR;
      }
      i += 3;
    }
    // log
    if (str[i] == 'l' && str[i + 1] == 'o') {
      if (i > strLength - 6) {
        res = ERROR;
      }
      if (i != 0 || i < strLength - 6) {
        if (i > 0 &&
            (strchr(")x", str[i - 1]) || isdigit(str[i - 1])))
          res = ERROR;
      }
      i += 2;
    }
  }
  return res;
}

int validateX(char* str) {
  int res = OK;
  int strLength = (int)strlen(str);
  for (int i = 0; i < strLength && res == OK; i++) {
    if (str[i] == 'x') {
      if (i == 0 &&
          (isdigit(str[i + 1]) || strchr(")x", str[i + 1]))) {
        res = ERROR;
      }
      if (i == strLength - 1 &&
          (isdigit(str[i - 1]) || strchr(")x", str[i - 1]))) {
        res = ERROR;
      }
      if (i > 0 && i < strLength - 1 &&
          (isdigit(str[i + 1]) || str[i + 1] == '(' ||
           str[i + 1] == 'x')) {
        res = ERROR;
      }
      if (i > 0 && i < strLength - 1 &&
          (isdigit(str[i - 1]) || str[i - 1] == ')' ||
           str[i - 1] == 'x')) {
        res = ERROR;
      }
    }
  }
  return res;
}
