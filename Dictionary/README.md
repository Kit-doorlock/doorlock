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

if you want to append data from file, below is example   
you just follow rule <code>&lt;key&gt;:&lt;direction(1 - GPIO_IN / 0 - GPIO_OUT)&gt;:&lt;pin num&gt;</code>   
if you want to write comment in text, just use `#` character.
```
# this is example of comment.
# key - identify in dictionary
# direction - direction of gpio current flow 
# pin num - i use wiringpi gpio pin map


ponml:1
mnopqrs:0
defghij:0
wxyzuv:0
klmnopqrst:1
mnopqrs:1
qwer:1
zxcv:1
sdfg:1
wert:0
xcvb:1
iojioasjdf:1


jncjkasd:1
iojqior:1
ajkl:1
iojioasjdf:1
9192hjjknas:0
jaiocjsd09:0
iojio:0
iojnnn:1
z,.xmcop:0
901njk:1
iojcais:0
```