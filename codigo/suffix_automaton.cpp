// ===== COPIA SAM: copia TODO este struct =====
struct SAM{
  static const int A=26; static const ll LIM=4000000000000000000LL;
  struct St{int len,link,next[A];
    St(int l=0,int k=-1):len(l),link(k){fill(next,next+A,-1);}};
  vector<St> st; vector<int> occ; vector<ll> ways; int last;
  static int id(char c){if(c>='A'&&c<='Z')c=c-'A'+'a';
    return(c<'a'||c>'z')?-1:c-'a';}
  SAM(const string&s=""){
    st.reserve(2*max(1,sz(s))); st.pb(St()); occ.pb(0); last=0;
    for(char c:s)extend(c);
    calc_occ(); calc_ways();}
  void extend(char ch){int c=id(ch); if(c<0)return; int cur=sz(st);
    st.pb(St(st[last].len+1)); occ.pb(1);
    int p=last;
    while(p!=-1&&st[p].next[c]<0){st[p].next[c]=cur;p=st[p].link;}
    if(p==-1)st[cur].link=0; else{int q=st[p].next[c];
      if(st[p].len+1==st[q].len)st[cur].link=q;
      else{int cl=sz(st); st.pb(st[q]);
        st[cl].len=st[p].len+1; occ.pb(0);
        while(p!=-1&&st[p].next[c]==q){st[p].next[c]=cl;p=st[p].link;}
        st[q].link=st[cur].link=cl;}}
    last=cur;}
  vector<int> order(){int n=sz(st),mx=st[last].len;
    vector<int> cnt(mx+1),o(n); forn(i,0,n)++cnt[st[i].len];
    forn(i,1,mx+1)cnt[i]+=cnt[i-1];
    rforn(i,0,n)o[--cnt[st[i].len]]=i;
    return o;}
  void calc_occ(){auto o=order(); rforn(i,1,sz(o)){
    int v=o[i]; if(st[v].link>=0)occ[st[v].link]+=occ[v];}}
  void calc_ways(){int n=sz(st); ways.assign(n,0); auto o=order();
    rforn(i,0,n){int v=o[i]; ll t=0; forn(c,0,A)if(st[v].next[c]>=0){
      t+=1+ways[st[v].next[c]]; if(t>LIM){t=LIM;break;}} ways[v]=t;}}
  ll distinct(){ll a=0;
    forn(v,1,sz(st))a+=st[v].len-st[st[v].link].len;
    return a;}
  int count(const string&p){if(p.empty())return 0; int v=0;
    for(char ch:p){int c=id(ch); if(c<0||st[v].next[c]<0)return 0;
      v=st[v].next[c];} return occ[v];}
  int lcs(const string&t){int v=0,len=0,best=0;
    for(char ch:t){int c=id(ch);
    if(c<0){v=0;len=0;continue;}
    while(v!=-1&&st[v].next[c]<0)v=st[v].link;
    if(v==-1){v=0;len=0;continue;} len=min(len,st[v].len)+1;
    v=st[v].next[c]; best=max(best,len);} return best;}
  string kth(ll k){if(k<=0||k>ways[0])return ""; string r; int v=0;
    while(1){forn(c,0,A){int u=st[v].next[c]; if(u<0)continue;
      ll cnt=1+ways[u]; if(k>cnt){k-=cnt;continue;}
      r.pb(char('a'+c)); if(--k==0)return r; v=u; break;}}}
  ll min_occ(int k){if(k<=0)return distinct(); ll a=0;
    forn(v,1,sz(st))if(occ[v]>=k)
      a+=st[v].len-st[st[v].link].len;
    return a;}
};
// ===== FIN SAM =====
