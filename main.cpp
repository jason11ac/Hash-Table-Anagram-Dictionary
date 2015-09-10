#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void anagramCallback(string anagram);

int main()
{
    cout << "Enter name of dictionary file: ";
    string filename;
    getline(cin, filename);
    ifstream wordFile(filename.c_str());
    if ( ! wordFile)
    {
        cout << "Cannot open " << filename << endl;
        return 1;
    }
    
    Dictionary dict;
    
    string word;
    while (getline(wordFile, word))
        dict.insert(word);
    wordFile.close();
    
    for (;;)
    {
        cout << "Enter a set of letters: ";
        string letters;
        getline(cin,letters);
        if ( ! cin  ||  letters.empty())
            break;
        
        cout << "Anagrams of " << letters << ":\n";
        
        dict.lookup(letters, anagramCallback);
        
        cout << endl;
    }
}

void anagramCallback(string anagram)
{
    cout << "  " << anagram;
}
