#ifndef NRESOURCES_H
#define NRESOURCES_H

#include <QObject>

class NResources : public QObject
{
	Q_OBJECT
public:
	static QString getLightCSS();
	static QString getDarkCSS();

signals:

public slots:
};

#endif // NRESOURCES_H
