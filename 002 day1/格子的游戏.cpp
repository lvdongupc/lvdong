//������߼��ṹ��ͼ��(���鼯)
//����Ĵ洢�ṹ��˳��
/*
����˼·���㷨:
�۲����⣺��������Ҫ�жϻ����ߺ���û��Χ�ɻ�
�������Χ��һ��������ô��󻭵��ߵ������˵��Ȼ�Ѿ���һ����ͨ����
�ж��Ƿ���һ����ͨ��
ʹ�ò��鼯�㷨
���鼯��һ�����͵����ݽṹ�����ڴ���һЩ���ཻ���ϣ�disjointsetsdisjointsets���ĺϲ�����ѯ����
*/
//Ч��:ʱ�临�Ӷ�:O(n^2+m) �ռ临�Ӷ�:O(N)
/*�������ݣ�
���룺
3 5
1 1 D
1 1 R
1 2 D
2 1 R
2 2 D

�����
4
*/
#include<bits/stdc++.h>
using namespace std;
const int N=40010;
int n,m;
int p[N];
int get(int x, int y)
{
    return x*n+y;
}
int find(int x)
{
    if(p[x]!=x)return p[x]=find(p[x]);
    else
    {
        return x;
    }
}
int main()
{
    cin>> n>>m;

    for (int i=0; i<n*n;i++) p[i]=i;

   /*
   �㷨�������£�
   ��������˵��Ѿ���ͬһ������(find����)����ô�ɻ�
   ��������˵㲻��ͬһ��������(find����)����ô������������ͨ���ϲ���������(merge����)
  */
    int res=0;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        char d;
        cin>>x>>y>>d;
        x--, y--;
        int a=get(x, y);
        int b;
        if (d=='D') b=get(x+1,y);
        else b=get(x,y+1);
        int pa=find(a), pb=find(b);
        if (pa==pb)
        {
            res=i;
            break;

        }
        p[pa]=pb;
    }

    if (!res)
    {
        cout<<"draw"<<"\n";
    }
    else cout<<res<<"\n";

    return 0;
}

