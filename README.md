# ckd library

I recently read:

Towards Integer SafetyDavid Svobodasvoboda@cert.org available from
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2683.pdf

and I wanted to explore Jinja2 templating system in C language and I
decided to implement the library.

## What works?

The library provides the following:

The value of the name `{{N}}` and corresponding type `{{T}}` are shown in the table below:
| `{{N}}` | `{{T}}`            |
| ------- | -------            |
| schar   | signed char        |
| uchar   | unsigned char      |
| shrt    | short              |
| ushrt   | unsigned short     |
| int     | int                |
| uint    | unsigned int       |
| long    | long               |
| ulong   | unsigned long      |
| llong   | long long          |
| ullong  | unsigned long long |
| int128  | __int128           |
| uint128 | unsigned __int128  |
|         |                    |

`ckd_{{N}}_t` is a abstract type that stores a value and if the value
has overflowed (ie. type + bool).

Two macros are provided to access the type:
  - `{{T}} ckd_value(ckd_{{N}}_t)` macro to extract value from the type
  - `bool ckd_inexact(ckd_{{N}}_t)` macro to extract if the value is inexact

There is a macro `ckd_{{N}}_t ckd_mk_{{N}}_t({{T}} value, bool inexact)`
that allows constructing the `ckd_{{N}}_t` type.

Ther is a macro `ckd_{{N}}_t ckd_mk({{T}} type, bool inexact)` that constructs
a `ckd_{{N}}_t` corresponding to given `{{T}}` type.

The are four macros for doing operations on values: addition, subtraction,
multiplication and division. The macros are overloaded for 2 and 3 arguments.
With 2 arguments, the return type `ckd_{{N}}_t` with the result of computation
and inexact bit set or unset depending if the operation overflowed or not.
The 3 argument overload store the result of computation to a `{{T}}` pointer
passed as the first argument and return a `bool` indicating if the computation
overflowed with.

The macros are like this:
  - `{{OP}}` is one of `[add, sub, mul, div]`
  - `{{ANY}}` is one of available `{{T}}` __or__ one of available `ckd_{{N}}_t`.
  - `bool ckd_{{OP}}({{T}} *r, {{ANY}} a, {{ANY}} b)`
    - computes `a OP b` and stores the result at `*r`
    - so for example `int a; ckd_add(&a, 1, 2)` computes `1 + 2` and stores the result in `a`
      and returns `false`, because the operation is fine.
  - `ckd_{{N}}_t ckd_{{OP}}({{ANY}} a, {{ANY}} b)` - computes `a OP b` and returns the result
    in a `ckd_{{N}}_t` variable. Use macros `ckd_value` and `cks_inexact` to access it.
    - So for example `printf("%d\n", cks_value(ckd_add(ckd_mul(2, 3), 4)));` outputs `10`.

I am providing `_div` operation that is missing from the N2683. I am checking in `div` 
if the second operand is `0`, but also if the first one is min and the other is `-1`,
like `INT_MIN / -1`.

I am also providing `char` `short` and `__int128` overloads missing from N2683.

## Examples:

```
    printf("%d\n", ckd_value(ckd_mul(ckd_add(1, 1), 2)));
    int a;
    bool b = ckd_div(&a, ckd_mul(ckd_mul(1, 2), 4), 2);
    printf("1 * 2 * 4 / 2 = %d\n", a);
```

## What does not work?

The `*int*_t` and other `size_t` and such types are missing - because
they are aliased to normal standard types, it's not possible to switch on
them with `_Generic` (well, it's possible but it's rather hard...). Also,
interoperation and integer promotions are hard to figure out.

I have implemented all types mixes, however they are __not correctly__ promoted.
For that, some additional code on cmake side would be needed to
detect which type promotes to which type. The table is static and just the "next"
type is chosen. Let's say for example:

```
static_assert(CHAR_BIT == 32, "");
static_assert(sizeof(int) == 1, "");
ckd_add(UCHAR_MAX, 1); // the result has type int, __not__ unsigned !
```

## Building

With cmake, needs python and jinja2 for templating.

# Opinion 

I do not believe this library should be merged into C, as it does not
standardize existing behaviors, and macros `__builtin_*_overflow` is
just a single compiler extension. It could make a semi-good library, tho.

The resulting header file has over 200'000 lines. A short C files takes a
log of time to compile. While I see maybe a way to shorten it a bit, it's
still _very big_ and I do not believe such library is feasible to use.

A version with just all three same types (ie. `ckd_add(int *, int, int)`
- all 3 types the same) results in a header file with about ~3500 lines
and is totally fine and fun to use. Such library is actually OK. But I do not
believe N->M->K relations are ever needed (ie. `ckd_add(N *, M, K)` where `N`
`M` `K` are _any_ types). Such relations are just bloat - single types
are enough.

Because typedefs from standard like `size_t` or `ptrdiff_t` or `uint8_t` 
alias normal fundamental types and because you can't put two same types
inside a `_Generic` association list, I do believe with the current
features of C language it's not possible to implement the specification
as presented in the paper. In particular, `ckd_add((size_t)1, (size_t)1)`
_has to_ return a fundamental type like `ckd_ullong_t`. Or, one could do
`typedef ckd_ullong_t ckd_size_t` knowing that `size_t` and `unsigned long long`
are the same type - for that, a library implementor has to have a
`#if __same_type(size_t, unsigned long long)`-ish comparison.

# Written

Written by Kamil Cukrowski 2021
Licensed jointly under Beerware License and MIT License.

