//DynamicTrees by using self-adjusting tree
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
int const maxN = 30010;
class SplayTree {       //So-called LinkCut-Trees
    public:
        SplayTree *father, *left, *right;
        int maxCost, cost, sum;
        void Set() {
            father = left = right = 0;
        }
        void UpDate() {
            maxCost = sum = cost;
            if (left) {
                maxCost >?= left->maxCost;
                sum += left->sum;
            }
            if (right) {
                maxCost >?= right->maxCost;
                sum += right->sum;
            }
        }
        void Zig() {
            if (father->father) {
                if (father->father->left == father) father->father->left = this;
                else if (father->father->right == father) father->father->right = this;
            }
            father->left = right;
            if (right) right->father = father;
            right = father;
            father = right->father;
            right->father = this;
            right->UpDate();
            UpDate();
        }
        void Zag() {
            if (father->father) {
                if (father->father->left == father) father->father->left = this;
                else if (father->father->right == father) father->father->right = this;
            }
            father->right = left;
            if (left) left->father = father;
            left = father;
            father = left->father;
            left->father = this;
            left->UpDate();
            UpDate();
        }
        void Splay() {
            while (father && (father->left == this || father->right == this)) {
                if (!father->father || father->father->left != father && father->father->right != father) {
                    if (father->left == this) Zig();
                    else                      Zag();
                    return;
                }
                if (father->father->left == father) {
                    if (father->left == this) {father->Zig(); Zig();}
                    else  {Zag(); Zig();}
                }
                else if (father->left == this) {Zig();Zag();}
                else {father->Zag();Zag();}
            }
        }
} tree[maxN];
struct dataType {
    int nxt, node;
} data[maxN << 1];
int totCases;
int head[maxN], edge[maxN];
bool v[maxN];
int n, dataL;
void Init();
void Dfs(int now);
void Add(int n1, int n2);
void Work();
int Query(int a, int b, int kind);
void Change(int i, int ti);
int main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    Init();
    Dfs(0);
    Work();
}
void Init()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    dataL = 0;
    for (int i(1); i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        Add(a, b), Add(b, a);
    }
    for (int i(0); i != n; ++i) tree[i].Set();
    for (int i(0); i != n; ++i) {
        scanf("%d", &tree[i].cost);
        tree[i].maxCost = tree[i].sum = tree[i].cost;
    }
}
void Add(int n1, int n2)
{
    data[dataL].node = n2;
    data[dataL].nxt = head[n1];
    head[n1] = dataL;
    dataL++;
}
void Dfs(int now)
{
    v[now] = true;
    for (int tem(head[now]); tem != -1; tem = data[tem].nxt)
        if (!v[data[tem].node]) {
            tree[data[tem].node].father = &tree[now];
            Dfs(data[tem].node);
        }
    v[now] = false;
}
void Work()
{
    int q, a, b;
    char ch[20];
    scanf("%d", &q);
    for (int i(0); i < q; ++i) {
        scanf("%s", ch);
        scanf("%d%d", &a, &b);
        if (ch[0] == 'Q') {
            if (ch[1] == 'M') printf("%d\n", Query(a, b, 0));
            else              printf("%d\n", Query(a, b, 1));
        }
        else Change(a, b);
    }
}

int Query(int a, int b, int kind)
{
    int ret1, ret2;
    //ACCESS(a)
    SplayTree *u = &tree[a - 1], *v = 0;
    while (u) {
        u->Splay();
        u->right = v;
        if (v) v->father = u;
        u->UpDate();
        v = u;
        u = u->father;
    }
    //ACCESS(b)
    u = &tree[b - 1], v = 0;
    while (u) {
        u->Splay();
        if (!u->father) {
            ret1 = ret2 = u->cost;
            if (v) ret1 >?= v->maxCost, ret2 += v->sum;
            if (u->right) ret1 >?= u->right->maxCost, ret2 += u->right->sum;
        }
        u->right = v;
        if (v) v->father = u;
        u->UpDate();
        v = u;
        u = u->father;
    }
    if (!kind) return ret1;
    else    return ret2;
}   

void Change(int i, int ti)
{
    tree[i - 1].cost = ti;
    tree[i - 1].UpDate();
    SplayTree *tem = &tree[i - 1]; 
    while (tem->father && (tem->father->left == tem || tem->father->right == tem)) {
        tem = tem->father;
        tem->UpDate();
    }
}
