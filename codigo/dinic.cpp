// ===== COPIA DINIC: todo este bloque =====
struct Dinic{
  struct E{int to,rev; ll cap;}; struct R{int u,v; ll cap;};
  int n; vector<vector<E>> g; vector<R> raw; vector<int> lv,it;
  Dinic(int n):n(n),g(n),lv(n),it(n){}
  void add(int u,int v,ll c){raw.pb({u,v,c});
    E a{v,sz(g[v]),c},b{u,sz(g[u]),0}; g[u].pb(a); g[v].pb(b);}
  bool bfs(int s,int t){fill(all(lv),-1); queue<int> q;
    lv[s]=0; q.push(s);
    while(!q.empty()){int v=q.front();q.pop();
      for(auto&e:g[v])if(e.cap>0&&lv[e.to]<0){
        lv[e.to]=lv[v]+1; q.push(e.to);}}
    return lv[t]>=0;}
  ll dfs(int v,int t,ll f){if(v==t)return f;
    for(int&i=it[v];i<sz(g[v]);++i){auto&e=g[v][i];
      if(!e.cap||lv[e.to]!=lv[v]+1)continue;
      ll x=dfs(e.to,t,min(f,e.cap)); if(!x)continue;
      e.cap-=x; g[e.to][e.rev].cap+=x; return x;}
    return 0;}
  ll maxflow(int s,int t){ll f=0;
    while(bfs(s,t)){fill(all(it),0); while(ll x=dfs(s,t,INF))f+=x;}
    return f;}
  vector<char> cut(int s){vector<char> vis(n); queue<int> q;
    vis[s]=1; q.push(s);
    while(!q.empty()){int v=q.front();q.pop();
      for(auto&e:g[v])if(e.cap>0&&!vis[e.to]){
        vis[e.to]=1; q.push(e.to);}}
    return vis;}
  vector<pair<int,int>> cut_edges(int s){auto vis=cut(s);
    vector<pair<int,int>> r;
    for(auto&e:raw)if(vis[e.u]&&!vis[e.v])r.pb({e.u,e.v});
    return r;}
};
// ===== FIN DINIC =====
