#ifndef FILTERCHANNELMIX_H
#define FILTERCHANNELMIX_H

#include <vector>
#include "Filter.h"

class FilterChannelMix : public Filter
{
    public:
        FilterChannelMix(int ch0, int ch1): Filter(1, "Channel Mix"), m_ch0(ch0), m_ch1(ch1) {
            assert(ch1 < 4 && ch1 >= 0 && ch0 < 4 && ch0 >= 0);
        }

        virtual void use(cv::Mat & img) override
        {
            for (int x = 0; x < img.cols; ++x) {
                for (int y = 0; y < img.rows; ++y) {
                    auto & pixel = img.at<cv::Vec4b>(y,x);

                    auto tmp = pixel[m_ch0];
                    pixel[m_ch0] = pixel[m_ch1];
                    pixel[m_ch1] = tmp;
                }
            }
        }
    protected:
        int m_ch0;
        int m_ch1;
};


#endif // FILTERCHANNELMIX_H
