#include <iostream>
#include <string>
using namespace std;
/*
bm算法主要基于两个匹配规则
1、坏字符
    当匹配从后比那开始，匹配到坏字符串时，如果模式串中没有相同的字符，就推进模式串的长度个字符；
    如果模式串中有出现当前字符，就将最右边的该字符与匹配串对齐。注意不是最左端，跳跃不能太快为了保证安全。
    因此bmbc[256]数组中保存的是该位置字符出现在模式串中最左端位置距尾后的距离，如果未出现则保存模式串的长度。
    因此这样的话，直接跳转到相应位置就可以了。
2、好后缀
    好后缀规则主要有三个规则，首先当匹配到坏字符时，如果字符中出现好后缀则将最右端的出现的好后缀与匹配串对齐，
    如果没有出现好后缀，就寻找最大前缀，对齐，否则将模式串向前移动模式串的长度。

3、最后
    将两种规则同时运用，取将模式串移动距离较大的情况，以加快匹配速度。
 */
int* preBMBC(const string& pattern){
    int pattern_size = pattern.size(), *bmbc = new int[UCHAR_MAX+1]; //bmbc的长度是256，

    for(int i = 0; i < UCHAR_MAX+1; ++i){
        bmbc[i] = pattern_size; //将每个字符都保存成模式串的长度
    }


    for(int i = 0; i < pattern_size; ++i){
        bmbc[pattern[i]] = pattern_size-i-1; // 更改模式串中出现了的字符列表
    }

    return bmbc;
}

int* preBMGS(const string& pattern){
    int pattern_size = pattern.size(), endpose = pattern_size-1;
    int* suffix = new int[pattern_size]; // 保存当前字符与尾部匹配的长度 例如"qwertqwer" [0,0,0,4,0,0,0,0,9]
    suffix[endpose] = pattern_size;
    
    for(int i = endpose-1; i >= 0; --i){
        if(pattern[i] == pattern[endpose]){
            int j = 1;
            while(i-j>=0 && pattern[i-j] == pattern[endpose-j]){//出现最后一个字符后，往后匹配。
                ++j;
            }
            suffix[i] = j;
        }
        else{
            suffix[i] = 0;//不是最后一个字符就为0；
        }
    }
    /*
    有了suffix数组后就可以得到最大前缀和是否出现好后缀的情况。
    为了确保安全移动，我们采取尽可能小的跳跃速度，就是每次都是与最右端出现好后缀的位置匹配，
    并且出现好几种情况都符合是，选取最小跳跃距离，应此我们发现移动距离一般来说是第一种最小，
    其次第二种然后第三种，这样处理这三种情况的顺序是先三 后二 然后一。
    
    在这里处理的顺序很重要。

    bmgs保存的是需要跳转的距离
     */
    int *bmgs = new int[pattern_size];
    //第三种情况，将所有的情况都赋值成跳转成最大，后边根据需求更改值
    for(int i = 0; i < pattern_size; ++i){
        bmgs[i] = pattern_size;
    }
    //第二种情况
    int j = 0;
    for(int i = endpose; i >=0; --i){//从后往前是后边修改时，尽可能使移动距离最小，即每次匹配到最右边的
        if(suffix[i] == i+1){//出现最大前缀的条件，其实这里只处理了出现最右边的最大
            for(; j < endpose-i; ++j){//j的值不变保证不后退。每个位置只改变一次
                //if(bmgs[j]==m){} 这个判断好像可以去掉
                bmgs[j] = endpose - i;//注意时subffix[i],对应的是最大前缀
            }
        }
    }

    for(int i = 0; i < endpose; ++i){//顺序不能换
        bmgs[endpose - suffix[i]] = endpose-i;
    }
    delete suffix;
    return bmgs;
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
    string pattern{"abaghabahjkabaghaba"};
    string s{"qjhgabaghabahjkabaghabashjgfdstyqwertyq"};
    int* bmgs = preBMGS(pattern);
    for(int i = 0; i < pattern.size(); ++i){
        cout << bmgs[i] << " ";
    }
    cout << endl;
    int* bmbc = preBMBC(pattern);
    //cout << BM_find(pattern, s, bmbc, bmgs) << endl;
    return 0;
}