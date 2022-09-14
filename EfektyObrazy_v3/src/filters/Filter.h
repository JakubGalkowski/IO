#ifndef FILTER_H
#define FILTER_H

#include "../Action.h"
#include <opencv2/opencv.hpp>

class Filter: public Action
{
public:
    Filter(std::string name);

    Filter(int size, std::string name);

    virtual ~Filter();

public:
    virtual void use(cv::Mat & img);

    double calcK();

    int size() const;

    int reach() const;

    double at(int x, int y);

    void fill(double v);

    void set(double v, int x, int y);

    void setSize(int s);

    void setReach(int r);


protected:
    int m_size;
    int m_reach;

    double** m_matrix;


};

#endif // FILTER_H
