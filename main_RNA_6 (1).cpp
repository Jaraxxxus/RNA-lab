#pragma once
#include <iostream>
#include <string>
#include "rna.h"

using namespace std;

	 
	    void RNA::reference::setBit(int data){
        	int mult=3 << 2*((sizeof(int)*4)-pos-1);
   		    data= data<<2*((sizeof(int)*4)-pos-1);
   	        mult =~mult;
   	        *pt=(*pt& mult) | data;
        }
        int RNA::reference::getBit() const{
            int sdvig = 2*((sizeof(int)*4)-pos-1);
            return ((*pt >> sdvig) & 0b00000011);
        }

        RNA::reference::reference(int Npos, int *Npt){
            pos = Npos;
            pt = Npt;            
        }
        
        RNA::reference& RNA::reference::operator=(int nucleotide){
            int mult = 3 << 2 * ((sizeof(int) * 4) - pos - 1);
            nucleotide = nucleotide << 2 * ((sizeof(int) * 4) - pos - 1);
            mult = ~mult;
            *this->pt = (*this->pt & mult) | nucleotide;
            return *this;
        }
        RNA::reference& RNA::reference::operator=(reference& ref){
            setBit(ref.getBit());
            return *this;
        }
        bool RNA::reference:: operator==(const reference& ref) const{
            return getBit() == ref.getBit();
        }
       // RNA::reference::operator Nucleotide() const{
       //     return (Nucleotide) getBit();
      //  }
        
   

 /*   reference operator()(int pos) const{
       
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i,&this->arr[j]);
      return ref;
     }*/
//----------------


//==========выделяет память массиву   
  void RNA::setm (int size) {
       cur = size + 1;
       if (!size) size=1;
       size = (size/sizeof(int)/8+1)*2;
       arr = new int [size];   //в байтах, а не битах!!

       for (int i = 0; i < size; i++) { 
        arr[i] = 0;         
       }
       cursize= size;
       flag++; 
  }
  
//==============увеличение размера массива 
  void RNA::setNewm(int newsize){
        //int oldsize=size;
		cur = newsize+1;  	
  	    newsize = (newsize/sizeof(int)/8+1)*2;
        int *new_array = new int[newsize];
        for (int i = 0; i < cursize; i++) {
            new_array[i] = arr[i];
        }
        for (int i = cursize; i < newsize; i++) {
            new_array[i] = 0;
        }
        delete arr;
        arr = new_array;
        cursize= newsize;
        flag++;
		  
}
		  

 //===========получить   элемент  из массива 
  int RNA::getn(int num) {

      int nInd = 0, nNucl = 0;
      int rez = 0;


      nNucl = (num % (sizeof(int) * 4)); //элементе в массиве для поиска
      nInd = (num / (sizeof(int) * 4)); //колво нуклидов в последненм элементе массива
      rez = arr[nInd];
      int sdvig = 2 * ((sizeof(int) * 4) - nNucl - 1);
      return ((rez >> sdvig) & 0b00000011);
  }
    
   
//============переопределение квардратных скобок================

//---------------------
 RNA::reference RNA::operator[](int pos) {
    
     if ((pos / (4 * sizeof(int))) + 1 > this->cursize) {
            if (this->arr == nullptr) setm(pos);
			else setNewm(pos);

        }
        if (pos < 0) pos=0;
        this->cur = pos + 1;
        if (pos > this->cur) this->cur = pos+1;
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i,&(this->arr[j]));
        return ref;
    }

const RNA::reference& RNA::operator[](int pos) const {
 
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i, &(this->arr[j]));
        return ref;
  }


//===========переопределение = создает копию RNA=============================

 RNA & RNA::operator =(RNA& rna) {
    arr = new int[rna.cursize];
    cur = rna.cur;
    cursize = rna.cursize;
  
    for (int i = 0; i < cursize; i++) {
       arr[i] = rna.arr[i];
    }
    return *this;
 }

//========удаляет хвост с номера=============
 void RNA::delp (int num ) {
   int m=0; 
   int n =0; 
   int z=0; 
   int m1 = 0; 
   int n1 = 0;
  	m = (num/(sizeof(int)*4));  //элемент массива
   	n = (num%(sizeof(int)*4)); //сдвиг в элементе
   	n1 = (cur%(sizeof(int)*4)); //колво нуклидов в последненм элементе
   	m1 = (cur/(sizeof(int)*4));//последний элемент массива
   	
   if (n1==0) m1= m1-1;  //деление целочисленное, то работа в текущ байте
   	if (n==0) m= m-1;
   	if (m==m1) {
   		z = arr[m];
    	z= z >> 2*(n1-n);
	    arr[m]=z;
	   
    }
   	else{
    	z = arr[m];
    	z= z >> 2*((sizeof(int)*4)-n-1);
 	    arr[m] = z;
   }
   cur = num;
}
//=============== заменяет номер на введенный==================
  
 void RNA::changeN (int num, int data ) {
   	int nInd = 0, nNucl = 0;
    int rez = 0;


    nNucl = (num % (sizeof(int) * 4)); //элементе в массиве для поиска
    nInd = (num / (sizeof(int) * 4)); //колво нуклидов в последненм элементе массива
    rez = arr[nInd];



    int mult = 3 << 2 * ((sizeof(int) * 4) - nNucl - 1);
    data = data << 2 * ((sizeof(int) * 4) - nNucl - 1);

    mult = ~mult;
    arr[nInd] = (arr[nInd] & mult) | data;
   	
    }

 /*RNA& RNA::split(int num) {
     int curw;
     RNA tail(cur - num - 1);
     for (int i = num-1; i < cur; i++) {
         curw = getn(i);
         tail.changeN((i - (num-1)), curw);
     }
     tail.cur = cur - num;
     *this = tail;
     return *this;
     
 }*/


 RNA& RNA::split(int num) {
     delp(num);
     return *this;
 }

//===========
bool RNA::operator==(const RNA &rna) const{
	if (cur != rna.cur) return false; 
        for (int i = 0; i < cursize; i++) {
            if (arr[i] != rna.arr[i]) return false;
        }
        return true;
}
bool RNA::operator!=(const RNA &rna) const{
	if (cur != rna.cur) return true; 
        for (int i = 0; i < cursize; i++) {
            if (arr[i] != rna.arr[i]) return true;
        }
        return false;
}

RNA & RNA::operator +(RNA& rna1) {
    int i;
   
    RNA sum(rna1.cur + cur);
    sum.cur = rna1.cur + cur;
   

    for (i = 0; i <= cur; i++) {  //по числу элементов
        int get = getn(i);
        
        sum.changeN(i, get);
    }
    for (i = 0; i <= rna1.cur; i++) {  //по числу элементов
        int get = rna1.getn(i);
        int cpos = 0;
        cpos = i + cur;
        sum.changeN(cpos, get);

    }

    *this = sum;
    return *this;
}

RNA::RNA (int size) {
	flag=0;
	setm(size);

}


RNA::RNA() {
 
  cursize = 0;
  cur = 0;
  flag = 0;
  arr = nullptr; // setm(1);
}

RNA::RNA(const RNA &rnk) {

    cursize = rnk.cursize;
    cur = rnk.cur;
    flag = 0;
    arr = new int[rnk.cursize];
    if (!arr)
        return;

    for (int i = 0; i < rnk.cursize; i++) {
        arr[i] = rnk.arr[i];

    }      
}


//===================== +=

 RNA& RNA::operator+=(RNA& rna){
     int i;
     int size = ((rna.cur + cur) / (cursize)*16);

        
     if ((rna.cur + cur) > size) {
         size = ((rna.cur + cur) / sizeof(int) / 8 + 1) * 2;
         int *sum = new int[size];
         for (i = 0; i < cursize; i++) {
             sum[i] = arr[i];
         }
         delete this->arr;
         this->arr = sum;

     }
     
          

     for (i = 0; i < rna.cur; i++) {  //по числу элементов
         int get = rna.getn(i);
         int cpos = 0;
         cpos = i + cur;
         this->changeN(cpos, get);

     }
     
 
     cur = rna.cur + cur;
 return *this;
 }


RNA::~RNA(){
	delete arr;	
}

  
   
/*
int main(int argc, char** argv) {
	

	RNA  rna1;


    
   
    for (int i = 0; i < 21; i += 3) {
        rna1[i] = RNA::G;
        rna1[i + 1] = RNA::A;
        rna1[i + 2] = RNA::C;
    }
    RNA rna4(rna1);

    cout << " " << (rna4 == rna1);
    cout << "\n";
   // rna2 = rna1.split(10);
    for (int i = 0; i < 21; i++) {
        // ASSERT_EQ(rna1[i + 100], rna2[i]);
        cout << " " << rna4[i];
        cout << " " << rna1[i];
        cout << "\n";
    }
    cout << "\n";
	
	return 0;
}*/
