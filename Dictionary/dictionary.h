#ifndef __DICT__
#define __DICT__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_HASH 26

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;

struct __dict_chain {
    char* key;
    int value;
    struct __dict_chain* next;
};

struct __dict_head {
    uint32_t count;
    struct __dict_chain* next;
};

struct dictionary {
    struct __dict_head head[MAX_HASH];
};

extern struct dictionary dict;

uint32_t appendElement(const char* key, int value);
uint32_t deleteElement(const char* key);
uint32_t setValue(const char* key, int value);
int getValue(const char* key);
void initDictionary();
void clearDictionary();
uchar_t getHash(const char* key);
void showAllDictionary();
void showDictionary(int hash);

#endif