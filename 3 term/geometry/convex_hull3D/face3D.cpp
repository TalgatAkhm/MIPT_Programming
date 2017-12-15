//
// Created by Талгат on 27.11.2017.
//

\


#include "face3D.h"


vector3D face3D::getFace_external_normal() const {
    return face_external_normal;
}


void face3D::set_vertex_indexes(const point3D &p1, const point3D &p2, const point3D &p3,
                                const short &point1_ind, const short &point2_ind, const short &point3_ind) {
    vertexes.push_back(point1_ind);
    vertexes.push_back(point2_ind);
    vertexes.push_back(point3_ind);
}


void face3D::check_normal_to_be_external(point3D outface_point) {
    vector3D way_corrector(outface_point.minus(vertexes[0].second));

    if (way_corrector * face_external_normal > 0) {
        face_external_normal = face_external_normal * (-1);

        pair<short, point3D> swap = vertexes[2];
        vertexes[2].first = vertexes[1].first;
        vertexes[2].second = vertexes[1].second;

        vertexes[1].first = swap.first;
        vertexes[1].second = swap.second;
    }
}

bool face3D::operator<(const face3D &another) {
    if (vertexes[0].first < another.vertexes[0].first)
        return true;
    else if (vertexes[0].first == another.vertexes[0].first && vertexes[1].first < another.vertexes[1].first)
        return true;
    else if (vertexes[0].first == another.vertexes[0].first &&
             vertexes[1].first == another.vertexes[1].first &&
             vertexes[2].first < another.vertexes[2].first)
        return true;

    return false;
}




