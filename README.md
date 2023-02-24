# 42-ft_containers

This repository contains one of my projects of the core curriculum at [42 Heilbronn].

The project ft_containers is about some of the container class templates from the C++ standard template library (STL).
As with all C++ projects at 42 Heilbronn, the code has to be written according to the C++98 standard.

## Description

The task in this project is to reimplement some of the [container] types from the C++ STL:

- [`vector`]
- [`map`]
- [`stack`]
- [`set`] _(bonus)_

Further, some additional features are required:
- `iterator_traits`
- `reverse_iterator`
- `enable_if`
- `is_integral`
- `equal`
- `lexicographical_compare`
- `pair`
- `make_pair`

The structure of each standard container has to be taken as reference.
As the solution has to comply with the C++98 standard, every C++98 feature (even deprecated ones) is expected.
Any later feature of the containers must not be implemented.
If the container has an iterator system, then this has to be implemented as well.

Apart from implementing set, the bonus part is to use a [red-black tree] as internal data structure for map and set.

## Approach

## Testing

To check that my own containers (namespace `ft`) work as the original ones (namespace `std`), some tests are included.

The [Makefile] rule `all` compiles my [tests] into two binaries, `ft` and `std`, using the containers from the respective namespace.
Running them shows the test output, including the time from a small benchmark.
Further, the `rb_tree` rule produces a binary of the same name. 
This program will display a small visualization of the insertion and deletion process of the red-black tree.

A small script [test.sh] is also included.
It automates the comparison between the `ft` and the `std` containers and saves the result in a file `result.diff`.
Ideally, this file should only contain the benchmark times.

Apart from my own tests, I also used the following testers:
- [Mikastiv/ft_containers-terminator]
- [mli42/containers_test]

## Resources

#### C++ STL

- [CPP Reference]
- [cplusplus.com]
- [GNU Compiler Collection]
- [LLVM Compiler Infrastructure]

#### Red-Black Tree

- Cormen, Leiserson, Rivest, Stein: Introduction to Algorithms, Third Edition
- [CodesDope: Red-Black Trees]

#### Miscellaneous

- [CodeProject: An Introduction to Iterator Traits]
- [Internal Pointers: A quick primer on type traits in modern C++]
- [Sandor Dargo: What are type traits in C++]
- [Siddharth Bhasin: What is std::enable_if and how to use it?]



[42 Heilbronn]: https://www.42heilbronn.de/learncoderepeat

[container]: https://en.cppreference.com/w/cpp/container
[`vector`]: https://cplusplus.com/reference/vector/vector/
[`map`]: https://cplusplus.com/reference/map/map/
[`stack`]: https://cplusplus.com/reference/stack/stack/
[`set`]: https://cplusplus.com/reference/set/set/
[red-black tree]: https://en.wikipedia.org/wiki/Red-black_tree

[Makefile]: https://github.com/hepple42/42-ft_containers/blob/master/Makefile
[tests]: https://github.com/hepple42/42-ft_containers/blob/master/src/test_containers.cpp
[test.sh]: https://github.com/hepple42/42-ft_containers/blob/master/test.sh
[Mikastiv/ft_containers-terminator]: https://github.com/Mikastiv/ft_containers-terminator
[mli42/containers_test]: https://github.com/mli42/containers_test

[CPP Reference]: https://en.cppreference.com/w/
[cplusplus.com]: https://cplusplus.com/reference/
[GNU Compiler Collection]: https://github.com/gcc-mirror/gcc/tree/master/libstdc++-v3/include/bits
[LLVM Compiler Infrastructure]: https://github.com/llvm-mirror/libcxx/tree/master/include
[CodesDope: Red-Black Trees]: https://www.codesdope.com/course/data-structures-red-black-trees/
[CodeProject: An Introduction to Iterator Traits]: https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
[Internal Pointers: A quick primer on type traits in modern C++]: https://www.internalpointers.com/post/quick-primer-type-traits-modern-cpp
[Sandor Dargo: What are type traits in C++]: https://dev.to/sandordargo/what-are-type-traits-in-c-18j5
[Siddharth Bhasin: What is std::enable_if and how to use it?]: https://medium.com/@sidbhasin82/c-templates-what-is-std-enable-if-and-how-to-use-it-fd76d3abbabe
