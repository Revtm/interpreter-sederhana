#include <iostream>
#include <stack>
#include<stdlib.h>
using namespace std;

/* -------------------------------------------------------
 Aldi Indrawan (14117055)
 Habib Abdurrasyid (14117038)
 M. Iqbal Revantama (14117003)

 TBFO
 "Interpreter Sederhana Dengan Bahasa C++"
 ----------------------------------------------------------
*/

//linkedlist
typedef float infoAngka;
typedef char infoOp;
typedef struct TElementAngka *addrAngka;
typedef struct TElementOperasi *addrOperasi;
typedef struct TElementAngka{
  addrAngka nextA; infoAngka angka;
}ElementAngka;

typedef struct TElementOperasi{
  addrOperasi nextO; infoOp operasi;
}ElementOperasi;

typedef struct{addrAngka firstA= NULL; addrAngka lastA = NULL;}listAngka;
typedef struct{addrOperasi firstO= NULL; addrOperasi lastO = NULL;}listOperasi;

bool isEmptyA(listAngka L){  return (L.firstA == NULL);}
bool isEmptyO(listOperasi L){  return (L.firstO == NULL);}

addrAngka AlloAngk(infoAngka x){
  addrAngka NewAngka;
  NewAngka = (ElementAngka*) malloc(sizeof(ElementAngka));
  NewAngka -> angka = x;NewAngka ->nextA = NULL;

  return NewAngka;
}

addrOperasi AlloOP(infoOp x){
  addrOperasi NewOP;
  NewOP = (ElementOperasi*) malloc(sizeof(ElementOperasi));
  NewOP -> operasi = x; NewOP -> nextO = NULL;

  return NewOP;
}

void DeallocA(addrAngka data){free(data);}
void DeallocO(addrOperasi data){free(data);}

void InsertFirst(listAngka *L, infoAngka x){
  addrAngka New = AlloAngk(x);

  if(New != NULL){
    if(isEmptyA(*L)){
      New -> nextA = NULL;
      (*L).lastA = New;
    }else{
      New -> nextA = (*L).firstA;
    }
    (*L).firstA = New;

  }
}

void InsertLastA(listAngka *L, infoAngka x){
  addrAngka New = AlloAngk(x);
  addrAngka pred = (*L).firstA;

  if(New != NULL){
    if(isEmptyA(*L)){
      New -> nextA = NULL;
      (*L).firstA = New;
      (*L).lastA = New;
    }else{
      while(pred -> nextA != NULL){
        pred = pred -> nextA;
      }
      pred -> nextA = New;
      (*L).lastA = New;
    }

  }
}

void InsertLastO(listOperasi *L, infoOp x){
  addrOperasi New = AlloOP(x);
  addrOperasi pred = (*L).firstO;

  if(New != NULL){
    if(isEmptyO(*L)){
      New -> nextO = NULL;
      (*L).firstO = New;
      (*L).lastO =New;
    }else{
      while(pred -> nextO != NULL){
        pred = pred -> nextO;
      }
      pred -> nextO = New;
      (*L).lastO = New;
    }

  }
}

void deleteFirstA(listAngka *L, infoAngka *x){
  if(!isEmptyA(*L)){
    addrAngka Elmt = (*L).firstA;
    *x=Elmt->angka;
    (*L).firstA = Elmt -> nextA;
    Elmt -> nextA = NULL;
    DeallocA(Elmt);
  }
}

void deleteFirstO(listOperasi *L, infoOp *x){
  if(!isEmptyO(*L)){
    addrOperasi Elmt = (*L).firstO;
    *x=Elmt->operasi;
    (*L).firstO = Elmt -> nextO;
    Elmt -> nextO = NULL;
    DeallocO(Elmt);
  }
}

void deleteLastA(listAngka *L, infoAngka *x){
  if(!isEmptyA(*L)){
    addrAngka Elmt = (*L).firstA;
    if(Elmt -> nextA == NULL){
      deleteFirstA(&(*L), &(*x));
    }else{
      addrAngka pred = NULL;
      while(Elmt -> nextA != NULL){
        pred = Elmt;
        Elmt = Elmt -> nextA;
      }

      addrAngka Elmthapus = pred -> nextA;
      *x = Elmthapus -> angka;

      pred -> nextA = NULL;
      (*L).lastA = pred;
      Elmthapus->nextA = NULL;
      DeallocA(Elmthapus);
    }
  }
}

void deleteLastO(listOperasi *L, infoOp *x){
  if(!isEmptyO(*L)){
    addrOperasi Elmt = (*L).firstO;
    if(Elmt -> nextO == NULL){
      deleteFirstO(&(*L), &(*x));
    }else{
      addrOperasi pred = NULL;
      while(Elmt -> nextO != NULL){
        pred = Elmt;
        Elmt = Elmt -> nextO;
      }

      addrOperasi Elmthapus = pred -> nextO;
      *x = Elmthapus -> operasi;

      pred -> nextO = NULL;
      (*L).lastO = pred;
      Elmthapus->nextO = NULL;
      DeallocO(Elmthapus);
    }
  }
}

//==============================================================================================
//=================== ^ Kumpulan fungsi Linked List  ===========================================
//==============================================================================================


int matrix[17][128];
listAngka list_Arimatika; //deklarasi linkedlist untuk angka dan operasi
listOperasi list_Operasi;

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
 //setiap huruf mewakili nilai ASCII nya
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

  //angka
  matrix[6]['('] = -2;
  matrix[6][')'] = -2;
  matrix[6]['0'] = 18;
  matrix[6]['1'] = 18;
  matrix[6]['2'] = 18;
  matrix[6]['3'] = 18;
  matrix[6]['4'] = 18;
  matrix[6]['5'] = 18;
  matrix[6]['6'] = 18;
  matrix[6]['7'] = 18;
  matrix[6]['8'] = 18;
  matrix[6]['9'] = 18;


  matrix[18]['('] = -2;
  matrix[18][')'] = -2;
  matrix[18]['0'] = 18;
  matrix[18]['1'] = 18;
  matrix[18]['2'] = 18;
  matrix[18]['3'] = 18;
  matrix[18]['4'] = 18;
  matrix[18]['5'] = 18;
  matrix[18]['6'] = 18;
  matrix[18]['7'] = 18;
  matrix[18]['8'] = 18;
  matrix[18]['9'] = 18;

  matrix[18]['*'] = 19;
  matrix[18]['/'] = 19;
  matrix[18]['+'] = 19;
  matrix[18]['-'] = 19;

  matrix[19]['('] = -2;
  matrix[19][')'] = -2;
  matrix[19]['0'] = 20;
  matrix[19]['1'] = 20;
  matrix[19]['2'] = 20;
  matrix[19]['3'] = 20;
  matrix[19]['4'] = 20;
  matrix[19]['5'] = 20;
  matrix[19]['6'] = 20;
  matrix[19]['7'] = 20;
  matrix[19]['8'] = 20;
  matrix[19]['9'] = 20;

  matrix[20]['('] = -2;
  matrix[20][')'] = -2;
  matrix[20]['0'] = 20;
  matrix[20]['1'] = 20;
  matrix[20]['2'] = 20;
  matrix[20]['3'] = 20;
  matrix[20]['4'] = 20;
  matrix[20]['5'] = 20;
  matrix[20]['6'] = 20;
  matrix[20]['7'] = 20;
  matrix[20]['8'] = 20;
  matrix[20]['9'] = 20;

  matrix[20]['*'] = 19;
  matrix[20]['/'] = 19;
  matrix[20]['+'] = 19;
  matrix[20]['-'] = 19;

  matrix[20][';'] = 21;


}

bool isStuck(int state){ //untuk mengecek apakah
  if (state < 0){        //string stuck atau mencapai null / -1
    return true;
  }else{
    return false;
  }
}

bool isFinal(int state){            //untuk mengecek  apakah sudah mencapai
  if(state == 9 || state == 17 || state == 21){    //final state
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

void kosongin_list(){
  infoAngka x;
  infoOp y;
  while(!isEmptyA(list_Arimatika)){
    deleteFirstA(&list_Arimatika, &x);
  }

  while(!isEmptyO(list_Operasi)){
    deleteFirstO(&list_Operasi, &y);
  }
}

void simpankata (string *x, char y){ // untuk menyimpan char yang terdeteksi
  *x = *x + y;
}


void simpanangka (char y){
   float x;
   deleteLastA(&list_Arimatika, &x);
   x = (10*(x)) + (y - '0');
   InsertLastA(&list_Arimatika, x);
}


void simpanOP (char y){
    InsertLastO(&list_Operasi, y);
}

float hasiloperasi(listAngka*AR, listOperasi*OP){
  float E,E2;
  char O;

  if(isEmptyO(*OP)){
    deleteFirstA(&(*AR), &E);
    return E;
  }else{
    if((*OP).firstO -> operasi == '+'){
      deleteFirstA(&(*AR), &E);
      deleteFirstO(&(*OP), &O);

      return (E + hasiloperasi(&(*AR),&(*OP)));
    }else if((*OP).firstO -> operasi == '-'){
      deleteFirstA(&(*AR), &E);
      deleteFirstO(&(*OP), &O);

      return (E - hasiloperasi(&(*AR),&(*OP)));

    }else if((*OP).firstO -> operasi == '*'){
      deleteFirstA(&(*AR), &E);
      deleteFirstA(&(*AR), &E2);

      E=E*E2;

      InsertFirst(&(*AR), E);
      deleteFirstO(&(*OP), &O);

      return (hasiloperasi(&(*AR),&(*OP)));
    }else{
      deleteFirstA(&(*AR), &E);
      deleteFirstA(&(*AR), &E2);

      E=E/E2;

      InsertFirst(&(*AR), E);
      deleteFirstO(&(*OP), &O);

      return (hasiloperasi(&(*AR),&(*OP)));
    }
  }
}




//menelusuri state dari state 0 hingga string diterima atau tidak
void FA(string x, bool *selesai){ //memanfaatkan tabel perpindahan state yang telah dibuat
  int i = 0;
  int state = 0;            // inisialisasi
  string kata="\0";

  InsertLastA(&list_Arimatika, 0);


  while(i < x.length() && isStuck(state) == false){ // selama char masih ada dan belum terjadi stuck
    state = matrix[state][x[i]];                    // maka penelusuran akan terus berlangsung
    if(state == 7 && x[i] != 34){
      simpankata(&kata, x[i]);
    }else if(state == 18 || state == 20){
      simpanangka(x[i]);
    }else if (state == 19){
      if(!isEmptyO(list_Operasi) && list_Operasi.lastO->operasi == '-'){
        char temp_O;
        float temp = (list_Arimatika.lastA) -> angka;
        (list_Arimatika.lastA) -> angka = temp * (-1);
        deleteLastO(&list_Operasi, &temp_O);
        simpanOP('+');
      }

      simpanOP(x[i]);

      InsertLastA(&list_Arimatika, 0);
    }
    i++;
  }

  if(isStuck(state) == true || isFinal(state) == false ){ // jika terjadii stuck atau tidak final
    kata = "\0";  //mengembalikan kata ke null            //ketika string ditelusuri,
    if(state == -1) cout << "> Ada kesalahan: Kode tidak sesuai dengan peraturan"<< endl;
    else{
      kosongin_list();
      cout << "> Ada kesalahan: spesifikasi tubes hanya terdapat operasi '+', '-', '*' dan '/' "<< endl;
    }
    return;
  }else{
    if(isEnd(state) == true) *selesai = true;  //jika user menginputkan "# selesai;" merubah variabel
                                               //selesai menjadi true untuk menghentikan perulangan
    else {
      if(state == 9){
       cout << "> " << kata << endl;
      }
      else{
       float hasil = hasiloperasi(&list_Arimatika, &list_Operasi);
       cout << "> " << hasil << endl;
       kosongin_list();
      }
    }         //jika bukan, maka mengoutputkan string inputan user
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
