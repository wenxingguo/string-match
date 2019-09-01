#include <iostream>
#include <string>
using namespace std;

int* kmp_next_array(const string& s){
    int* next = new int[s.length()]{0,0};//前两个数字是固定的
    int flag = 0;
    for (int i = 2; i < s.length(); ++i){
        for(int j = i-1; j >=1;){
            if(s[i-1] == s[next[j]]){//递推查找最大公共前后缀
                next[i] = next[j]+1;//通过next[j] ==> next[j+1];
                flag = 1;//找到了公共前后缀
                break;
            }
            j = next[j]; //关键迭代
        }
        if(flag==0){//没找着公共前后缀
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
            if(j==temp.length()-1) return i-temp.length()+1;//匹配到最后一个，完成匹配，返回开始的位置
            ++j;
            continue;//继续匹配
        }
        else{//失配
            if(j == 0) continue;//j还停留在第一个字符的位置, 而i则往前移
            j = next[j]; //向右平移模式字符串
            --i; //失配时保证i的位置不变
        }
    }
    return -1; //没有找到返回-1
}

int main(){
    string root{"1abaabc"}, temp{"abaabc"};
    int* next = kmp_next_array(temp);
    int pose = KMP_find(temp, root, next);
    cout << pose << endl;    
}
