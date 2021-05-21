# CADTs

```
           /\_/\
      .---.>^.^<            C A.D.T.'s
    /(     '-´-'   C macros for general purpose
 .-´.´) /--| /           data structures.
'--´  '-"  '-"
```

**WARNING:** This library is still being developed, thus many changes may arise.

# Instructions

## Definining an ADT

To define an ADT for an specific datatype you have to use the macro defined on its respective header.

For instance, to define a vector of `int`s (that we will name `intvec`), you have to use this code:

```c
#include "cadts_vector.h"

CADTS_VECTOR(intvec,int)
```

You can also create ADTs for your own structs, passing their name as a parameter.

```c
#include "cadts_vector.h"

typedef struct{
    float foo;
    float bar;
} foobarpair;

CADTS_VECTOR(foobarvec,foobarpair)
```

Note that this macro doesn't create an instance of `foobarvec`, just defines the `foobarvec` struct and its "*methods*" (functions really), that's why it never goes inside a function.

## Using an ADT

First you have create the ADT instance, the macro defines the function `[adtname]_init` for this propose, it returns a pointer to it.

```c
intvec *myvec = intvec_init(0);
//
// Use myvec ...
// e.g.:
//     intvec_endadd(myvec,42);
//
intvec_free(myvec);
```

You can access the ADT instance trough the "*methods*" generated for your ADT, besides `[adtname]_init` they all request a pointer to this instance as first parameter. For their usage see the documentation at the beginning of the corresponding header.

After using an ADT, you have to call the `[adtname]_free` function over it so that the memory that it allocated internally is released.

### Usage rules

* **Never** access the ADTs by their members unless they are specified in the `VARIABLES` section of their documentation, also don't modify the members that are **read only**.

* **Never** define two ADTs with the same name, this will result in "*methods*" generated with the same name and compilation will fail.

## TODOs:

* Detect errors when `malloc` fails to allocate memory.
