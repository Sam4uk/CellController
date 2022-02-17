#pragma once

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QQueue>
#include <QRandomGenerator>
#include <QString>

static int randomBetween(int low, int high, int seed) {
  qsrand(seed);
  return (qrand() % ((high + 1) - low) + low);
}
class CellController : public QObject {
  Q_OBJECT
 public:
  CellController(QObject* parent) : QObject(parent){};
  void run() {
    CellController::Command command{NO_COMMAND};
    for (;;) {
      switch (command) {
        case CHECK_1:
          qDebug() << "CHECK_1";
          command = NO_COMMAND;
          break;

        case CHECK_2: {
          qDebug() << "CHECK_2";
          command = NO_COMMAND;
        } break;

        case OPEN_CELL:
          qDebug() << tasks.head();
          tasks.dequeue();
          command = NO_COMMAND;
          break;

        default:  ///< NO_COMMAND
          if (tasks.isEmpty()) {
            if (randomBetween(Command::CHECK_1, Command::CHECK_2,
                              QDateTime::currentMSecsSinceEpoch()) ==
                Command::CHECK_1) {
              command = CHECK_1;
            } else {
              command = CHECK_2;
            }
          }

          else {
            command = OPEN_CELL;
          }
          break;
      }
    }  ///< forever loop end
    return;
  };

 public slots:
  void addTask(const QString& task) { tasks.push_back(task); };

 private:
  enum Command {
    NO_COMMAND,
    CHECK_1,
    CHECK_2,
    OPEN_CELL,
  };

  QQueue<QString> tasks;
};
