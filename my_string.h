//
// Created by 93539 on 2023/4/19.
//

#ifndef TEST_CPP_MY_STRING_H
#define TEST_CPP_MY_STRING_H

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

namespace my_string {
    class string {
    public:
        typedef char *iterator;
        typedef const char *const_iterator;

        void swap(string &s) {
            std::swap(_str, s._str);
            std::swap(_size, s._size);
            std::swap(_capacity, s._capacity);
        }

    public:
        template<class InputIterator>
        string(InputIterator begin, InputIterator end) {
            _size = end - begin;
            _capacity = _size;
            _str = new char[_capacity + 1];
            size_t i = 0;
            while (begin != end) {
                _str[i] = *begin;
                i++;
                begin++;
            }
            _str[_size] = '\0';
        }

        explicit string(const char *str = "") {
            if (str == nullptr)
                str = "";
            _size = strlen(str);
            _capacity = _size;
            _str = new char[strlen(str) + 1];
            strcpy(_str, str);
        }

#if 0
        //传统深拷贝写法
        string(const string &s) {
            _str = new char[sizeof(s._str) + 1];
            strcpy(_str, s._str);
            _size = s._size;
            _capacity = s._capacity;
        }

        string &operator=(const string &s) {
            if (this == &s) {
                return *this;
            } else {
                _str = new char[strlen(s._str) + 1];
                strcpy(_str, s._str);
                _size = s._size;
                _capacity = s._capacity;
            }
            return *this;
        }
#endif


//      现代深拷贝写法
        string(const string &s)
                : _str(nullptr), _size(0), _capacity(0) {
            string temp(s._str);
            swap(temp);
        }

        string &operator=(const string &s) {
            if (this == &s) {
                return *this;
            } else {
                _str = nullptr;
                string temp(s._str);
                swap(temp);
            }
            return *this;
        }


        ~string() {
            if (_str != nullptr) {
                delete[] _str;
                _size = 0;
                _capacity = 0;
                _str = nullptr;
            }
        }

        //////////////////////////////////////////////////////
        ////Iterators:
        iterator begin() {
            return _str;
        }

        iterator end() {
            return _str + _size;
        }

        const_iterator begin() const {
            return _str;
        }

        const_iterator end() const {
            return _str + _size;
        }

        //////////////////////////////////////////////////////
        ////Capacity:
        size_t size() const {
            return _size;
        }

        size_t length() const {
            return _size;
        }

        size_t capacity() const {
            return _capacity;
        }

        bool empty() const {
            return 0 == _size;
        }

        void clear() {
            _size = 0;
            _str[_size] = '\0';
        }

        void resize(size_t newsize, char c = '\0') {
            size_t oldsize = _size;
            if (newsize < oldsize) {
                _size = newsize;
                _str[_size] = '\0';
            } else if (newsize > oldsize) {
                if (newsize > _capacity) {
                    reserve(newsize);
                }
                memset(_str + _size, c, newsize - _size);
            }
            _size = newsize;
            _str[_size] = '\0';
        }

        void reserve(size_t newcapacity) {
            size_t oldcapacity = _capacity;
            if (newcapacity > oldcapacity) {
                char *temp = new char[newcapacity];
                strcpy(temp, _str);
                delete[] _str;
                _str = temp;
                _capacity = newcapacity;
            }
        }

        //////////////////////////////////////////////////////
        ////Element access:
        char &operator[](size_t index) {
            assert(index < _size);
            return _str[index];
        }

        const char &operator[](size_t index) const {
            assert(index < _size);
            return _str[index];
        }

        char &at(size_t pos) {
            if (pos >= _size)
                throw std::out_of_range("index >= _size");
            return _str[pos];
        }

        const char &at(size_t pos) const {
            if (pos >= _size)
                throw std::out_of_range("index >= _size");
            return _str[pos];
        }

        //////////////////////////////////////////////////////
        ////Modifiers:

        string &operator+=(const string &str) {
            *this += str._str;
            return *this;
        }

        string &operator+=(const char *s) {
            size_t newcapacity = _size + strlen(s);
            reserve(newcapacity);
            strcat(_str, s);
            _capacity = newcapacity;
            return *this;
        }

        string &operator+=(char c) {
            push_back(c);
            return *this;
        }

        void push_back(char ch) {
            if (_size == _capacity)
                reserve((size_t) (_capacity * 1.5) + 3);
            _str[_size++] = ch;
            _str[_size] = '\0';
        }

        string &append(const string &str) {
            *this += str;
            return *this;
        }

        string &append(const char *s) {
            *this += s;
            return *this;
        }

        string &append(size_t n, char c) {
            for (int i = 0; i < n; ++i)
                push_back(c);
            return *this;
        }

        iterator insert(iterator pos, char c) {
            if (pos < begin() || pos > end())
                return end();
            if (_size == _capacity)
                reserve((size_t) (_capacity) * 1.5);
            iterator it = end() - 1;
            while (it >= pos) {
                *(it + 1) = *it;
                --it;
            }
            *(it + 1) = c;
            ++_size;
            _str[_size] = '\0';
            return it + 1;
        }

        iterator erase(iterator pos) {
            if (pos < begin() || pos > end())
                return end();
            iterator it = pos + 1;
            while (it != end()) {
                *(it - 1) = *it;
                ++it;
            }
            --_size;
            _str[_size] = '\0';
            return pos;
        }

        //////////////////////////////////////////////////////
        ////operations:

        const char *c_str() const {
            return _str;
        }

        size_t find(char c, size_t pos = 0) const {
            while (pos < _size) {
                if (_str[pos] == c) {}
                return pos;
                ++pos;
            }
            return npos;
        }

        size_t rfind(char c, size_t pos = -1) const {
            if (pos == npos || pos > _size)
                pos = _size - 1;
            int i = pos;
            while (i >= 0) {
                if (_str[i] == c)
                    return i;
                --i;
            }
            return npos;
        }

        string substr(size_t pos = 0, size_t n = npos) const {
            if (pos == npos || pos >= _size)
                return string();
            if (pos + n >= _size)
                n = _size - pos;
            return string(begin() + pos, begin() + pos + n);
        }

        friend std::ostream &operator<<(std::ostream &_cout, const string &s) {
            for (size_t i = 0; i < s._size; ++i) {
                _cout << s[i];
            }
            return _cout;
        }

    private:
        char *_str;
        size_t _size;
        size_t _capacity;
    public:
        static const size_t npos = -1;
    };

    bool operator==(const string &lhs, const string &rhs) {
        return strcmp(lhs.c_str(), rhs.c_str());
    }

    bool operator!=(const string &lhs, const string &rhs) {
        return !(lhs == rhs);
    }
}


#endif //TEST_CPP_MY_STRING_H
