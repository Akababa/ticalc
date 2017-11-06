#include <bits/stdc++.h>
using namespace std;
#define fst first
#define sec second
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define DEB true;
typedef unsigned char byte;
const int MIN_OFFSET=1,MAX_OFFSET=MIN_OFFSET+255+25600;
const int MIN_RUN=3,MAX_RUN=200;
const int MIN_LIT=1;
const int MAX_SIZE=65536;
const int MAX_RLE_BYTE=MAX_RUN-MIN_RUN;
const int MIN_LIT_BYTE=MAX_RLE_BYTE+1;

static std::vector<char> ReadAllBytes(string filename){
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

class cmp{
	public:
 	bool operator()(const vector<byte> &a,const vector<byte> &b){
		if(a.size()<b.size()) return true;
		for(int i=0;i<(int)a.size();i++)
			if(a[i]<b[i]) return true;
			else if(a[i]>b[i]) return false;
		return true;
	}
};

bool ext(const vector<byte>& comp,const vector<byte> &data){
	int place=0;
	for(int i=0;i<(int)comp.size();i++){
		int x=comp[i];
		if(x>=MIN_LIT_BYTE){ //literals
			x= x - MIN_LIT_BYTE+MIN_LIT;
			int j=i+x;
			for(;i<j;){
				if(data[place++]!=comp[++i])
					return false;
			}
		}else{
			x+=MIN_RUN;
			int k=place;
			int offs=comp[++i]+MIN_OFFSET;
			for(int j=k-offs;j<k-offs+x;j++){
				if(data[place++]!=data[j])
					return false;
			}
		}
	}
	return true;
}

bool operator==(const auto &a,const auto &b){
	if(a.size()!=b.size())
		return false;
	for(int i=a.size();i--;){
		if(a[i]!=b[i])
			return false;
	}
	return true;
}

vector<int> par;
deque<pair<int,int>> tre;
int codel[256];
int code[256];
pair<int,int> codelen[256];


int depth(int i){
	if(par[i]=-1) return 0;
	else return depth(par[i])+1;
}

int main(){
	for(int i=0;i<256;i++){
		tre.push_back({0,i});
		par.push_back(-1);
	}
	DEBUG(MIN_LIT_BYTE);
	ios::sync_with_stdio(false);
	string name;cin>>name;
	vector<byte> comp,data;
	for(byte c:ReadAllBytes(name)){
		data.push_back(c);
		tre[c].fst++;
	}
	sort(tre.begin(),tre.end());
	while(tre.size()>1){
		auto a=tre.front();tre.pop_front();
		auto b=tre.front();tre.pop_front();
		par[a.sec]=par[b.sec]=par.size();
		tre.push_back({a.fst+b.fst,par.size()});
		sort(tre.begin(),tre.end());
		par.push_back(-1);
	}
	for(int i=0;i<256;i++){
		codel[i]=depth(i);
		codelen[i]={codel[i],i};
	}
	sort(codelen,codelen+256);

	data={0,0,0,0,0,0,1,1,1};

	comp=rle(data);
	DEBUG(comp.size());
	ofstream oo{"_"+name};
	for(byte c:comp){
		oo<<c;
		//cout<<(int)c<<" ";
	}
	//cout<<endl;
	oo.flush();
	cout<<ext(comp,data)<<endl;
	return 0;
}