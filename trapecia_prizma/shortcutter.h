#ifndef SHORTCUTTER_H
#define SHORTCUTTER_H

#include <QApplication>
#include <QEvent>
#include <QObject>

class ShortCutter: public QObject
{
protected:
     bool eventFilter(QObject *obj, QEvent *ev)
     {
          //����� � ������������ ��� ������� ����������


     }
public:
    ShortCutter()
    {
        QApplication::instance()->installEventFilter(this);
    }

    virtual ~ShortCutter(){}
};

#endif // SHORTCUTTER_H
