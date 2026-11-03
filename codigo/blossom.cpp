// ===== COPIA BLOSSOM: todo este bloque =====
struct Blossom{
  int n; vector<vector<int>> g; vector<int> mt,p,b,q;
  vector<char> used,bl;
  Blossom(int n):n(n),g(n),mt(n,-1),p(n),b(n),used(n),bl(n){}
  void add(int u,int v){g[u].pb(v); g[v].pb(u);}
  int lca(int a,int c){vector<char> s(n);
    while(1){a=b[a];s[a]=1;if(mt[a]<0)break;a=p[mt[a]];}
    while(1){c=b[c];if(s[c])return c;c=p[mt[c]];}}
  void mark(int v,int x,int ch){while(b[v]!=x){
      bl[b[v]]=bl[b[mt[v]]]=1; p[v]=ch; ch=mt[v]; v=p[mt[v]];}}
  int find(int root){used.assign(n,0); p.assign(n,-1);
    forn(i,0,n)b[i]=i; q.clear(); q.pb(root); used[root]=1;
    forn(qi,0,sz(q)){int v=q[qi];
      for(int to:g[v]){if(b[v]==b[to]||mt[v]==to)continue;
        if(to==root||(mt[to]>=0&&p[mt[to]]>=0)){
          int x=lca(v,to); bl.assign(n,0); mark(v,x,to); mark(to,x,v);
          forn(i,0,n)if(bl[b[i]]){b[i]=x;
            if(!used[i]){used[i]=1;q.pb(i);}}}
        else if(p[to]<0){p[to]=v; if(mt[to]<0)return to;
          to=mt[to]; used[to]=1; q.pb(to);}}}
    return -1;}
  int matching(){mt.assign(n,-1);
    forn(i,0,n){if(mt[i]>=0)continue; int v=find(i);
      while(v>=0){int x=p[v],y=mt[x]; mt[v]=x; mt[x]=v; v=y;}}
    int r=0; for(int x:mt)if(x>=0)++r; return r/2;}
};
// ===== FIN BLOSSOM =====
