#pragma once

#include <iostream>
#include <fstream>
#include "convex_hull_builder.h"

using namespace std;

int main()
{
    int m;
    ifstream in("input.txt");
    ofstream out("output.txt");
    cin >> m;
    int n = 0;
    vector<point3D> points;
    short a = 0, b = 0, c = 0;
    face3D res;
    for (short i = 0; i < m; ++i)
    {
        cin >> n;
        for (int j = 0; j < n; ++j)
        {
            cin >> a >> b >> c;
            points.emplace_back(point3D(a, b, c));
        }
        convex_hull_builder builder(static_cast<short>(n), points);
        points.clear();
        builder.build();
        out << builder.get_faces_num() << std::endl;

        const int FACES_NUM = builder.faces.size();
        for (int j = 0; j < builder.faces.size(); ++j)
        {
            out << "3 ";
            auto res = builder.get_face_by_index(j);
            out << res[0] << " " << res[1] << " " << res[2] << endl;
        }

    }

    in.close();
    out.close();

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}