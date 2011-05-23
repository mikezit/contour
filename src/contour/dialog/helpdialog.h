#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include "ui_helpdialog.h"

class HelpDialog : public QDialog,public Ui::HelpDialog
{
Q_OBJECT

public:
     HelpDialog( QWidget * parent = 0, Qt::WindowFlags f = 0 );

     ~HelpDialog();

     public slots:

     void showHtml();
};
#endif
