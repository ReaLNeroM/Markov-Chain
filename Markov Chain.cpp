#include <fstream>
#include <iostream>
#include <map>

typedef long long ll;

const int SEED = 1353203; // perfectly random, no questions asked

std::map<int, std::string> mapping;
std::map<std::string, int> reference;
std::map<std::pair<int, int>, int> occurences;
std::map<int, int> appearances_total;

int main(int argc, char* argv[]){
    std::ios::sync_with_stdio(false);

    int file_start = 0;
    int file_end = 0;

    for(char* i = argv[1]; *i; i++){
        file_start *= 10;
        file_start += (*i - '0');
    }
    for(char* i = argv[2]; *i; i++){
        file_end *= 10;
        file_end += (*i - '0');
    }

    int curr_start = 1;

    for(int x = file_start; x <= file_end; x++){
        std::string build = "output/";

        int get = x;
        do {
            build += ('0' + get % 10);
            get /= 10;
        } while(get);

        build += ".txt";
        
        std::ifstream fin(build.c_str());

        if(!fin){
            continue;
        }

        std::string prev = "";

        std::string curr = "";
        while(fin >> curr){
            if(prev != ""){
                int reference_prev = reference[prev];
                int reference_curr = reference[curr];

                if(reference_prev == 0){
                    reference_prev = reference[prev] = curr_start;
                    mapping[reference_prev] = prev;
                    curr_start++;
                }
                if(reference_curr == 0){
                    reference_curr = reference[curr] = curr_start;
                    mapping[reference_curr] = curr;
                    curr_start++;
                }

                occurences[{reference_prev, reference_curr}]++;
                appearances_total[reference_prev]++;
            }

            prev = curr;
            curr = "";
        }
    }

    if(mapping.size() == 0){
        std::cout << "ERROR: The files were blank or only contained one word";
        return -1;
    }

    int texts, length;
    std::cout << "How many texts should be generated: ";
    std::cin >> texts;
    std::cout << "How many words per text: ";
    std::cin >> length;

    std::srand(SEED);

    for(int x = 0; x < texts; x++){
        std::cout << "Text " << x + 1 << ": ";

        int curr = std::rand() % (mapping.size() / 4) + 1;  //higher values are usually rarer words
                                                            //and generate uninteresting texts
        for(int i = 0; i < length; i++){
            std::cout << mapping[curr] << ' ';

            int forward_size = appearances_total[curr];

            if(forward_size == 0){
                std::cerr << '\n' << "ERROR: No forward edge!" << '\n';
                break;
            }

            int searching_for = std::rand() % forward_size;

            for(auto ite = occurences.lower_bound({curr, 0}); ite != occurences.end(); ite++){
                if(searching_for < ite->second){
                    curr = ite->first.second;
                    break;
                } else {
                    searching_for -= ite->second;
                }
            }
        }
        
        std::cout << '\n';
    }
}
