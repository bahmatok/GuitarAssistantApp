#include <QDir>
#include <QFileInfo>
#include <cmath>
#include <QObject>
#include <QtTest>
#include "tuner.h"

class TestTuner : public QObject
{
    Q_OBJECT

private slots:
    void cleanupTestCase();

    void testFrequenciesSixString();
    void testFrequenciesSevenString();
    void testFrequenciesUkulele();
    void testFrequenciesFourStringBass();
    void testFrequenciesFiveStringBass();
    void testInvalidStringNumber();

    void testGenerateSoundDataSize();
    void testGenerateSoundDataRange();

    void testGenerateSoundFile();
};

void TestTuner::cleanupTestCase()
{
    // Удаляем созданную папку с тестовыми файлами
    QString appDir = QCoreApplication::applicationDirPath();
    QString tonesDir = appDir + "/generated_tones";
    QDir dir(tonesDir);
    if (dir.exists()) {
        dir.removeRecursively();
    }
}

void TestTuner::testFrequenciesSixString()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::SixString);
    QCOMPARE(tuner.getFrequency(1), 82.41);
    QCOMPARE(tuner.getFrequency(2), 110.00);
    QCOMPARE(tuner.getFrequency(3), 146.83);
    QCOMPARE(tuner.getFrequency(4), 196.00);
    QCOMPARE(tuner.getFrequency(5), 246.94);
    QCOMPARE(tuner.getFrequency(6), 329.63);
}

void TestTuner::testFrequenciesSevenString()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::SevenString);
    QCOMPARE(tuner.getFrequency(1), 65.41);
    QCOMPARE(tuner.getFrequency(2), 82.41);
    QCOMPARE(tuner.getFrequency(3), 110.00);
    QCOMPARE(tuner.getFrequency(4), 146.83);
    QCOMPARE(tuner.getFrequency(5), 196.00);
    QCOMPARE(tuner.getFrequency(6), 246.94);
    QCOMPARE(tuner.getFrequency(7), 329.63);
}

void TestTuner::testFrequenciesUkulele()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::Ukulele);
    QCOMPARE(tuner.getFrequency(1), 261.63);
    QCOMPARE(tuner.getFrequency(2), 293.66);
    QCOMPARE(tuner.getFrequency(3), 329.63);
    QCOMPARE(tuner.getFrequency(4), 392.00);
}

void TestTuner::testFrequenciesFourStringBass()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::FourStringBass);
    QCOMPARE(tuner.getFrequency(1), 84.41);
    QCOMPARE(tuner.getFrequency(2), 110.00);
    QCOMPARE(tuner.getFrequency(3), 147.83);
    QCOMPARE(tuner.getFrequency(4), 207.00);
}

void TestTuner::testFrequenciesFiveStringBass()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::FiveStringBass);
    QCOMPARE(tuner.getFrequency(1), 61.74);
    QCOMPARE(tuner.getFrequency(2), 84.41);
    QCOMPARE(tuner.getFrequency(3), 110.00);
    QCOMPARE(tuner.getFrequency(4), 147.83);
    QCOMPARE(tuner.getFrequency(5), 207.00);
}

void TestTuner::testInvalidStringNumber()
{
    Tuner tuner;
    tuner.setGuitarType(Tuner::SixString);
    QCOMPARE(tuner.getFrequency(0), 0.0);
    QCOMPARE(tuner.getFrequency(7), 0.0);
    QCOMPARE(tuner.getFrequency(100), 0.0);
}

void TestTuner::testGenerateSoundDataSize()
{
    Tuner tuner;
    int sampleRate = 44100;
    int duration = 1;
    double frequency = 440.0;

    QByteArray data = tuner.generateSoundData(frequency, sampleRate, duration);
    int expectedSize = sampleRate * duration * sizeof(qint16);
    QCOMPARE(data.size(), expectedSize);
}

void TestTuner::testGenerateSoundDataRange()
{
    Tuner tuner;
    int sampleRate = 44100;
    int duration = 1;
    double frequency = 440.0;

    QByteArray data = tuner.generateSoundData(frequency, sampleRate, duration);
    const qint16 *samples = reinterpret_cast<const qint16*>(data.constData());
    int numSamples = data.size() / sizeof(qint16);

    for (int i = 0; i < numSamples; ++i) {
        QVERIFY2(samples[i] >= -32768 && samples[i] <= 32767,
                 QString("Sample %1 out of range: %2").arg(i).arg(samples[i]).toLocal8Bit());
    }
}

void TestTuner::testGenerateSoundFile()
{
    Tuner tuner;
    double frequency = 440.0;
    QString appDir = QCoreApplication::applicationDirPath();
    QString tonesDir = appDir + "/generated_tones";
    QString expectedFileName = QString("tone_%1.wav").arg(frequency);
    QString expectedFilePath = tonesDir + "/" + expectedFileName;

    // Удаляем папку, если она существует
    QDir dir(tonesDir);
    if (dir.exists()) {
        dir.removeRecursively();
    }

    QString resultPath = tuner.generateSoundFile(frequency);

    // Проверяем возвращаемый путь
    QCOMPARE(resultPath, expectedFilePath);

    // Проверяем создание папки
    QVERIFY(dir.exists());

    // Проверяем существование файла
    QFile file(expectedFilePath);
    QVERIFY(file.exists());

    // Проверяем, что размер файла больше минимального заголовка WAV (44 байта)
    QVERIFY(file.size() > 44);
}

QTEST_MAIN(TestTuner)
#include "test_tuner.moc"