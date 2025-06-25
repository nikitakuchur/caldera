# C Code Style Guide

## Formatting
- Use 4 spaces for indentation (no tabs).
- Keep lines no longer than 120 characters.
- Use K&R brace style:
```c
if (condition) {
  do_something();
}
```

## Naming
- Use `snake_case` for functions, variables, types, and struct names.
- Use `UPPER_CASE` for macros and constants.

## Structs and Memory
- Use `typedef` when defining structs to avoid repeating the `struct` keyword.
- If a function creates a struct instance without allocating memory, name it `*_init()`, and `*_free()` to clean it up.
- If a function creates a struct instance with memory allocation, name it `*_create()` and `*_destroy()` to free the instance.

```c
typedef struct logger logger;

bool logger_init(logger *log);
void logger_free(logger *log);

logger *logger_create(void);
void logger_destroy(logger *log);
```

## Header Guards
- Always use classic include guards, not `#pragma once`.
- Use the following format:

```c
#ifndef HEADER_H
#define HEADER_H

typedef struct foo {
    int bar;
} foo;

#endif // HEADER_H
```
