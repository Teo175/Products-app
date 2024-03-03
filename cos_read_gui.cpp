#include "cos_read_gui.h"
#include "Service.h"

CartCRUDRead::CartCRUDRead(Cos& cart_serv) : cart_serv{ cart_serv }
{
    cart_serv.addObserver(this);
    repaint();
}

/*void CartCRUDRead::paintEvent(QPaintEvent* event) {

    QPainter g{ this };
    g.setPen(Qt::red);

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> x_coord(0, this->width());
    std::uniform_int_distribution<> y_coord(0, this->height());
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    int z_coord = 1000;
    int p_coord = 150;
    int x = 10, y = 30;
    int xx = 100, yy = 200;
    auto lst = cart_serv.get_cos();

    QPen pen(Qt::black);
    g.setPen(pen);

    QPoint startPoint(x, y);
    QPoint endPoint(xx, yy);



    int i;
    for (i = 0; i < lst.size(); i++)
    {
        if (lst[i].get_nume() == "ciocolata")
            g.drawRect(x_coord(mt), height(mt), z_coord, p_coord);
        else if (lst[i].get_nume() == "telefon")
            g.drawPie(x_coord(mt), y_coord(mt), width(mt), height(mt), z_coord, p_coord);
        else
        {
            g.drawLine(startPoint, endPoint);
            xx += 14;
            yy += 20;
        }
    }


}*/

//cerculete13-14
void CartCRUDRead::paintEvent(QPaintEvent* event)
{
    QPainter g{ this };
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    int a = 200, b = 200;       // coordonatele centrului cercului
    int r = 150;                // raza cercului
    int t = 0;
    int k = 0;
    g.drawEllipse(a - r, b - r, 2 * r, 2 * r);
    for (const auto& prod : this->cart_serv.get_cos())
    {
        k++;
        if (k == 1)
            g.setPen(Qt::blue);
        else if (k == 2)
            g.setPen(Qt::red);
        else if (k == 3)
            g.setPen(Qt::green);
        else if (k == 4)
            g.setPen(Qt::yellow);
        else if (k == 5)
        {
            g.setPen(Qt::black);
            k = 0;
        }

        int x = a + r * sin(t);
        int y = b + r * cos(t);
      //  g.drawEllipse(x, y, 50, 50);
        g.drawEllipse(x-25, y-25, 50, 50);
        t += 10;
    }
}

void CartCRUDRead::update() {
    repaint();
}