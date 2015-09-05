#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cmath>
#define time_num 100
#define generation 1000
#define maxn 500
#define alpha 1
#define beta 7
#define rho 0.5
int n,m;
double X[maxn+5],Y[maxn+5];
int a[maxn+5][maxn+5],b[maxn+5][maxn+5];
int flag[maxn+5],p[maxn+5][maxn+5],res[maxn+5];
double tao[maxn+5][maxn+5],yita[maxn+5][maxn+5],q[maxn+5];
int main(){
	srand(time(0));
	freopen("tsp.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int _;
		scanf("%d%lf%lf",&_,&X[i],&Y[i]);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			b[i][j]=(int)sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]));
	int sum_ans=0;
	int Min_ans=-1;
	for(;;/*int time=1;time<=time_num;++time*/){
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				a[i][j]=b[i][j];
		m=100;
		for(int i=1;i<=n;++i) flag[i]=0;
		int st=rand()%n+1;
		int cur=st;
		flag[cur]=1;
		int t0=0;
		for(int i=1;i<n;++i){
			int Min=-1;
			for(int j=1;j<=n;++j)
				if(!flag[j]&&(a[cur][j]<Min||Min==-1)){
					Min=a[cur][j];
				}
			t0+=Min;
			for(int j=1;j<=n;++j)
				if(!flag[j]&&a[cur][j]==Min){
					cur=j;
					break;
				}
			flag[cur]=1;
		}
		t0+=a[cur][st];
		int Ans=100*t0;
		for(int ga=generation;ga;--ga){
			for(int i=1;i<=m;++i) p[i][1]=rand()%n+1;
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j)
					tao[i][j]=m*1.0/t0;
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j)
					yita[i][j]=1.0/a[i][j];
			for(int i=1;i<n;++i){
				for(int j=1;j<=m;++j){
					for(int k=1;k<=n;++k) flag[k]=0;
					for(int k=1;k<=i;++k) flag[p[j][k]]=1;
					double sum_q=0;
					for(int k=1;k<=n;++k){
						if(flag[k]){
							q[k]=0;
							continue;
						}
						q[k]=pow(tao[p[j][i]][k],alpha)*pow(yita[p[j][i]][k],beta);
						sum_q+=q[k];
					}
					for(int k=1;k<=n;++k) q[k]/=sum_q;
					double now_p=(rand()%1001*1000000+rand()%1001*1000+rand()%1001)/1000000000.0;
					if(now_p<0) now_p=0;
					if(now_p>1) now_p=1;
					for(int k=1;k<=n;++k){
						if(flag[k]){
							q[k]=q[k-1];
							continue;
						}
						q[k]+=q[k-1];
						if(now_p<q[k]+1e-10){
							p[j][i+1]=k;
							break;
						}
					}
				}
			}
			for(int j=1;j<=n;++j)
				for(int k=1;k<=n;++k)
					tao[j][k]*=(1-rho);
			for(int j=1;j<=m;++j){
				int len=0;
				for(int k=1;k<=n;++k) len+=a[p[j][k]][p[j][k%n+1]];
				if(len<Ans) Ans=len;
				if(len<Min_ans||Min_ans==-1){
					Min_ans=len;
					for(int k=1;k<=n;++k) res[k]=p[j][k];
					printf("%d\n",Min_ans);
					for(int i=1;i<=n;++i) printf("%d ",res[i]);
					puts("");
				}
				for(int k=1;k<=n;++k) tao[p[j][k]][p[j][k%n+1]]+=1.0/len;
				for(int k=1;k<=n;++k) tao[p[j][k%n+1]][p[j][k]]+=1.0/len;
			}
		}
		sum_ans+=Ans;
	}
	//printf("%d %lf\n",Min_ans,sum_ans*1.0/time_num);
	return 0;
}
