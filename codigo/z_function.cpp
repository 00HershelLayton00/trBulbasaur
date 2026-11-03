// ===== COPIA Z-FUNCTION: todo este bloque =====
vector<int> zfun(const string&s){int n=sz(s);vector<int> z(n);
  for(int i=1,l=0,r=0;i<n;++i){
    if(i<=r)z[i]=min(r-i+1,z[i-l]);
    while(i+z[i]<n&&s[z[i]]==s[i+z[i]])++z[i];
    if(i+z[i]-1>r){l=i;r=i+z[i]-1;}}
  return z;}

// Busca p en t. Usa un separador que no aparezca en las strings.
vector<int> zsearch(const string&t,const string&p){
  if(p.empty())return {}; string u=p+"#"+t; auto z=zfun(u);
  vector<int> r; forn(i,sz(p)+1,sz(u))if(z[i]==sz(p))r.pb(i-sz(p)-1);
  return r;}
// ===== FIN Z-FUNCTION =====
