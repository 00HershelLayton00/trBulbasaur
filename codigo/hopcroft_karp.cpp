// ===== COPIA HOPCROFT-KARP: todo este bloque =====
struct HK{
  int n,m; vector<vector<int>> g; vector<int> pu,pv,d;
  HK(int n,int m):n(n),m(m),g(n),pu(n,-1),pv(m,-1),d(n){}
  void add(int u,int v){g[u].pb(v);}
  bool bfs(){queue<int> q;
    forn(u,0,n){if(pu[u]<0){d[u]=0;q.push(u);}else d[u]=-1;}
    bool f=0; while(!q.empty()){int u=q.front();q.pop();
      for(int v:g[u]){int w=pv[v];
        if(w<0)f=1; else if(d[w]<0){d[w]=d[u]+1;q.push(w);}}}
    return f;}
  bool dfs(int u){for(int v:g[u]){int w=pv[v];
      if(w<0||(d[w]==d[u]+1&&dfs(w))){pu[u]=v;pv[v]=u;return 1;}}
    d[u]=-1; return 0;}
  int matching(){int r=0;
    while(bfs())forn(u,0,n)if(pu[u]<0&&dfs(u))++r; return r;}
  vector<int> cover(){vector<char> a(n),b(m); queue<int> q;
    forn(u,0,n)if(pu[u]<0){a[u]=1;q.push(u);}
    while(!q.empty()){int u=q.front();q.pop();
      for(int v:g[u]){if(pu[u]==v||b[v])continue; b[v]=1;
        if(pv[v]>=0&&!a[pv[v]]){a[pv[v]]=1;q.push(pv[v]);}}}
    vector<int> r; forn(u,0,n)if(!a[u])r.pb(u);
    forn(v,0,m)if(b[v])r.pb(n+v); return r;}
  vector<int> indep(){auto c=cover(); vector<char> u(n+m);
    for(int x:c)u[x]=1; vector<int> r;
    forn(i,0,n+m)if(!u[i])r.pb(i); return r;}
};
int path_cover(int n,const vector<pair<int,int>>&e){
  HK h(n,n); for(auto&p:e)h.add(p.fi,p.se); return n-h.matching();}
// ===== FIN HOPCROFT-KARP =====
