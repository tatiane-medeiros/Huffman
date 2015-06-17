#include "bitvector.h"



BitVector::BitVector(){
    m_size = 0;
}

BitVector::~BitVector(){}


int BitVector::size() const{
    return m_size;
}


void BitVector::add(bool value){
    m_size++;
    this->resize(m_size);
    this->setBit(m_size-1,value);
}

void BitVector::append(const QBitArray data){
    this->resize(m_size + data.size());
    for(int i=0; i<data.size(); ++i){
        this->setBit(i+m_size, data.at(i));
    }
    m_size += data.size();

}

void BitVector::chop(int n){
    m_size -= n;
    this->resize(m_size);
}

void BitVector::clear(){
    m_size = 0;
    this->resize(0);
}


int BitVector::complete(){
    int trash = 0;
    if(m_size%8 != 0){
        while(m_size%8 != 0){
            this->add(false);
            ++trash;
        }
    }
    return trash;
}



BitVector BitVector::toBits(const QByteArray bytes){
    QBitArray bits(bytes.count()*8);

    for(int i=0; i<bytes.count(); ++i) {
        for(int b=0; b<8;++b) {
            bits.setBit( i*8+b, bytes.at(i)&(1<<(7-b)) );
        }
    }
    BitVector aux;
    aux +=bits;
    return aux;
}

QByteArray BitVector::toBytes() const{
    QByteArray bytes;
    for(int b=0; b< m_size; b+=8){
        int bit = 128;
        uchar c = 0;
        for(int a = b; a<b+8; ++a){

           if(this->at(a)) c+=bit;
           bit/=2;
        }

        bytes.append(c);
    }
    return bytes;

}

QBitArray BitVector::binCode(const QByteArray code){
    QBitArray bits(code.size());
    for(int i=0;i<code.size(); ++i){
        if(code.at(i) != '0') bits.setBit(i, true);
        else bits.setBit(i, false);
    }

    return bits;
}


void BitVector::setValue(int value, int n){
    this->resize(n);
    m_size = n;
    this->fill(false);
    int val = value;
    for(int i=n-1; i>=0; --i){
       this->setBit(i, val%2);
       val /= 2;
    }

}


int BitVector::value(){
    int value=0;
    int b=1;
    for(int i=m_size -1; i>=0; --i){
       if(this->at(i)) value +=b;
       b*=2;
    }
    return value;
}


void BitVector::show(){

    for(int i=0; i<m_size; ++i){
        qDebug()<<this->at(i);
    }
}

void BitVector::showBinary(){
    QByteArray code;
    for(int i=0; i<m_size; ++i){
        if(this->at(i)) code +='1';
        else code+='0';
    }
    qDebug()<<qPrintable(code);
}

void BitVector::operator+=(const QBitArray data){
    this->append(data);
}

void BitVector::operator+=(const BitVector data){
    this->append(data);
}

