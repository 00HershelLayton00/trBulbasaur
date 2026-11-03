// ===== COPIA MANACHER: todo este bloque =====
struct Manacher{vector<int> d1,d2;
  Manacher(const string&s){int n=sz(s);d1.assign(n,0);d2.assign(n,0);
    for(int i=0,l=0,r=-1;i<n;++i){int k=(i>r)?1:min(d1[l+r-i],r-i+1);
      while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])++k;
      d1[i]=k--; if(i+k>r){l=i-k;r=i+k;}}
    for(int i=0,l=0,r=-1;i<n;++i){
      int k=(i>r)?0:min(d2[l+r-i+1],r-i+1);
      while(i-k-1>=0&&i+k<n&&s[i-k-1]==s[i+k])++k;
      d2[i]=k--; if(i+k>r){l=i-k-1;r=i+k;}}}
  ll count_all(){ll ans=0;
    forn(i,0,sz(d1))ans+=d1[i]+d2[i]; return ans;}
  pair<int,int> longest(){int best=0,st=0;
    forn(i,0,sz(d1)){int len=2*d1[i]-1;
      if(len>best){best=len;st=i-d1[i]+1;}
      len=2*d2[i]; if(len>best){best=len;st=i-d2[i];}}
    return {st,best};}
};
// ===== FIN MANACHER =====
