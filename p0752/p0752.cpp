// Author: jmyang
// Creation Date: 2024/04/22
// Running Time: 86ms

#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
using namespace std;

class Solution {
public:
    // Target number in integer type
    int target_num;
    // Record the number of attempts
    vector<bool> used;
    // Store dead end numbers
    set<int> deadends_set;
    // Using priority queue to find the shortest path
    priority_queue<pair<int, int>> state;

    // Convert string to int
    int str_to_int(string input){
        int num=0;
        for(int i=input.length()-1, weight=1; i>=0; i--, weight*=10){
            num += (input[i]-'0')*weight;
        }
        return num;
    }

    // Check whether the number worth to try
    bool check_valid(int num){
        if(used[num]) return false;
        if(deadends_set.count(num)==1) return false;
        return true;
    }

    // Find all numbers within one step that have not been tried yet
    vector<int> get_one_step(int num){
        vector<int> ans(0);
        int next_num;
        for(int i=1000;i>0;i/=10){
            if(num/i%10 == 9) next_num = num-9*i;
            else next_num = num+i;
            if(check_valid(next_num)){
                used[next_num]=true;
                ans.push_back(next_num);
            }

            if(num/i%10 == 0) next_num = num+9*i;
            else next_num = num-i;
            if(check_valid(next_num)){
                used[next_num]=true;
                ans.push_back(next_num);
            }
        }
        return ans;
    }

    // Find the shortest distance from 0000 to target
    int openLock(vector<string>& deadends, string target) {
        used.clear();
        used.resize(10000, false);
        deadends_set.clear();
        for(string str:deadends){
            if(str == "0000") return -1;
            deadends_set.insert(str_to_int(str));
        }
        target_num = str_to_int(target);
        used[0] = true;
        while(!state.empty()) state.pop();
        state.push(make_pair(0, 0));
        while(!state.empty()){
            pair<int, int> cur = state.top();
            state.pop();
            if(cur.second == target_num) return -cur.first;
            vector<int> next_vec = get_one_step(cur.second);
            for(int next_num: next_vec){
                state.push(make_pair(cur.first-1, next_num));
            }
        }
        return -1;
    }
};


int main(){
    Solution solution;
    vector<string> deadends1 = {"0201","0101","0102","1212","2002"};
    cout<<solution.openLock(deadends1, "0202")<<endl;

    vector<string> deadends2 = {"8888"};
    cout<<solution.openLock(deadends2, "0009")<<endl;

    vector<string> deadends3 = {"8887","8889","8878","8898","8788","8988","7888","9888"};
    cout<<solution.openLock(deadends3, "8888")<<endl;
    return 0;
}