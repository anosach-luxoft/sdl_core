// checksum 0x56a9 version 0x80001
/*
  This file was generated by the Qt Quick 2 Application wizard of Qt Creator.
  QtQuick2ApplicationViewer is a convenience class containing mobile device
  specific
  code such as screen orientation handling. Also QML paths and debugging are
  handled here.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "qtquick2applicationviewer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>

class QtQuick2ApplicationViewerPrivate {
  QString mainQmlFile;
  friend class QtQuick2ApplicationViewer;
  static QString adjustPath(const QString& path);
};

QString QtQuick2ApplicationViewerPrivate::adjustPath(const QString& path) {
#if defined(Q_OS_MAC)
  if (!QDir::isAbsolutePath(path))
    return QString::fromLatin1("%1/../Resources/%2")
        .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_UNIX)
  const QString pathInInstallDir =
      QString::fromLatin1("%1/../%2")
          .arg(QCoreApplication::applicationDirPath(), path);
  if (QFileInfo(pathInInstallDir).exists())
    return pathInInstallDir;
#endif
  return path;
}

QtQuick2ApplicationViewer::QtQuick2ApplicationViewer(QWindow* parent)
    : QQuickView(parent), d(new(__FILE__, __LINE__) QtQuick2ApplicationViewerPrivate()) {
  connect(engine(), SIGNAL(quit()), SLOT(close()));
  setResizeMode(QQuickView::SizeRootObjectToView);
}

QtQuick2ApplicationViewer::~QtQuick2ApplicationViewer() {
  delete d;
}

void QtQuick2ApplicationViewer::setMainQmlFile(const QString& file) {
  d->mainQmlFile = QtQuick2ApplicationViewerPrivate::adjustPath(file);
  setSource(QUrl::fromLocalFile(d->mainQmlFile));
}

void QtQuick2ApplicationViewer::addImportPath(const QString& path) {
  engine()->addImportPath(QtQuick2ApplicationViewerPrivate::adjustPath(path));
}

void QtQuick2ApplicationViewer::showExpanded() {
#if defined(Q_WS_SIMULATOR)
  showFullScreen();
#else
  show();
#endif
}
