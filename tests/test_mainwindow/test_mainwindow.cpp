    #include <QtTest>
    #include <QDir>
    #include <QFile>
    #include <QTemporaryDir>
    #include <QTextStream>
    #include "mainwindow.h"
    #include "ui_mainwindow.h"

    class TestMainWindow : public QObject
    {
        Q_OBJECT

    private:
        QTemporaryDir tempDir;  

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void testXorEncryptSymmetry();
        void testXorEncryptDifferentKeys();
        void testSettingsFormatAndParse();
    };

    void TestMainWindow::initTestCase()
    {
        // Подавляем всплывающие окна
        MainWindow::suppressMessageBoxes(true);

        QVERIFY(tempDir.isValid());
        QDir::setCurrent(tempDir.path());
    }

    void TestMainWindow::cleanupTestCase()
    {
        QDir::setCurrent(QCoreApplication::applicationDirPath());
    }

    void TestMainWindow::testXorEncryptSymmetry()
    {
        MainWindow w;
        QString original = "Test string with 123!@#";
        QString encrypted = w.xorEncrypt(original);
        QString decrypted = w.xorEncrypt(encrypted);
        QCOMPARE(decrypted, original);
    }

    void TestMainWindow::testXorEncryptDifferentKeys()
    {
        MainWindow w1, w2;
        QString original = "TestString123";

        w1.setKeyForTesting("key1");
        w2.setKeyForTesting("key2");

        QString encrypted1 = w1.xorEncrypt(original);
        QString encrypted2 = w2.xorEncrypt(original);

        QVERIFY(encrypted1 != encrypted2);

        QCOMPARE(w1.xorEncrypt(encrypted1), original);
        QCOMPARE(w2.xorEncrypt(encrypted2), original);
    }

    void TestMainWindow::testSettingsFormatAndParse()
    {
        MainWindow w;

        w.testUi()->volumeSlider->setValue(75);
        w.testUi()->BPMSlider->setValue(120);
        w.testUi()->stressFirstBitCheckBox->setChecked(true);
        w.testUi()->textEdit->setPlainText("C G Am");

        w.saveSettings();

        QFile file("settings.txt");
        QVERIFY(file.exists());

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString encryptedData = QString::fromUtf8(file.readAll());
        file.close();

        QString decrypted = w.xorEncrypt(encryptedData);
        QString expected = "75 120 1 C G Am";
        QCOMPARE(decrypted, expected);

        MainWindow w2;
        w2.getSettings();

        QCOMPARE(w2.testUi()->volumeSlider->value(), 75);
        QCOMPARE(w2.testUi()->BPMSlider->value(), 120);
        QCOMPARE(w2.testUi()->stressFirstBitCheckBox->isChecked(), true);
        QCOMPARE(w2.testUi()->textEdit->toPlainText(), QString("C G Am"));
    }

    QTEST_MAIN(TestMainWindow)
    #include "test_mainwindow.moc"