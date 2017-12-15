//
// Created by Талгат on 27.11.2017.
//
#pragma once

#include <vector>
#include <algorithm>
#include "face3D.h"
using std::vector;
using std::sort;
using std::pair;

class convex_hull_builder
{
public:
    convex_hull_builder(){}
    convex_hull_builder(const convex_hull_builder& another):
    points_set(another.points_set),
    points_num(another.points_num),
    faces_num(another.faces_num),
    degree_list_graph(another.degree_list_graph)
    {}

    convex_hull_builder(const vector<point3D>& points):
            points_num(static_cast<short>(points.size())),
            faces_num(0)
        {
            points_set = points;
            degree_list_graph.assign(points.size(), vector<char>(points.size(), 0) );
        }


    convex_hull_builder(short n, const vector<point3D>& points):
            points_num(n),
            faces_num(0),
            points_set(points)
        {
            degree_list_graph.resize(n-1);
            for(int i=0;i<n-1;++i)
                degree_list_graph[i] = vector<char>(n - i - 1,0);
        }


    bool build();
    short get_points_num()const;
    short get_faces_num()const;

    face3D get_face_by_index(short i)const;
    vector<face3D> faces;
private:
    short points_num;
    vector<point3D> points_set;
    short faces_num;
    vector<vector<char>> degree_list_graph;

    struct upd_edge
    {
        short a;
        short b;

        upd_edge(const short &f, const short &s) :
                a(f),
                b(s)
        {}
        upd_edge(){}
    };
    vector<upd_edge> current_updated_edges;


    face3D build_face(const short& p1_ind, const short& p2_ind, const short& p3_ind, const short& outface_point);
    void add_vert_to_graph_by_face(const face3D &face);
    void delete_vert_from_graph_by_face(const face3D& face);
    void add_first_points();


    void incr_degree_in_graph(int a, int b);
    void decr_degree_in_graph(int a, int b);
    char get_degree(int a, int b);

};

