// ===== COPIA KMP: todo este bloque =====
vector<int> pref(const string&s){int n=sz(s);vector<int> pi(n);
  forn(i,1,n){int j=pi[i-1];
    while(j&&s[i]!=s[j])j=pi[j-1];
    if(s[i]==s[j])++j; pi[i]=j;}
  return pi;}

vector<int> kmp(const string&t,const string&p){
  if(p.empty())return {}; auto pi=pref(p); vector<int> r; int j=0;
  forn(i,0,sz(t)){while(j&&t[i]!=p[j])j=pi[j-1];
    if(t[i]==p[j])++j;
    if(j==sz(p)){r.pb(i-sz(p)+1);j=pi[j-1];}}
  return r;}
// ===== FIN KMP =====
