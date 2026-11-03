// ===== COPIA WYTHOFF: todo este bloque =====
ll floor_phi(ll d){ll lo=0,hi=2*d+1;
  while(lo+1<hi){ll m=(lo+hi)/2;
    __int128 a=(__int128)2*m-d;
    bool le=((__int128)2*m<=d)||(a*a<=(__int128)5*d*d);
    if(le)lo=m; else hi=m;}
  return lo;}

bool wythoff(ll a,ll b){if(a>b)swap(a,b); return a!=floor_phi(b-a);}
// ===== FIN WYTHOFF =====
