//本题的逻辑结构：树套树
//本题的存储结构： 链式
/*解题思路和算法：
一共 5 个操作：
操作 1：
查询 vv 在 [l,r][l,r] 中的排名
那么我们将线段树相应的区间比 xx 小的数的个数 cntcnt 统计一下， ans=∑cnt+1ans=∑cnt+1
操作 2：
查询 [l,r][l,r] 排名为 kk 的值，可以做个二分，转化为操作 1
操作 3：
将 pospos 的值改为 vv，相当于 Splay 中的 删除+插入 操作，然后对应地在线段树相应的区间修改即可。
操作 4, 5：
查询前缀后缀，见代码。
难点还是在于细节
*/
//效率:时间复杂度: O((n+m)*log(n)*log(n)) 空间复杂度：O(n*log(n))
/*测试数据：
输入：
9 6
4 2 2 1 9 4 0 1 1
2 1 4 3
3 4 10
2 1 4 3
1 2 5 9
4 3 9 5
5 2 8 5
输出：
2
4
3
4
9
*/
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=5e4+5;
namespace FastIO
{
char c;
bool sign;
template<class T>
inline void read(T &x)
{
    x=0;
    sign=false;
    for(c=getchar();c<'0'||c>'9';c=getchar())
        if(c=='-')
            sign=true;
    for(;c>='0'&&c<='9';c=getchar())
        x=(x<<1)+(x<<3)+(c&15);
    if(sign) x=~x+1;
    return;
}
template<class T>
void print(T x)
{
    if(x<0) putchar('-'),x=~x+1;
    if(x>9) print(x/10);
    putchar(x%10+'0');
    return;
}
}
using FastIO::read;
using FastIO::print;
//================================================
struct Lazytree
{
    vector<int> v;
    Lazytree() { v.clear(); }
    inline void insert(int key) { v.insert(lower_bound(v.begin(),v.end(),key),key); }
    inline void erase(int key) { v.erase(lower_bound(v.begin(),v.end(),key)); }
    inline int between(int x,int y)
    {
        return (int)(upper_bound(v.begin(),v.end(),y)-lower_bound(v.begin(),v.end(),x));
    }
}t[N<<3];

const int INF=2147483647;

void Insert(int now,const int &pos,const int &key,int l,int r)
{
    t[now].insert(pos);
    if(l==r) return;
    int mid=(l+r)>>1;
    if(key<=mid) Insert(now<<1,pos,key,l,mid);
    else Insert(now<<1|1,pos,key,mid+1,r);
    return;
}

void Erase(int now,const int &pos,const int &key,int l,int r)
{
    t[now].erase(pos);
    if(l==r) return;
    int mid=(l+r)>>1;
    if(key<=mid) Erase(now<<1,pos,key,l,mid);
    else Erase(now<<1|1,pos,key,mid+1,r);
}

int Getrank(int now,const int &key,const int &x,const int &y,int l,int r)
{
    if(l==r) return 1;
    int mid=(l+r)>>1;
    if(key<=mid) return Getrank(now<<1,key,x,y,l,mid);
    else return Getrank(now<<1|1,key,x,y,mid+1,r)+t[now<<1].between(x,y);
}

int Getnum(int now,int rank,const int &x,const int &y,int l,int r)
{
    if(l==r) return l;
    int tmp=t[now<<1].between(x,y);
    int mid=(l+r)>>1;
    if(tmp>=rank)
        return Getnum(now<<1,rank,x,y,l,mid);
    else return Getnum(now<<1|1,rank-tmp,x,y,mid+1,r);
}

int Find(int now,const int &x,const int &y,const int &key,int l,int r)
{
    if(l==r) return t[now].between(x,y);
    int mid=(l+r)>>1;
    if(key<=mid) return Find(now<<1,x,y,key,l,mid);
    else return Find(now<<1|1,x,y,key,mid+1,r);
}

struct quiz
{
    int opt;
    int x,y,z;
}q[N];
vector<int> v;
int a[N];
int n,m;
int main()
{
//  freopen("1.in","r",stdin);
    rint i;
    rint tmp;
    read(n); read(m);
    for(i=1;i<=n;i++) {
        read(a[i]);
        v.push_back(a[i]);
    }
    for(i=1;i<=m;i++) {
        read(q[i].opt);
        read(q[i].x); read(q[i].y);
        if(q[i].opt!=3)
            read(q[i].z);
        if(q[i].opt==1||q[i].opt==4||q[i].opt==5)
            v.push_back(q[i].z);
        if(q[i].opt==3)
            v.push_back(q[i].y);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(i=1;i<=n;i++)
        a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
    for(i=1;i<=m;i++) {
        if(q[i].opt==3)
            q[i].y=(int)(lower_bound(v.begin(),v.end(),q[i].y)-v.begin())+1;
        if(q[i].opt==1||q[i].opt==4||q[i].opt==5)
            q[i].z=(int)(lower_bound(v.begin(),v.end(),q[i].z)-v.begin())+1;
    }
    for(i=1;i<=n;i++)
        Insert(1,i,a[i],1,v.size());
    for(i=1;i<=m;i++) {
        if(q[i].opt==1)
            print(Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size()));
        else if(q[i].opt==2)
            print(v[Getnum(1,q[i].z,q[i].x,q[i].y,1,v.size())-1]);
        else if(q[i].opt==3)
            Erase(1,q[i].x,a[q[i].x],1,v.size()),
            Insert(1,q[i].x,q[i].y,1,v.size()),a[q[i].x]=q[i].y;
        else if(q[i].opt==4) {
            tmp=Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size());
            if(tmp==1)
                print(-INF);
            else print(v[Getnum(1,tmp-1,q[i].x,q[i].y,1,v.size())-1]);
        }
        else if(q[i].opt==5) {
            tmp=Getrank(1,q[i].z,q[i].x,q[i].y,1,v.size());
            if(tmp==q[i].y-q[i].x+2)
                print(INF);
            else print(v[Getnum(1,tmp+Find(1,q[i].x,q[i].y,q[i].z,1,v.size()),
                q[i].x,q[i].y,1,v.size())-1]);
        }
        if(q[i].opt!=3)
            putchar('\n');
    }
    return 0;
}
