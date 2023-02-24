# 42-ft_containers

This repository contains one of my projects of the core curriculum at [42 Heilbronn].
The project ft_containers is about some of the container class templates from the C++ standard template library (STL).
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


[42 Heilbronn]: https://www.42heilbronn.de/learncoderepeat
[binary search tree]: https://en.wikipedia.org/wiki/Binary_search_tree
[red-black tree]: https://en.wikipedia.org/wiki/Red-black_tree