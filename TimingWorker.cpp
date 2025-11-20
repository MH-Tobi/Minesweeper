#include <QElapsedTimer>
#include <QThread>
#include <QAbstractEventDispatcher>
#include "TimingWorker.h"


void TimingWorker::doWork()
{
    QElapsedTimer timer;
    uint16_t lastTime = 0;

    timer.start();

    while (!_cancelExecution)
    {
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::ProcessEventsFlag::AllEvents);
        if ((timer.elapsed() / 1000) > lastTime)
        {
            lastTime = timer.elapsed() / 1000;
            emit timeIncreasedOneSecond();
        }
        QThread::yieldCurrentThread();
    }
    emit done();
}

void TimingWorker::cancel()
{
    _cancelExecution = true;
}