#include "KPAOS4Checker.h"
#include "Midi.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include "Stomp.h"

#include <memory>

KPAOS4Checker::KPAOS4Checker(QObject *parent) : QObject(parent) {
  mTimer.reset(new QTimer(this));
}

void KPAOS4Checker::check() {
  QString inPort(Settings::get().getMidiInPort());
  QString outPort(Settings::get().getMidiOutPort());

  if (inPort.isEmpty() || outPort.isEmpty()) {
    SettingsDialog settingsDialog(nullptr);
    settingsDialog.exec();
    inPort = Settings::get().getMidiInPort();
    outPort = Settings::get().getMidiOutPort();
  }

  if (Midi::get().openPorts(inPort, outPort)) {
    QEventLoop el;
    auto stompDelayObj = std::unique_ptr<Stomp>(new Stomp(StompDelay));
    el.connect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
    el.connect(stompDelayObj.get(), &Stomp::onOffReceived, this,
               &KPAOS4Checker::onOfReceived);
    el.connect(mTimer.get(), &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
    mTimer->start(500);
    stompDelayObj->requestOnOff();
    el.exec();
    el.disconnect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
    el.disconnect(stompDelayObj.get(), &Stomp::onOffReceived, this,
                  &KPAOS4Checker::onOfReceived);
    el.disconnect(mTimer.get(), &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
  }
}

void KPAOS4Checker::onOfReceived(bool) {
  if (mTimer != nullptr)
    mTimer->stop();

  Settings::get().setKPAOSVersion(0x04000000);

  emit stopLoop();
}

void KPAOS4Checker::timerTimeout() {
  Settings::get().setKPAOSVersion(0x03000000);
  emit stopLoop();
}
