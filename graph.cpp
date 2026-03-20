#include "graph.h"

Graph::Graph(int n) : n(n), g(n, vector <long long>(n, 0)) {}

int Graph::size() const {
    return n;
}

long long Graph::getWeight(int u, int v) const {
    return g[u][v];
}

void Graph::addToEdge(int u, int v, long long w) {
    if (u == v) return;
    g[u][v] += w;
    g[v][u] += w;
}

Graph Graph::readFromInput() {
    int n;
    cin >> n;

    Graph graph(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph.g[i][j];
        }
    }

    return graph;
}


static pair<long long, pair<int,int>> minCutPhase(Graph& graph, vector <int>& v) {
    int n = v.size();

    vector <long long> w(n, 0);
    vector <bool> used(n, false);

    int prev = -1, sel = -1;

    for (int i = 0; i < n; i++) {
        sel = -1;

        for (int j = 0; j < n; j++) {
            if (!used[j] && (sel == -1 || w[j] > w[sel])) {
                sel = j;
            }
        }

        used[sel] = true;

        if (i == n - 1) {
            return {w[sel], {v[prev], v[sel]}};
        }

        prev = sel;

        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                w[j] += graph.getWeight(v[sel], v[j]);
            }
        }
    }

    return {0, {-1, -1}};
}


static pair<long long, vector <int>> stoerWagnerRecursive(Graph graph, vector<int> v, vector<vector<int>> groups) {

    if (v.size() == 1)
        return {numeric_limits<long long>::max(), {}};

    auto phase = minCutPhase(graph, v);

    long long cut = phase.first;
    int s = phase.second.first;
    int t = phase.second.second;

    int s_i = -1, t_i = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == s) s_i = i;
        if (v[i] == t) t_i = i;
    }

    vector <int> cutSet = groups[t_i];

    for (int u : v) {
        if (u == s || u == t) continue;

        long long w = graph.getWeight(t, u);
        graph.addToEdge(s, u, w);
    }

    groups[s_i].insert(groups[s_i].end(),
                        groups[t_i].begin(),
                        groups[t_i].end());

    vector<int> newV;
    vector<vector<int>> newGroups;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] != t) {
            newV.push_back(v[i]);
            newGroups.push_back(groups[i]);
        }
    }

    auto rec = stoerWagnerRecursive(graph, newV, newGroups);

    if (cut < rec.first)
        return {cut, cutSet};
    else
        return rec;
}


MinCutResult stoerWagnerWithEdges(const Graph& original) {
    int n = original.size();

    vector<int> v(n);
    vector<vector<int>> groups(n);

    for (int i = 0; i < n; i++) {
        v[i] = i;
        groups[i] = {i};
    }

    auto res = stoerWagnerRecursive(original, v, groups);

    long long best = res.first;
    vector<int> setS = res.second;

    vector<bool> inSet(n, false);
    for (int u : setS) inSet[u] = true;

    vector<pair<int,int>> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (inSet[i] != inSet[j] &&
                original.getWeight(i, j) > 0) {
                edges.emplace_back(i, j);
            }
        }
    }

    return {best, edges};
}