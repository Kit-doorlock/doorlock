#include "dictionary.h"

// when delete not element, only print success
#define MINUS_VALUE_IS_FAIL(f) (f < 0 ? "fail" : "success")

void appendInCode() {
    printf("%2d hash's count - %d\n", getHash("ponml"), appendElement("ponml", 10, 20));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 10, 20) );
    printf("%2d hash's count - %d\n", getHash("ponml"), appendElement("ponml", 20, 20));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 20, 20));
    printf("%2d hash's count - %d\n", getHash("defghij"), appendElement("defghij", 1, 200));;
    printf("%2d hash's count - %d\n", getHash("wxyzuv"), appendElement("wxyzuv", 1, 200));
    printf("%2d hash's count - %d\n", getHash("klmnopqrst"), appendElement("klmnopqrst", 1, 200));
    printf("%2d hash's count - %d\n", getHash("mnopqrs"), appendElement("mnopqrs", 1, 200));
    printf("%2d hash's count - %d\n", getHash("qwer"), appendElement("qwer", 1, 200));
    printf("%2d hash's count - %d\n", getHash("zxcv"), appendElement("zxcv", 1, 200));
    printf("%2d hash's count - %d\n", getHash("sdfg"), appendElement("sdfg", 10, 20));
    printf("%2d hash's count - %d\n", getHash("wert"), appendElement("wert", 1, 200));
    printf("%2d hash's count - %d\n", getHash("xcvb"), appendElement("xcvb", 10, 20));
}

int main() {
    dict_ret ret;

    initDictionary();
    // append test
    readDataFromFile("datalist.txt");
    // appendInCode(); // not recomment

    // show test
    printf("\n\n");
    showAllDictionary();

    // setValue & getValue test
    printf("\n\n");

    ret = getValue("ponml");
    printf("ponml value - %d, %d\n", ret.value, ret.pin);
    printf("setvalue %s\n", MINUS_VALUE_IS_FAIL(setValue("mnopqrs", 30, 20)));
    printf("ponml value - %d, %d\n", ret.value, ret.pin);

    // delete test
    printf("\n\n");
    showDictionary(4);
    printf("delete %s\n", MINUS_VALUE_IS_FAIL(deleteElement("mnopqrs")));
    showDictionary(4);
    printf("delete %s\n", MINUS_VALUE_IS_FAIL(deleteElement("mnopqrs")));

    // clear test
    printf("\n\n");
    clearDictionary();
    showAllDictionary();
}