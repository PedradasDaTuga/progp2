#include "elements.hpp"

namespace svg {
    ellipse::ellipse(const svg::color &fill,
                     const point &center,
                     const point &radius) :
            shape(fill), center(center), radius(radius) {

    }
    void ellipse::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }
    void ellipse::translate(const point &t) {
        center = center.translate(t);
    }
    void ellipse::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin,v);
    }

    void ellipse::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }
    shape *ellipse::duplicate() const {
        return new ellipse(get_color(), center, radius);
    }

            //###### CIRClE #################
    circle::circle(const svg::color &fill, const point &center, const point &radius): ellipse(fill,center,radius) {

    }
    void circle::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }

            //###### POLYGON #################

    polygon::polygon(const svg::color &fill, const std::vector<point> &ponto) : shape(fill),pontos(ponto){}

    void polygon::draw(png_image &img) const {
        img.draw_polygon(pontos,get_color());
    }


    //###### RECT #################
    rect::rect(const svg::color &color, const std::vector<point> &ponto) : polygon(color,ponto){}

    void rect::draw(png_image &img) const {
        img.draw_polygon(pontos,get_color());
    }


    //###### POLYLINE #################
    polyline::polyline(const svg::color &color, const std::vector<point> &ponto):shape(color),points(ponto) {}
    void polyline::draw(png_image &img) const {
        for(int i=0;i<points.size()-1;i++)
            img.draw_line(points.at(i),points.at(i+1),get_color());
    }

    //###### LINE #################
    line::line(const svg::color &color, const std::vector<point> &ponto): polyline(color,ponto) {

    }
    void line::draw(png_image &img) const {
        img.draw_line(points.at(0),points.at(1),get_color());
    }

}
