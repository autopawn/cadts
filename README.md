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
#include <cadts_vector.h>

CADTS_VECTOR(intvec,int)
```

You can also create ADTs for your own structs, passing their name as a parameter.

```c
#include <cadts_vector.h>

typedef struct{
    float foo;
    float bar;
} foobarpair;

CADTS_VECTOR(foobarvec,foobarpair)
```

Note that this doesn't create a `foobarvec`, just defines the `foobarvec` struct and its methods, that's why it is not inside a function.

## Using an ADT

```c
intvec myvec;
intvec_init(&myvec,0);
//
// Use myvec ...
//
intvec_free(&myvec);
```

First you have create the space in memory for the ADT instance, you can do this by creating a variable.

Then you have to initialize the ADT, the macro defines the function `[adtname]_init` for this propose. In this case the `[adtname]_init` function requires a pointer to the instance and an initial `size`, which we can left as 0.

You can access the ADT instance trough the functions generated for your ADT, see the comments at the beginning of the corresponding header.

After using an ADT, you have to call the `[adtname]_free` function over it so that the memory that it allocated internally is released.

### Usage rules

* Never access the ADTs by their members, always by their methods.

* Don't define two ADTs with the same name.

* You can't use the ADTs Before `[adtname]_init` or after `[adtname]_free`.

* Since the ADTs are complex datatypes and they allocate memory on their own, you can't just copy one into another variable like:

    ```c
    intvec yourvec;
    yourvec = myvec;
    ```

    As `yourvec` will hold the same inner references to data than `myvec` and having two ADTs sharing their data **will** lead to **undefined behavior**.

* ADT functions doesn't check for incorrect arguments (accessing a position that doesn't exists on an array), that's also **undefined behavior**.
