#ifndef FILTERADD_H
#define FILTERADD_H

#include <vector>
#include "Filter.h"

class FilterAdd : public Filter
{
    protected:
        int m_red = 0;
        int m_green = 0;
        int m_blue = 0;

    public:
        /**
         * Tworzy filtr podstawowy
         * @brief FilterAdd
         * @param rv kolor czerowny
         * @param gv kolor zielony
         * @param bv kolor niebieski
        */
        FilterAdd(int rv, int gv, int bv): Filter(1, "Add"), m_red(rv), m_green(gv), m_blue(bv) {}

        virtual void use(cv::Mat & img) override
        {
            cv::Mat original = img.clone();

            for (int r = 0; r < original.rows; r++)
            {
                for (int c = 0; c < original.cols; c++)
                {
                    for (int i = 0; i < original.at<cv::Vec4b>(r, c).channels; i++)
                    {
                        if (i == 0)
                            img.at<cv::Vec4b>(r, c)[i] = original.at<cv::Vec4b>(r, c)[i] + m_red;
                        if (i == 1)
                            img.at<cv::Vec4b>(r, c)[i] = original.at<cv::Vec4b>(r, c)[i] + m_green;
                        if (i == 2)
                            img.at<cv::Vec4b>(r, c)[i] = original.at<cv::Vec4b>(r, c)[i] + m_blue;
                        if (img.at<cv::Vec4b>(r, c)[i] < 0)
                            img.at<cv::Vec4b>(r, c)[i] = 256 - img.at<cv::Vec4b>(r, c)[i];
                    }

                }
            }
        }
};

#endif // FILTERADD_H
