//
// Created by Талгат on 27.11.2017.
//

#include "convex_hull_builder.h"
#include <iostream>
#include <unordered_set>
#include <utility>

using std::min;
using std::max;

face3D convex_hull_builder::build_face(const short &p1_ind, const short &p2_ind, const short &p3_ind,
                                       const short &outface_point)
{
    face3D new_face(points_set[p1_ind], points_set[p2_ind], points_set[p3_ind], p1_ind, p2_ind, p3_ind, outface_point);

    new_face.check_normal_to_be_external(points_set[outface_point]);
    add_vert_to_graph_by_face(new_face);

    faces.push_back(new_face);
    ++faces_num;
    return face3D();
}

void convex_hull_builder::add_vert_to_graph_by_face(const face3D &face)
{
    incr_degree_in_graph(face[0], face[1]);
    incr_degree_in_graph(face[0], face[2]);
    incr_degree_in_graph(face[1], face[2]);
}

bool convex_hull_builder::build()
{
    //build a small hull with 4 points
    short FIRST_POINTS_NUM = 4;
    int POINTS_NUM = points_set.size();
    add_first_points();

    //vector<upd_edge> current_updated_edges;

    for (int i = FIRST_POINTS_NUM; i < points_set.size(); ++i)
    {
        //vector<upd_edge> current_updated_edges;
        for (int j = 0; j < faces.size(); ++j)
        {
            face3D current_face = faces[j];
            vector3D radius_vec_to_another_face(points_set[i].minus(points_set[current_face[0]]));

            if (current_face.face_external_normal * radius_vec_to_another_face > 0)
            {
                delete_vert_from_graph_by_face(current_face);
                faces[j] = faces.back();
                --j;
                faces.resize(faces.size() - 1);
                --faces_num;
            }
        }
        for (int j = 0; j < current_updated_edges.size(); ++j)
            if (/*degree_list_graph[current_updated_edges[j].a][current_updated_edges[j].b] == 1*/
                    get_degree(current_updated_edges[j].a, current_updated_edges[j].b) == 1)
            {
                int k = 0;
                while (k == i || k == current_updated_edges[j].a || (k == current_updated_edges[j].b))
                    ++k;

                build_face(current_updated_edges[j].a,
                           /*static_cast<const short &>(current_updated_edges[j].a + current_updated_edges[j].b + 1*/
                current_updated_edges[j].b, i,
                           k);
                //std::cout << "*";
            }
        current_updated_edges.resize(0);

    }
    sort(faces.begin(), faces.end());
    return false;
}

short convex_hull_builder::get_points_num() const
{
    return points_num;
}

short convex_hull_builder::get_faces_num() const
{
    return static_cast<short>(faces.size());
}

face3D convex_hull_builder::get_face_by_index(short i) const
{
    return (faces[i]);
}

void convex_hull_builder::add_first_points()
{

    short FIRST_BASE_POINTS_NUM2 = 4;
    for (int i = 0; i < FIRST_BASE_POINTS_NUM2; i++)
        for (int j = i + 1; j < FIRST_BASE_POINTS_NUM2; j++)
            for (int k = j + 1; k < FIRST_BASE_POINTS_NUM2; k++)
                build_face((i), (j),
                           (k),
                           (FIRST_BASE_POINTS_NUM2 - i - j - k + 1 + 1));

}

void convex_hull_builder::delete_vert_from_graph_by_face(const face3D &current_face)
{

    int p1 = current_face[0], p2 = current_face[1], p3 = current_face[2];
    decr_degree_in_graph(p1, p2);
    decr_degree_in_graph(p2, p3);
    decr_degree_in_graph(p1, p3);

    current_updated_edges.push_back(upd_edge(p1, p2));
    current_updated_edges.push_back(upd_edge(p2, p3));
    current_updated_edges.push_back(upd_edge(p1, p3));
}

void convex_hull_builder::incr_degree_in_graph(int a, int b)
{
    if (a > b)
    {
        std::swap(a, b);
    }
    ++degree_list_graph[a][points_num - b - 1];
}

void convex_hull_builder::decr_degree_in_graph(int a, int b)
{
    if (a > b)
    {
        std::swap(a, b);
    }
    --degree_list_graph[a][points_num - b - 1];

}

char convex_hull_builder::get_degree(int a, int b)
{
    if (a > b)
    {
        std::swap(a, b);
    }
    return degree_list_graph[a][points_num - b - 1];
}
