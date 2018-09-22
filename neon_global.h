#ifndef NEON_GLOBAL_H
#define NEON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NEON_LIBRARY)
#  define NEONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NEONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NEON_GLOBAL_H
