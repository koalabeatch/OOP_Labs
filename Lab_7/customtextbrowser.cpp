#include <customtextbrowser.h>

CustomTextBrowser::CustomTextBrowser(QWidget *parent) : QTextBrowser(parent)
{

}


void CustomTextBrowser::append(QString Text , QColor Color)
{

     QTextBrowser::setTextColor(Color);
     QTextBrowser::append(Text);
}


