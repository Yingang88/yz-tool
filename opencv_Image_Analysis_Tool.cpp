namespace Image_Analysis_Tool
{
    /*Finds the global minimum and maximum in an array and calculates a mean and standard deviation of array elements.*/
    bool minMaxLoc_meanStdDev(cv::Mat &image)
    {
        if (image.empty())
        {
            std::cerr << "Image is empty!" << std::endl;
            return false;
        }

        cv::Mat mean, stddev;
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        int ch = image.channels();

        if (1 == ch)
        {
            minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
            meanStdDev(image, mean, stddev);
        }
        else
        {
            cv::Mat gray;
            cv::cvtColor(image, gray, COLOR_BGR2GRAY);
            minMaxLoc(gray, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
            meanStdDev(image, mean, stddev);
        }
        std::cout << "There are " << ch << " channels of input image." << std::endl;
        std::cout << "minimum value: " << minVal << "\tminimum location: " << minLoc << std::endl;
        std::cout << "maximum value: " << maxVal << "\tmaximum location: " << maxLoc << "\n"
                  << std::endl;
        for (int i = 0; i < ch; ++i)
        {
            std::cout << "Channel " << i << " : " << endl;
            std::cout << "mean value: " << mean.at<double>(i) << "\tstandard deviation: " << stddev.at<double>(i) << "\n"
                      << std::endl;
        }
        return true;
    }

    /****This is an overloaded member function****/
    bool minMaxLoc_meanStdDev(cv::Mat &image, cv::Mat &mask)
    {
        if (image.empty())
        {
            std::cerr << "Image is empty!" << std::endl;
            return false;
        }

        cv::Mat mean, stddev;
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        int ch = image.channels();

        if (1 == ch)
        {
            minMaxLoc(image, &minVal, &maxVal, &minLoc, &maxLoc, mask);
            meanStdDev(image, mean, stddev);
        }
        else
        {
            cv::Mat gray;
            cv::cvtColor(image, gray, COLOR_BGR2GRAY);
            minMaxLoc(gray, &minVal, &maxVal, &minLoc, &maxLoc, mask);
            meanStdDev(image, mean, stddev);
        }
        std::cout << "There are " << ch << " channels of input image." << std::endl;
        std::cout << "minimum value: " << minVal << "\tminimum location: " << minLoc << std::endl;
        std::cout << "maximum value: " << maxVal << "\tmaximum location: " << maxLoc << "\n"
                  << std::endl;
        for (int i = 0; i < ch; ++i)
        {
            std::cout << "Channel " << i << " : " << endl;
            std::cout << "mean value: " << mean.at<double>(i) << "\tstandard deviation: " << stddev.at<double>(i) << "\n"
                      << std::endl;
        }
        return true;
    }
    /*********************************************/
} // namespace Image_Analysis_Tool