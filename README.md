# About ft_deque
This study's aim is to understand the `std::deque`, one of the STL containers of c++98.

The main goal is to emulate the memory management of the original `std::deque`:
Blocks of 4 elements not necessairly adjacent store the data, then a `std::vector` of poiters store the addresses of each block. Doing so the containers allows random access indices without much computational weight:

`_base[(__idx + offset) / CHUNK] + (__idx + offset) % CHUNK`

Where
- __idx: the random index
- offset: the amount of elements in the first chunk
- _base: the `std::vector` of pointers
- CHUNK: size of a single deque block
---
Example Deque memory disposition
```
a: |x,x,x,x|
b: |x,x,x,x|
c: |x,x,x,x|
...

base: |&a,&b,&c,...| 
```

## Todo
ft_deque.insert() without destruction