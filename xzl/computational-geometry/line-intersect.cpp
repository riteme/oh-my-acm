/**
 * title: 直线交点
 * category: 计算几何
 * description: /dev/null
 */
// v: direction; %: cross product
vec isect(const line &a, const line &b) {
  vec z = b.u - a.u;
  double t = (b.v % z) / (b.v % a.v);
  return a.u + a.v * t;
}