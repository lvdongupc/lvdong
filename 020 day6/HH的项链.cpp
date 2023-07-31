//������߼��ṹ��Ī��
//����Ĵ洢�ṹ�� ˳��
/*����˼·���㷨������˼·������ʽ��˼��������˫ָ����ƶ��˵㣬
������һ���������Ϣ�����µ�ǰ���䡣
���Ҷ˵��ƶ���ʱ�򣬸���cnt��ֵ���Դ𰸵�ά���������� O(1)��
*/
//Ч��:ʱ�临�Ӷȣ�O(q*log(q)+q*sqrt(n)) �ռ临�Ӷȣ�O(n+q)
/*�������ݣ�
���룺
6
1 2 3 4 3 5
3
1 2
3 5
2 6
�����
2
2
4
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef double db;
const int N=1e6+10;
int n,q1,ans;
int a[N],Ans[N],vis[N];
struct Q
{
    int l,r,id,pos;
} q[N];
int cmp(Q a,Q b)
{
    return a.pos==b.pos ? a.r<b.r : a.pos<b.pos;
}
void add(int x)
{
    if(vis[a[x]]==0) ans++;
    vis[a[x]]++;
}
void removes(int x)
{
    vis[a[x]]--;
    if(vis[a[x]]==0) ans--;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>n;
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];
    }

    int siz=(int)sqrt(n);

    cin>>q1;

    for(int i=1; i<=q1; i++)
    {
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
        q[i].pos=(q[i].l-1)/siz+1;
    }
    sort(q+1,q+1+q1,cmp);
    int l=1,r=0;
    for(int i=1; i<=q1; i++)
    {
        while(l>q[i].l)add(--l);
        while(r<q[i].r)add(++r);
        while(l<q[i].l)removes(l++);
        while(r>q[i].r)removes(r--);
        Ans[q[i].id]=ans;

    }

    for(int i=1; i<=q1; i++)
    {
        cout<<Ans[i]<<"\n";
    }



    return 0;
}

