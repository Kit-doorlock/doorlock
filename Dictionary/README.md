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
you just follow rule <code>&lt;key&gt;:&lt;value&gt;</code>
```
ponml:18
mnopqrs:12
defghij:15
wxyzuv:11
klmnopqrst:13
mnopqrs:12
qwer:11
zxcv:16
sdfg:12
wert:15
xcvb:18
iojioasjdf:12
jncjkasd:13
iojqior:18
ajkl:111
iojioasjdf:1293
9192hjjknas:1907451
jaiocjsd09:129
iojio:1123
iojnnn:1415
z,.xmcop:1214
901njk:111
iojcais:1565
```