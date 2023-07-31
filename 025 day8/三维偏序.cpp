//本题的逻辑结构：CDQ分治
//本题的存储结构： 链式
/*解题思路和算法：
再考虑到本题的点权之间是进行加法求和，树状数组可以表示前缀加和，且拥有比线段树更优的常数，所以我们可以考虑采用 二维动态树状数组，
先模拟一次运算过程（不进行实际运算）加点，所有点加入之后统一建树，再遍历一次进行实际的计算，加入点权，二维区间查询即可。
*/
//效率:时间复杂度：O(nlogn)空间复杂度：O(n)
/*测试数据：
输入：
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1
输出：
3
1
3
0
1
0
1
0
0
1
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1e5+10,M=2e5+10;
struct node{
    int a,b,c,s,res;
    bool operator<(const node &tp)const{
        if(a!=tp.a)return a<tp.a;
        if(b!=tp.b)return b<tp.b;
        return c<tp.c;
    }
    bool operator==(const node &tp)const{
        return a==tp.a&&b==tp.b&&c==tp.c;
    }
}p[N],w[N];
int tr[M],m;
int lowbit(int x){
    return x&-x;
}
void insert(int x,int d){
    for(int i=x;i<=m;i+=lowbit(i))
        tr[i]+=d;
}
int query(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        res+=tr[i];
    return res;
}
void merge(int l,int r){
    if(l>=r)return;
    int mid=l+r>>1;
    merge(l,mid),merge(mid+1,r);
    int i=l,j=mid+1,c=0;
    while(i<=mid&&j<=r){
        if(p[i].b<=p[j].b)
            insert(p[i].c,p[i].s),w[++c]=p[i++];
        else
            p[j].res+=query(p[j].c),w[++c]=p[j++];
    }
    while(i<=mid){
        insert(p[i].c,p[i].s);
        w[++c]=p[i++];
    }
    while(j<=r){
        p[j].res+=query(p[j].c);
        w[++c]=p[j++];
    }
    for(i=l;i<=mid;i++)
        insert(p[i].c,-p[i].s);
    for(i=l,j=1;i<=r;i++,j++)
        p[i]=w[j];
}
int n,k;
int ans[N];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
    sort(p+1,p+1+n);
    p[k=1].s=1;
    for(int i=2;i<=n;i++)
        if(p[i]==p[i-1])
            p[k].s++;
        else
            p[++k]=p[i],p[k].s=1;
    merge(1,k);
    for(int i=1;i<=k;i++)
        ans[p[i].res+p[i].s-1]+=p[i].s;
    for(int i=0;i<n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
