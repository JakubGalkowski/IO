#ifndef FILTERMEDIAN_H
#define FILTERMEDIAN_H

#include <vector>
#include "Filter.h"

class FilterMedian : public Filter
{
    public:
        FilterMedian(): Filter("Median") {}
        FilterMedian(int size): Filter(size, "Median") {}

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
                            //if (r - p<0 || r + p>original.rows) { break; }
                            for (int o = 0 - (reach()); o <= reach(); o++)
                            {
                                //if (c - o<0 || c + o>original.cols) { break; }
                                vec.push_back(at(p + reach(), o + reach()) * original.at<cv::Vec4b>(r + o, c + p)[i]);
                            }
                        }
                        sort(vec.begin(),vec.end());
                        int am = vec.at(floor(vec.size()/2));
                        if (am < 0) { am = 256 - am; }
                        img.at<cv::Vec4b>(r, c)[i] = am;
                        vec.clear();
                    }

                }
            }
        }
};

#endif // FILTERMEDIAN_H
