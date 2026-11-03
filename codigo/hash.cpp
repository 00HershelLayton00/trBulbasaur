// ===== COPIA HASH DOBLE: todo este bloque =====
struct Hash{
  static const ll M1=1000000007,M2=1000000009,B=911382323;
  int n; vector<ll> p1,p2,h1,h2;
  Hash(const string&s):n(sz(s)),p1(n+1,1),p2(n+1,1),h1(n+1),h2(n+1){
    forn(i,0,n){ll c=(unsigned char)s[i]+1;
      p1[i+1]=p1[i]*B%M1; p2[i+1]=p2[i]*B%M2;
      h1[i+1]=(h1[i]*B+c)%M1; h2[i+1]=(h2[i]*B+c)%M2;}}
  pair<ll,ll> get(int l,int r){
    ll a=(h1[r]-h1[l]*p1[r-l])%M1,b=(h2[r]-h2[l]*p2[r-l])%M2;
    if(a<0)a+=M1; if(b<0)b+=M2; return {a,b};}
  bool equal(int l1,int r1,int l2,int r2){
    return r1-l1==r2-l2&&get(l1,r1)==get(l2,r2);}
  int lcp(int i,int j){int lo=0,hi=min(n-i,n-j);
    while(lo<hi){int m=(lo+hi+1)/2;
      if(get(i,i+m)==get(j,j+m))lo=m;else hi=m-1;} return lo;}
};
// ===== FIN HASH DOBLE =====
