#ifndef CONTOURSCENE_H
#define CONTOURSCENE_H
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
class ContourScene : public QGraphicsScene
{
	Q_OBJECT

public:
	ContourScene();
	~ContourScene();
	
	void showScaleRect(){_scaleRect.setVisible(true);
	}
	void hideScaleRect(){_scaleRect.setVisible(false);}
	void setScaleRectRightBottomPos(QPointF pt)
	{
		QRectF r=_scaleRect.rect();
		_scaleRect.setRect(r.x(),r.y(),pt.x()-r.x(),pt.y()-r.y());
	}
	void setScaleRectLeftTopPos(QPointF pt)
	{
		_scaleRect.setRect(pt.x(),pt.y(),0,0);
	}
	QRectF scaleRect(){return _scaleRect.rect();}

private:
	QGraphicsRectItem _scaleRect;
};

#endif // FASTSCENE_H
