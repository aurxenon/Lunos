#pragma once

#include <ArchSpecific/Types.h>

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class VectorIterator {
    public:
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;

        VectorIterator();

        size_t operator++() {
            location = location + 1;
            return location++;
        }
        size_t operator+=(size_t num) {
            location = location + num;
            return location;
        }
        size_t operator-=(size_t num) {
            location = location - num;
            return location;
        }
        size_t operator--() {
            location = location - 1;
            return location;
        }
        size_t operator+(size_t num) {
            return location + num;
        }
        size_t operator-(size_t num) {
            return location - num;
        }
        bool operator>(VectorIterator& vecItr) {
            return location > vecItr.location;
        }
        bool operator<(VectorIterator& vecItr) {
            return location < vecItr.location;
        }
        bool operator>=(VectorIterator& vecItr) {
            return location >= vecItr.location;
        }
        bool operator<=(VectorIterator& vecItr) {
            return location <= vecItr.location;
        }
        bool operator==(VectorIterator& vecItr) {
            return location == vecItr.location;
        }
        bool operator!=(VectorIterator& vecItr) {
            return location != vecItr.location;
        }
    private:
        size_t location;
};

template<class Iterator, class Distance>
void advance(Iterator& itr, Distance index);

template<class Iterator>
size_t distance(Iterator first, Iterator second);

template<class Container>
auto begin(Container& container);

template<class Container>
auto end(Container& container);

template<class Iterator>
auto prev(Iterator itr, size_t before);

template<class Iterator>
auto prev(Iterator itr, size_t next);