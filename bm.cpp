#include <iostream>
#include <string>

using namespace std;
int* preBMPc(const string& pattern){
    int pattern_size = pattern.size(), *temp = new int[UCHAR_MAX+1];

    for(int i = 0; i < UCHAR_MAX+1; ++i){
        temp[i] = pattern_size;
    }

    for(int i = 0; i < pattern_size; ++i){
        temp[pattern[i]] = pattern_size-i-1;
    }
    return temp;
}

int* subfix(const string& pattern){
    int pattern_size = pattern.size(), endpose = pattern_size-1;
    int* good_fit_temp = new int[pattern_size];
    good_fit_temp[endpose] = pattern_size;
    for(int i = endpose-1; i >= 0; --i){
        if(pattern[i] == pattern[endpose]){
            int j = 1;
            while(i-j>=0 && pattern[i-j] == pattern[endpose-j]){
                ++j;
            }
            good_fit_temp[i] = j;
        }
        else{
            good_fit_temp[i] = 0;
        }
    }

    int *next_ = new int[pattern_size];
    for(int i = 0; i < pattern_size; ++i){
        next_[i] = pattern_size;
    }

    int j = 0;
    for(int i = endpose; i >=0; --i){
        if(good_fit_temp[i] == i+1){
            for(; j < endpose-i; ++j){
                if(next_[j] == pattern_size) next_[j] = endpose - i;
            }
        }
    }

    for(int i = 0; i < endpose; ++i){
        next_[endpose - good_fit_temp[i]] = endpose-i;
    }
    delete good_fit_temp;
    return next_;
}

int BM_find(const string& pattern, const string& s, const int* bad_char_position, int* good_back_char){
    int endpose = pattern.size()-1, j = endpose;
    for(int i = endpose; i < s.size(); --i){
        if(pattern[j] == s[i]){
            if(j == 0) return i;
            else{
                --j;
                continue;
            }
        }
        else{
            i += bad_char_position[s[i]] > good_back_char[i]? bad_char_position[s[i]]:good_back_char[i];
            ++i;
            j = endpose;
        }
    }
    return -1;
}

int main(){
    string pattern{"j"};
    string s{"qjhgfdshjgfdstyqwertyq"};
    int* good_fit_back = subfix(pattern);
    int* good_fit = preBMPc(pattern);
    cout <<BM_find(pattern, s, good_fit, good_fit_back) << endl;
    return 0;
}