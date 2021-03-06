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
    void circle::translate(const point &t) {
        center = center.translate(t);
    }
    void circle::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin,v);
    }
    void circle::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }
    shape *circle::duplicate() const {
        return new circle(get_color(),center,radius);
    }
            //###### POLYGON #################

    polygon::polygon(const svg::color &fill, const std::vector<point> &ponto) : shape(fill),pontos(ponto){}

    void polygon::draw(png_image &img) const {
        img.draw_polygon(pontos,get_color());
    }
    void polygon::translate(const point &t) {
        for (auto &itr:pontos){
            itr=itr.translate(t);
        }
    }
    void polygon::scale(const point &origin, int v) {
        for (auto &itr:pontos){
            itr=itr.scale(origin,v);
        }
    }
    void polygon::rotate(const point &origin, int degrees) {
        for (auto &itr:pontos){
            itr=itr.rotate(origin,degrees);
        }
    }
    shape *polygon::duplicate() const {
        return new polygon(get_color(),pontos);
    }

    //###### RECT #################
    rect::rect(const svg::color &color, const std::vector<point> &ponto) : polygon(color,ponto){}

    void rect::draw(png_image &img) const {
        img.draw_polygon(pontos,get_color());
    }
    void rect::translate(const point &t) {
        polygon::translate(t);
    }
    void rect::scale(const point &origin, int v) {
        polygon::scale(origin,v);
    }
    void rect::rotate(const point &origin, int degrees) {
        polygon::rotate(origin,degrees);
    }
    shape *rect::duplicate() const {
        return new rect(get_color(),pontos);
    }

    //###### POLYLINE #################
    polyline::polyline(const svg::color &color, const std::vector<point> &ponto):shape(color),points(ponto) {}
    void polyline::draw(png_image &img) const {
        for(int i=0;i<(points.size()-1);i++)
            img.draw_line(points.at(i),points.at(i+1),get_color());
    }
    void polyline::translate(const point &t) {
        for (auto &itr:points){
            itr=itr.translate(t);
        }
    }
    void polyline::scale(const point &origin, int v) {
        for (auto &itr:points){
            itr=itr.scale(origin,v);
        }
    }
    void polyline::rotate(const point &origin, int degrees) {
        for (auto &itr:points){
            itr=itr.rotate(origin,degrees);
        }
    }
    shape *polyline::duplicate() const {
        return new polyline(get_color(),points);
    }

    //###### LINE #################
    line::line(const svg::color &color, const std::vector<point> &ponto): polyline(color,ponto) {

    }
    void line::draw(png_image &img) const {
        img.draw_line(points.at(0),points.at(1),get_color());
    }
    void line::translate(const point &t) {
        polyline::translate(t);
    }
    void line::scale(const point &origin, int v) {
        polyline::scale(origin,v);
    }
    void line::rotate(const point &origin, int degrees) {
        polyline::rotate(origin,degrees);
    }
    shape *line::duplicate() const {
        return new line(get_color(),points);
    }

    //####### GROUP ########

    group::group(const svg::color &fill, std::vector<shape *> shapes) : shape(fill), g(shapes){

    }
    group::~group() noexcept {
        for(auto s :g)
            delete s;

    }
    void group::draw(png_image &img) const {
        for(auto &itr : g)
            itr->draw(img);
    }
    void group::translate(const point &t) {
        for(auto &itr : g)
            itr->translate(t);
    }
    void group::scale(const point &origin, int v) {
        for(auto &itr : g)
            itr->scale(origin,v);
    }
    void group::rotate(const point &origin, int degrees) {
        for(auto &itr : g)
            itr->rotate(origin,degrees);
    }
    shape *group::duplicate() const {
        std::vector<shape*> temp;
        for(auto &s :g)
            temp.push_back(s->duplicate());
        return new group(get_color(),temp);
    }
}
