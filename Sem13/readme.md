# Семинар №13 по СДА, спец. СИ - Минимално покриващо дърво. Алгоритъм на Прим и Крускал.
  
## Покриващо дърво (Spanning tree) на граф

- Дърво е свързан ацикличен свързан граф.
- Покриващо дърво на граф е дърво, подграф на дадения граф, което свързва всички възли на графа.
- Покриващото дърво на граф *G(V, E)* съдържа *V* на брой върха и *V - 1* ребра.
- Добавянето на ребро към покриващо дърво, ще създаде граф с цикъл.
- Премахването на ребро от покриващо дърво, ще създаде граф с две несвързани компоненти.

По-рядко срещано - В случай на несвързан граф имаме гора от покриващи дървета. (Spanning forest)

## Минимално покриващо дърво (Minimum spanning tree)

- Минимално покриващо дърво на претеглен ненасочен граф е покриващото дърво на графa с минимална сума на ребрата.
- Възможно е да съществува повече от 1 МПД (MST) за даден граф.
  
![Spanning trees of a graph example](https://cdn1.byjus.com/wp-content/uploads/2022/07/minimum-spanning-tree.png)

## Алгоритъм на Прим (Prim's algorithm)

- Намира минимално покриващо дърво на граф.
- Започва от даден връх и добавя реброто с най-малка тежест до съседен връх, който все още не е част от дървото.
- Сложността по време зависи от структурата за извличане на реброто с най-малка тежест.
- При използването на *Binary Heap* сложността е *O(E\*logE)*. (При използване на друг вид heap може да достигне до *O(E\*logV)*)

```c++
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};
// we assume that the graph is represented as an adjacency list
std::vector<Edge> prim(int n, int start, std::unordered_map<int, std::vector<Edge>>& graph) {
    std::priority_queue<Edge> pq;
    std::unordered_set<int> visited;
    pq.push({ start, start, 0 });

    std::vector<Edge> mstEdges;

    while (!pq.empty() && visited.size() < n) { // visited.size() < n to stop earlier if the mst is ready
        auto current = pq.top();
        pq.pop();
        if (visited.count(current.to)) {
            continue;
        }

        visited.insert(current.to);
        mstEdges.push_back(current);
        for (auto& adj : graph[current.to]) {
            if(visited.count(adj.to)) {
                continue;
            }
            pq.push(adj);
        }
    }

    return mstEdges;
}
```

Пример при започване от *връх 6*:

![Prim's algorithm creating a MST of a graph, step by step example.](https://images.tpointtech.com/core/images/prims-algorithm-java.png)

- Имплементацията наподобява тази на алгоритъма на Дийкстра с разликата, че приоритетната опашка държи ребра, а не двойка връх и изминат път от началото до него.
- В случай, че искаме да поддържаме гора от MST трябва да променим имплементацията

## Disjoint-set структура от данни (Union find data structure)
Структура от данни предназначена за работа с несвързани множества. Две множества са несвързани, ако нямат общи елементи ({1, 2} и {3, 4}).
Относно структурата - първоначално инициализира всеки елемент да бъде в свое собствено множество.
Поддържа две основни операции:
- Проверка дали два елемента са в едно множество
- Да обедини множествата на два елемента 

Структурата е удобна за използване в алгоритъм на Крускал. 

```c++
struct DSU
{
    vector<int> parent, size;
    
    int n;

    DSU(int n) : n(n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);

        for(int i = 0; i < n + 1; i++)
        {
            parent[i] = i;
        }
    }

    int find(int node)
    {
        if(node == parent[node]) 
        {
            return node;
        }

        return parent[node] = my_find(parent[node]);
    }

    bool union(int u, int v)
    {
        int p_u = find(u);
        int p_v = find(v);

        if(p_u == p_v)
        {
            return false;
        }

        if(size[p_u] > size[p_v])
        {
            parent[p_v] = p_u;
            size[p_u] += size[p_v];
        }
        else
        {
            parent[p_u] = p_v;
            size[p_v] += size[p_u];
        }
            
        n--;
        
        return true;
    }
    
    int get_comps() const
    {
        return n;
    }

```


[Disjoint-set visualization](https://www.cs.usfca.edu/~galles/visualization/DisjointSets.html)

## Алгоритъм на Крускал (Kruskal's algorithm)

- Намира минимално покриващо дърво на граф.
- Сортира ребрата по минимална тежест, като на всяка стъпка добавя реброто с най-малка тежест, което няма да създаде цикъл в графа.
- Използва структурата *Disjoint set* за оптимална проверка за цикличност.
- Сложност по време *O(E\*logE)* заради сортирането на всички ребра.
- При *dense* граф, когато *Е = V<sup>2</sup>*, *O(ElogE) = O(ElogV<sup>2</sup>) = O(2ElogV) = O(ElogV)*


```c++
struct Edge {
    int from;
    int to;
    int weight;
};

std::vector<Edge> kruskal(int n, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    DSU uf(n);
    std::vector<Edge> mstEdges;
    for (size_t i = 0; i < edges.size(); i++) {
        uf.union(edges[i].from, edges[i].to);
        mstEdges.push_back(edges[i]);
        if (mstEdges.size() == n - 1) {
            break;
        }
    }

    return mstEdges;
}
```


![Kruskal's algorithm creating a MST of a graph, step by step example.](https://www.dotnetlovers.com/Images/KruskalsAlgorithmforMinimumSpanningTreeMST110201931155AM.png)

Крускал поддържа гора от покриващи дървета с леки промени в имплементацията.

## Задачи 🌻

- [Prim's (MST) : Special Subtree](https://www.hackerrank.com/challenges/primsmstsub/problem)
- [Kruskal (MST): Really Special Subtree](https://www.hackerrank.com/challenges/kruskalmstrsub/problem)
- [Min cost to connect all points - Medium](https://leetcode.com/problems/min-cost-to-connect-all-points/description/)
- [Number of provinces - Medium](https://leetcode.com/problems/number-of-provinces/description/)
- [Find critical and pseudo critical edges in MST - Hard](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)
- [Clusters](https://www.hackerrank.com/contests/2024-2025-2/challenges/clusterstask?fbclid=IwY2xjawPVe1pleHRuA2FlbQIxMABicmlkETBMblcyVlpNU0h2ejVUZFVYc3J0YwZhcHBfaWQQMjIyMDM5MTc4ODIwMDg5MgABHkbhKP_fa4WrKsjMjruNXgyadWNcvxE-4_6QOutvBa3U6OCq592EJIAA7SGv_aem_RJHofkVlyqN1wdRUrqLkfw)
