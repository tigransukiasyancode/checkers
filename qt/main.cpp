#include <QApplication>
#include "CheckersGameWidget.hpp"
int main(int argc, char *argv[]){
	QApplication app(argc,argv);
	CheckersGameWidget *p = new CheckersGameWidget();
	p->show();
	p->start();
 	
	return app.exec();
}
