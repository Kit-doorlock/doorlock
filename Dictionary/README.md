## Usage

if you installed "make", just type command <code>make</code>.   
then type command <code>test</code> to test this dictionary.

my dictionary struct only support <code>&lt;string&gt;: &lt;int&gt;</code> pair, because i just this dictionary to control raspberry pi's GPIO pin.

``` c
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
```