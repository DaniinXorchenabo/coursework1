


class BaseFigure{
    public:
        list complex_figure = NULL
        list points_with_line = NULL
        list points_no_line = NULL

        BaseFigure(){}
        BaseFigure(Point points[]){
            points_with_line = points
        }
        BaseFigure(list[int[2]] coordinates){
            points_with_line = []
            for (auto data: coordinates){
                points_with_line.add(Point(data[0], data[1]))
            }
        }
        BaseFigure(BaseFigure figure_material){
            points_no_line = figure_material.points_no_line
            points_with_line = figure_material.points_with_line
            complex_figure = figure_material.complex_figure
        }

        void draw(){
            if (len(complex_figure) > 1){
                for (auto figure: complex_figure){
                    figure.draw()
                }
            }
            else {
                for (auto point: points_with_line){}
                for (auto point: points_no_line){}
            }
        }

        const BaseFigure operator+(const BaseFigure& other_figure) const {
            if ((len(complex_figure) == 0) && (len(other_figure.complex_figure) == 0)){
                complex_figure.add(BaseFigure(this))
                complex_figure.add(other_figure)
            }
            else if ((len(complex_figure) != 0) && (len(other_figure.complex_figure) == 0)){
                complex_figure.add(BaseFigure(other_figure))
            }
            else if ((len(complex_figure) == 0) && (len(other_figure.complex_figure) != 0)){
                complex_figure = other_figure.complex_figure
                complex_figure.insert(0, BaseFigure(this))
            }
            else if ((len(complex_figure) != 0) && (len(other_figure.complex_figure) != 0)){
                complex_figure.exists(other_figure.complex_figure)
            }
            return this
        }

    private:
        int same;
};

