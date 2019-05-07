#include <iostream>
using namespace std;

/* -------------------------------------------------------
 Aldi Indrawan (14117055)
 Habib Abdurrasyid (14117038)
 M. Iqbal Revantama (14117003)

 TBFO
 "Interpreter Sederhana Dengan Bahasa C++"
 ----------------------------------------------------------
*/

int matrix[17][128];

//membangun table transisi state berisi null atau -1
void setmin(int matrix[17][128]){
  for(int i = 0 ; i < 17 ; i++){
    for(int j = 0 ; j < 128 ; j++){
      matrix[i][j] = -1;
    }
  }
}

//membangun table transisi state
//referensi DFA yang telah dibuat dengan 127
//karakter ASCII yang dapat diinput
void setFA(){
  matrix[0][' '] = 0;
  //huruf kecil
  matrix[0]['c'] = 1;
  matrix[1]['e'] = 2;
  matrix[2]['t'] = 3;
  matrix[3]['a'] = 4;
  matrix[4]['k'] = 5;
  matrix[5][' '] = 6;
  matrix[6][' '] = 6;
  matrix[6]['"'] = 7;
  //huruf besar
  matrix[0]['C'] = 1;
  matrix[1]['E'] = 2;
  matrix[2]['T'] = 3;
  matrix[3]['A'] = 4;
  matrix[4]['K'] = 5;
  for(int i = 0 ; i < 128 ; i++){ //state yang menyerap string inputan user
    matrix[7][i] = 7;
  }
  matrix[7]['"'] = 8;
  matrix[8][' '] = 8;
  matrix[8][';'] = 9;
 //huruf kecil
  matrix[0]['s'] = 10;
  matrix[10]['e'] = 11;
  matrix[11]['l'] = 12;
  matrix[12]['e'] = 13;
  matrix[13]['s'] = 14;
  matrix[14]['a'] = 15;
  matrix[15]['i'] = 16;
  matrix[16][' '] = 16;
  matrix[16][';'] = 17;
 //huruf besar
  matrix[0]['S'] = 10;
  matrix[10]['E'] = 11;
  matrix[11]['L'] = 12;
  matrix[12]['E'] = 13;
  matrix[13]['S'] = 14;
  matrix[14]['A'] = 15;
  matrix[15]['I'] = 16;


}

bool isStuck(int state){ //untuk mengecek apakah
  if (state < 0){        //string stuck atau mencapai null / -1
    return true;
  }else{
    return false;
  }
}

bool isFinal(int state){            //untuk mengecek  apakah sudah mencapai
  if(state == 9 || state == 17){    //final state
    return true;
  }else{
    return false;
  }
}

bool isEnd(int state){  // untuk mengecek apakah final state yang dicapai
  if(state == 17){      // adalah final state untuk keluar dari interpreter
    return true;
  }else{
    return false;
  }
}

void simpankata (string *x, char y){ // untuk menyimpan char yang terdeteksi
  *x = *x + y;
}

//menelusuri state dari state 0 hingga string diterima atau tidak
void FA(string x, bool *selesai){ //memanfaatkan tabel perpindahan state yang telah dibuat
  int i = 0;
  int state = 0;            // inisialisasi
  string kata="\0";

  while(i < x.length() && isStuck(state) == false){ // selama char masih ada dan belum terjadi stuck
    state = matrix[state][x[i]];                    // maka penelusuran akan terus berlangsung
    if(state == 7 && x[i] != 34){ simpankata(&kata, x[i]);}
    i++;
  }

  if(isStuck(state) == true || isFinal(state) == false ){ // jika terjadii stuck atau tidak final
    kata = "\0";  //mengembalikan kata ke null            //ketika string ditelusuri,
    cout << "> Ada kesalahan: Kode tidak sesuai dengan peraturan"<< endl;
    return;
  }else{
    if(isEnd(state) == true) *selesai = true;  //jika user menginputkan "# selesai;" merubah variabel
                                               //selesai menjadi true untuk menghentikan perulangan
    else cout << "> " << kata << endl;         //jika bukan, maka mengoutputkan string inputan user
    return;
  }
}


void compilerQ(){ //untuk memulai input user
  string x;
  bool selesai = false; //selama selesai belum dikembalikan sebagai true
  while(selesai ==false){ // maka compiler akan terus berjalan
    cout <<"# ";
    getline(cin,x);
    FA(x, &selesai);
  }
  cout << "> Terima kasih sudah menggunakan compiler ini" << endl;
}

int main(){
  setmin(matrix); //membangun tabel berisi null
  setFA(); // membangun tabel transisi
  compilerQ(); // memulai compiler

  return 0;
}
