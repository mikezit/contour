#include "helpdialog.h"
#include <QProcess>
#include <QMessageBox>

HelpDialog::HelpDialog( QWidget * parent/* = 0*/, Qt::WindowFlags f /*= 0*/)  
{
     setupUi(this);
     connect(htmlButton,SIGNAL(clicked()),this,SLOT(showHtml()));
}

HelpDialog::~HelpDialog()
{

}

void HelpDialog::showHtml()
{
     QStringList list;
     int result;
     list<<"https://sites.google.com/site/jianssoft/";
#ifndef WIN32
     if(!(result = QProcess::startDetached( "mozilla",  list)))
	  result = QProcess::startDetached( "firefox",  list);
#else
	       result = QProcess::startDetached(QString("C:\\Program Files\\Internet Explorer\\iexplore.exe"),list);
#endif
     if(!result)
	  QMessageBox::information(this,"information",
				   "Can't find brower,you should open it youself\n"
				   "           The address is :\n" 
				   "https://sites.google.com/site/jianssoft/");
}
