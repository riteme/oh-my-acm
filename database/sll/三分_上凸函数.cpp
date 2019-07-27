/**
 * title: 三分_上凸函数
 * category: 杂项
 * description: /dev/null
 */
double solve() {
  while(l+eps<r) {
    double mid=(l+r)/2.0;
    double mmid=(mid+r)/2.0;
    if(cal(mid)>cal(mmid))r=mmid;
    else l=mid;
  }
  if(cal(l)<cal(r))return r;
  else return l;
}

