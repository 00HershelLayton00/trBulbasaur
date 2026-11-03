// ===== COPIA GRUNDY: todo este bloque =====
int mex(const vector<int>&v){vector<char> s(sz(v)+1);
  for(int x:v)if(x>=0&&x<=sz(v))s[x]=1;
  int g=0; while(g<sz(s)&&s[g])++g; return g;}

struct Grundy{int n; vector<vector<int>> g;
  Grundy(int n):n(n),g(n){}
  void add(int u,int v){g[u].pb(v);}
  vector<int> calc(){vector<int> in(n),o;
    forn(u,0,n)for(int v:g[u])++in[v];
    queue<int> q; forn(i,0,n)if(!in[i])q.push(i);
    while(!q.empty()){int u=q.front();q.pop();o.pb(u);
      for(int v:g[u])if(--in[v]==0)q.push(v);}
    if(sz(o)!=n)return {};
    vector<int> sg(n),mk(n+1); int t=0;
    rforn(i,0,n){int u=o[i]; ++t;
      for(int v:g[u])if(sg[v]<=n)mk[sg[v]]=t;
      int x=0; while(mk[x]==t)++x; sg[u]=x;}
    return sg;}
};

vector<int> subgrundy(int N,const vector<int>&mv){
  vector<int> sg(N+1),mk(N+1);
  forn(x,1,N+1){for(int m:mv)if(m<=x)mk[sg[x-m]]=x;
    int g=0; while(mk[g]==x)++g; sg[x]=g;}
  return sg;}
// ===== FIN GRUNDY =====
