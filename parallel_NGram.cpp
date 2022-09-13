#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <omp.h>
#include <cmath>
#include <chrono>
#include <thread>

#include "parallel_main.h"
using namespace std;
using namespace std::chrono;

class parallelNGram
{
    public:
        static string format_text(string file_name)
    {
        fstream text;
        string my_text;

        text.open(file_name, fstream ::in);
        if (!text)
        {
            cout << "No such file"<< endl;
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

        map<string, int> parallel_thread(int start, int finish, int dimension, string text_local)
        {

        map<string, int> local_dictionary;

        if (finish > text_local.size())
        {
            finish = text_local.size() - 1;
        }

        for ( int i = start + dimension - 1; i <=  finish; i++)
        {
            string n_gram;
            for (int j = dimension - 1; j >= 0; j--)
            {
                n_gram.push_back(text_local[i - j]);
            }

            if (local_dictionary.count(n_gram))
            {
               local_dictionary[n_gram] = local_dictionary[n_gram] + 1;
            } else
            {
                local_dictionary.insert(pair<string, int> (n_gram, 1));

            }

        }

       return local_dictionary;
    }

};
int main_parallel()
 {
    string text;
    int cores = 8;
    int n_gram_dimension = 2;
    map<string, int> thread_dictionaries[cores];
    map<string, int> :: iterator pos;
    parallelNGram par;

    text = par.format_text("Testo 10MB.txt");

    int k = round(text.size()/cores);
    auto start_time_2 =  high_resolution_clock::now();

    omp_set_num_threads(cores);
    # pragma omp parallel
    # pragma omp for
        for (int i = 0; i < cores; i++)
        {
            thread_dictionaries[i] = par.parallel_thread(i*k,((i+1) * k) + (n_gram_dimension - 1) - 1, n_gram_dimension, text);
        }

    auto finish_time_2 = high_resolution_clock::now();
    auto duration_2 = duration_cast<seconds>(finish_time_2 - start_time_2);

//    for (int i = 0; i < cores; i++)
//    {
//        for (pos = thread_dictionaries[i].begin(); pos != thread_dictionaries[i].end(); ++pos) {
//            cout << "ngram: " << pos->first << "\t"
//                << "freq: " << pos->second << endl;
//        }
//    }

    cout << duration_2.count() << endl;

    return 0;
}

