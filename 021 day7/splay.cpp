//本题的逻辑结构： splay
//本题的存储结构： 链式
/*解题思路和算法：
平衡树都有旋转操作，Splay也不例外。旋转操作和Treap是一样的。
Splay不断通过splay操作，不断地把点旋转到根节点的位置，使得Splay平衡。
Splay插入，删除，修改都是 O(log2⁡n) 的。
*/
//效率:时间复杂度：O(m*log(n)) 空间复杂度：O(N)
/*测试数据：
输入：
6 3
2 4
1 5
3 5
输出：
5 2 1 4 3 6
*/
#include<iostream>
using namespace std;
const int N=100010;
int n,m;
struct node{
    int s[2],p,v;
    int size;
    bool flag;
    void init(int _v,int _p){
        v=_v,p=_p;
        size=1;
    }
}tr[N];
int root,idx;
inline void pushup(int p){
    tr[p].size=tr[tr[p].s[0]].size+tr[tr[p].s[1]].size+1;
}
inline void pushdown(int p){
    if(!tr[p].flag)
        return;
    swap(tr[p].s[0],tr[p].s[1]);
    tr[tr[p].s[0]].flag^=1;
    tr[tr[p].s[1]].flag^=1;
    tr[p].flag=0;
}
inline void rotate(int x){
    int y=tr[x].p;
    int z=tr[y].p;
    bool k=tr[y].s[1]==x;
    tr[z].s[tr[z].s[1]==y]=x,tr[x].p=z;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].p=y;
    tr[x].s[k^1]=y,tr[y].p=x;
    pushup(y),pushup(x);
}
inline void splay(int x,int k){
    while(tr[x].p!=k){
        int y=tr[x].p;
        int z=tr[y].p;
        if(z!=k)
            if((tr[y].s[1]==x)^(tr[z].s[1]==y))
                rotate(x);
            else
                rotate(y);
        rotate(x);
    }
    if(!k)
        root=x;
}
inline void insert(int v){
    int u=root,p=0;
    while(u)
        p=u,u=tr[u].s[v>tr[u].v];
    u=++idx;
    if(p)
        tr[p].s[v>tr[p].v]=u;
    tr[u].init(v,p);
    splay(u,0);
}
inline int get_k(int k){
    int u=root;
    while(1){
        pushdown(u);
        if(tr[tr[u].s[0]].size>=k)
            u=tr[u].s[0];
        else if(tr[tr[u].s[0]].size+1==k)
            return u;
        else
            k-=tr[tr[u].s[0]].size+1,u=tr[u].s[1];
    }
    return -1;
}
void output(int u){
    pushdown(u);
    if(tr[u].s[0])
        output(tr[u].s[0]);
    if(tr[u].v>=1&&tr[u].v<=n)
        printf("%d ",tr[u].v);
    if(tr[u].s[1])
        output(tr[u].s[1]);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;i++)
        insert(i);
    while(m--){
        int l,r;
        scanf("%d%d",&l,&r);
        l=get_k(l),r=get_k(r+2);
        splay(l,0);
        splay(r,l);
        tr[tr[r].s[0]].flag^=1;
    }
    output(root);
    return 0;
}

