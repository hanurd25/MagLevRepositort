#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <vector>


int main() {
    int cameraPort = 1; // Replace with the correct port number

    // Open the camera
    cv::VideoCapture cap(cameraPort);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera on port " << cameraPort << std::endl;
        return -1;
    }

    std::cout << "Camera opened on port " << cameraPort << ". Press ESC to exit." << std::endl;

    cv::Mat frame;
    while (true) {
        // Capture a frame
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            break;
        }

        // Reduce contrast
        cv::Mat contrastReducedFrame;
        double alpha = 0.5; // Contrast factor (0.0 to 1.0). Lower values reduce contrast.
        int beta = 0;       // Brightness offset. Leave as 0 for now.
        frame.convertTo(contrastReducedFrame, -1, alpha, beta); // Apply contrast adjustment

        // Apply Gaussian blur to the contrast-reduced frame
        cv::Mat blurredFrame;
        cv::GaussianBlur(contrastReducedFrame, blurredFrame, cv::Size(9, 9), 0); // Kernel size = 9x9, sigmaX = 0

        // Create a circular mask
        cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8UC1);
        cv::Point maskCenter(frame.cols / 2 + 10, frame.rows / 2 - 25); // Center of the circle
        int maskRadius = std::min(frame.cols, frame.rows) / 6.2;        // Radius of the circle
        cv::circle(mask, maskCenter, maskRadius, cv::Scalar(255), -1); // Draw filled circle on the mask

        // Apply the mask to the blurred frame
        cv::Mat maskedFrame;
        blurredFrame.copyTo(maskedFrame, mask); // Copy only the region inside the mask

        // Perform Canny edge detection on the masked frame
        cv::Mat edges;
        //identifying edges inside the masked frame.
        cv::Canny(maskedFrame, edges, 100, 200); // Adjust thresholds as needed

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            // Fit an ellipse only if the contour has enough points
            if (contours[i].size() >= 5) {
                cv::RotatedRect ellipse = cv::fitEllipse(contours[i]);

                // Check if the ellipse center is inside the circular mask
                cv::Point2f ellipseCenter = ellipse.center;
                double distanceFromMaskCenter = cv::norm(ellipseCenter - cv::Point2f(maskCenter));

                if (distanceFromMaskCenter <= maskRadius) { // Center must fall inside the mask radius
                    // Filter ellipses by size
                    if (ellipse.size.width > 20 && ellipse.size.height > 20 &&
                        ellipse.size.width < 150 && ellipse.size.height < 150) {
                        // Draw the ellipse on the original frame
                        cv::ellipse(frame, ellipse, cv::Scalar(0, 255, 0), 2); // Green ellipse

                        // Get the (x, y) coordinates of the center
                        int x = cvRound(ellipse.center.x);
                        int y = cvRound(ellipse.center.y);

                        // Print the coordinates to the console
                        std::cout << "Ellipse Center: (" << x << ", " << y << ")" << std::endl;

                        // Draw the coordinates on the interface
                        std::string text = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
                        cv::putText(frame, text, cv::Point(x + 10, y - 10), // Slight offset to avoid overlapping the ellipse
                                    cv::FONT_HERSHEY_SIMPLEX, 0.5,           // Font and scale
                                    cv::Scalar(255, 0, 0), 2);               // Blue color, thickness 2

                        cv::circle(frame, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1); // Red dot, radius 5
                    }
                }
            }
        }

        // Display the original frame with ellipses and coordinates drawn
        //
        cv::imshow("Blurred frame",blurredFrame);
        cv::imshow("Masked frame", maskedFrame);
        cv::imshow("Detected Ellipses", frame);
        cv::imshow("Edges", edges);

        // Break the loop if ESC key is pressed
        if (cv::waitKey(1) == 27) { // 27 is the ASCII code for ESC
            std::cout << "Exiting live video feed." << std::endl;
            break;
        }
    }

    // Release the camera and close OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}




/*
int main() {
    int cameraPort = 1; // Replace with the correct port number

    // Open the camera
    cv::VideoCapture cap(cameraPort);
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera on port " << cameraPort << std::endl;
        return -1;
    }

    std::cout << "Camera opened on port " << cameraPort << ". Press ESC to exit." << std::endl;

    cv::Mat frame;
    while (true) {
        // Capture a frame
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            break;
        }

        // Reduce contrast
        cv::Mat contrastReducedFrame;
        double alpha = 0.5; // Contrast factor (0.0 to 1.0). Lower values reduce contrast.
        int beta = 0;       // Brightness offset. Leave as 0 for now.
        frame.convertTo(contrastReducedFrame, -1, alpha, beta); // Apply contrast adjustment

        // Apply Gaussian blur to the contrast-reduced frame
        cv::Mat blurredFrame;
        cv::GaussianBlur(contrastReducedFrame, blurredFrame, cv::Size(9, 9), 0); // Kernel size = 9x9, sigmaX = 0

        // Create a circular mask
        cv::Mat mask = cv::Mat::zeros(frame.size(), CV_8UC1);
        cv::Point center(frame.cols / 2 + 10, frame.rows / 2 - 25); // Center of the circle
        int maskRadius = std::min(frame.cols, frame.rows) / 6.2;    // Radius of the circle
        cv::circle(mask, center, maskRadius, cv::Scalar(255), -1); // Draw filled circle on the mask

        // Apply the mask to the blurred frame
        cv::Mat maskedFrame;
        blurredFrame.copyTo(maskedFrame, mask); // Copy only the region inside the mask

        // Perform Canny edge detection on the masked frame
        cv::Mat edges;
        cv::Canny(maskedFrame, edges, 100, 200); // Adjust thresholds as needed

        // Display the original frame, contrast-reduced frame, blurred frame, masked frame, and edges
        cv::imshow("Live Video Feed (Original)", frame);
        cv::imshow("Contrast Reduced Frame", contrastReducedFrame);
        cv::imshow("Blurred Frame", blurredFrame);
        cv::imshow("Masked Frame", maskedFrame);
        cv::imshow("Canny Edges", edges);

        // Break the loop if ESC key is pressed
        if (cv::waitKey(1) == 27) { // 27 is the ASCII code for ESC
            std::cout << "Exiting live video feed." << std::endl;
            break;
        }
    }

    // Release the camera and close OpenCV windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
*/
