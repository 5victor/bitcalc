#include "BitCalc.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <stdio.h>

BitLable::BitLable(QWidget *parent)
    : QLabel(parent)
{

}

void BitLable::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit BitLableClicked(index);
}

void BitLable::setValue(int v)
{
    this->setNum(v);
    this->value = v;
}

BitCalc::BitCalc(QWidget *parent)
    : QWidget(parent)
{
    init();
}

void BitCalc::init()
{
    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QHBoxLayout *bitLayout;
    QHBoxLayout *ctrlLayout;
    int i;

    value = 0;

    titleLayout = new QHBoxLayout;
    this->setWindowTitle(tr("BitCalc"));
    titleLayout->setSpacing(0);
    for (i = MAX_BIT - 1; i >= 0; i--)
    {
        QLabel *title = new QLabel(this);
        if (i % 4 == 3)
        {
            title->setNum(i);
        }
        //title->setFrameShape(QFrame::Box);
        title->setFixedWidth(13);
        title->setAlignment(Qt::AlignHCenter);
        titleLayout->addWidget(title);
    }
    titleLayout->addStretch();

    bitLayout = new QHBoxLayout;
    for (i = MAX_BIT - 1; i >= 0; i--)
    {
        BitLable *bit = new BitLable;
        labels[i] = bit;
        bit->index = i;
        bit->value = 0;
        bit->setNum(0);
        QObject::connect(bit, SIGNAL(BitLableClicked(int)),
                         this, SLOT(BitLableClicked(int)));
        bit->setFixedWidth(13);
        bit->setAlignment(Qt::AlignHCenter);
        bitLayout->addWidget(bit);
    }
    bitLayout->setSpacing(0);
    bitLayout->addStretch();

    ctrlLayout = new QHBoxLayout;
    ctrlLayout->setSpacing(30);
    text = new QLineEdit;
    //QObject::connect(text, SIGNAL(textChanged(QString)), this, SLOT(textChange(QString)));
    QPushButton *set = new QPushButton;
    QPushButton *clear = new QPushButton;
    QPushButton *quit = new QPushButton;
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(set, SIGNAL(clicked()), this, SLOT(set()));
    QObject::connect(clear, SIGNAL(clicked()), this, SLOT(clear()));
    set->setText(tr("&set"));
    set->setMaximumWidth(80);
    clear->setText(tr("&clear"));
    clear->setMaximumWidth(80);
    quit->setText(tr("&quit"));
    quit->setMaximumWidth(80);
    ctrlLayout->addWidget(text);
    ctrlLayout->addWidget(set);
    ctrlLayout->addWidget(clear);
    ctrlLayout->addWidget(quit);
    ctrlLayout->addStretch();


    this->setText(0);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(bitLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(ctrlLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

void BitCalc::setText(unsigned int n)
{
    QString str;
    str.sprintf("0x%08X",n);
    text->setText(str);
}

void BitCalc::BitLableClicked(int index)
{
    if (labels[index]->value)
    {
        labels[index]->value = 0;
        labels[index]->setNum(0);
        value &= ~(1 << index);
    }
    else
    {
        labels[index]->value = 1;
        labels[index]->setNum(1);
        value |= 1 << index;
    }
    setText(value);
}

void BitCalc::set()
{
    setValueFormStr(text->text());
}

void BitCalc::clear()
{
    int i;
    for (i = 0; i < MAX_BIT; i++)
    {
        labels[i]->setValue(0);
    }
    this->value = 0;
    this->setText(0);
}

void BitCalc::setValueFormStr(QString str)
{

    int ret;
    unsigned int data;
    int i;

    ret = sscanf(str.toAscii().data(), "0x%x", &data);
    if (ret != 1)
    {
        QMessageBox::information(this, "input err", "please input valid hex value");
    }

    for (i = 0; i < sizeof(data) * 8; i++)
    {
        if ((data >> i) & 1)
        {
            labels[i]->setValue(1);
        }
        else
        {
            labels[i]->setValue(0);
        }
    }
    this->value = data;

}
