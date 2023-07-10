/**
 *  @file   FEP_TX22_os6.h
 *  @brief  送信用FEPライブラリ (os6対応)
 *  @author 安澤瑠 (梅沢晄平追記)
 *  @date   22/10/6 (23/7/10追記)
 */
#ifndef FEP_TX22_H
#define FEP_TX22_H

#include "mbed.h"

/**
 *  @class class for FEP using FEP-01, FEP-02
 *  @note  mbed-os 6 で使えます。  Compatible with mbed-os 6
 */
class FEP_TX22 : public mbed::BufferedSerial {
public :
    /** constructor
     *  @param tx    FEPと接続するSerialTX pin
     *  @param rx    FEPと接続するSerialRX pin
     *  @param addr_ 通信相手のアドレス
     *  @param baud  通信速度(デフォルト115200)
     */
    FEP_TX22(PinName tx, PinName rx, uint8_t addr_, int baud=115200);

    /** send message
     *  @brief BusInの値とstickの値が入った配列を送信する
     *  @param data   送るデータ配列のアドレス
     *  @param length 送るデータのバイト数
     *
     *  @return 0  通信成功
     *  @return 2  コマンドエラー
     *  @return 3  通信相手からのレスポンス無し
     *  @return 4  通信相手が受け取りに失敗
     *  @return -1 可否不明
     */
    int8_t SendData(char *data, uint8_t datalen);

    /** Get response
     *  @return 0  通信成功
     *  @return 2  コマンドエラー
     *  @return 3  通信相手からのレスポンス無し
     *  @return 4  通信相手が受け取りに失敗
     *  @return -1 可否不明
     *  @note getc()を他のループで回している場合に不具合確認　SerialArduinoと共存不可
     */
    int8_t GetResponse();

private :

    char header[10]={'@','T','B','N'};  //! 送信コマンド
};

#endif
