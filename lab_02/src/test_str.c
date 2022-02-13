#include "test_str.h"
#include "stdio.h"

void test_my_strcpy() {
    char s[20] = "yyy";
    assert(!my_strcmp(my_strcpy(s, "bb"), "bb"));
    assert(!my_strcmp(my_strcpy(s, "fifo"), "fifo"));
    assert(!my_strcmp(my_strcpy(s, "tryhardandyouwillwin"), "tryhardandyouwillwin"));
}

void test_my_strcat() {
    char s[20] = "aa";
    assert(!my_strcmp(my_strcat(s, "add"), "aaadd"));
    my_strcpy(s, "code");
    assert(!my_strcmp(my_strcat(s, "potato"), "codepotato"));
    my_strcpy(s, "");
    assert(!my_strcmp(my_strcat(s, ""), ""));
}

void test_my_strcmp() {
    assert(my_strcmp("arrias", "arrias") == 0);
    assert(my_strcmp("ant.filatov", "arrias") < 0);
    assert(my_strcmp("kek", "ke") > 0);
    assert(my_strcmp("aba", "abacaba") < 0);
    assert(my_strcmp("ilya", "boboniu") > 0);
    assert(my_strcmp("##ilin", "@dump") < 0);
    assert(my_strcmp("", "a") < 0);
    assert(my_strcmp("", "") == 0);
}

void test_my_strlen() {
    assert(my_strlen("") == 0);
    assert(my_strlen("aba") == 3);
    assert(my_strlen("withkey") == 7);
    assert(my_strlen("#$#$#$#$#$$#") == 12);
}
