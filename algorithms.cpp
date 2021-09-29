#include <iostream>
#include <string>
#include <math.h>

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <queue>

#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef long long int lli;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pair<int, int>> vii;

//****************** hash_pair() *******************//

//hash function for unordered_map with pair<int, int> is the key
//Using: unordered_map<pair<int, int>, bool, hash_pair> um;
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

//sort function for sorting vector of pair<int, int>
//Using: sort(vect.begin(), vect.end(), sortbysecond);
bool sortbysecond(const pair<int,int> &a, const pair<int,int> &b){
       return (a.second > b.second); // sorting by descending order of second elements
       //return (a.second < b.second); // sorting by ascending order of second elements
}

//priority_queue in increasing order
//Using:
priority_queue<int, vector<int>, greater<int> > gquiz;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//***************** OTHER FORM *******************//

// UnionFind Disjoint Set
// Using: UnionFind bridge(N);
class UnionFind{
public:
    vector<int> p, rank;
    UnionFind(int N){
        rank.assign(N, 0);
        p.assign(N, 0);
        for(int i = 0; i < N; ++i) p[i] = i;
    }
    int findSet(int i){
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }
    bool isSameSet(int i, int j){
        return findSet(i) == findSet(j);
    }
    void unionSet(int i, int j){
        if(!isSameSet(i, j)){
            int x = findSet(i);
            int y = findSet(j);
            if(rank[x] > rank[y]) p[y] = x;
            else{
                p[x] = y;
                if(rank[x] == rank[y]) rank[y]++;
            }
        }
    }
};

// Cantor function
// Using: create a unique number from 2 number, can be use to create keys of map
int cantor(int x, int y){ // create a unique number from 2 number
    return (x + y) * (x + y + 1) /2 + y;
}

int createKey(int x1, int y1, int x2, int y2){ // create a unique number from x1, y1, x2, y2
    return cantor(cantor(x1, y1), cantor(x2, y2));
}

// Find LCM (Least Common Multiple) and GCD (Greatest Common Divisor) of two number
long long gcd(long long int a, long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
// Function to return LCM of two numbers
long long lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

//**************** SEGMENT TREE ****************//

/*Using: 
int main() {
    int arr[] = { 18, 17, 13, 19, 15, 11, 20 }; // the original array
    vi A(arr, arr + 7);
    SegmentTree st(A);
    printf("RMQ(1, 3) = %d\n", st.rmq(1, 3)); // answer = index 2
    printf("RMQ(4, 6) = %d\n", st.rmq(4, 6)); // answer = index 5
}
*/
class SegmentTree { // the segment tree is stored like a heap array
private:
    vi st, A; // recall that vi is: typedef vector<int> vi;
    int n;
    int left (int p) { return p << 1; } // same as binary heap operations
    int right(int p) { return (p << 1) + 1; }
    void build(int p, int L, int R) { // O(n)
        if (L == R) // as L == R, either one is fine
            st[p] = L; // store the index
        else { // recursively compute the values
            build(left(p) , L , (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R );
            int p1 = st[left(p)], p2 = st[right(p)];
            st[p] = (A[p1] <= A[p2]) ? p1 : p2;
        }
    }
    int rmq(int p, int L, int R, int i, int j) { // O(log n)
        if (i > R || j < L) return -1; // current segment outside query range
        if (L >= i && R <= j) return st[p]; // inside query range
        // compute the min position in the left and right part of the interval
        int p1 = rmq(left(p) , L , (L+R) / 2, i, j);
        int p2 = rmq(right(p), (L+R) / 2 + 1, R , i, j);
        if (p1 == -1) return p2; // if we try to access segment outside query
        if (p2 == -1) return p1; // same as above
        return (A[p1] <= A[p2]) ? p1 : p2; // as in build routine
    }
public:
    SegmentTree(const vi &_A) {
        A = _A; n = (int)A.size(); // copy content for local usage
        st.assign(4 * n, 0); // create large enough vector of zeroes
        build(1, 0, n - 1); // recursive build
    }
    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); } // overloading
};

//**************** Sieve of Eratosthenes ****************//

// print all prime numbers not greater than 'n'
// O(n*log(log(n))) 
void SieveOfEratosthenes(int n)
{
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
 
    for (int p = 2; p * p <= n; p++)
    {
        // If prime[p] is not changed,
        // then it is a prime
        if (prime[p] == true)
        {
            // Update all multiples
            // of p greater than or
            // equal to the square of it
            // numbers which are multiple
            // of p and are less than p^2
            // are already been marked.
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
    // Print all prime numbers
    for (int p = 2; p <= n; p++)
        if (prime[p])
            cout << p << " ";
}
 
/* Using:
int main()
{
    int n = 30;
    cout << "Following are the prime numbers smaller than or equal to " << n << endl;
    SieveOfEratosthenes(n);
    return 0;
}
*/