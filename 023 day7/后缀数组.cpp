//本题的逻辑结构：后缀数组
//本题的存储结构： 顺序
/*解题思路和算法：
后缀数组有两个关键的数组：
在后缀形成的数组  x[i]中，
sa[i] 数组表示数组 x中 排名为 i 的数组下标
height[i] 表示 sa[i] 和 sa[i−1] 的最长公共前缀
*/
//效率:时间复杂度：O(n*log^2(n)) 空间复杂度：O(n)
/*测试数据：
输入：
abababab
输出：
7 5 3 1 8 6 4 2
0 2 4 6 0 1 3 5
*/
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define endl '\n'
using LL=long long ;
const int N=1e6+10;
int n,m;
string s;
int fi[N],sec[N],cnt[N];
int sa[N],rk[N],height[N];
void get_sa(){
    for(int i=1;i<=n;i++) cnt[fi[i]=s[i]]++; //统计第一关键字
    for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1]; //计算前缀和
    for(int i=n;i;i--) sa[cnt[fi[i]]--]=i; //基数排序

    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;i++) sec[++num]=i; //存储没有第二关键字的
        for(int i=1;i<=n;i++)
            if(sa[i]>k)
                sec[++num]=sa[i]-k;       //枚举第二关键字
        for(int i=1;i<=m;i++) cnt[i]=0;  //清空第二关键字
        for(int i=1;i<=n;i++) cnt[fi[i]]++;      //统计第一关键字
        for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1]; //计算前缀和
        for(int i=n;i;i--) sa[cnt[fi[sec[i]]]--]=sec[i],sec[i]=0; //基数排序
        swap(fi,sec);
        fi[sa[1]]=num=1;
        for(int i=2;i<=n;i++)
            fi[sa[i]]=(sec[sa[i]]==sec[sa[i-1]]&&sec[sa[i]+k]==sec[sa[i-1]+k])
                ?num:++num; //离散化
        if(num==n) break;  //已经有序，结束
        m=num;
    }
}
void get_height(){
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
    for(int i=1,k=0;i<=n;i++){
        if(rk[i]==1) continue;
        if(k) k--;
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]) k++;
        height[rk[i]]=k;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>s;
    s=' '+s;
    n=s.size()-1,m=(int)'z';

    get_sa(),get_height();
    for(int i=1;i<=n;i++) cout<<sa[i]<<" \n"[i==n];
    for(int i=1;i<=n;i++) cout<<height[i]<<" \n"[i==n];
    return 0;
}

