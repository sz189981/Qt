#ifndef COMBASE_H
#define COMBASE_H

class Combase
{
public:
    Combase();

    //9、在Combase.h中添加十六进制发送和十六进制接收的标志位，如下：
    void setIsHexSend(bool isHexSend)
    {
        m_isHexSend = isHexSend;
    }

    void setIsHexDisplay(bool isHexDisplay)
    {
        m_isHexDisplay = isHexDisplay;
    }

    bool m_isHexSend;       //是否16进制发送
    bool m_isHexDisplay;    //是否16进制显示
};













#endif // COMBASE_H
