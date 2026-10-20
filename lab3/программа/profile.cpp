#include "profile.hpp"
using namespace std;


Profile::Profile(string model, double offset, double scale)
    :model(model),offset(offset),scale(scale){
}
string Profile::getModel() const {
    return model;
}
double Profile::getOffset() const {
    return offset;
}
double Profile::getScale() const {
    return scale;
}
double Profile::calibrate(double raw) const {
    return raw*scale+offset;
}
