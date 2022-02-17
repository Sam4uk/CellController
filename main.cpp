#include <QCoreApplication>
#include <QtTest/QTest>
#include <thread>

#include "CellController.hpp"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  CellController df(nullptr);

  df.addTask("TEST TASK1");
  //  df.run();
  std::thread loop([&]() { df.run(); });
  std::thread adds([&]() {
    for (auto i{0}; i < 25; i++) {
      df.addTask("NEW_TASK");
      QTest::qWait(2000);
    }
  });
  loop.detach();
  adds.join();
  //  QThread loop(df.run);
  df.addTask("TEST TASK2");
  return a.exec();
}
