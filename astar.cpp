#include <iostream>
#include <queue>
#include <list>
#include <cmath>
using namespace std;
const int INF = 0x7fffffff; //最大整数
const int maxn = 30000; //最大点数
int head[maxn];
int pre[maxn];  //记录前驱节点
int visit[maxn];    //记录是否访问
double pointX[maxn],pointY[maxn];
int ip;
struct node
{
    int v,next;
    int danger;
    int value;
} edge[65000];     //最大边数
struct leaf{
    int id;     //序号
    int g;      //距离 g(n)
    double f,h;
    friend bool operator<(leaf a, leaf b){
        return a.f > b.f;
    }
}leaves[maxn];
void init()
{
    memset(head,-1,sizeof(head));
    ip=0;
}
//计算欧几里得距离
double getDist(int x,int y){
    return sqrt((pointX[x]-pointX[y])*(pointX[x]-pointX[y])+
                (pointY[x]-pointY[y])*(pointY[x]-pointY[y]));
}
void addedge(int u,int v,int value,int danger)
{
    edge[ip].v=v;
    edge[ip].value = value;
    edge[ip].danger = danger;
    edge[ip].next=head[u];
    head[u]=ip++;
}

void Astar(int s,int t){
    for(int i=0;i<maxn;i++){
        leaves[i].id = i;
        leaves[i].g = INF;
        pre[i] = -1;
        visit[i] = 0;
    }
    leaves[s].g = 0;
    priority_queue<leaf> q;
    q.push(leaves[s]);
    while(!q.empty()){
        leaf l = q.top();
        q.pop();
        if(l.id==t){
            break;
        }
        if(visit[l.id]){
            continue;
        }
        visit[l.id] = 1;
        int v;
        int u = l.id;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v = edge[i].v;
            
            if(!visit[v]&&leaves[v].g>leaves[u].g+edge[i].value){
                leaves[v].g = leaves[u].g+edge[i].value;
                leaves[v].h = 0.01*getDist(v, t);
                leaves[v].f = leaves[v].g+leaves[v].h;
                pre[v] = u;
                q.push(leaves[v]);
            }
        }
    }
}
int main(){
    init();
    FILE *fp = NULL;
    char *line;
    char buffer[1024];
    //XY坐标的文件 格式csv，为第四五列
    if ((fp = fopen("/Users/Desktop/ttt.csv", "r")) != NULL)
    {
        fseek(fp, 0L, SEEK_SET);  
        int cnt=0;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续
        {
            cnt++;
            if(cnt==1)
                continue;
            int t = 0;
            int a=0;
            int i;
            for(i=0;i<strlen(buffer);i++){
                if(buffer[i]>='0'&&buffer[i]<='9'){
                    t = t*10+buffer[i]-'0';
                }else{
                    a = t;
                    t = 0;break;
                }
            }
            
            double tem = 0,tem2=0;
            double flag = 1;
            double x,y;
            x = y = 0;
            int num = 0;
            //只要是从字符串中提取数字，第四五位为需要的坐标
            for(;i<strlen(buffer);i++){
                if(buffer[i]>='0'&&buffer[i]<='9'){
                    if(flag){
                        tem = tem*10+buffer[i]-'0';
                    }else{
                        tem2 = tem2*10+buffer[i]-'0';
                    }
                }else if(buffer[i]=='.'){
                    flag = 0;
                }else{
                    while(tem2>=1){
                        tem2/=10;
                    }
                    num++;
                    if(num==4){
                        x = tem+tem2;
                    }else if(num==5){
                        y = tem+tem2;break;
                    }
                    flag = 1;
                    tem = tem2 = 0;
                }
            }
            pointX[a] = x;
            pointY[a] = y;
            
        }
        fclose(fp);
        fp = NULL;
    }
    //点的坐标 第1-3列为起点终点路径长度
    if ((fp = fopen("/Users/Desktop/arcs-1.csv", "r")) != NULL)
    {
        fseek(fp, 0L, SEEK_SET);  //定位到第二行，每个英文字符大小为1
        int cnt=0;
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续
        {
            cnt++;
            if(cnt==1)
                continue;
            
            int num = 0;
            int t = 0;
            int a[4];
            for(int i=0;i<strlen(buffer);i++){
                if(buffer[i]>='0'&&buffer[i]<='9'){
                    t = t*10+buffer[i]-'0';
                }else{
                    a[num++] = t;
                    t = 0;
                    
                }
            }
            addedge(a[0],a[1],a[2],a[3]);
            
            //            printf("\n");
            
        }
        fclose(fp);
        fp = NULL;
    }
    
    printf("请输入起点：");
    int s;
    scanf("%d",&s);
    printf("请输入终点：");
    int t;
    scanf("%d",&t);
    Astar( s, t);
    //    if(l.id==t){
    int path[maxn];
    int tem;
    tem = 0;
    
    int tt = t;
    while(pre[t]!=-1){
        path[tem++] = t;
        t = pre[t];
    }
    cout<<"路径长度为"<<leaves[tt].g<<endl;
    cout<<"路径为:"<<s;
    for(int j=tem-1;j>=0;j--){
        cout<<"->"<<path[j];
    }
    cout<<endl;
    return 0;
    
}
