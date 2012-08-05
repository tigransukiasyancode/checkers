#ifndef QT_BOARD_HPP
#define QT_BOARD_HPP
#include <QWidget>
#include <QMouseEvent>
#include <QPointF>
#include <QPainter>
#include "Figures.hpp"
#include <iostream>
class QtBoard:public QWidget{
	Q_OBJECT
	public:
	enum State{WHITE,WHITEKING,BLACK,BLACKKING,CAPTURED,FROM,MID,NONE};
	
	signals:
		void boardPresed(int i);	
	private:
	void mousePressEvent ( QMouseEvent * event ){
		QPointF point = event->posF();
		int row = 7 - static_cast<int>(point.y()/32);
		int col = point.x()/32;
		//cout<<point.y()<<" p "<<point.y()/32<<endl;
		//cout<<row<<" r "<<col<<endl;
		int i = 0;
		if((row%2) == (col%2)){
			int i = row*4  + static_cast<int>((col)/2); 
			//row==0 && ?i:--i;
			//cout<<i<<std::endl;
			emit boardPresed(i );
			
		}
			 	
	}
	public:
	QtBoard(QWidget* parent ,const vector<State> s ):QWidget(parent),state(s){
		resize(320,320);
	}
	void draw(const vector<State>& st){
		state = st;
		update();
	}
	void paintEvent(QPaintEvent *event)
	{
		//qDebug() << "CheckersPicture::paintEvent()";

		QPainter painter(this);
		//painter.setRenderHint(QPainter::Antialiasing, true);
		//painter.setViewport(p.x(),p.y(),side,side);
		//painter.setWindow(0, 0, zoom*(n+1.0), zoom*(n+1.0));
		QColor border(0xce,0x5c,0x00);
		painter.fillRect(QRect(0,0,10,10), border);

		/*QColor border(0xce,0x5c,0x00);
		painter.fillRect(QRect(0,0,zoom*(n+1.0),zoom*0.5), border);
		painter.fillRect(QRect(0,zoom*(n+0.5),zoom*(n+1.0),zoom*0.5), border);
		painter.fillRect(QRect(0,0,zoom*(0.5),zoom*(n+1.0)), border);
		painter.fillRect(QRect(zoom*(n+0.5),0,zoom*0.5,zoom*(n+1.0)), border);
	*/
		QColor dark(0xcc,0xcc,0xcc);

		for(int i=0; i<8; i++) {
			for(int j=0; j<8; j++) {
				QRect rect(i*32 , j*32 , 32 , 32);
				if( ((i+j%2)%2) ) {
						painter.fillRect(rect, dark);
						//painter.drawEllipse(QPoint(zoom*(i+1),zoom*(10-j)),s,s);
				} else {
					painter.fillRect(rect, Qt::white);
				}
			}
		}
		for(int i=0 ; i < 32;++i){
			int row = i/4;
			int y = (8 - row -1)*32;
			int x = row%2 * 32 + (i%4) * 64;
			State s = state[i];
			if(s==WHITE)
			{
				painter.setPen(QPen(Qt::white,2));
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == WHITEKING){
				painter.setPen(QPen(Qt::white,2));
				painter.drawEllipse(QPoint(x+ 16,y+16),13,13);
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == BLACK){	
				painter.setPen(QPen(Qt::black,2));
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == BLACKKING){
				painter.setPen(QPen(Qt::black,2));
				painter.drawEllipse(QPoint(x+ 16,y+16),13,13);
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == CAPTURED){
				painter.setPen(QPen(Qt::red,2));	
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == FROM){
				painter.setPen(QPen(Qt::green,2));	
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}else if(s == MID){
				painter.setPen(QPen(Qt::yellow,2));	
				painter.drawEllipse(QPoint(x+ 16,y+16),10,10);
			}




		}	
	/*	int ix,jx;
	//	QColor endColor(0x4c,0x4c,0xcc);
		QColor endColor(0x90,0x00,0x90);
		QColor startColor(0x33,0xff,0x00);
		QColor capturedColor(0xff,0x33,0x33);
		QColor normalColor(0x4c,0x4c,0xcc);
		if(v.size()) {
			int type;
			for(unsigned i=0; i< v.size(); i++) {
				color==WHITE ? jx = n-1-v.at(i).y : jx = v.at(i).y;
				color==WHITE ? ix = n-1-v.at(i).x : ix = v.at(i).x;
				QRect rect = pixelRect(ix, jx);
				type = v.at(i).type;
				if(type == MOVEDFROM)
					painter.fillRect(rect, startColor);
				else if(type == MOVEDTO || type == TOKING)
					painter.fillRect(rect, endColor);
				else if(type == MOVEDTHROUGH)
					painter.fillRect(rect, normalColor);
				else if(type == DELETED)
					painter.fillRect(rect, capturedColor);
			}
		}

		int s = zoom*0.4;
		int sd = zoom*0.2;
		if(curstate) {
			painter.setPen(QPen(Qt::black,zoom*0.1));
			painter.setBrush(QBrush(Qt::white));
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					color==WHITE ? jx = j+1 : jx = n-j;
					color==WHITE? ix = n-i : ix = i+1;
					if(curstate->at(i,j)==WHITE)
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),s,s);
					if(curstate->at(i,j)==WHITEKING) {
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),s,s);
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),sd,sd);
					}
				}
			}
			painter.setBrush(QBrush(Qt::black));
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					color==WHITE ? jx = j+1 : jx = n-j;
					color==WHITE ? ix = n-i : ix = i+1;
					if(curstate->at(i,j)==BLACK)
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),s,s);
					if(curstate->at(i,j)==BLACKKING) {
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),s,s);
						painter.setPen(QPen(Qt::white,zoom*0.1));
						painter.drawEllipse(QPoint(zoom*(ix),zoom*(jx)),sd,sd);
						painter.setPen(QPen(Qt::black,zoom*0.1));
					}
				}
			}
		}*/
	}
	private:
	vector<State> state;
};
#endif
