//������߼��ṹ��RMQ
//����Ĵ洢�ṹ��˳��
/*����˼·���㷨
(RMQ�㷨,Ҳ��Ϊst��) O(nlogn)
�����������Ƚϴ󣬲�ѯҲ�Ƚ϶࣬Ѱ����ƽ�����Ӷ�һ���ᳬʱ���������RMQ�㷨��
ʵ���Ͼ����ö�̬�滮Ԥ�ȴ������ݣ���ѯʱʱ�临�Ӷ��ǳ�������
*/
//Ч��:ʱ�临�Ӷ�:O(NlogN)+O(MlogN) �ռ临�Ӷ� O(NlogN)
/*��������
���룺
6
34 1 8 123 3 2
4
1 2
1 5
3 4
2 3
�����
34
123
123
8
*/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=2e5+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
int Max[MAXN][19];
int Query(int l,int r)
{
    int k=log2(r-l+1);
    return max(Max[l][k],Max[r-(1<<k)+1][k]);//�Ѳ����������ֱ�ȡ��ֵ
}
int main()
{
    int N=read();
    for(int i=1;i<=N;i++) Max[i][0]=read();
    for(int j=1;j<=log2(N);j++)
        for(int i=1;i+(1<<j)-1<=N;i++)//ע������Ҫ���Ʊ߽�
            Max[i][j]=max(Max[i][j-1],Max[i+(1<<(j-1))][j-1]);//����������߽�Ļ�����úÿ���ͼ

   int M=read();
    for(int i=1;i<=M;i++)
    {
        int l=read(),r=read();
        printf("%d\n",Query(l,r));
    }
    return 0;
}
