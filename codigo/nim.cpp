// ===== COPIA NIM: todo este bloque =====
bool nim_win(const vector<int>&p){int x=0;
  for(int a:p)x^=a; return x;}

bool misere(const vector<int>&p){int x=0; bool one=1;
  for(int a:p){x^=a; if(a>1)one=0;}
  return one?x==0:x;}

// {indice, nuevo tamano} para dejar XOR = 0; {-1,-1} si no hay.
pair<int,int> nim_move(const vector<int>&p){int x=0; for(int a:p)x^=a;
  if(!x)return {-1,-1}; forn(i,0,sz(p)){int t=p[i]^x;
    if(t<p[i])return {i,t};} return {-1,-1};}
// ===== FIN NIM =====
