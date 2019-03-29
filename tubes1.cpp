#include <iostream>
using namespace std;

void getString(string x){
  cout << "> ";
  int i = 5;
  while(x[i] == ' '){
    i++;
  }

  for(int j = i+1 ; j < x.length()-2 ; j++){
        cout << x[j];
  }

  cout << endl;
}

void cekSelesai(string x,bool *y){
	if(x[0] == 's' || x[0]=='S'){
    	if(x[1] == 'e' || x[1]=='E'){
      		if(x[2] == 'l' || x[2]=='L'){
        		if(x[3] == 'e' || x[3]=='E'){
		          if(x[4] == 's' || x[4]=='S'){
		            if(x[5] == 'a' || x[5]=='A'){
		              if(x[6] == 'i' || x[6]=='I'){
		                if(x[7] == ';'){
						 *y = false;
                }else{
					cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}}else{
						cout << "> kode tidak sesuai dengan peraturan\n";
				}
}

void test(string x,bool *y){
	int i=0;
	int k;
		if(x[i]=='c' ||x[i]=='C' ){
			if(x[i+1]=='e' ||x[i+1]=='E'){
				if(x[i+2]=='t' ||x[i+2]=='T'){
					if(x[i+3]=='a' ||x[i+3]=='A'){
						if(x[i+4]=='k' ||x[i+4]=='K'){
			k=5;
			while(x[k]==' '){
				k++;
			}
			if(x[k]=='"' && x[x.length()-2]=='"' && x[x.length()-1]==';'){
				getString(x);
			}else{
				cout<<"> kode tidak sesuai dengan peraturan\n";
			}		
		}else{
		cekSelesai(x,y);
		}}else{
		cekSelesai(x,y);
		}}else{
		cekSelesai(x,y);
		}}else{
		cekSelesai(x,y);
		}}else{
		cekSelesai(x,y);
		}
	
}


void compilerQ(){
  string x;
  bool y = true;
  while(y == true){
    cout << "# ";
    getline(cin, x);
    test(x, &y);
  }
}

int main() {
	compilerQ();
	cout<<"teimakasih sudah menggunakan compiler ini (HIA)";
}

