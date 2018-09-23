#ifndef NEON_H
#define NEON_H

#include "neon_global.h"
#include "theme.h"

#include <iostream>
#include <QProxyStyle>

using namespace std;

class NEONSHARED_EXPORT Neon : public QProxyStyle
{

public:

	/* CONSTRUCTOR */

	Neon(QStyle *style = nullptr, Theme theme = DARK);
	Neon(const QString &key, Theme theme = DARK);

	/* NEON METHODS */

	void polish(QPalette& palette) override;
	void polish(QWidget* widget) override;
	void unpolish(QWidget* widget) override;
	int pixelMetric(PixelMetric metric, const QStyleOption* option,
					const QWidget* widget) const override;
	int styleHint(StyleHint hint, const QStyleOption* option,
				  const QWidget* widget,
				  QStyleHintReturn* returnData) const override;
	void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
					   QPainter* painter, const QWidget* widget) const override;
	void drawControl(ControlElement control, const QStyleOption* option,
					 QPainter* painter, const QWidget* widget) const override;

	/* GETTER & SETTER */

	Theme getTheme() const;
	void  setTheme(Theme theme);

private:	
	Theme theme;

	void initialize(Theme theme);
};

#endif // NEON_H
