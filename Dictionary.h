#ifndef DICTIONARY_INCLUDED
#define DICTIONARY_INCLUDED

#include <string>

class DictionaryImpl;

class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
private:
    DictionaryImpl* m_impl;
    Dictionary(const Dictionary&);
    Dictionary& operator=(const Dictionary&);
};

#endif // DICTIONARY_INCLUDED
