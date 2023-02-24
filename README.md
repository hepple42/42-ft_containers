# 42-ft_containers

This repository contains one of my projects of the core curriculum at [42 Heilbronn].

The project ft_containers is about some of the [container] class templates from the C++ standard template library (STL).
As with all C++ projects at 42 Heilbronn, the code has to be written according to the C++98 standard.

## Description

The task in this project is to reimplement four of the container types from the C++ STL:

- `vector`
- `map`
- `stack`
- `set` _(bonus)_

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
As the solution has to comply with the C++98 standard, so every C++98 feature (even deprecated ones) is expected.
Any later feature of the containers must not be implemented.
If the container has an iterator system, then this has to be implemented as well.
For memory management, std::allocator has to be used.
For map and set, a [binary search tree] is required, for the bonus part, it has to be a [red-black tree].

## Approach

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
[binary search tree]: https://en.wikipedia.org/wiki/Binary_search_tree
[red-black tree]: https://en.wikipedia.org/wiki/Red-black_tree
[CPP Reference]: https://en.cppreference.com/w/
[cplusplus.com]: https://cplusplus.com/reference/
[GNU Compiler Collection]: https://github.com/gcc-mirror/gcc/tree/master/libstdc++-v3/include/bits
[LLVM Compiler Infrastructure]: https://github.com/llvm-mirror/libcxx/tree/master/include
[CodesDope: Red-Black Trees]: https://www.codesdope.com/course/data-structures-red-black-trees/
[CodeProject: An Introduction to Iterator Traits]: https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
[Internal Pointers: A quick primer on type traits in modern C++]: https://www.internalpointers.com/post/quick-primer-type-traits-modern-cpp
[Sandor Dargo: What are type traits in C++]: https://dev.to/sandordargo/what-are-type-traits-in-c-18j5
[Siddharth Bhasin: What is std::enable_if and how to use it?]: https://medium.com/@sidbhasin82/c-templates-what-is-std-enable-if-and-how-to-use-it-fd76d3abbabe
