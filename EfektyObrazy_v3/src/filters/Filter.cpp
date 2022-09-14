#include "Filter.h"

Filter::Filter(std::string name) : Filter(3, name) {};

Filter::Filter(int size, std::string name) :
    Action(name),
    m_size(std::abs(size)),
    m_reach(abs(std::floor(size / 2))),
    m_matrix( new double * [std::abs(size)])
{
    for (int i = 0; i < m_size; ++i) {
        m_matrix[i] = new double[m_size];
    }

    fill(1);
    assert(size % 2 != 0 && size >= 1);
};

Filter::~Filter()
{
    for (int i = 0; i < m_size; ++i)
    {
        delete [] m_matrix[i];
    }
    delete [] m_matrix;
};


double Filter::calcK()
{
    double sum = 0;
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            sum += m_matrix[i][j];
        }
    }
    if (sum == 0) { return 1; }
    return sum;
}

int Filter::size() const
{
    return m_size;
}

int Filter::reach() const
{
    return m_reach;
}

double Filter::at(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_size || y >= m_size)
    {
//            cout << "\nYou are trying to retrieve wrong coordinates! Returning default value" << endl;
        return 1;
    }

    return m_matrix[x][y];
}

void Filter::fill(double v)
{
    for (int i = 0; i < m_size; i++)
    {
        for (int j = 0; j < m_size; j++)
        {
            m_matrix[i][j] = v;
        }
    }
}

void Filter::set(double v, int x, int y)
{
    if (x < 0 || y < 0 || x >= m_size || y >= m_size)
    {
//            cout << "\nYou are trying to retrieve wrong coordinates! Returning default value" << endl;
        return;
    }

    m_matrix[x][y] = v;
}

void Filter::setSize(int s)
{
    m_size = s;
    setReach(std::floor(s/2));
}

void Filter::setReach(int r)
{
    m_reach= r;
}

void Filter::use(cv::Mat & img)
{
    cv::Mat original = img.clone();

    for (int r = reach(); r < original.rows - reach(); r++)
    {
        for (int c = reach(); c < original.cols - reach(); c++)
        {
            for (int i = 0; i < original.at<cv::Vec4b>(r, c).channels; i++)
            {
                double suma = 0;
                for (int p = 0 - reach(); p <= reach(); p++)
                {
                    //if (r - p<0 || r + p>original.rows) { break; }
                    for (int o = 0 - (reach()); o <= reach(); o++)
                    {
                        //if (c - o<0 || c + o>original.cols) { break; }
                        suma += at(p + reach(), o + reach()) * original.at<cv::Vec4b>(r + o, c + p)[i];
                    }
                }
                int am = suma / calcK();
                if (am < 0) { am = 256 - am; }
                img.at<cv::Vec4b>(r, c)[i] = am;
            }

        }
    }
}
