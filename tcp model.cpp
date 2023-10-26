#include<cstdio>
#include<iostream>
#include<string>
#include<cstdlib>
#include<queue>
#include<stack>
#include<utility>
#include<string>
#include<cstring>
#include<set>
#include<vector>
#include<fstream>
#include<map>
#include<list>
#include<algorithm>
using namespace std;
#define int long long
int mod=1000000007;
int MAX_INT=2147483647;
vector<vector<int> >cost(7,vector<int>(7,100));
string xor1(string a, string b){
    string result = "";
    int n = b.length();
    for (int i = 1; i < n; i++) {
        if (a[i] == b[i])
            result += "0";
        else
            result += "1";
    }
    return result;
}
string mod2div(string dividend, string divisor){
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
 
    int n = dividend.length();
 
    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
            tmp = xor1(string(pick, '0'), tmp)
                  + dividend[pick];
        pick += 1;
    }
    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(string(pick, '0'), tmp);
    return tmp;
}
void crcencoder(string &s){
    string data=s;
    string key="1011";
    int l_key = key.length();
    string appended_data = (data + string(l_key - 1, '0'));
    // cout<<appended_data<<" appended data\n";

    string remainder = mod2div(appended_data, key);
    string codeword = data + remainder;
    cout << "Encoded Bits :" << codeword<< "\n";
}
void bitstuff(string &s){
    vector<int>vec;
    string ans="";
    for(int i=0;i<s.length()-5;i++){
        bool flag=true;
        for(int j=i;j<i+5;j++){
            if(s[j]!='1'){
                flag=false;
            }
        }
        if(flag){
            vec.push_back(i+4);
        }
    }
    int j=0;
    for(int i=0;i<s.length();i++){
        ans+=s[i];
        if(j<vec.size() &&vec[j]==i){
            ans+='0';
            j++;
        }
    }
    s=ans;
    cout<<"Stuffed Bits: "<<s<<endl;
}

void bitunstuff(string &s){
    vector<int>vec;
    string ans="";
    for(int i=0;i<s.length();i++){
        bool flag=true;
        for(int j=i;j<i+5;j++){
            if(s[j]!='1'){
                flag=false;
            }
        }
        if(flag){
            vec.push_back(i+4);
        }
    }
    int j=0;
    for(int i=0;i<s.length();i++){
        ans+=s[i];
        if(j<vec.size()&&vec[j]==i){
            i++;
            j++;
        }
    }
    s=ans;
    cout<<"Unstuffed Bits: "<<s<<endl;
}

class vertex {
    public :
    int ind ; 
    vector<int> a ;
    vertex(int ind) {
        a.resize(7) ;
        this->ind = ind ;
        for(int i=0;i<7;i++) a[i] = cost[ind][i] ;
    }
    void adjustcost(vector<int> &b, int m) {
        for(int i=0;i<7;i++) {
            a[i] = min(a[i],cost[ind][m]+b[i]) ; 
        }
    }
};               
int32_t main(){
int n=7;
for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
        cout<<"Enter cost (max:100) of the "<<j<<" node from "<<i<<" node"<<endl;
        cin>>cost[i][j];
        cost[j][i]=cost[i][j];
    }
}
cout<<"\nThe input cost Matrix:\n \n";
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
    cout<<cost[i][j]<<" ";
    cout<<endl;
}
cout<<endl;

vector<vertex> nodes;
for(int i=0;i<7;i++) {
    nodes.push_back(vertex(i)) ;
}

int iterations=0;
while(iterations<100) {
    
    for(int i=0;i<7;i++) {
        for(int j=0;j<7;j++) {
            if(i==j) continue ;
            nodes[i].adjustcost(nodes[j].a,j) ;
        }
    }
    iterations++; 
}
cout<<"The updated cost Matrix:\n \n";
    for(int i=0;i<7;i++) {
        for(int j=0;j<7;j++) {
            cout<<(nodes[i].a)[j]<<" ";
        }
        cout<<"\n";
    }
queue<string>q;
int size;
cout<<"Enter the size of the buffer\n";
cin>>size;
for(int i=0;i<2000;i++){
    if(i%5==0){
    q.pop();
    continue;
    }
    else{
        string data;
        cin>>data;
        if(q.size()<size)
        q.push(data);
    }
}

return 0;
}