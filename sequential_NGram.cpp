#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "sequential_NGram.h"

using namespace std;
using namespace std::chrono;

class SequentialNGram
{
public:
    string format_text(string file_name)
    {
        fstream text;
        string my_text;

        text.open(file_name, ios::in);
        if (!text)
        {
            cout << "No such file";
        }
        else
        {

            while (1)
            {
                char ch;
                text >> ch;
                if (text.eof())
                    break;
                my_text.push_back(ch);
            }
        }

        text.close();

        return my_text;
    }

    map<string, int> calculate_n_gram(int n_gram_dim, string text){
        map<string, int> dictionary;


        for (int i = 0; i < text.size() - n_gram_dim +1; i++)
        {
            string n_gram;

            for (int j = 0;  j < n_gram_dim; j++)
            {
                n_gram.push_back(text[ i + j]);
            }

            if (dictionary.count(n_gram))
            {
                dictionary[n_gram] = dictionary[n_gram] + 1;
            } else
            {
                dictionary.insert(pair<string, int> (n_gram, 1));

            }

        }

        return dictionary;
    }


};

int main_sequential()
{
    int nGramDimention = 2;
    map<string, int> dictionary_main;
    map<string, int> :: iterator pos;
    string my_file;
    SequentialNGram utils;

    my_file = utils.format_text("Testo 10MB.txt");

    auto start_time_1 =  high_resolution_clock::now();

    dictionary_main = utils.calculate_n_gram(nGramDimention, my_file);

    auto finish_time_1 = high_resolution_clock::now();
    auto duration_1 = duration_cast<seconds>(finish_time_1 - start_time_1);
    cout << duration_1.count() << endl;


    for (pos = dictionary_main.begin(); pos != dictionary_main.end(); ++pos) {
        cout << "ngram: " << pos->first << "\t"
             << "freq: " << pos->second << endl;
    }



    return 0;
};
