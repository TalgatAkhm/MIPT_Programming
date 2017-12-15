//
// Created by Талгат on 27.11.2017.
//
#include "vector3D.h"
#include <algorithm>
#include <math.h>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

struct face3D
{
public:
    face3D()
    {}

    face3D(const point3D &p1, const point3D &p2, const point3D &p3,
           const short &point1_ind, const short &point2_ind, const short &point3_ind
    const point3D& outface_point)
    {
        set_vertex_indexes(p1, p2, p3, point1_ind, point2_ind, point3_ind);
        vector3D onface1(p2 - p1);
        vector3D onface2(p3 - p1);

        face_external_normal = onface1.product(onface2);
    }

    vector3D getFace_external_normal() const;

    void set_face_external_normal(const vector3D &face_external_normal);

    const short *getVertex_indexes() const;

    void set_vertex_indexes(const point3D &p1, const point3D &p2, const point3D &p3,
                            const short &point1_ind, const short &point2_ind, const short &point3_ind);

    //bool vert_comparator(const pair<short, point3D>& v1, const pair<short, point3D>& v2);

    void check_normal_to_be_external(point3D outface_point);


    int operator[](const int& index) const
    {
        return vertexes[index];
    }

    bool operator<(const face3D& another);


    vector<short> vertexes;
    vector3D face_external_normal;
};


