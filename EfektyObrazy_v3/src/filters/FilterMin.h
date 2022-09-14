#ifndef FILTERMIN_H
#define FILTERMIN_H

#include <vector>
#include "Filter.h"

class FilterMin : public Filter
{
    public:
        FilterMin(): Filter("Min") {}
        FilterMin(int size): Filter(size, "Min") {}

        virtual void use(cv::Mat & img) override
        {
            cv::Mat original = img.clone();

            for (int r = reach(); r < original.rows - reach(); r++)
            {
                for (int c = reach(); c < original.cols - reach(); c++)
                {
                    for (int i = 0; i < original.at<cv::Vec4b>(r, c).channels; i++)
                    {
                        std::vector<int>vec;
                        for (int p = 0 - reach(); p <= reach(); p++)
                        {
                            if (r - p<0 || r + p>=original.rows) { break; }
                            for (int o = 0 - (reach()); o <= reach(); o++)
                            {
                                if (c - o<0 || c + o>=original.cols) { break; }
                                vec.push_back(at(p + reach(), o + reach()) * original.at<cv::Vec4b>(r + o, c + p)[i]);
                            }
                        }
                        sort(vec.begin(), vec.end());
                        int am = vec.front();
                        if (am < 0) { am = 256 - am; }
                        img.at<cv::Vec4b>(r, c)[i] = am;
                        vec.clear();
                    }

                }
            }
        }
};

#endif // FILTERMIN_H
