/**
 * title: 圆心角
 * category: 计算几何
 * description: /dev/null
 */

#include <cmath>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define EPS 1e-8
#define NMAX 1000

template <typename T>
bool eq(T x, decltype(x) y) {
    return std::abs(x - y) < EPS;  // abs != std::abs
}

struct vec {
    vec() : x(0), y(0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}

    double x, y;

    double len() const {
        return hypot(x, y);
    }

    int region() const {
        if (x >= 0 && y >= 0) return 1;
        if (x <= 0 && y >= 0) return 2;
        if (x <= 0 && y <= 0) return 3;
        return 4;
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }

    vec operator*(double k) const {
        return {x * k, y * k};
    }

    vec &operator/=(double k) {
        x /= k;
        y /= k;
        return *this;
    }
};

double dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

double cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

struct cir {
    vec C;
    double r;
};

#define ACM_BEGIN
double p2arc(double r, const vec &u, const vec &v) {
    if (eq(u.x, v.x) && eq(u.y, v.y))
        return 0;
    double d = dot(u, v);
    double cr = cross(u, v);
    double t = acos(max(-1.0, min(1.0, d / r / r)));  // avoid nan
    return cr > 0 ? t : 2 * M_PI - t;
}
#define ACM_END
