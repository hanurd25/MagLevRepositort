#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QStringList>
#include <qcustomplot.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "serial/serial.h"
#include <rapidcsv.h>

// Function to split CSV lines
std::vector<std::string> splitCSV(const std::string& line, char delimiter = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


bool plot = false;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Live Serial Plot");

    // Create a plotting widget
    QCustomPlot *customPlot = new QCustomPlot(&mainWindow);
    mainWindow.setCentralWidget(customPlot);

    // Add 3 graphs for X, Y, Z
    customPlot->addGraph(); customPlot->graph(0)->setPen(QPen(Qt::red));   // X Data (Red)
    customPlot->addGraph(); customPlot->graph(1)->setPen(QPen(Qt::blue));  // Y Data (Blue)
    customPlot->addGraph(); customPlot->graph(2)->setPen(QPen(Qt::green)); // Z Data (Green)

    customPlot->xAxis->setLabel("Time");
    customPlot->yAxis->setLabel("Sensor Values");
    customPlot->xAxis->setRange(0, 10);
    customPlot->yAxis->setRange(-2, 2);

    QVector<double> timeData, xData, yData, zData;
    double time = 0.0;

    // Open Serial Port
    serial::Serial mySerial("COM12", 9600, serial::Timeout::simpleTimeout(100));


    std::ofstream csvFile("CSVData/HallEffectData/hallEffectData1.CSV");
    if (plot) {
        csvFile << "Time,X,Y,Z\n";  // Write CSV header
    }
    // Timer for real-time update
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        time += 0.1;

        if (mySerial.available()) {
            std::string line = mySerial.readline();
            auto values = splitCSV(line);

            if (values.size() == 3) {
                try {
                    double valX = std::stod(values[0]);
                    double valY = std::stod(values[1]);
                    double valZ = std::stod(values[2]);

                    timeData.append(time);
                    xData.append(valX);
                    yData.append(valY);
                    zData.append(valZ);

                    customPlot->graph(0)->setData(timeData, xData);
                    customPlot->graph(1)->setData(timeData, yData);
                    customPlot->graph(2)->setData(timeData, zData);
                    customPlot->xAxis->setRange(qMax(0.0, time - 10), time);
                    customPlot->replot();

                    // Save to CSV
                    if (plot) {
                        csvFile << time << "," << valX << "," << valY << "," << valZ << "\n";
                    }
                } catch (...) {
                    std::cerr << "Error parsing CSV values\n";
                }
            }
        }
    });

    // Start the timer (update every 5ms)
    timer.start(5);

    mainWindow.resize(800, 600);
    mainWindow.show();

    int result = app.exec();

    // Close CSV file
    csvFile.close();
    return result;
}