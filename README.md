# C String Library
A simple string that can be passed to most library functions, e.g. printf, and supports its own methods such as add, insert, replace, and remove.

This string library is partially based on anitrez's [Simple Dynamic Strings](https://github.com/antirez/sds/), and like it, this library does not require a function call to access the string, e.g. STRING_GET_CONTENTS(s). Instead, it can be easily passed to many library functions such as printf:

```c
printf("%s\n", str);
```

In most other libraries this, printing a string looks like this:

```c
printf("%s\n", str->buf);
```

or

```c
printf("%s\n", getStringPointer(str));
```

Similarly to SDS strings, this is achieved by using an alternative design, in which a pointer to the actual string is provided rather than a structure that points to a buffer stored elsewhere. In both libraries, header information containing the string's length and amount of allocated memory is stored directly _before_ the buffer like so:


    +--------+-------------------------------+-----------+
    | Header | Binary safe c-alike string... | Null term |
    +--------+-------------------------------+-----------+
             |
             `-> Pointer returned to the user.


# Usage

This library's strings are the same type as a regular c string, `char*`, but this library defines `string` as an alias, which should be used for every string associated with this library to avoid confusion.

You can create a string by calling `string_create` like so:

```c
string s = string_create("Hello world!");
```
or

```c
string s = string_create(NULL); // will create an empty string
```

This library includes a variety functions such as `string_add`, `string_insert`, and `string_replace`, most of which take a `string*` (which is the same as a `char**`) as an argument:

```c
string_insert(&s, 2, "hello");
```

Some functions never have to move the string to a new location, so they just take a regular `string` (or a `char*`) as an argument:

```c
string_remove(s, 2, 3);
```

or

```c
int size = string_size(s);
```

# Differences

This library has a few notable differences from the _Simple Dynamic Strings_ library, the most significant of which being the function calls. Because these strings have to be moved to a new location sometimes, most functions calls in SDS look like this:

```c
s = sdscat(s,"Some more data");
```

In order to make these function calls look better, this library's function calls work like this:

```c
string_add(&s, "Some more data");
```

The second main difference is memory usage and speed. SDS uses less memory in it's headers, but each time it's functions are called, flags have to be read from part of the header to determine the rest of it's size, which is slightly less efficient.

If memory usage is your main concern and you want to store a variety of very small and extremely large strings, SDS is probably the best choice. This library is definitley a good choice if you are planning on storing very large objects or files. If you want this library's slight advantage in efficiency and also want to store a large amount of small strings, consider replacing the header's members with a smaller data type such as `unsigned char` or even `int`.

This can be done by changing the line at the top of `str.h` from `typedef size_t str_size;` to `typedef unsigned char str_size;`, for example.
