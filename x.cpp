/*
 * standard dsu on tree & Bit problem 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 400
//#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
#define gc getchar_unlocked
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=666013;
const ld pai=acos(-1);
int N = 3e5 , n ;
vi v [300009] ;
vpi que [500009] ;
int a [300009] , dis [300009] , sz [300009] , ans [500009] , Bit [300009] ;
void upd ( int pos , int x ) { 
	for ( int i = pos ; i <= N ; i += i & -i ) Bit [i] += x ;
}
int query ( int pos ) {
	int sum = 0 ;
	for ( int i = pos ; i > 0 ; i -= i & -i ) {
		sum += Bit [i] ;
	}
	return sum ;
}
void fill ( int node , int p ) {
	dis [node] = dis [p] + 1 ;
	sz  [node] = 1 ;
	for ( auto u : v [node] ) {
		if ( u == p ) C ;
		fill ( u , node ) ;
		sz [node] += sz [u] ;
	}
}
void go ( int node , int p , int sgn ) {
	upd ( dis [node] ,  a [node] * sgn ) ;
	for ( auto u : v [node] ) {
                if ( u == p ) C ;
		go ( u , node , sgn ) ;
        }
}
void dfs ( int node , int p ) {
	pi Mx = { -1 , -1 } ;
	for ( auto u : v [node] ) {
		if ( u == p ) C ;
		Mx = max ( Mx , { sz [u] , u } ) ;
	}
	for ( auto u : v [node] ) {
		if ( u == p || Mx.se == u ) C ;
		dfs ( u , node ) ;
		go  ( u , node , -1 ) ;
	}
	if ( Mx.fi != -1 ) dfs ( Mx .se , node ) ;
	upd ( dis [node] ,  a [node] ) ;
	for ( auto u : v [node] ) {
		if ( u == p || Mx.se == u ) C ;
		go ( u , node , 1 ) ;
	}
	for ( auto u : que [node] ) {
		int x = dis [node] + u.fi ;
		ans [u.se] = query ( x ) ; 
	}
}
int main () {
	freopen("arb.in", "r", stdin);
	freopen("arb.out", "w", stdout);
	cin >> n ;
	for ( int i = 0 ; i < n ; i ++ ) scanf("%d",&a[i]) ;
	for ( int i = 1 ; i < n ; i ++ ) {
		int a = i , b ;
		scanf("%d",&b) , b -- ;
		v [a] .pb ( b ) ;
		v [b] .pb ( a ) ;
	}
	int q ;
	cin >> q ;
	for ( int i = 0 ; i < q ; i ++  ) {
		int node , x ;
		scanf("%d%d",&node,&x) ; 
		node -- ;
		que [node] .pb ( { x , i } ) ;
	}
	fill ( 0 , 0 ) ;
	dfs  ( 0 , 0 ) ;
	for ( int i = 0 ; i < q ; i ++ ) printf("%d\n",ans[i]) ; 
}
