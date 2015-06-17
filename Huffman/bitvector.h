#ifndef BITVECTOR_H
#define BITVECTOR_H
#include <QDebug>
#include <QByteArray>
#include <QBitArray>

class BitVector: public QBitArray
{
    int  m_size;

public:
    BitVector();
    ~BitVector();

    //adiciona um bit no array
    void add(bool value);
    //adiciona um array de bits ao array
    void append(const QBitArray data);
    //remove n elementos no fim do array
    void chop(int n);
    //esvazia o array
    void clear();
    //completa o array pra formar um byte e retorna o lixo
    int complete();
    //transforma um qbytearray em qbitarray
    BitVector toBits(const QByteArray bytes);
    //transforma o array de bits em qbytearray
    QByteArray toBytes() const;
    //transforma um codigo binario em bytes em qbitarray
    QBitArray binCode(const QByteArray code);
    //transforma um inteiro em um array de bits com n bits
    void setValue(int value,int n);
    //retorna o valor inteiro do array
    int value();
    //exibe o array
    void show();
    void showBinary();
    //adiciona um array de bits ao array
    void operator+=(const QBitArray data);
    void operator+=(const BitVector data);
    //retorna o tamanho
    int size() const;


};

#endif // BITVECTOR_H
