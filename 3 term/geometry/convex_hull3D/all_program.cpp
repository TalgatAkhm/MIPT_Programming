//
// Created by Талгат on 30.11.2017.
//
#include <vector>
#include <math.h>
#include <algorithm>
#include <utility>
#include <iostream>
#include <fstream>
using namespace std;

class point3D
{
public:
    int x;
    int y;
    int z;

    point3D() : x(0), y(0), z(0)
    {}

    point3D(int a, int b, int c) :
            x(a),
            y(b),
            z(c)
    {}

    point3D(const point3D& another):
            x(another.x),
            y(another.y),
            z(another.z){}


    point3D operator=(const point3D &another);

    point3D operator*(const double &c);

    point3D operator+(const point3D &another);

    point3D operator-();

    bool operator==(const point3D& another);

    point3D minus(const point3D& another) const;

};




point3D point3D::operator*(const double &c)
{
    return point3D(x * c, y * c, z * c);
}

point3D point3D::operator+(const point3D &another)
{
    return point3D(x + another.x, y + another.y, z + another.z);
}

point3D point3D::operator-()
{
    return point3D(-x, -y, -z);
}


point3D point3D::operator=(const point3D &another)
{
    point3D res(another.x, another.y, another.z);
    x = another.x;
    y = another.y;
    z = another.z;
    return res;
}

point3D point3D::minus(const point3D &another) const
{
    point3D res;
    res.x = x - another.x;
    res.y = y - another.y;
    res.z = z - another.z;
    return res;
}




bool point3D::operator==(const point3D &another)
{
    return (x == another.x && y == another.y && z == another.z);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





class vector3D
{
public:

    vector3D(){}


    vector3D( const point3D& vector_coordinate_ex ) :
            vector_coordinate( vector_coordinate_ex )
    {}

    double operator*(const vector3D& another);
    vector3D operator*(const double& c);
    vector3D operator+(const vector3D& another);
    vector3D operator-();
    vector3D operator-(const vector3D& another);
    bool operator==(const vector3D & another);

    double normalize( );

    vector3D product(const vector3D& first, const vector3D& second);
    vector3D product(const vector3D& another);
    double dot( const vector3D& v1, const vector3D& v2 );
private:

    point3D vector_coordinate;

};


double vector3D::operator*(const vector3D &another)
{
    return dot(vector3D(point3D(vector_coordinate.x,vector_coordinate.y,vector_coordinate.z)), another);
}

vector3D vector3D::operator*(const double &c)
{
    return vector3D(vector_coordinate * c);
}

vector3D vector3D::operator+(const vector3D &another)
{
    return vector3D(vector_coordinate + another.vector_coordinate);
}


vector3D vector3D::operator-(const vector3D &another)
{
    vector3D res(vector_coordinate.minus(another.vector_coordinate));
    return res;
}

double vector3D::normalize()
{
    return sqrt(dot(*this, *this));
}

bool vector3D::operator==(const vector3D &another)
{
    return (vector_coordinate == another.vector_coordinate);
}


double vector3D::dot(const vector3D &v1, const vector3D &v2)
{
    double dot_x = v1.vector_coordinate.x * v2.vector_coordinate.x;
    double dot_y = v1.vector_coordinate.y * v2.vector_coordinate.y;
    double dot_z = v1.vector_coordinate.z * v2.vector_coordinate.z;
    return (dot_x + dot_y + dot_z);
}

vector3D vector3D::product(const vector3D &first, const vector3D &second)
{
    int det_x = first.vector_coordinate.y * second.vector_coordinate.z -
                first.vector_coordinate.z * second.vector_coordinate.y;

    int det_y = first.vector_coordinate.z * second.vector_coordinate.x -
                first.vector_coordinate.x * second.vector_coordinate.z;

    int det_z = first.vector_coordinate.x * second.vector_coordinate.y -
                first.vector_coordinate.y * second.vector_coordinate.x;

    vector3D res = vector3D(point3D(det_x, det_y, det_z));
    return res;
}

vector3D vector3D::product(const vector3D &another)
{
    return vector3D(product(*this, another));
}

vector3D vector3D::operator-()
{
    return vector3D(-vector_coordinate);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



struct face3D
{
public:
    face3D()
    {}

    face3D(const point3D &p1, const point3D &p2, const point3D &p3,
           const short &point1_ind, const short &point2_ind, const short &point3_ind)
    {
        set_vertex_indexes(p1, p2, p3, point1_ind, point2_ind, point3_ind);
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
        return vertexes[index].first;
    }

    bool operator<(const face3D& another);


    vector<pair<short, point3D>> vertexes;
    vector3D face_external_normal;
};


vector3D face3D::getFace_external_normal() const
{
    return face_external_normal;
}


void face3D::set_vertex_indexes(const point3D &p1, const point3D &p2, const point3D &p3,
                                const short &point1_ind, const short &point2_ind, const short &point3_ind)
{
    vertexes.push_back(std::make_pair(point1_ind, p1));
    vertexes.push_back(std::make_pair(point2_ind, p2));
    vertexes.push_back(std::make_pair(point3_ind, p3));

    vector3D tmp_to_norm1(vertexes[1].second.minus(vertexes[0].second));
    vector3D tmp_to_norm2(vertexes[2].second.minus(vertexes[0].second));

    face_external_normal = tmp_to_norm1.product(tmp_to_norm2);
}


void face3D::check_normal_to_be_external(point3D outface_point)
{
    vector3D way_corrector(outface_point.minus(vertexes[0].second));

    if (way_corrector * face_external_normal > 0)
    {
        face_external_normal = face_external_normal * (-1);

        pair<short, point3D> swap = vertexes[2];
        vertexes[2].first = vertexes[1].first;
        vertexes[2].second = vertexes[1].second;

        vertexes[1].first = swap.first;
        vertexes[1].second = swap.second;
    }
}

bool face3D::operator<(const face3D &another)
{
    if(vertexes[0].first < another.vertexes[0].first)
        return true;
    else if(vertexes[0].first == another.vertexes[0].first && vertexes[1].first < another.vertexes[1].first)
        return true;
    else if(vertexes[0].first == another.vertexes[0].first &&
            vertexes[1].first == another.vertexes[1].first &&
            vertexes[2].first < another.vertexes[2].first)
        return true;

    return false;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




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
            points_num((points.size())),
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
        degree_list_graph.resize(n);
        for(int i=0;i<n;i++)
            degree_list_graph[i] = vector<char>(n - i - 1,0);
    }


    bool build();
    short get_points_num()const;
    short get_faces_num()const;

    face3D get_face_by_index(short i)const;
    vector<face3D> faces;
private:
    int points_num;
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





face3D convex_hull_builder::build_face(const short &p1_ind, const short &p2_ind, const short &p3_ind,
                                       const short &outface_point)
{
    face3D new_face(points_set[p1_ind], points_set[p2_ind], points_set[p3_ind], p1_ind, p2_ind, p3_ind);

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

                //std::cout << "*";
                faces[j] = faces.back();
                --j;
                //faces.clear();
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





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
