# Hash-Table-Anagram-Dictionary

Hash Table Anagram Dictionary

The Anagram dictionary is a c++, xcode program that takes a file of words and allows the user to search those words for any anagrams of an inputted word of their choice. For example, if the user inputted cat, and tac and act were in the dictionary file, the program would output tac and act. This program works by using a linked list, hash table to quickly and efficiently search for anagrams, even if the dictionary file contains a ridiculously large number of words.

My hash function, the function in charge of sorting the dictionary for fast lookups, sorts words by what letters the words contain. Therefore, all the words that are anagrams of each other are automatically placed in the same index of the hash table and can easily be retrieved if the inputted word corresponds to said index.
