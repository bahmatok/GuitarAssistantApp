#include <QtTest>
#include <QSignalSpy>
#include "timer.h"

class TestTimer : public QObject
{
    Q_OBJECT

private slots:
    // Проверка преобразования BPM в интервал (60000/120 = 500 мс)
    void testBPMConversion();

    // Проверка запуска и остановки таймера
    void testStartStop();

    // Проверка обновления интервала во время работы
    void testBPMUpdateWhileRunning();

    // Проверка генерации сигнала timeout
    void testTimeoutSignal();
};

void TestTimer::testBPMConversion()
{
    Timer timer;
    timer.setTickingValue(120); // BPM = 120
    QCOMPARE(timer.tickingValue, 500); // ожидаемый интервал в мс
}

void TestTimer::testStartStop()
{
    Timer timer;
    QSignalSpy spy(&timer, &Timer::timeout);

    timer.setTickingValue(60); // 1000 мс
    timer.start();
    QVERIFY(timer.timer->isActive());

    QTest::qWait(500); // меньше интервала
    QCOMPARE(spy.count(), 0);

    timer.stop();
    QVERIFY(!timer.timer->isActive());

    QTest::qWait(600); // после остановки сигнал не должен появиться
    QCOMPARE(spy.count(), 0);
}

void TestTimer::testBPMUpdateWhileRunning()
{
    Timer timer;
    QSignalSpy spy(&timer, &Timer::timeout);

    timer.setTickingValue(120); // 500 мс
    timer.start();
    QTest::qWait(300); // ещё нет сигнала
    QCOMPARE(spy.count(), 0);

    // Меняем BPM на 60 (1000 мс) 
    timer.setTickingValue(60);
    QTest::qWait(1200); // ждём новый интервал
    QCOMPARE(spy.count(), 1); // должен прийти один сигнал

    timer.stop();
}

void TestTimer::testTimeoutSignal()
{
    Timer timer;
    QSignalSpy spy(&timer, &Timer::timeout);

    timer.setTickingValue(60); // 1000 мс
    timer.start();
    QVERIFY(spy.wait(1500)); // ждём сигнал максимум 1500 мс
    QCOMPARE(spy.count(), 1);

    timer.stop();
}

QTEST_MAIN(TestTimer)
#include "test_timer.moc"