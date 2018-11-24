#include "nresources.h"

QString NResources::getLightCSS() {
#ifdef QT_DEBUG
	return "res/css/neon_light.css";
#else
	return ":/css/neon_light";
#endif
}

QString NResources::getDarkCSS() {
#ifdef QT_DEBUG
	return "res/css/neon_dark.css";
#else
	return ":/css/neon_dark";
#endif
}
