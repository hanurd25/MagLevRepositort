#include <QApplication>
#include <QTimer>
//#include "externals/qt/qcustomplot.h"
//#include <qcustomplot.h>
#include <qcustomplot.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Live Plot");

    QCustomPlot *customPlot = new QCustomPlot(&mainWindow);
    mainWindow.setCentralWidget(customPlot);

    customPlot->addGraph();
    customPlot->xAxis->setLabel("Iteration");
    customPlot->yAxis->setLabel("Position");
    customPlot->xAxis->setRange(0, 10);  // Initial range for x-axis
    customPlot->yAxis->setRange(-1, 1);  // Initial range for y-axis

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
