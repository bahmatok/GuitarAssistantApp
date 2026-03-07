TEMPLATE = subdirs
SUBDIRS = \
    test_chordtransposer \
    test_timer \
    test_ticker \
    test_tuner \
    test_mainwindow

check.target = check
check.commands = \
    cd test_chordtransposer && ./test_chordtransposer && \
    cd ../test_timer && ./test_timer && \
    cd ../test_ticker && ./test_ticker && \
    cd ../test_tuner && ./test_tuner && \
    cd ../test_mainwindow && ./test_mainwindow
QMAKE_EXTRA_TARGETS += check