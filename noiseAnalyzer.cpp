#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <qcustomplot.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include "serial/serial.h"

std::vector<std::string> splitCSV(const std::string& line, char delimiter = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Live Serial Plot");

    // Create QCustomPlot instance
    QCustomPlot *customPlot = new QCustomPlot(&mainWindow);
    mainWindow.setCentralWidget(customPlot);

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::blue));

    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(Qt::green));

    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Sensor Values");
    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(-2, 2);

    QVector<double> xData, yData1, yData2, yData3;
    double time = 0.0;

    serial::Serial mySerial("COM12", 9600, serial::Timeout::simpleTimeout(100));

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        time += 0.1;

        if (mySerial.available()) {
            std::string line = mySerial.readline();
            auto values = splitCSV(line);

            if (values.size() == 3) {
                try {
                    double val1 = std::stod(values[0]);
                    double val2 = std::stod(values[1]);
                    double val3 = std::stod(values[2]);

                    xData.append(time);
                    yData1.append(val1);
                    yData2.append(val2);
                    yData3.append(val3);


                    customPlot->graph(0)->setData(xData, yData1);
                    customPlot->graph(1)->setData(xData, yData2);
                    customPlot->graph(2)->setData(xData, yData3);

                    //customPlot->xAxis->setRange(qMax(0.0, time - 10), time);
                    customPlot->xAxis->setRange(qMax(0.0, 0.0), time);
                    customPlot->replot();
                } catch (...) {
                    qDebug() << "Error parsing CSV values";
                }
            }
        }
    });
    //updating every 1 ms
    timer.start(5);

    mainWindow.resize(800, 600);
    mainWindow.show();
    return app.exec();
}
