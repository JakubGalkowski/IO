#ifndef FILTERINVERT_H
#define FILTERINVERT_H

#include <vector>
#include "Filter.h"

class FilterInvert : public Filter
{
    public:
        FilterInvert(): Filter(1, "Invert"){}

        virtual void use(cv::Mat & img) override
        {
            for (int x = 0; x < img.cols; ++x) {
                for (int y = 0; y < img.rows; ++y) {
                    auto & pixel = img.at<cv::Vec4b>(y,x);
                    pixel = cv::Vec4b(255,255,255,255) - pixel;
                }
            }
        }
};


#endif // FILTERINVERT_H
