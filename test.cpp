#include <bits/stdc++.h>
using namespace std;
#define fst first
#define sec second
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<pll> vpll;
const ll INF=LLONG_MAX,MOD=1e9+7;
const int L=17,N=1<<L;

ll n;

int main(){
	ios::sync_with_stdio(false);
	ofstream testo{"test.8xp"};
	for(int i=0;i<10000;i++){
		char c='a';
		c+=(rand()%26);
		testo<<c;
	}
	testo.flush();
	return 0;
}