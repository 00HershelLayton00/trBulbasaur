// ===== COPIA COMBINATORIA: todo este bloque =====
ll modpow(ll a,ll e,ll m){ll r=1%m;
  for(;e;e>>=1,a=a*a%m)if(e&1)r=r*a%m; return r;}

struct Comb{
  int n; ll mod; vector<ll> f,inv;
  Comb(int N,ll M=1000000007):n(N),mod(M),f(N+1),inv(N+1){
    f[0]=1; forn(i,1,N+1)f[i]=f[i-1]*i%mod;
    inv[N]=modpow(f[N],mod-2,mod);
    rforn(i,0,N)inv[i]=inv[i+1]*(i+1)%mod;}
  ll C(int a,int b){if(b<0||b>a)return 0;
    return f[a]*inv[b]%mod*inv[a-b]%mod;}
  ll P(int a,int b){if(b<0||b>a)return 0;return f[a]*inv[a-b]%mod;}
  ll H(int a,int b){return C(a+b-1,b);}   // x1+...+xb=a, xi>=0
  ll cat(int a){return C(2*a,a)*modpow(a+1,mod-2,mod)%mod;}
};

vector<ll> stirling2(int n,ll mod=1000000007){
  vector<ll> s(n+1),t(n+1); s[0]=1;
  forn(i,1,n+1){t.assign(n+1,0);
    forn(k,1,i+1)t[k]=(s[k-1]+k*s[k])%mod; s.swap(t);}
  return s;}

ll bell(int n,ll mod=1000000007){auto s=stirling2(n,mod);
  ll r=0; for(ll x:s)r=(r+x)%mod; return r;}

ll der(int n,ll mod=1000000007){ll a=1,b=0;
  forn(i,2,n+1){ll c=(i-1)*(a+b)%mod; a=b; b=c;}
  return n==0?1:b;}
// ===== FIN COMBINATORIA =====
