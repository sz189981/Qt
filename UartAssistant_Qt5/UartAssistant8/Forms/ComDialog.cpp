#include "ComDialog.h"
#include "ui_ComDialog.h"
#include <QMessageBox>

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
    //8.5、添加选择串口号和串口数据读取连接程序(函数ReadMyCom()为串口读函数，)
    //选择串口号
    QString portName = ui->PortNamecomboBox->currentText();
    myCom = new QextSerialPort(portName);

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
        return false;
    }
    return true;
}






















