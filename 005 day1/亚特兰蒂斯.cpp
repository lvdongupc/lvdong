//������߼��ṹ��ɨ����
//����Ĵ洢�ṹ����ʽ
/*
����˼·���㷨��
���㼸�Ρ���ɨ�����㷨
���һ������ͼ�Σ������ͨ����ĳһ��������е���ɨ�裬����ͼ�δ���ķ�ʽ����ɨ�����㷨��
*/
//Ч��:ʱ�临�Ӷȣ�O(NlogN) �ռ临�Ӷȣ�O(maxn)
/*�������ݣ�
 ���룺
2
10 10 20 20
15 15 25 25.5
0
�����
Test case #1
Total explored area: 180.00

*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef double db;
const int maxn = 2e5 + 5;   //��Ϊһ�������������������ݷ�ΧҪ��2
db v[maxn];                //������к�ߵ�y����
struct L                    //��Ԫ��
{
    db x;      //���ߵ�x����
    db y1,y2;  //���ߵ�y���꣬y1��С
    int state;  //����߻����ұ�
    bool operator<(L oth)
    {
        return x<oth.x;    //����ʱʹ��x��������
    }
} line[maxn];
struct Node         //�߶���
{
    db l,r;        //�����������
    int cover;      //�����Ǵ���
    db len;  //������ʵ����
} sgt[maxn<<3];     //ע�������С
inline int ls(int k)
{
    return k<<1;    //ȡ�����
}
inline int rs(int k)
{
    return k<<1|1;    //ȡ�Ҷ���
}
inline void pushup(int k)       //����ͨ�߶���������
{
    if(sgt[k].cover) sgt[k].len=sgt[k].r-sgt[k].l;
    else sgt[k].len=sgt[ls(k)].len+sgt[rs(k)].len;
}
void build(int l,int r,int k=1)
{
    sgt[k].l=v[l],sgt[k].r=v[r];//����ͨ�߶���������
    if(r-l<=1) return;          //����ͨ�߶���������
    int m = (l+r)>>1;
    build(l,m,ls(k));
    build(m,r,rs(k));
}
void modify(db x,db y,int z,int k=1)
{
    db l=sgt[k].l,r=sgt[k].r;
    if(x<=l&&y>=r)
    {
        sgt[k].cover+=z;
        pushup(k);              //����ͨ�߶���������
        return;
    }
    if(x<sgt[ls(k)].r) modify(x,y,z,ls(k)); //����ͨ�߶���������
    if(y>sgt[rs(k)].l) modify(x,y,z,rs(k)); //����ͨ�߶���������
    pushup(k);
}
signed main()
{
    int n;
    int cnt=0;
    while(cin>>n)
    {
        if(n==0)
        {
            break;
        }
        cnt++;
        db a,b,c,d;
        for(int i=1; i<=n; i++)     //�������ݣ�λ������ν������Ҫ����
        {
            cin>>a>>b>>c>>d;
            v[i]=b,v[n+i]=d;
            line[i]=(L) {a,b,d,1},line[n+i]=(L)
            {
                c,b,d,-1
            };
        }
        std::sort(v+1,v+1+(n<<1));

        std::sort(line+1,line+1+(n<<1));

        build(1,n<<1);

        db ans=0;

        for(int i=1; i<=n<<1; i++)
        {
            ans += sgt[1].len*(line[i].x-line[i-1].x);  //ע�������˳��
            modify(line[i].y1,line[i].y2,line[i].state);
        }
        printf("Test case #%d\n",cnt);
        printf("Total explored area: %.2lf\n",ans);
        printf("\n");

    }

    return 0;
}

