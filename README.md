# var
SO wrong and dirty class to help in development but who would need this? idk

### NOTE
There are **NO allocations**, **ONLY typesafe**, **asserts** in wrong usecases.

### How to use it?
Firstly, you need to include header file
```
#include "var.hpp"
```
Next, you can use it like every another primitive type (like char* or int or float)
```
var a = "test";
var b = 12345678765432;
auto result = a == b;
b = a;
result = a == b;
var c = 1.2;
a = 1.2f; b = c;
result = a == b;
char* chr = var("test");
```
