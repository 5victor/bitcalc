#ifndef BITCALC_H
#define BITCALC_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#define MAX_BIT 32

class BitLable : public QLabel
{
    Q_OBJECT
public:
    BitLable(QWidget *parent = 0);
    void setValue(int v);
    int index; /* for indicate which bit*/
    int value; /* 0 or 1*/
signals:
    void BitLableClicked(int index);
protected:
    void mouseReleaseEvent(QMouseEvent *ev);
};

class BitCalc : public QWidget
{
    Q_OBJECT
public:
    BitCalc(QWidget *parent = 0);

protected:
    void init();
    //int bitArray[MAX_BIT];
    unsigned int value;
    QLineEdit *text;
    BitLable *labels[MAX_BIT];

    void setText(unsigned int n);
    void setValue(QString s);
    void setValueFormStr(QString s);

public slots:
    void set();
    void clear();
    void BitLableClicked(int index);
};

#endif // BITCALC_H
