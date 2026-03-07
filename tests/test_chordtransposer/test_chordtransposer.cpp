#include <QtTest>
#include "chordtransposer.h"

class TestChordTransposer : public QObject
{
    Q_OBJECT

private slots:
    // Тесты валидации аккордов
    void testValidateChords_valid();
    void testValidateChords_invalid();

    // Тесты сортировки
    void testSortChords_simple();
    void testSortChords_withAccidentals();
    void testSortChords_withSuffixes();

    // Тесты обнаружения повторяющихся подстрок
    void testHasRepeatedSubstring_true();
    void testHasRepeatedSubstring_false();

    // Тесты транспонирования отдельного аккорда
    void testTransposeChord_simple();
    void testTransposeChord_withSuffixes();
    void testTransposeChord_flats();

    // Тесты транспонирования списка аккордов
    void testTransposeChords_normal();
    void testTransposeChords_repeatedPattern();

    // Тесты бинарного поиска
    void testBinarySearch_found();
    void testBinarySearch_notFound();
    void testBinarySearch_emptyList();
    void testBinarySearch_singleElement();
};

void TestChordTransposer::testValidateChords_valid()
{
    ChordTransposer ct;
    QStringList validChords = {
        "C", "Am", "G#7", "F#m7", "D#dim", "A#sus2", "Bbmaj7", "C#m7b5"
    };
    QVERIFY(ct.validateChords(validChords));
}

void TestChordTransposer::testValidateChords_invalid()
{
    ChordTransposer ct;
    QStringList invalidChords = {
        "H", "C#maj9#11", "A!!", "", " ", "C#maj7sus2", "Cb", "E#"
    };
    QVERIFY(!ct.validateChords(invalidChords));
}

void TestChordTransposer::testSortChords_simple()
{
    ChordTransposer ct;
    QStringList input = {"C", "A", "G", "E"};
    QStringList expected = {"A", "C", "E", "G"};
    QCOMPARE(ct.sortChords(input), expected);
}

void TestChordTransposer::testSortChords_withAccidentals()
{
    ChordTransposer ct;
    QStringList input = {"C#", "C", "Db", "D"};
    QStringList expected = {"C", "C#", "D", "Db"};
    QCOMPARE(ct.sortChords(input), expected);
}

void TestChordTransposer::testSortChords_withSuffixes()
{
    ChordTransposer ct;
    QStringList input = {"Cm", "C", "C#"};
    QStringList expected = {"C", "C#", "Cm"};
    QCOMPARE(ct.sortChords(input), expected);
}

void TestChordTransposer::testHasRepeatedSubstring_true()
{
    ChordTransposer ct;
    QVERIFY(ct.hasRepeatedSubstring("abcabc"));
    QVERIFY(ct.hasRepeatedSubstring("aa"));
    QVERIFY(ct.hasRepeatedSubstring("C C"));
}

void TestChordTransposer::testHasRepeatedSubstring_false()
{
    ChordTransposer ct;
    QVERIFY(!ct.hasRepeatedSubstring("abca"));
    QVERIFY(!ct.hasRepeatedSubstring("abc"));
    QVERIFY(!ct.hasRepeatedSubstring("C D"));
}

void TestChordTransposer::testTransposeChord_simple()
{
    ChordTransposer ct;
    QCOMPARE(ct.transposeChord("C", 1), QString("C#"));
    QCOMPARE(ct.transposeChord("C", -1), QString("B"));
    QCOMPARE(ct.transposeChord("C", 12), QString("C"));
}

void TestChordTransposer::testTransposeChord_withSuffixes()
{
    ChordTransposer ct;
    QCOMPARE(ct.transposeChord("C#m7", 1), QString("Dm7"));
    QCOMPARE(ct.transposeChord("Bb", 2), QString("C"));
}

void TestChordTransposer::testTransposeChord_flats()
{
    ChordTransposer ct;
    QCOMPARE(ct.transposeChord("Gb", -1), QString("F"));
}

void TestChordTransposer::testTransposeChords_normal()
{
    ChordTransposer ct;
    QStringList input = {"C", "Am", "F"};
    QStringList expected = {"D", "Bm", "G"};
    QCOMPARE(ct.transposeChords(input, 2), expected);
}

void TestChordTransposer::testTransposeChords_repeatedPattern()
{
    ChordTransposer ct;
    QStringList input = {"C", "C", "C"};
    QStringList expected = {"D", "D", "D"};
    QCOMPARE(ct.transposeChords(input, 2), expected);
}

void TestChordTransposer::testBinarySearch_found()
{
    ChordTransposer ct;
    QStringList sorted = {"A", "C", "E", "G"};
    QVERIFY(ct.binarySearch(sorted, "C"));
}

void TestChordTransposer::testBinarySearch_notFound()
{
    ChordTransposer ct;
    QStringList sorted = {"A", "C", "E", "G"};
    QVERIFY(!ct.binarySearch(sorted, "B"));
}

void TestChordTransposer::testBinarySearch_emptyList()
{
    ChordTransposer ct;
    QStringList sorted;
    QVERIFY(!ct.binarySearch(sorted, "C"));
}

void TestChordTransposer::testBinarySearch_singleElement()
{
    ChordTransposer ct;
    QStringList sorted = {"C"};
    QVERIFY(ct.binarySearch(sorted, "C"));
    QVERIFY(!ct.binarySearch(sorted, "D"));
}

QTEST_MAIN(TestChordTransposer)
#include "test_chordtransposer.moc"