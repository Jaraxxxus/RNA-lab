#pragma once
#include <iostream>
#include <string>


//===sizeof int: 4 bytes

//*********************************************


class RNA {
public:

    enum Nucleotide {
        T, C, G, A
    };

    //----------------
private:
    int* arr;
    int cursize;  //выделено байт
    int cur;  //посл нуклеотид  
    int flag;

public:
    class reference {
    private:
        int pos;
        int* pt;

        void setBit(int data);
        int getBit() const;
    public:
        reference(int Npos, int* Npt);
        Nucleotide operator!() const {
            return (Nucleotide)(0b00000011 - getBit());
        }
        reference& operator=(int nucleotide);
        reference& operator=(reference& ref);
        bool operator==(const reference& ref) const;
        operator Nucleotide() const {
            return (Nucleotide)getBit();
        }


    };

    


    reference operator()(int pos) const;

    void setm(int size);
    void setNewm(int newsize);
    int getn(int num);

    reference operator[](int pos);
    const reference& operator[](int pos) const;

    RNA& operator =(RNA& rna);
    RNA& split(int index);
    void delp(int num);
    void changeN(int num, int data);
    bool operator==(const RNA& rna) const;
    bool operator!=(const RNA& rna) const;
    RNA& operator +(RNA& rna1);
    RNA(int size);
    RNA();
    RNA(const RNA&);
    RNA& operator+=(RNA& rna);
    ~RNA();

};
