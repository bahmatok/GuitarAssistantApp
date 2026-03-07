#include "chordtransposer.h"
#include <QRegExp>
#include <QMap>
#include <algorithm>

QStringList ChordTransposer::sortChords(const QStringList &chords) {
    QVector<QString> chordVector = chords.toVector();
    heapSort(chordVector);
    return QStringList::fromVector(chordVector);
}

void ChordTransposer::heapSort(QVector<QString> &chords) {
    int n = chords.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(chords, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        std::swap(chords[0], chords[i]);
        heapify(chords, i, 0);
    }
}

void ChordTransposer::heapify(QVector<QString> &chords, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && chords[left] > chords[largest])
        largest = left;
    if (right < n && chords[right] > chords[largest])
        largest = right;
    if (largest != i) {
        std::swap(chords[i], chords[largest]);
        heapify(chords, n, largest);
    }
}

bool ChordTransposer::validateChords(const QStringList &chords) {
    // Регулярное выражение для аккордов: корень [A-G] с возможным # или b,
    // затем необязательные суффиксы: m, maj, min, dim, aug, sus2, sus4,
    // затем необязательная цифра 7,9,11,13,
    // затем необязательные модификаторы: b5, #5, maj7
    QRegExp validChordPattern(
        "^[A-G][#b]?(m|maj|min|dim|aug|sus2|sus4)?(7|9|11|13)?(b5|#5|maj7)?$"
    );
    for (const QString &chord : chords) {
        if (!validChordPattern.exactMatch(chord)) {
            return false;
        }
    }
    return true;
}

bool ChordTransposer::hasRepeatedSubstring(const QString &input) {
    QString cleaned = input;
    cleaned.remove(' '); // убираем пробелы, оставляем только аккорды
    int n = cleaned.length();
    if (n == 0) return false;

    for (int len = 1; len <= n / 2; ++len) {
        if (n % len != 0) continue; // длина не кратна паттерну
        QString pattern = cleaned.left(len);
        bool repeated = true;
        for (int j = len; j < n; j += len) {
            if (cleaned.mid(j, len) != pattern) {
                repeated = false;
                break;
            }
        }
        if (repeated) return true;
    }
    return false;
}

QStringList ChordTransposer::transposeChords(const QStringList &chords, int transposeInterval) {
    if (hasRepeatedSubstring(chords.join(" "))) {
        return transposeRepeatedSubstrings(chords, transposeInterval);
    } else {
        QStringList transposedChords;
        for (const QString &chord : chords) {
            transposedChords.append(transposeChord(chord, transposeInterval));
        }
        return transposedChords;
    }
}

QStringList ChordTransposer::transposeRepeatedSubstrings(const QStringList &chords, int transposeInterval) {
    int n = chords.size();
    int patternLen = 0;

    // Находим длину повторяющегося паттерна
    for (int p = 1; p <= n / 2; ++p) {
        if (n % p != 0) continue;
        bool ok = true;
        for (int i = p; i < n; ++i) {
            if (chords[i] != chords[i % p]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            patternLen = p;
            break;
        }
    }

    if (patternLen == 0) {
        // Если паттерн не найден (не должно происходить, так как функция вызывается только при hasRepeatedSubstring==true)
        return chords;
    }

    // Транспонируем найденный паттерн
    QStringList transposedPattern;
    for (int i = 0; i < patternLen; ++i) {
        transposedPattern.append(transposeChord(chords[i], transposeInterval));
    }

    // Собираем результат, повторяя транспонированный паттерн
    QStringList result;
    int repeats = n / patternLen;
    for (int r = 0; r < repeats; ++r) {
        result.append(transposedPattern);
    }
    return result;
}

QString ChordTransposer::transposeChord(const QString &chord, int interval) {
    QStringList notes = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    // Соответствие бемолей диезам
    static QMap<QString, QString> flatToSharp = {
        {"Bb", "A#"}, {"Db", "C#"}, {"Eb", "D#"}, {"Gb", "F#"}, {"Ab", "G#"},
        {"Cb", "B"},  {"Fb", "E"}
    };

    // Выделяем корневую ноту (первый символ и возможно второй, если это # или b)
    QString rootNote;
    if (chord.length() > 1 && (chord[1] == '#' || chord[1] == 'b')) {
        rootNote = chord.left(2);
    } else {
        rootNote = chord.left(1);
    }
    QString suffix = chord.mid(rootNote.length());

    // Преобразуем бемоль в диез
    if (flatToSharp.contains(rootNote)) {
        rootNote = flatToSharp[rootNote];
    }

    int noteIndex = notes.indexOf(rootNote);
    if (noteIndex == -1) {
        return chord;
    }

    int newIndex = (noteIndex + interval + notes.size()) % notes.size();
    QString newChord = notes[newIndex] + suffix;
    return newChord;
}

bool ChordTransposer::binarySearch(const QStringList &sortedChords, const QString &chord) {
    int left = 0;
    int right = sortedChords.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedChords[mid] == chord) {
            return true;
        } else if (sortedChords[mid] < chord) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}