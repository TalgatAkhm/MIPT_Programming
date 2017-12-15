#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


struct point
{
    double x;
    double y;

    point()
    {}

    point(const double &a, const double &b) :
            x(a),
            y(b)
    {}

    point operator+(const point &another)
    {
        return point(x + another.x, y + another.y);
    }
};


double distance(const point &p1, const point &p2)
{
    double res = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    return res;
}

void sort_by_y_coordinate(std::vector<point> &to_sort)
{
    double min_y = to_sort[0].y;
    double min_x = to_sort[0].x;

    int index_of_min_x = 0;
    const int TO_SORT_SIZE = to_sort.size();

    for (int i = 1; i < TO_SORT_SIZE; ++i)
    {
        if (to_sort[i].y < min_y)
        {
            min_y = to_sort[i].y;
            min_x = to_sort[i].x;

        }
    }
    for (int i = 0; (i < TO_SORT_SIZE); ++i)
    {
        if (to_sort[i].x <= min_x && (to_sort[i].y == min_y))
        {
            min_x = to_sort[i].x;
            index_of_min_x = i;
        }
    }

    std::vector<point> res(TO_SORT_SIZE);
    int j = 0;
    for (int i = index_of_min_x; i < TO_SORT_SIZE; ++i, ++j)
        res[j] = to_sort[i];

    for (int i = 0; i < index_of_min_x; ++i, ++j)
        res[j] = to_sort[i];
    to_sort = res;
}


double angel_segment_and_x_axis(const point &begin, const point &end)
{
    const double PI_APROXIMATED = 3.1416;
    double angle_acos = std::acos((end.x - begin.x)/sqrt(pow(end.x-begin.x,2) + pow(end.y-begin.y,2)));

    if((begin.y - end.y) > 0)
        return angle_acos + 2 * PI_APROXIMATED;
    return angle_acos;
}

double rotate(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}


bool intersect(point a, point b, point c, point d)
{
    return (rotate(a, b, c) * rotate(a, b, d) < 0) && (rotate(c, d, a) * rotate(c, d, b) < 0);
}


void calculate_minkovsi_sum(vector<point> &first, vector<point> &second, std::vector<point> &minkovski)
{
    int i = 0;
    int j = 0;

    int first_size = first.size();
    int second_size = second.size();

    first.push_back(first[0]);
    first.push_back(first[1]);
    second.push_back(second[0]);
    second.push_back(second[1]);

    while (i <= first_size && j <= second_size)
    {
        minkovski.push_back(first[i] + second[j]);

        if (angel_segment_and_x_axis(first[i], first[(i + 1)])
            < angel_segment_and_x_axis(second[j], second[j + 1]))
        {
            ++i;
        } else if (angel_segment_and_x_axis(first[i], first[i + 1])
                   > angel_segment_and_x_axis(second[j], second[j + 1]))
        {
            ++j;
        } else
        {
            ++i, ++j;
        }
    }

}




void binary_search_to_check_intersect(int &left, int &right, const vector<point>& another, const point &p)
{
    while (right - left > 1)
    {
        int middle = (left + right) / 2;
        if (rotate(another[0], another[middle], p) < 0)
        {
            right = middle;
        } else
        {
            left = middle;
        }
    }
}



bool is_inside_polygon(const point &p, const vector<point>  &another)
{
    if (rotate(another[0], another[1], p) == 0)
    {
        if (distance(p, another[0]) > distance(another[0], another[1]))
        {
            return false;
        }
        else if (distance(another[1], p) > distance(another[0],another[1]))
        {
            return false;
        }
    }

    if (rotate(another[0], another[1], p) < 0)
    {
        return false;
    }
    else if (rotate(another[0], another[another.size() - 1], p) > 0)
    {
        return false;
    }

    int left = 1;
    int right = another.size() - 1;

    binary_search_to_check_intersect(left, right, another, p);
    return !intersect(another[0], p, another[left], another[right]);

}







int main()
{
    int n, m;
    double x, y;
    std::ifstream inp("input.txt");

    inp >> n;

    vector<point> polygon1(n);
    for (int i = 0; i < n; ++i)
    {
        inp >> x >> y;
        polygon1[i] = point(x, y);
    }
    reverse(polygon1.begin(), polygon1.end());
    inp >> m;

    vector<point> polygon2(m);
    for (int i = 0; i < m; ++i)
    {
        inp >> x >> y;
        polygon2[i] = point(-x, -y);
    }
    reverse(polygon2.begin(), polygon2.end());

    inp.close();

    sort_by_y_coordinate(polygon1);
    sort_by_y_coordinate(polygon2);
    vector<point> minkovski;

    calculate_minkovsi_sum(polygon1, polygon2, minkovski);


    point zero(0, 0);
    bool is_inside = is_inside_polygon(zero, minkovski);


    std::cout << (is_inside ? "YES" : "NO") << std::endl;

    return 0;
}