#include <vector>
#include <iostream>
#include <string>
using namespace std;

int* kmp_next_array(const string& s){
    if(s.length() < 2){
        cerr << "string too short" << endl; //KMP算法适用于长度大于等于2的模式串；
    }
    int* next = new int[s.length()]{-1,0};//前两个数字是固定的
    int flag = 0;
    for (int i = 2; i < s.length(); ++i){
        for(int j = i-1; j >=1;){
            if(s[i-1] == s[next[j]]){
                next[i] = next[j]+1;//通过next[j] ==> next[j+1];
                flag = 1;
                break;
            }
            j = next[j]; //关键迭代
        }
        if(flag==0){
            next[i] = 0;
            continue;
        }
        flag = 0;
    }
    return next;
}

int KMP_find(const string& temp, const string& root, int* next){//查找，缺点只能找到第一个匹配字符串
    int j = 0;
    for(int i = 0; i < root.length(); ++i){
        if(temp[j] == root[i]){
            if(j==temp.length()-1) return i-temp.length()+1;
            ++j;
            continue;
        }
        else{
            if(next[j] == -1) continue;
            j = next[i];
            --i;
        }
    }
    return -1;
}

int main(){
    string root{"qweqwabaabaaabrtyu"};
    string temp{"abaabaaab"};
    int* next = kmp_next_array(temp);
    int pose = KMP_find(temp, root, next);
    //for(int i = 0; i < root.length(); ++i){
    //    cout<< next[i];
    //}
    //cout << endl;
    cout << pose << endl;

    
}