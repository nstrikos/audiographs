#ifndef FUNCTIONZOOMER_H
#define FUNCTIONZOOMER_H


class FunctionModel;
class IDragZoom;

class FunctionZoomer
{
public:
    FunctionZoomer(IDragZoom &iface, FunctionModel &model);
    void zoom(double delta, int derivMode);

private:
    IDragZoom &iface;
    FunctionModel &model;
    void performZoom(double factor, int derivMode);


};

#endif // FUNCTIONZOOMER_H
