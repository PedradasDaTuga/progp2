//! @file elements.hpp
#ifndef __svg_elements_hpp__
#define __svg_elements_hpp__

#include "shape.hpp"

namespace svg {
    class ellipse : public shape {
    protected:
        point center;
        point radius;
    public:
        ellipse(const svg::color &fill, const point &center, const point &radius);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int v) override;
        shape *duplicate() const override;
    };

    //###### CIRLCE #################
    class circle: public ellipse{
    public:
        circle(const svg::color &fill, const point &center, const point &radius);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int v) override;
    };

    //###### POLYGON #################
    class polygon : public shape{
    protected:
        std::vector<point> pontos;

    public:
        polygon(const svg::color &color,const std::vector<point> &ponto);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int degrees) override;

    };

    //###### Rect #################

    class rect : public polygon{
    public:
        rect(const svg::color &color,const std::vector<point> &ponto);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int degrees) override;
    };

    //###### POLYLINE #################
    class polyline : public shape{
    protected:
        std::vector<point> points;
    public:
        polyline(const svg::color &color,const std::vector<point> &ponto);
        void draw(png_image &img) const override;
       void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int degrees) override;
    };

    //###### LINE #################
    class line : public polyline{
    public:
        line(const svg::color &color,const std::vector<point> &ponto);
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int degrees) override;
    };

    //####### GROUP ########
    class group:public shape{
    protected:
        std::vector<shape *> g;
    public:
        group(const svg::color &fill, std::vector<shape *> shapes);
        ~group();
        void draw(png_image &img) const override;
        void translate(const point &t) override;
        void scale(const point &origin, int v) override;
        void rotate(const point &origin, int degrees) override;
    };

}
#endif
