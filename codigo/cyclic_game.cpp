// ===== COPIA JUEGOS CON CICLOS: todo este bloque =====
// state: 1 = gana, -1 = pierde, 0 = empate.
vector<int> solve_game(int n,const vector<vector<int>>&g){
  vector<int> out(n),st(n); vector<vector<int>> rev(n);
  forn(u,0,n)for(int v:g[u]){++out[u]; rev[v].pb(u);}
  queue<int> q; forn(v,0,n)if(!out[v]){st[v]=-1;q.push(v);}
  while(!q.empty()){int v=q.front();q.pop();
    for(int u:rev[v]){if(st[u])continue;
      if(st[v]==-1){st[u]=1;q.push(u);}
      else if(--out[u]==0){st[u]=-1;q.push(u);}}}
  return st;}
// ===== FIN JUEGOS CON CICLOS =====
