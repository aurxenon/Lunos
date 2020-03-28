#include "Vector.h"

template<class T>
void Vector<T>::push_back(T value) {
    vectorBlock[size()] = value;
}

template<class T>
void Vector<T>::pop_back() {
    vectorBlock[num - 1] = nullptr;
}

template<class T>
void Vector<T>::erase() {
    for (int i = 0; i < num; i++) {
        vectorBlock[i] = nullptr;
    }
}

template<class T>
size_t Vector<T>::size() {
    return num;
}

template<class T>
size_t Vector<T>::capacity() {
    return vectorCapacity;
}

template<class T>
T& Vector<T>::at(size_t index) {
    autoresize();
    return vectorBlock[index];
}

template<class T>
T& Vector<T>::front() {
    return vectorBlock[0];
}

template<class T>
T& Vector<T>::back() {
    return vectorBlock[num - 1];
}

template<class T>
T* Vector<T>::data() {
    return vectorBlock;
}

template<class T>
void Vector<T>::resize(size_t new_len) {
    T* newVectorBlock = (T*)kmalloce(sizeof(T) * new_len);

    if (new_len >= vectorCapacity) {
        memcpy(newVectorBlock, vectorBlock, vectorCapacity);
    } else {
        memcpy(newVectorBlock, vectorBlock, new_len);
        num = new_len;
    }
    vectorCapacity = new_len;
}

template<class T>
void Vector<T>::autoresize() {
    if (num > (int)(vectorCapacity * 0.80)) {
        resize((size_t)vectorCapacity * 1.8);
    }
}

template<class T>
void Vector<T>::clear() {
    resize(0);
    vectorBlock[0] = nullptr;
}

template<class T>
bool Vector<T>::empty() {
    if (num > 0) {
        return false;
    } else {
        return true;
    }
}

template<class T>
T& Vector<T>::operator[](size_t index) {
    autoresize();
    return vectorBlock[index];
}

template int& Vector<int>::operator[](size_t index);