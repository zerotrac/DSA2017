#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonTextHelp, SIGNAL(clicked(bool)), this, SLOT(showTextHelp()));
    QObject::connect(ui->buttonMatchHelp, SIGNAL(clicked(bool)), this, SLOT(showMatchHelp()));
    QObject::connect(ui->buttonSigmaHelp, SIGNAL(clicked(bool)), this, SLOT(showSigmaHelp()));
    QObject::connect(ui->buttonTextGenerate, SIGNAL(clicked(bool)), this, SLOT(generateText()));
    QObject::connect(ui->buttonMatchGenerate, SIGNAL(clicked(bool)), this, SLOT(generateMatch()));
    QObject::connect(ui->buttonStart, SIGNAL(clicked(bool)), this, SLOT(start()));
    gen = std::mt19937(rd());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextHelp()
{
    QMessageBox* msgbox = new QMessageBox(QMessageBox::Question, "Help", "在应用程序的同级目录中有一个input.txt文件，用来存放文本串。\n你可以修改该文件来决定使用的文本串，其中第一行为文本串的长度，第二行为文本串。\n你也可以让程序随机生成一个文本串并输出到input.txt中，并且可以选择文本串的字符集。", QMessageBox::Ok, this);
    msgbox->exec();
}

void MainWindow::showMatchHelp()
{
    QMessageBox* msgbox = new QMessageBox(QMessageBox::Question, "Help", "你可以直接在上方输入框中直接输入匹配串，或者让程序生成一个匹配串。", QMessageBox::Ok, this);
    msgbox->exec();
}

void MainWindow::showSigmaHelp()
{
    QMessageBox* msgbox = new QMessageBox(QMessageBox::Question, "Help", "你可以在选项卡中选择随机生成串的字符集。\nASCII 33-126表示常用的字母，数字和符号。", QMessageBox::Ok, this);
    msgbox->exec();
}

void MainWindow::generateText()
{
    int len = ui->lineTextSize->text().toInt();
    if (len <= 0 || len > 1000000)
    {
        QMessageBox* msgbox = new QMessageBox(QMessageBox::Warning, "Warning", "文本串的长度参数不正确！", QMessageBox::Ok, this);
        msgbox->exec();
        return;
    }

    std::ofstream out("input.txt");

    out << len << std::endl;

    int l, r;
    if (ui->radioSigma0->isChecked())
    {
        l = 97;
        r = 99;
    }
    else if (ui->radioSigma1->isChecked())
    {
        l = 48;
        r = 57;
    }
    else
    {
        l = 33;
        r = 126;
    }
    std::uniform_int_distribution<int> dis(l, r);

    for (int i = 0; i < len; ++i)
    {
        char ch = dis(gen);
        out << ch;
    }
    out << std::endl;
    out.close();

    QMessageBox* msgbox = new QMessageBox(QMessageBox::Information, "Info", "生成成功！", QMessageBox::Ok, this);
    msgbox->exec();
}

void MainWindow::generateMatch()
{
    int l, r;
    if (ui->radioSigma0->isChecked())
    {
        l = 97;
        r = 99;
    }
    else if (ui->radioSigma1->isChecked())
    {
        l = 48;
        r = 57;
    }
    else
    {
        l = 33;
        r = 126;
    }
    std::uniform_int_distribution<int> dis(l, r);
    int len = ui->lineMatchSize->text().toInt();
    QString result;
    for (int i = 0; i < len; ++i)
    {
        char ch = dis(gen);
        result.append(ch);
    }
    ui->lineMatchString->setText(result);
}

void MainWindow::start()
{
    std::ifstream in("input.txt");
    int len;
    in >> len;
    std::string st;
    in >> st;
    StringMatch proc(st);
    std::string model = ui->lineMatchString->text().toStdString();
    std::vector<int> result;
    if (ui->radioBF->isChecked())
    {
        result = proc.matchBF(model);
    }
    else if (ui->radioKMP->isChecked())
    {
        result = proc.matchKMP(model);
    }
    else
    {
        result = proc.matchBM(model);
    }

    std::ofstream out("output.txt");
    out << result.size() << std::endl;
    for (auto elem: result) out << elem << std::endl;

    QMessageBox* msgbox = new QMessageBox(QMessageBox::Information, "Info", "匹配完成！共匹配到"+QString::number(result.size())+"次，具体位置已经输出到output.txt文件中。", QMessageBox::Ok, this);
    msgbox->exec();
}
