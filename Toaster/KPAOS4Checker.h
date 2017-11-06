#ifndef KPAOS4CHECKER_H
#define KPAOS4CHECKER_H

#include <QObject>
#include <memory>

class QTimer;

class KPAOS4Checker : public QObject {
  Q_OBJECT
public:
  explicit KPAOS4Checker(QObject *parent = 0);

  void check();

signals:
  void stopLoop();

public slots:
  void onOfReceived(bool);
  void timerTimeout();

private:
  std::unique_ptr<QTimer> mTimer;
};

#endif // KPAOS4CHECKER_H
