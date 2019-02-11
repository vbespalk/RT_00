# ft_printf

Re-written **printf** function

## Installation and Usage

Run **make**

```
make
```

You will get **libftprintf.a** - static library, which contains functions from libft + ft_printf()

Header file: **libftprintf.h**


Implemented flags: **+, -, (space), 0, #**;

Implemented length modifiers: **l, ll, h, hh, j, z**;

Implemented conversions: **sSpdDioOuUxXcC** and **bB** for printing numbers in **binary**;

Estimated speed rate: **60%**, comparing with original function (tested with [42FileChecker](https://github.com/jgigault/42FileChecker.git))
