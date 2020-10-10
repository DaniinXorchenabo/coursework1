#pragma once

class Point
{
    public:
        float x, y;
        //=======! Конструкторы !=======
        Point();
        Point(int, int);

        void muve_up(int, int);
        void muve_up(float, float);

        void set_x(int);
        void set_y(int);
        void set_point(int, int);
        void set_x(float);
        void set_y(float);
        void set_point(float, float);

        int get_x();
        int get_y();


    private:


};