#ifndef __DICT__
#define __DICT__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_HASH 26
#define MAX_BUFFER 201

#define DIR_IN 0
#define DIR_OUI 1

typedef unsigned char uchar_t;
typedef unsigned int uint32_t;

struct __dict_chain {
    char* key;
    struct __dict_chain* next;
    uchar_t pin;
    uchar_t value;
};

struct __dict_head {
    uint32_t count;
    struct __dict_chain* next;
};

struct dictionary {
    struct __dict_head head[MAX_HASH];
};

typedef struct dictionary_return_value {
    uchar_t value;
    uchar_t pin;
} dict_ret;

extern struct dictionary dict;
// extern char filepath[MAX_BUFFER];

uint32_t appendElement(const char* key, uchar_t value, uchar_t pin);
uint32_t deleteElement(const char* key);
uint32_t setValue(const char* key, uchar_t value, uchar_t pin); // alias: modifyElement
dict_ret getValue(const char* key);

void initDictionary();
void clearDictionary();

uchar_t getHash(const char* key);

void showAllDictionary();
void showDictionary(int hash);

void readDataFromFile(const char* filename);
void reloadDataFromFile();
void setDataFilename(const char* filename);

#endif