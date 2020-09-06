#include "loadiconfromfiles.h"

#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QMap>
#include <QPixmap>
#include <QStringList>
#include <QStyle>

static QMap<QString, QIcon> s_iconCache;

static void addFileToIcon(QIcon &icon, QString iconFilePath,
                          QSize size = QSize(),
                          QIcon::Mode mode = QIcon::Normal,
                          QIcon::State state = QIcon::Off) {
  QFileInfo iconFile(iconFilePath);
  if (iconFile.exists()) {
    icon.addFile(iconFile.absoluteFilePath(), size, mode, state);
  } else {
    qWarning() << "Failed to load icon file:" << iconFile.absoluteFilePath();
  }
}

static void doCompositeLoading(QIcon &icon, QString fileName,
                               QList<int> iconSizeList,
                               QIcon::State state = QIcon::Off) {
  for (int size : iconSizeList) {
    // Example: "Save %1 %2 p.png" -> "Save 16 d p.png"
    // State: (d)isabled.
    addFileToIcon(icon, fileName.arg(size).arg("d"), QSize(size, size),
                  QIcon::Disabled, state);
    //        (h)ot.
    addFileToIcon(icon, fileName.arg(size).arg("h"), QSize(size, size),
                  QIcon::Active, state);
    //        (n)eutral.
    addFileToIcon(icon, fileName.arg(size).arg("n"), QSize(size, size),
                  QIcon::Normal, state);
  }
}

QIcon loadIconFromFiles(const QString &fileName, QList<int> iconSizeList) {
  if (fileName.isNull()) {
    return QIcon();
  }

  // Only cache if using the default icon size list.
  const bool mayCacheIcon = iconSizeList.isEmpty();

  if (mayCacheIcon && s_iconCache.contains(fileName)) {
    return s_iconCache.value(fileName);
  }

  if (iconSizeList.isEmpty()) {
    iconSizeList << 16 << 24 << 32 << 48 << 64 << 128;
  }

  QIcon icon;
  if (fileName.contains(";;")) {
    auto fileNameOnOff = fileName.split(";;");

    // Two states assumed; first is "On", second is "Off".
    doCompositeLoading(icon, fileNameOnOff[0], iconSizeList, QIcon::On);
    doCompositeLoading(icon, fileNameOnOff[1], iconSizeList, QIcon::Off);

  } else if (fileName.contains("%1") && fileName.contains("%2")) {
    doCompositeLoading(icon, fileName, iconSizeList);
  } else if (fileName.contains("%1")) {
    for (const int size : iconSizeList) {
      addFileToIcon(icon, fileName.arg(size), QSize(size, size), QIcon::Normal);
    }
  } else if (fileName.startsWith(":/")) {
    addFileToIcon(icon, fileName);
  } else {
    addFileToIcon(icon, ":/" + QCoreApplication::applicationName() + "/" +
                            fileName + ".png");
  }

  if (mayCacheIcon) {
    s_iconCache.insert(fileName, icon);
  }
  if (icon.isNull()) {
    qWarning() << "icon not found" << fileName << fileName;
  }
  Q_ASSERT(!icon.isNull());
  return icon;
}

QCursor loadCursorFromFiles(const QString &fileNameOrID, double hotX,
                            double hotY, QList<int> iconSizeList) {
  Q_ASSERT(hotX >= 0 && hotX <= 1 && hotY >= 0 && hotY <= 1);
  if (fileNameOrID.isNull()) {
    return QPixmap();
  }
  QIcon icon = loadIconFromFiles(fileNameOrID, iconSizeList);
  int size = QApplication::style()->pixelMetric(QStyle::PM_LargeIconSize);
  QPixmap p = icon.pixmap(size, size);
  Q_ASSERT(!p.size().isEmpty());
  return QCursor(p, size * hotX, size * hotY);
}
