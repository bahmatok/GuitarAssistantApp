#include <QtTest>
#include "ticker.h"

class TestTicker : public QObject
{
    Q_OBJECT

private slots:
    // Начальное состояние
    void testInitialState();

    // Логика воспроизведения с акцентом на первую долю
    void testPlaySoundWithStress();

    // Логика воспроизведения без акцента
    void testPlaySoundWithoutStress();

    // Изменение громкости
    void testSetVolume();

    // Переключение акцента
    void testToggleStress();
};

void TestTicker::testInitialState()
{
    Ticker ticker;
    QCOMPARE(ticker.counter, 0);
    QCOMPARE(ticker.stressFirstBeat, true);
    QCOMPARE(ticker.player->volume(), 60);
}

void TestTicker::testPlaySoundWithStress()
{
    Ticker ticker;
    // Первый вызов -> playHigh (индекс 0)
    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 0);
    QCOMPARE(ticker.counter, 1);

    // Следующие три -> playLow (индекс 1)
    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 1);
    QCOMPARE(ticker.counter, 2);

    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 1);
    QCOMPARE(ticker.counter, 3);

    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 1);
    QCOMPARE(ticker.counter, 0); // сброс после четвёртого

    // Пятый снова high
    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 0);
    QCOMPARE(ticker.counter, 1);
}

void TestTicker::testPlaySoundWithoutStress()
{
    Ticker ticker;
    ticker.stressFirstBeat = false;
    ticker.counter = 5; // произвольное значение

    int oldCounter = ticker.counter;
    ticker.playSound();
    QCOMPARE(ticker.playlist->currentIndex(), 1); // всегда low
    QCOMPARE(ticker.counter, oldCounter); // счётчик не меняется
}

void TestTicker::testSetVolume()
{
    Ticker ticker;
    ticker.setVolumeLevel(80);
    QCOMPARE(ticker.player->volume(), 80);
}

void TestTicker::testToggleStress()
{
    Ticker ticker;
    QVERIFY(ticker.stressFirstBeat);
    ticker.counter = 5;
    ticker.reqToStressFirstBeat();
    QVERIFY(!ticker.stressFirstBeat);
    QCOMPARE(ticker.counter, 0);

    ticker.reqToStressFirstBeat();
    QVERIFY(ticker.stressFirstBeat);
    QCOMPARE(ticker.counter, 0);
}

QTEST_MAIN(TestTicker)
#include "test_ticker.moc"