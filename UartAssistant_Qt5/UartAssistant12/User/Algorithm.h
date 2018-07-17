#ifndef ALGORITHM_H
#define ALGORITHM_H
//添加uint8_t声明头文件
#include <QObject>


class Algorithm
{
public:
    Algorithm();

//11.2①、添加“求SUM”实现函数
    uint8_t Sum_Calculate(uint8_t * puchMsg, uint16_t usDataLen);
//11.3①、添加“求CRC16”实现函数
    uint16_t Crc16_Calculate(uint8_t * puchMsg, uint16_t usDataLen);



};

#endif // ALGORITHM_H
