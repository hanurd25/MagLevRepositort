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

void printCSVValues(const std::vector<std::string>& values) {
    for (size_t i = 0; i < values.size(); ++i) {
        std::cout << "Value " << i + 1 << ": " << values[i] << std::endl;
    }
}

std::vector<std::string> splitCSV(const std::string& line, char delimiter = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}



int main(int argc, char *argv[]) { //SimpleSerial : https://github.com/dmicha16/simple_serial_port
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Live Plot");

    QCustomPlot *customPlot = new QCustomPlot(&mainWindow);
    mainWindow.setCentralWidget(customPlot);

    customPlot->addGraph();
    customPlot->xAxis->setLabel("Iteration");
    customPlot->yAxis->setLabel("Position");
    //These are the initial ranges for X and Y axis.
    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(-1, 1);

    QVector<double> xData, yData;

    QTimer timer;
    double time = 0.0;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        time += 0.1;
        xData.append(time);
        yData.append(qSin(time));
        customPlot->graph(0)->setData(xData, yData);

        //customPlot->xAxis->setRange(time - 10, time);
        customPlot->xAxis->setRange(0, time);

        customPlot->replot();
    });

    timer.start(50);
    mainWindow.resize(800, 600);
    mainWindow.show();

    return app.exec();
}
