
#include "Dictionary.h"
#include <string>
#include <cctype>
#include <algorithm>  // for swap

using namespace std;

const int tableSize = 50000;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl();
    ~DictionaryImpl();
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
    
    size_t hash(string word) const;
    
    size_t count(string word) const;
    
private:
    struct Bucket
    {
        string name;
        Bucket* next;
    };
    
    Bucket* m_buckets[tableSize];
    
};


DictionaryImpl::DictionaryImpl()
{
    for (int i = 0; i < tableSize; i++)
    {
        m_buckets[i] = nullptr;
    }
}


DictionaryImpl::~DictionaryImpl()
{
    for (int i = 0; i < tableSize; i++)
    {
        Bucket* tempdel = m_buckets[i];
        if (tempdel == nullptr)
            continue;
        else
        {
            while (tempdel != nullptr)
            {
                Bucket* temp = tempdel;
                tempdel = tempdel->next;
                delete temp;
            }
        }
    }
}


static const size_t Initial = 2166136261U;
static const size_t Multiple = 16777619;


size_t DictionaryImpl::hash(string word) const
{
    
    size_t index = Initial;
    
    for (size_t i = 0; i < word.length(); i++)
    {
        index = index * (word[i]);
        index = index * Multiple;
    }
    
    
    return (index * 107) % tableSize;
}



void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    
    size_t index = hash(word);
    
    if (! word.empty())
    {
        Bucket* node = new Bucket;
        node->name = word;
        
        Bucket* ptr = m_buckets[index];
        
        if (ptr != nullptr)
        {
            while (ptr->next != nullptr)
            {
                ptr = ptr->next;
            }
            ptr->next = node;
            node->next = nullptr;
        }
        else
        {
            m_buckets[index] = node;
            node->next = nullptr;
        }
    }
}

size_t DictionaryImpl::count(string word) const
{
    size_t count = 0;
    
    for (int i = 0; i < word.length(); i++)
    {
        count += word[i];
    }
    
    return count;
}



void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;
    
    removeNonLetters(letters);
    
    if (letters.empty())
        return;
    
    size_t find = hash(letters);
    
    string permutation = letters;
    
    Bucket* ptr = m_buckets[find];
    
    if (ptr != nullptr)
    {
        while (ptr != nullptr)
        {
            if (count(permutation) == count(ptr->name))
            {
                int found = 0;
                
                for (int k = 0; k < permutation.length(); k++)
                {
                    for (int i = 0; i < ptr->name.length(); i++)
                    {
                        if (permutation[k] == ptr->name[i])
                        {
                            found++;
                            break;
                        }
                    }
                }
                if (found == ptr->name.length())
                    callback(ptr->name);
            }
            ptr = ptr->next;
        }
    }
}


void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop off everything from "to" to end.
}


void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;
    
    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}


Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters, callback);
}

