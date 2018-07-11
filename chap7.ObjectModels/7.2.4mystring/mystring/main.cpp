/*
7.2.4 QString
2.编辑操作
3.查询操作
4.转换操作
*/

#include <QCoreApplication>
#include <QDebug>
#include <QStringList>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //add by sunzhong 20180710 for QString
    qDebug()<<QObject::tr("以下是编辑字符串操作：")<<endl;
    QString str = "hello";
    qDebug()<<QObject::tr("字符串大小：")<<str.size();    //大小为5
    qDebug()<<QObject::tr("str为：")<<str;

    str[0] = QChar('H');                            //将第一个字符换为'H'
    qDebug()<<QObject::tr("第一个字符：")<<str[0];    //结果为'H'

    str.append(" Qt");           //向字符串后添加"Qt"
    str.replace(1,4,"i");       //将第一个字符开始的后面4个字符换为字符串"i"
    str.insert(2," my");         //在第二个字符后面插入"my"
    qDebug()<<QObject::tr("str为：")<<str;    //结果为Hi my Qt
    /*******************************************/
    str = " hi\r\n Qt! \n ";
    qDebug()<<QObject::tr("str为：")<<str;

    QString str1 = str.trimmed();   //除去字符串两端的空白字符
    qDebug()<<QObject::tr("str1为：")<<str1;

    QString str2 = str.simplified();    //除去字符串两端和中断多于空白字符
    qDebug()<<QObject::tr("str2为：")<<str2;

    /*******************************************/
    str = "hi.my..Qt";
    //从字符串中有"."的地方将其分为多个字符串
    //QString::SkipEmptyParts表示跳过空的条目
    QStringList list = str.split(".", QString::SkipEmptyParts);
    qDebug()<<QObject::tr("str拆分后为：")<<list;    //结果为hi,my,Qt

    str = list.join(" ");   //将各个字符串组合为一个字符串，中间用" "隔开
    qDebug()<<QObject::tr("list组合后为：")<<str;    //结果为hi my Qt

    /******************************************/
    qDebug()<<QString().isNull();       //结果为true
    qDebug()<<QString().isEmpty();      //结果为true
    qDebug()<<QString("").isNull();     //false
    qDebug()<<QString("").isEmpty();    //true

    /******************************************/
    //查询操作
    qDebug()<<endl<<QObject::tr("以下是在字符串中进行查询的操作：")<<endl;
    str = "yafeilinux";
    qDebug()<<QObject::tr("字符串为：")<<str;

    //执行下面一行代码后，结果为linux
    qDebug()<<QObject::tr("包含右侧5个字符的字符串：")<<str.right(5);

    //执行下面一行代码后，结果为fei
    qDebug()<<QObject::tr("包含第二个字符以后3个字符的子字符串：")<<str.mid(2,3);

    //查找fel位置，结果为2
    qDebug()<<QObject::tr("'fei'的位置：")<<str.indexOf("fei");

    //查找第0个字符内容，结果为y
    qDebug()<<QObject::tr("str第0个字符为：")<<str.at(0);

    //查找字符i的个数，结果为2
    qDebug()<<QObject::tr("str中字符'i'的个数为：")<<str.count('i');

    //str是否以ya开始
    qDebug()<<QObject::tr("str是否以ya开始？")<<str.startsWith("ya");

    //str是否以linux结尾
    qDebug()<<QObject::tr("str是否以linux结尾？")<<str.endsWith("linux");

    //str是否包含lin字符串
    qDebug()<<QObject::tr("str是否包含lin字符串?")<<str.contains("lin");

    //比较两个字符串
    QString temp = "hello";
    if(temp > str)
        qDebug()<<temp; //两个字符串进行比较，结果为yafeillinux
    else
        qDebug()<<str;

    /******************************************/
    //转换操作
    qDebug()<<endl<<QObject::tr("以下是字符串的转换操作：")<<endl;

    str = "100";
    qDebug()<<QObject::tr("字符串转换为整数:")<<str.toInt();//结果为100

    int num = 45;
    qDebug()<<QObject::tr("整数转字符串：")<<QString::number(num); //结果为“45”

    str = "FF";
    bool ok;
    int hex = str.toInt(&ok, 16);
    //结果为ok:true 255
    qDebug()<<"ok:"<<ok<<QObject::tr("转换为16进制：")<<hex;

    num = 26;
    qDebug()<<QObject::tr("使用十六进制将整数转换为字符串:")
            <<QString::number(num, 16); //结果为1a

    str = "123.456";
    qDebug()<<QObject::tr("字符串转换为浮点数:")<<str.toFloat(); //结果为123.456

    str = "abc";
    qDebug()<<QObject::tr("转换为大写：")<<str.toUpper();
    str = "ABC";
    qDebug()<<QObject::tr("转换为小写：")<<str.toLower();

    int age = 25;
    QString name = "yafei";
    //name代替%1，age代替%2
    str = QString("name is %1, age is %2").arg(name).arg(age);
    //结果为name is yafei, age is 25
    qDebug()<<QObject::tr("更改后的str为：")<<str;

    str = "%1 %2";
    qDebug()<<str.arg("%1f", "hello");  //结果为%1f hello
    qDebug()<<str.arg("%1f").arg("hello");  //结果为hellof %2


    //end of add
    return a.exec();
}



















