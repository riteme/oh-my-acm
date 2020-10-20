/**
 * title: 后缀自动机
 * category: 字符串
 * description: sam.md
 */

#include <cstdio>
#include <cstring>

using namespace std;

using i64 = long long;

#define ACM_BEGIN
#include <numeric>
#include <algorithm>
constexpr int S = 26;
constexpr int NMAX = 2000000;  // 2n - 1
struct SAM {
    int mcnt;
    struct Node {
        int maxlen, fail;  // basic
        int cnt;  // number of occurrences
        int first;  // first right position
        int ch[S];
    } m[NMAX + 10];
    //SAM() { reset(); }
    void reset() {
        memset(this, 0, sizeof(SAM));
        mcnt = 1;  // x = 1 the root
        // ease x = 0 case
        m[0].maxlen = -1;
        fill(m[0].ch, m[0].ch + S, 1);
    }
    int append(int x, int c) {
        int y = ++mcnt;
        m[y].cnt = 1;
        m[y].first = m[y].maxlen = m[x].maxlen + 1;
        while (!m[x].ch[c]) {
            m[x].ch[c] = y;
            x = m[x].fail;
        }
        int p = m[x].ch[c];
        if (m[x].maxlen + 1 != m[p].maxlen) {
            int q = ++mcnt;
            m[q] = m[p];
            m[q].cnt = 0;
            m[q].maxlen = m[x].maxlen + 1;
            m[p].fail = m[y].fail = q;
            while (m[x].ch[c] == p) {
                m[x].ch[c] = q;
                x = m[x].fail;
            }
        } else
            m[y].fail = p;
        return y;
    }
    int seq[NMAX + 10], scnt[NMAX + 10];  // topological sequence
    void tsort() {
        memset(scnt, 0, sizeof(int) * mcnt);
        for (int i = 1; i <= mcnt; i++)
            scnt[m[i].maxlen]++;
        partial_sum(scnt, scnt + mcnt, scnt);
        for (int i = 1; i <= mcnt; i++)
            seq[scnt[m[i].maxlen]--] = i;
    }
    void subsum() {
        //tsort();
        for (int i = mcnt; i > 1; i--) {
            int x = seq[i];
            m[m[x].fail].cnt += m[x].cnt;
        }
    }
    struct State {
        int x, l;
    };
    auto go(State s, int c) -> State {
        while (!m[s.x].ch[c]) {
            s.x = m[s.x].fail;
            s.l = m[s.x].maxlen;
        }
        return {m[s.x].ch[c], s.l + 1};
    }
    Node &operator[](int i) {
        return m[i];
    }
};
#define ACM_END

SAM sam;
char s[NMAX + 10], t[NMAX + 10];

int main() {
    scanf("%s%s", s, t);
    int x = 1;
    sam.reset();
    for (int i = 0; s[i]; i++) {
        x = sam.append(x, s[i] - 'a');
    }
    SAM::State z = {1, 0};
    int ans = 0;
    for (int i = 0; t[i]; i++) {
        z = sam.go(z, t[i] - 'a');
        ans = max(ans, z.l);
    }
    printf("%d\n", ans);
    return 0;
}
