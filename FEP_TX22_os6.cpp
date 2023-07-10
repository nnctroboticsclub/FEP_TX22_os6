/**
 *  @file   FEP_TX22_os6.cpp
 *  @brief  送信用FEPライブラリ (os6対応)
 *  @author 安澤瑠 (梅沢晄平追記)
 *  @date   22/10/6 (23/7/10追記)
 */
#include "FEP_TX22_os6.h"

FEP_TX22::FEP_TX22(PinName tx, PinName rx, uint8_t addr_, int baud) :
    BufferedSerial(tx, rx, baud)
{
    for(uint8_t i=4,j=100;i<7;i++,j/=10) header[i] = (addr_%(j*10))/j+48;
}

int8_t FEP_TX22::SendData(char *data, uint8_t datalen)
{
    uint8_t sendindex; // index of 'data'
    for(uint8_t i=7,j=100;i<10;i++,j/=10) header[i] = (datalen%(j*10))/j+48;
    for (sendindex=0; sendindex<10; sendindex++) this->write(header+sendindex,1);// send comand
    for (sendindex=0; sendindex<datalen; sendindex++) this->write(data+sendindex,1);
    this->write("\r\n",2); // <cr><lf>
    return 0;
//    return GetResponse();
//    他にgetc()をループさせている場合に不具合確認
}

int8_t FEP_TX22::GetResponse()
{
    char res[256]; // array of storing response
    for (uint8_t resindex=0; resindex<256; resindex++) {
        this->read(res + resindex, 1);
        if (!strncmp(res+resindex-1, "\r\n", 2)) {
            if (!strncmp(res+resindex-3, "P0", 2))  return 0;
            else if (!strncmp(res+resindex-3, "N0", 2)) return 2;
            else if (!strncmp(res+resindex-3, "N1", 2)) return 3;
            else if (!strncmp(res+resindex-3, "N3", 2)) return 4;
        }
    }
    return -1;
}
