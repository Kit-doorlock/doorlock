#include "dictionary.h"
#include <stdio.h>
#include <string.h>

int main() {
    initDictionary();

    // append test
    printf("%2d hash's count - %d\n", getHash("ponml"), appendElement("ponml", 10));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 10) );
    printf("%2d hash's count - %d\n", getHash("ponml"), appendElement("ponml", 20));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 20));
    printf("%2d hash's count - %d\n", getHash("defghij"), appendElement("defghij", 10));;
    printf("%2d hash's count - %d\n", getHash("wxyzuv"), appendElement("wxyzuv", 10));
    printf("%2d hash's count - %d\n", getHash("klmnopqrst"), appendElement("klmnopqrst", 10));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 10));
    printf("%2d hash's count - %d\n", getHash("qwer"), appendElement("qwer", 10));
    printf("%2d hash's count - %d\n", getHash("zxcv"), appendElement("zxcv", 10));
    printf("%2d hash's count - %d\n", getHash("sdfg"), appendElement("sdfg", 10));
    printf("%2d hash's count - %d\n", getHash("wert"), appendElement("wert", 10));
    printf("%2d hash's count - %d\n", getHash("xcvb"), appendElement("xcvb", 10));

    // show test
    showAllDictionary();

    // setValue & getValue test
    printf("ponml value - %d\n", getValue("ponml"));
    setValue("ponml", 30);
    printf("ponml value - %d\n", getValue("ponml"));

    // delete test
    showDictionary(4);
    deleteElement("ponml");
    showDictionary(4);
}