//������߼��ṹ����״����
//����Ĵ洢�ṹ��˳��
/*
����˼·���㷨:
��״����ֻ֧�ֵ����ѯ,������������Ҫ�ʴ��������,��ô�͵���һ���������.
�������ǿ��Կ�һ������B,Ȼ�����ÿ��C����,����ֱ������ǰ׺�͵�˼��.
��b[l]+=d;
��b[r+1]-=d;
Ȼ�����Ǿͳɹ���ɳɾ�,��ά�����еľ���ֵ,ת��Ϊά��ָ����ۼ�Ӱ��,
ÿ�β�����Ӱ��,��l����ʼ,Ȼ����r+1������.Ȼ����õ����޸Ŀ���ά�������޸ġ�
*/
//Ч��:ʱ�临�Ӷȣ�O(n+mlogn) �ռ临�Ӷ� O(max(n,m))
/*�������ݣ�
���룺
10 5
1 2 3 4 5 6 7 8 9 10
Q 4
Q 1
Q 2
C 1 6 3
Q 2
�����
4
1
2
5
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int input[500010];
int tree[500100];
int lowbit(int x)
{
    return x & -x;
}
void add(int x,int k)
{
    while(x<=n)
    {
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int search(int x)
{
    int ans=0;
    while(x!=0)
    {
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
signed main()
{
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        cin>>input[i];
    for(int i=1; i<=m; i++)
    {
        char a;
         cin>>a;
        if(a=='C')
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,z);
            add(y+1,-z);
        }
        if(a=='Q')
        {
            int x;
            cin>>x;
           cout<<input[x]+search(x)<<"\n";
        }
    }
    return 0;
}

