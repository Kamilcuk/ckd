# ckd library

I recently read:

Towards Integer SafetyDavid Svobodasvoboda@cert.org available from
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2466.pdf

and I wanted to explore Jinja2 templating system in C language and I
decided to implement the library.

## What works?

The library provides the following:

Definitions:
  - `{{N}}` is one of `[int, uint, long, ulont, llong, ullong]`.
  - `{{T}}` is one of `[int, unsigned int, long, unsigned long, ...]` correspondingly to above.

`ckd_{{N}}_t` is a abstract type that stores a value and if the value
has overflowed.

Two macros are provided to access the type:
  - `{{T}} ckd_value(ckd_{{N}}_t)` macro to extract value from the type
  - `bool ckd_inexact(ckd_{{N}}_t)` macro to extract if the value is inexact

Four macros for operations on types that allow for addition, subtraction,
multiplication and division. The macros are overloaded for 2 and 3
arguments. The 2 arguments also accept `{{T}}` type or `ckd_{{N}}_t` type:
  - `{{OP}}` is one of `[add, sub, mul, div]`
  - `bool ckd_{{OP}}({{T}} *r, {{T}} a, {{T}} b)` - computes `a OP b` and stores the result at `*r`
  - The following overloads compute `a OP b` and return the result in a variable of `ckd_{{N}}_t`.
    Use macros `ckd_value` and `ckd_inexact` to get to the value.
    - `ckd_{{N}}_t ckd_{{OP}}({{T}} a, {{T}} b)`
    - `ckd_{{N}}_t ckd_{{OP}}({{T}} a, ckd_{{N}}_t b)`
    - `ckd_{{N}}_t ckd_{{OP}}(ckd_{{N}}_t a, {{T}} b)`
    - `ckd_{{N}}_t ckd_{{OP}}(ckd_{{N}}_t a, ckd_{{N}}_t b)`

I am providing `_div` operation that is missing from the N2466.

## Examples:

```
    printf("%d\n", ckd_value(ckd_mul(ckd_add(1, 1), 2)));
    int a;
    bool b = ckd_div(&a, ckd_mul(ckd_mul(1, 2), 4), 2);
    printf("1 * 2 * 4 / 2 = %d\n", a);
```

## Building

With cmake, needs python and jinja2.

## What does not work?

The `*int*_t` and other `size_t` and such types are missing - because
they are aliased to normal standard types, it's not possible to switch on
them with `_Generic` (well, it's possible but it's rather hard...). Also,
interoperation and integer promotions are hard to figure out.

# Personally

I do not believe the document should be merged into C, as it does not
standardize existing behaviors, and macros `__builtin_*_overflow` is
just a single compiler extension. It could make a semi-good library, tho.

# Written

Written by Kamil Cukrowski 2021
Licensed jointly under Beerware License and MIT License.

