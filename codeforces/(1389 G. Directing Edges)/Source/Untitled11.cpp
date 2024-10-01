//#pragma GCC optimize("O3")
//#pragma GCC optimize("-fcx-limited-range")
//#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
# include <sys/time.h>
# include <sys/resource.h>
#endif

/*** TEMPLATE CODE STARTS HERE ***/

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751
#endif

using namespace std;

typedef vector<string> vs;
typedef long long ll;
typedef complex<double> pnt;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define RA(x) begin(x), end(x)
#define FE(i, x) for (auto i = begin(x); i != end(x); ++i)
#define SZ(x) ((ll) (x).size())

template<class T>
void splitstr(const string &s, vector<T> &out)
{
    istringstream in(s);
    out.clear();
    copy(istream_iterator<T>(in), istream_iterator<T>(), back_inserter(out));
}

static void redirect(int argc, const char **argv)
{
#ifndef ONLINE_JUDGE
    struct rlimit rlim;
    getrlimit(RLIMIT_STACK, &rlim);
    rlim.rlim_cur = 256 * 1024 * 1024;
    setrlimit(RLIMIT_STACK, &rlim);
#ifndef __SANITIZE_ADDRESS__
    getrlimit(RLIMIT_DATA, &rlim);
    rlim.rlim_cur = 256 * 1024 * 1024;
    setrlimit(RLIMIT_DATA, &rlim);
#endif
#endif

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    if (argc > 1)
    {
        static filebuf f;
        f.open(argv[1], ios::in);
        cin.rdbuf(&f);
        if (!cin)
        {
            cerr << "Failed to open '" << argv[1] << "'" << endl;
            exit(1);
        }
    }

    if (argc > 2)
    {
        static filebuf f;
        f.open(argv[2], ios::out | ios::trunc);
        cout.rdbuf(&f);
        if (!cout)
        {
            cerr << "Failed to open '" << argv[2] << "'" << endl;
        }
    }
    cin.exceptions(ios::failbit);
}

/*** TEMPLATE CODE ENDS HERE */

struct edge
{
    int trg;
    ll w;
};

struct gnode
{
    int id = -1;
    ll c = 0;
    vector<edge> edges;
    bool special = false;
};

struct tnode
{
    ll c;
    vector<edge> edges;
    ll ans = 0;
    ll down = 0;
};

static pair<int, bool> dfs(vector<gnode> &nodes, int &pool, int cur, int parent, stack<int> &st, vector<vi> &comps)
{
    gnode &n = nodes[cur];
    n.id = pool++;
    st.push(cur);
    int top = n.id;
    bool special = n.special;
    for (const edge &e : n.edges)
    {
        const gnode &q = nodes[e.trg];
        if (q.id == -1)
        {
            auto s = dfs(nodes, pool, e.trg, cur, st, comps);
            top = min(top, s.first);
            special |= s.second;
        }
        else if (e.trg != parent)
            top = min(top, q.id);
    }
    if (top == n.id && special)
    {
        comps.emplace_back();
        vi &c = comps.back();
        do
        {
            c.push_back(st.top());
            st.pop();
        } while (c.back() != cur);
    }
    return {top, special};
}

static ll dfs2(vector<tnode> &nodes, int cur, int parent)
{
    tnode &n = nodes[cur];
    ll ans = n.c;
    for (const edge &e : n.edges)
        if (e.trg != parent)
        {
            ll sub = dfs2(nodes, e.trg, cur) - e.w;
            if (sub > 0)
                ans += sub;
        }
    n.down = ans;
    return ans;
}

static void solve()
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<gnode> gnodes(N);
    vi v(K);
    for (int i = 0; i < K; i++)
    {
        cin >> v[i];
        v[i]--;
        gnodes[v[i]].special = true;
    }
    for (int i = 0; i < N; i++)
        cin >> gnodes[i].c;
    vll w(M);
    for (int i = 0; i < M; i++)
        cin >> w[i];
    for (int i = 0; i < M; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        gnodes[x].edges.push_back(edge{y, w[i]});
        gnodes[y].edges.push_back(edge{x, w[i]});
    }

    int pool = 0;
    stack<int> st;
    vector<vi> comps;
    dfs(gnodes, pool, v[0], -1, st, comps);
    vi rcomp(N);
    int C = comps.size();
    for (int i = 0; i < C; i++)
        for (int x : comps[i])
            rcomp[x] = i;
    vector<tnode> tnodes(C);
    for (int i = 0; i < N; i++)
    {
        const gnode &n = gnodes[i];
        int comp = rcomp[i];
        tnodes[comp].c += n.c;
        for (const edge &e : n.edges)
            if (rcomp[e.trg] != comp)
            {
                int y = rcomp[e.trg];
                tnodes[comp].edges.push_back(edge{y, e.w});
            }
    }

    tnodes[C - 1].ans = dfs2(tnodes, C - 1, -1);
    for (int i = C - 2; i >= 0; i--)
    {
        tnode &n = tnodes[i];
        n.ans = n.down;
        ll pw = 0;
        int p = -1;
        for (const edge &e : n.edges)
            if (e.trg > i)
            {
                assert(p == -1);
                p = e.trg;
                pw = e.w;
            }
        if (n.down >= pw)
            n.ans = max(n.ans, tnodes[p].ans);
        else
            n.ans = max(n.ans, tnodes[p].ans + n.down - pw);
    }

    for (int i = 0; i < N; i++)
        cout << tnodes[rcomp[i]].ans << ' ';
    cout << '\n';
}

int main(int argc, const char **argv)
{
    redirect(argc, argv);
    solve();

    return 0;
}
