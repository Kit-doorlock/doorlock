#include "dictionary.h"

struct dictionary dict;
char filepath[MAX_BUFFER];

uint32_t appendElement(const char* key, uchar_t value) {
    struct __dict_chain *point;
    uchar_t hash;

    hash = getHash(key);

    // move to last element
    if (dict.head[hash].next == NULL) {
        // if no element in head << create new chain
        point = (struct __dict_chain*)malloc(sizeof(struct __dict_chain));
        dict.head[hash].next = point;
    }
    else {
        point = dict.head[hash].next;
        while (point->next != NULL) {
            if (strcmp(point->key, key) == 0) {
                point->value = value;
                return dict.head[hash].count;
            }
            point = point->next;
        }
        if (strcmp(point->key, key) == 0) {
            point->value = value;
            return dict.head[hash].count;
        }
        point->next = (struct __dict_chain *)malloc(sizeof(struct __dict_chain));
        point = point->next;
    }

    // set key and value
    point->next = NULL;
    point->key = malloc(sizeof(char) * (strlen(key)+1));
    strcpy(point->key, key);
    point->value = value;

    dict.head[hash].count++;
    return dict.head[hash].count;
}

uint32_t deleteElement(const char* key) {
    struct __dict_chain *point, *prev;
    uchar_t hash;

    hash = getHash(key);

    // unable delete element << no element in dictionary
    if (dict.head[hash].count == 0) return -1;

    // search key is ${key} element
    point = dict.head[hash].next;
    while (strcmp(key, point->key) != 0) {
        prev = point;
        point = point->next;

        // if point is pointing NULL, it is error
        if (point == NULL) return -1;
    }

    // modify chain
    if (point == dict.head[hash].next)
        dict.head[hash].next = point->next;
    else
        prev->next = point->next;

    free(point);


    dict.head[hash].count--;
    return dict.head[hash].count;
}

uint32_t setValue(const char* key, uchar_t value) {
    struct __dict_chain *point;
    uchar_t hash;

    hash = getHash(key);

    // unable modify element << no element in dictionary
    if (dict.head[hash].count == 0) return -1;

    point = dict.head[hash].next;
    while (strcmp(key, point->key) != 0) {
        point = point->next;

        // if point is pointing NULL, it is error
        if (point == NULL) return -1;
    }

    point->value = value;
    return 0;
}

int getValue(const char* key) {
    struct __dict_chain *point;
    uchar_t hash;
    uint32_t i;

    hash = getHash(key);

    if (dict.head[hash].count == 0) return -1;

    point = dict.head[hash].next;
    for (i = 0; i < dict.head[hash].count; i++) {
        if (strcmp(key, point->key) == 0) return point->value;
        point = point->next;
    }
    return -1;
}

void initDictionary() {
    int i;
    for (i = 0; i < MAX_HASH; i++) {
        dict.head[i].count = 0;
        dict.head[i].next = NULL;
    }
}

void clearDictionary() {
    int i, j, count;
    struct __dict_chain *point, *next;

    for (i = 0; i < MAX_HASH; i++) {
        point = dict.head[i].next;
        dict.head[i].next = NULL;

        count = dict.head[i].count;

        for (j = 0; j < count; j++) {
            next = point->next;
            free(point->key);
            free(point);
            point = next;
        }

        dict.head[i].count = 0;
    }
}

uchar_t getHash(const char* key) {
    uint32_t total;
    int i, len;

    total = 0;
    len = strlen(key);
    for (i = 0; i < len; i++)
        total += key[i] % MAX_HASH;

    total %= MAX_HASH;

    return total;
}

void showAllDictionary() {
    int i;

    for (i = 0; i < MAX_HASH; i++)
        if (dict.head[i].count > 0) showDictionary(i);

    return;
}

void showDictionary(int hash) {
    struct __dict_chain *point;

    if (hash < 0 || hash >= MAX_HASH) return;
    printf("datas of hash - %2d\n", hash);
    point = dict.head[hash].next;

    while (point != NULL) {
        printf("\t%10s: %10d\n", point->key, point->value);
        point = point->next;
    }
    printf("=====================\n");
    return;
}

int checkIfFileExists(const char *filename) {
  FILE *file;
  if ((file = fopen(filename, "r")) != NULL) {
    fclose(file);
    return 1;
  }

  return 0;
}

void readDataFromFile(const char* filename) {
    if (!checkIfFileExists(filename)) return;

    setDataFilename(filename);
    reloadDataFromFile();
}

void reloadDataFromFile() {
    char buffer[MAX_BUFFER];
    FILE* fp;
    char *key, *val_ptr;
    int val;

    if (!checkIfFileExists(filepath)) return;

    clearDictionary();
    // file exists logic is already exist
    fp = fopen(filepath, "r");

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strlen(buffer)-1] = '\0';

        key = strtok(buffer, ":");
        val_ptr = atoi(strtok(NULL, ":"));

        val = atoi(val_ptr);
        appendElement(key, val);
        // for debug
        // printf("%s(%2d) hash's count - %d\n", key, getHash(key), appendElement(key, val));
    }

    fclose(fp);
}

void setDataFilename(const char* filename) {
    strcpy(filepath, filename);
}