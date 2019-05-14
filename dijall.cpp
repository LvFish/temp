#include <iostream>
#include <queue>
using namespace std;
const int INF = 0x7fffffff; //最大整数
const int maxn = 30000; //最大点数
int head[maxn];
int pre[maxn];  //记录前驱节点
int visit[maxn];    //记录是否访问
int ip;
struct node
{
    int v,next;
    int value;
} edge[65000];     //最大边数
struct leaf{
    int id;     //序号
    int w;      //距离
    friend bool operator<(leaf a, leaf b){
        return a.w > b.w;
    }
}leaves[maxn];
void init()
{
    memset(head,-1,sizeof(head));
    ip=0;
}
void addedge(int u,int v,int value)
{
    edge[ip].v=v;
    edge[ip].value = value;
    edge[ip].next=head[u];
    head[u]=ip++;
}

void dijkstra(int s){
    for(int i=0;i<maxn;i++){
        leaves[i].id = i;
        leaves[i].w = INF;
        pre[i] = -1;
        visit[i] = 0;
    }
    leaves[s].w = 0;
    priority_queue<leaf> q;
    q.push(leaves[s]);
    while(!q.empty()){
        leaf l = q.top();
        q.pop();
        if(visit[l.id]){
            continue;
        }
        visit[l.id] = 1;
        int v;
        int u = l.id;
        for(int i=head[u];i!=-1;i=edge[i].next){
            v = edge[i].v;
            if(!visit[v]&&leaves[v].w>leaves[u].w+edge[i].value){
                leaves[v].w = leaves[u].w+edge[i].value;
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
            addedge(a[0],a[1],a[2]);
            //            printf("\n");
            
        }
        fclose(fp);
        fp = NULL;
    }
    printf("请输入起点：");
    int s;
    scanf("%d",&s);
    dijkstra(s);
    int tem;
    int path[maxn];
    for(int i=0;i<maxn;i++){
        if(leaves[i].w!=INF&&i!=s){
           tem = 0;
            int tt = i;
            while(pre[tt]!=-1){
                path[tem++] = tt;
                tt = pre[tt];
            }
            path[tem++] = s;
            cout<<"到达点"<<i<<"距离为"<<leaves[i].w<<endl;
            cout<<path[tem-1];
            for(int i=tem-2;i>=0;i--){
                cout<<"->"<<path[i];
            }
            cout<<endl;
        }
        
    }
    return 0;
    
}







