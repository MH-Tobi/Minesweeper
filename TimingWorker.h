#pragma once

#include <QObject>

class TimingWorker : public QObject {
    Q_OBJECT

    public:
        TimingWorker() {};
        ~TimingWorker() {};

        void doWork();
        void cancel();

    signals:
        void timeIncreasedOneSecond();
        void done();

    private:
        bool _cancelExecution = false;
};