#ifndef HELP_H
#define HELP_H

void help(){
    qDebug() << "HELP:\n\n"
        << "       COMANDOS:\n"
        << "$> huffman -c arquivo_origem.x -o arquivo_de_saida.huff\n"
        << "       Comprime o arquivo  e gera o arquivo de saída com o novo nome\n"
        << "$> huffman -c arquivo.x\n"
        << "       Comprime o arquivo gerando o arquivo.huff, mantendo o nome do arquivo original\n"
        << "$> huffman arquivo.huf\n"
        << "       Descomprime o arquivo 'arquivo.huff' na pasta local com o nome original\n"
        << "$> huffman arquivo.huff -d /home/user/destino\n"
        << "       Descomprime o arquivo 'arquivo.huff' na pasta '/home/user/destino' com o nome original\n"
        << "$> huffman --gui\n"
        << "       Inicia a interface\n";
}

void check(int i){
    if(i==0)qDebug() << "  Arquivo descomprimido com sucesso!\n";
    else qDebug() << "  O arquivo não pode ser lido!\n";
}

#endif // HELP_H
