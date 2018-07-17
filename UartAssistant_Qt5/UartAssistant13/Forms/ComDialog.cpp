#include "ComDialog.h"
#include "ui_ComDialog.h"
#include <QMessageBox>
#include <QDebug>

#define TIME_OUT 200    //串口读写延时

ComDialog::ComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComDialog)
{
    ui->setupUi(this);
    //7.1(4)同理将“串口配置界面”和“关于界面”设置窗口标题
    //设置窗口标题
    setWindowTitle(tr("串口配置"));

    //8.4(2) 声明初始化串口类
    //初始化串口类
    myCom = NULL;

    //10.2(2)③
    DisplayFlag = true;

    //8.5、选择串口号 之所以没有在控件里面添加串口的值，只不过是为了减少一些程序量。这里进行手动添加，如下：
    ui->PortNamecomboBox->addItem("COM1");
    ui->PortNamecomboBox->addItem("COM2");
    ui->PortNamecomboBox->addItem("COM3");
    ui->PortNamecomboBox->addItem("COM4");
    ui->PortNamecomboBox->addItem("COM5");
    ui->PortNamecomboBox->addItem("COM6");
    ui->PortNamecomboBox->addItem("COM7");
    ui->PortNamecomboBox->addItem("COM8");
    ui->PortNamecomboBox->addItem("COM9");
    ui->PortNamecomboBox->addItem("COM10");
    ui->PortNamecomboBox->addItem("COM11");
    ui->PortNamecomboBox->addItem("COM12");
    ui->PortNamecomboBox->addItem("COM13");
    ui->PortNamecomboBox->addItem("COM14");
    ui->PortNamecomboBox->addItem("COM15");
}

ComDialog::~ComDialog()
{
    delete ui;
}

//8.4(4)实现确认键信号槽函数
void ComDialog::on_ComEnter_clicked()
{
    if(myCom != NULL)
    {
        delete myCom;
    }
    WorkOpen();
    this->close();
}

//8.4(3) 声明定义打开串口函数
bool ComDialog::WorkOpen()
{
    //选择串口号
    QString portName = ui->PortNamecomboBox->currentText();
    myCom = new QextSerialPort(portName);
    //8.5、添加选择串口号和串口数据读取连接程序(函数ReadMyCom()为串口读函数)
    //串口数据读取连接
    connect(myCom, SIGNAL(readyRead()),this, SLOT(ReadMyCom()));

    //8.4(5)设置串口参数
    //在第四章创建串口配置界面时，我们已经将除串口号以外的设置量都已经填充到控件里，
    //波特率和数据位为数值，校验位和停止不是数值。所以波特率和数据位我们只需读取控件
    //  里的值即可实现设置的功能，校验位和停止位需要进行判断处理。如下：
    //设置波特率
    myCom->setBaudRate((BaudRateType)ui->BaudRatecomboBox->currentText().toInt());
    //设置数据位
    myCom->setDataBits((DataBitsType)ui->DataBitscomboBox->currentText().toInt());
    //设置校验位
    switch(ui->ParitycomboBox->currentIndex())
    {
        case 0:
            myCom->setParity(PAR_NONE);
            break;
        case 1:
            myCom->setParity(PAR_ODD);
            break;
        case 2:
            myCom->setParity(PAR_EVEN);
            break;
        default:
            myCom->setParity(PAR_NONE);
            qDebug("set to default:PAR_NONE");
            break;
    }
    //设置停止位
    switch(ui->StopBitscomboBox->currentIndex())
    {
        case 0:
            myCom->setStopBits(STOP_1);
            break;
        case 1:
            myCom->setStopBits(STOP_1_5);
            break;
        case 2:
            myCom->setStopBits(STOP_2);
            break;
        default:
            myCom->setStopBits(STOP_1);
            qDebug("set to default:STOP_1");
            break;
    }
    //设置数据流控制
    myCom->setFlowControl(FLOW_OFF);
    //设置延时
    myCom->setTimeout(TIME_OUT);

    //8.6、添加串口打开成功/失败提示
    //当打开串口失败时，弹框提示，所以我们需要添加消息框控件。
    //以可读写方式打开串口
    bool flag = myCom->open(QIODevice::ReadWrite);
    if(false == flag)
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("串口不存在或已被占用"), QMessageBox::Yes);
        //13.2(7)修改标志值
        m_isConnect = false;

        return false;
    }
    //13.2(8)修改标志值
    m_isConnect = true;
    //9.14、将bool ComDialog::WorkOpen()函数下添加串口成功开启，在主界面显示“串口已开启”。
    main_ui->ComStatuslabel->setText(tr("串口已开启！"));
    //12.1(4)初始化时将发送按钮屏蔽，等串口连接上再开启
    main_ui->SendDataPush->setEnabled(true);
    //12.2(6)撤销自动发送按钮的屏蔽
    main_ui->AutoSend->setEnabled(true);
    return true;
}

//9.2、在ComDialog.c中添加读取串口数据函数
void ComDialog::ReadMyCom()
{
    qDebug()<<">>Func:ReadMyCom";
    //9.3、在实现读取串口数据函数的时刻，我们需要提前考虑一些需要定义/实现的地方。
    //在第二章“主窗口控件添加”的时候，我们可以看到在数据接收窗口有“十六进制复选
    //框”、保存、停止、清除、显示文本框等。
    //但是这些控件都在mainwindow.ui中，我们在ComDialog.c中是无法调用到的，我
    //们需要通过标志位、虚函数等一些方法来实现这些控件的调用等。
    //9.13、读取串口数据函数可以分为三个步骤来实现，即数据读取、数据转化、数据显示，如下：
    //读取串口数据
    QByteArray byte_data = myCom->readAll();
    qDebug()<<"接收到数据："<<byte_data;
    //将读取到的数据进行转化
    QString strDisplay;
    if(m_isHexDisplay)
    {
        QString str = byte_data.toHex().data();
        str = str.toUpper();
        for(int i = 0; i < str.length(); i +=2)
        {
            QString st = str.mid(i,2);
            strDisplay += st;
            strDisplay += " ";
        }
    }
    else
    {
        strDisplay = QString(byte_data);
    }
    //10.2、停止显示
    //⑴停止显示即不显示收到的数据，所以只需在接收函数处添加一个条件即可，
    //当为“停止”时，则不显示数据，为“继续”时即显示数据。
    //(3)串口接收函数添加停止显示标志位判断
    if(true == DisplayFlag)
    {
        //将数据显示在主窗口的文本浏览器中
        //qDebug()<<"接收到数据："<<strDisplay;
        main_ui->ReceiveDatatextBrowser->insertPlainText(strDisplay);
    }
}

//12.1(1)②
void ComDialog::WorkSendMessage()   //发送函数
{
    if(! (myCom->isOpen())) return;

    QString sdata = main_ui->SendHeadLineEdit->displayText();
    sdata = sdata + main_ui->SendDatatextEdit->toPlainText();
    sdata = sdata + main_ui->SendCRCLineEdit->displayText();
    sdata = sdata + main_ui->SendLastLineEdit->displayText();

    if(sdata.isEmpty()) return;
    QByteArray sendBuf = "";
    if(m_isHexSend)
    {
        sendBuf = QByteArray::fromHex(sdata.toLatin1().data());
    }
    else
    {
        //sendBuf = sdata.toAscii();
        sendBuf = sdata.toLatin1();
    }

    qDebug()<<">>发送数据:"<<sendBuf;
    myCom->write(sendBuf);
}

//13.2(2)串口断开函数实现
bool ComDialog::WorkClose()
{
    //13.2(9)断开之前增加判断语句
    if(! m_isConnect)
    {
        this->close();
        return false;
    }
    myCom->close();
    ui->BaudRatecomboBox->setEnabled(true);
    ui->DataBitscomboBox->setEnabled(true);
    ui->ParitycomboBox->setEnabled(true);
    ui->StopBitscomboBox->setEnabled(true);
    ui->PortNamecomboBox->setEnabled(true);

    main_ui->SendDataPush->setEnabled(false);
    main_ui->AutoSend->setEnabled(false);
    main_ui->ComStatuslabel->setText(tr("串口已关闭！"));
    this->close();
}














