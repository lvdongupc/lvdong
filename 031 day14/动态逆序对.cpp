//������߼��ṹ��CDQ����
//����Ĵ洢�ṹ�� �ڽӱ�
/*����˼·���㷨��
��ʼ���������״���������
���߽�������֮��ÿһ��Ҫ��������Ϊ����
����ǰ�������ĸ���+�����������С�ĸ�����
����ʹ�ö�ά���ݽṹʵʱά�����ɣ�ɾ��֮���ٽ�������ӳ�ȥ�����ˡ�
*/
//Ч��:ʱ�临�Ӷȣ�O(nlogn) �ռ临�Ӷȣ�O(n)
/*�������ݣ�
���룺
5 4
1
5
3
4
2
5
1
4
2
�����
5
2
2
1
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read(){
    int x=0;
    char ch=getchar();
    bool st=false;
    while(ch<'0'||ch>'9'){
        ch=getchar();
        if(ch=='-')
            st=true;
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(st)return -x;
    return x;
}
const int N=1e5+10;
struct mode{
    int t,a,res;
}p[N],w[N];
int n,tr[N];
void insert(int x,int d){
    for(int i=x;i<=n;i+=i&-i)
        tr[i]+=d;
}
int query(int x){
    int res=0;
    for(int i=x;i;i^=(i&-i))
        res+=tr[i];
    return res;
}
void merge(int l,int r){
    if(l>=r)return;
    int mid=l+r>>1;
    merge(l,mid),merge(mid+1,r);

    int i=mid,j=r;
    while(i>=l&&j>mid){
        if(p[i].a>p[j].a)
            insert(p[i].t,1),i--;
        else
            p[j].res+=query(p[j].t),j--;
    }
    while(i>=l)
        insert(p[i].t,1),i--;
    while(j>mid)
        p[j].res+=query(p[j].t),j--;
    for(i=l;i<=mid;i++)
        insert(p[i].t,-1);

    i=l,j=mid+1;
    while(i<=mid&&j<=r){
        if(p[i].a>p[j].a)
            insert(p[j].t,1),j++;
        else
            p[i].res+=query(p[i].t),i++;
    }
    while(i<=mid)
        p[i].res+=query(p[i].t),i++;
    while(j<=r)
        insert(p[j].t,1),j++;
    for(i=mid+1;i<=r;i++)
        insert(p[i].t,-1);

    i=l,j=mid+1;
    int k=0;
    while(i<=mid&&j<=r)
        if(p[i].a<p[j].a)
            w[++k]=p[i++];
        else
            w[++k]=p[j++];
    while(i<=mid)
        w[++k]=p[i++];
    while(j<=r)
        w[++k]=p[j++];
    for(int i=l,j=1;i<=r;i++,j++)
        p[i]=w[j];
}
int m;
int pos[N];
ll ans[N];
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        p[i].a=read();
        pos[p[i].a]=i;
    }
    for(int i=1,x,j=n;i<=m;i++){
        x=read();
        p[pos[x]].t=j--;
        pos[x]=-1;
    }
    for(int i=1,j=n-m;i<=n;i++)
        if(~pos[i])
            p[pos[i]].t=j--;
    merge(1,n);
    for(int i=1;i<=n;i++)
        ans[p[i].t]=p[i].res;
    for(int i=1;i<=n;i++)
        ans[i]+=ans[i-1];
    for(int i=1,j=n;i<=m;i++,j--)
        printf("%lld\n",ans[j]);
    return 0;
}
