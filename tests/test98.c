#include <assert.h>
#include <stdio.h>
#include "utstring.h"

int findl(const UT_string *haystack, int pos, char needle) {
  return utstring_find(haystack, pos, &needle, 1);
}
int findr(const UT_string *haystack, int pos, char needle) {
  return utstring_findR(haystack, pos, &needle, 1);
}

int main()
{
    UT_string *s;

    utstring_new(s);
    utstring_printf(s, "%s %s!", "hello", "world");
    assert(utstring_len(s) == 12);

    printf("F:");
    for (int i = -12; i <= 12; ++i) {
      printf(" %d", findl(s, i, 'l'));
    }
    printf("\n");

    printf("R:");
    for (int i = -12; i <= 12; ++i) {
      printf(" %d", findr(s, i, 'l'));
    }
    printf("\n");

    /* 2026-10-04：验证边界起点仍搜索正文，但不匹配逻辑长度外的终止符。 */
    printf("R-end: %d %d\n", findr(s, 12, 'l'), findr(s, 12, '\0'));
    utstring_clear(s);
    printf("R-empty: %d\n", findr(s, 0, '\0'));
    utstring_bincpy(s, "a\0b", 3);
    printf("R-binary: %d %ld\n", findr(s, 3, '\0'), utstring_findR(s, 3, "b\0", 2));

    utstring_free(s);
    return 0;
}
