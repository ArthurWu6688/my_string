#include "my_string.h"

void TestString1()
{
    my_string::string s1;
    my_string::string s2("hello");
    my_string::string s3(s2);
    my_string::string s4(s2.begin(), s2.end());
}

void TestString2()
{
    my_string::string s("hello");
    // 注意：如果自定义类型想要支持范围for循环，类中必须包含begin和end
    // 的迭代器接口，以及对迭代器进行++
    for (auto e : s)
        cout << e;
    cout << endl;

    my_string::string::iterator it = s.begin();
    while (it != s.end())
    {
        cout << *it;
        ++it;
    }
    cout << endl;

    for (size_t i = 0; i < s.size(); ++i)
    {
        cout << s[i];
    }
    cout << endl;
}


void TestString3()
{
    my_string::string s;
    s.reserve(100);
    size_t sz = s.capacity();

    for (size_t i = 0; i < 100; ++i)
    {
        s.push_back('a');
        if (sz != s.capacity())
        {
            cout << sz << endl;
            sz = s.capacity();
        }
    }
}

void TestString4()
{
    my_string::string s("hello");
    s.resize(10, 'A');
    cout << s << endl;
    s.resize(30, 'B');
    cout << s << endl;


    s.resize(25);
    cout << s << endl;

    s.resize(16);
    cout << s << endl;

    s.resize(10);
    cout << s << endl;

}

void TestString5()
{
    my_string::string s("hello");
    cout << s << endl;
    s += "   ";
    cout << s << endl;
    my_string::string str("world");
    s += str;
    cout << s << endl;
    s.append(3, '!');
    cout << s << endl;
}


void TestString6()
{
    my_string::string s("hello");

    s += "world";
    s.insert(s.end(), '!');
    cout << s << endl;

    size_t pos = s.find('o');
    if (pos != string::npos)
    {
        s.insert(s.begin()+pos + 1, ' ');
        cout << s << endl;
    }

    s.insert(s.begin(), '#');
    cout << s << endl;

    s.erase(s.begin());
    cout << endl;

    pos = s.rfind(' ');
    if (pos != string::npos)
    {
        s.erase(s.begin() + pos);
        cout << endl;
    }
}


void TestString7()
{
    my_string::string s("hello world !!!");
    size_t pos = 0;
    size_t start = 0;
    while (true)
    {
        pos = s.find(' ', pos);
        my_string::string word = s.substr(start, pos - start);
        cout << word << endl;
        if (pos == my_string::string::npos)
        {
            return;
        }

        pos += 1;
        start = pos;
    }
}

int main()
{
    TestString1();
    TestString2();
    TestString3();
    TestString4();
    TestString5();
    TestString6();
    TestString7();


    return 0;
}