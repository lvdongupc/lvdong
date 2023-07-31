//������߼��ṹ��CDQ����
//����Ĵ洢�ṹ�� ��ʽ
/*����˼·���㷨��
�ٿ��ǵ�����ĵ�Ȩ֮���ǽ��мӷ���ͣ���״������Ա�ʾǰ׺�Ӻͣ���ӵ�б��߶������ŵĳ������������ǿ��Կ��ǲ��� ��ά��̬��״���飬
��ģ��һ��������̣�������ʵ�����㣩�ӵ㣬���е����֮��ͳһ�������ٱ���һ�ν���ʵ�ʵļ��㣬�����Ȩ����ά�����ѯ���ɡ�
*/
//Ч��:ʱ�临�Ӷȣ�O(nlogn)�ռ临�Ӷȣ�O(n)
/*�������ݣ�
���룺
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
�����
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
