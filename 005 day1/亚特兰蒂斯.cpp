//本题的逻辑结构：扫描线
//本题的存储结构：链式
/*
解题思路和算法：
计算几何——扫描线算法
面对一个几何图形，计算机通过向某一个方向进行单线扫描，进行图形处理的方式叫做扫描线算法。
*/
//效率:时间复杂度：O(NlogN) 空间复杂度：O(maxn)
/*测试数据：
 输入：
2
10 10 20 20
15 15 25 25.5
0
输出：
Test case #1
Total explored area: 180.00

*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef double db;
const int maxn = 2e5 + 5;   //因为一个矩形有两边所以数据范围要乘2
db v[maxn];                //存放所有横边的y坐标
struct L                    //四元组
{
    db x;      //竖边的x坐标
    db y1,y2;  //竖边的y坐标，y1较小
    int state;  //是左边还是右边
    bool operator<(L oth)
    {
        return x<oth.x;    //排序时使用x坐标排序
    }
} line[maxn];
struct Node         //线段树
{
    db l,r;        //结点区间左右
    int cover;      //被覆盖次数
    db len;  //区间真实长度
} sgt[maxn<<3];     //注意这个大小
inline int ls(int k)
{
    return k<<1;    //取左儿子
}
inline int rs(int k)
{
    return k<<1|1;    //取右儿子
}
inline void pushup(int k)       //与普通线段树的区别
{
    if(sgt[k].cover) sgt[k].len=sgt[k].r-sgt[k].l;
    else sgt[k].len=sgt[ls(k)].len+sgt[rs(k)].len;
}
void build(int l,int r,int k=1)
{
    sgt[k].l=v[l],sgt[k].r=v[r];//与普通线段树的区别
    if(r-l<=1) return;          //与普通线段树的区别
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
        pushup(k);              //与普通线段树的区别
        return;
    }
    if(x<sgt[ls(k)].r) modify(x,y,z,ls(k)); //与普通线段树的区别
    if(y>sgt[rs(k)].l) modify(x,y,z,rs(k)); //与普通线段树的区别
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
        for(int i=1; i<=n; i++)     //读入数据，位置无所谓，待会要排序
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
            ans += sgt[1].len*(line[i].x-line[i-1].x);  //注意两语句顺序
            modify(line[i].y1,line[i].y2,line[i].state);
        }
        printf("Test case #%d\n",cnt);
        printf("Total explored area: %.2lf\n",ans);
        printf("\n");

    }

    return 0;
}

