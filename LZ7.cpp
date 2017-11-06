#include <bits/stdc++.h>
using namespace std;
#define fst first
#define sec second
#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define DEB true;
typedef unsigned char byte;
const int MIN_OFFSET=1,MAX_OFFSET=MIN_OFFSET+255;
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

int runlength(int i, int j,const vector<byte> &data){
	int n=data.size();
	int ans=0;
	while(i<n&&j<n&&data[i]==data[j]&&ans<MAX_RUN){
		i++;j++;ans++;
	}
	return ans;
}

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
int totlit=0,nlit=0;
int totrun=0,nrun=0;

vector<byte> rle(const vector<byte> & data){
	vector<byte> comp;
	int n=data.size();
	comp.push_back(MIN_LIT_BYTE);
	comp.push_back(data[0]);
	int lastlit=0;
	for(int i=1;i<n;i++){
		int best=0,bestj=i;
		for(int j=i;j-- && j>=i-MAX_OFFSET;){
			int rl=runlength(i,j,data);
			if(rl>best){
				best=rl;
				bestj=j;
			}
		}
		if(best>=MIN_RUN){
			if(lastlit!=-1){
				nlit++;
				cout<<"LIT "<<comp[lastlit]-MIN_LIT_BYTE+MIN_LIT<<endl;
				totlit+=comp[lastlit]-MIN_LIT_BYTE+MIN_LIT;
			}
			lastlit=-1;
			comp.push_back(best-MIN_RUN);
			comp.push_back(i-bestj-MIN_OFFSET);
			totrun+=best;
			nrun++;
			cout<<i-bestj<<" "<<best<<endl;
			i+=best-1;
		}else{
			if(lastlit!=-1 && comp[lastlit]<255){
				comp[lastlit]++;
				comp.push_back(data[i]);
			}else{
				lastlit=comp.size();
				comp.push_back(MIN_LIT_BYTE);
				comp.push_back(data[i]);
			}
		}
	}
	return comp;
}

int main(){
	DEBUG(MIN_LIT_BYTE);
	ios::sync_with_stdio(false);
	string name;cin>>name;
	vector<byte> comp,data;
	for(char c:ReadAllBytes(name))
		data.push_back(c);
	//data={0,0,0,0,0,0,1,1,1};
	comp=rle(data);
	DEBUG(comp.size());
	ofstream oo{"_"+name};
	for(byte c:comp){
		oo<<c;
		//cout<<(int)c<<" ";
	}
	DEBUG(totrun/nrun);
	DEBUG(totlit/nlit);
	//cout<<endl;
	oo.flush();
	cout<<ext(comp,data)<<endl;
	return 0;
}