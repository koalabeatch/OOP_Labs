#ifndef CUSTOMTEXTBROWSER_H
#define CUSTOMTEXTBROWSER_H

#include <QColor>
#include <QTextBrowser>

class CustomTextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit CustomTextBrowser(QWidget *parent = nullptr);
    //void SetTextColor(QColor Color);
public slots:
    void append(QString Text, QColor Color = QColor(0,0,0));
};

#endif // CUSTOMBUTTON_H
