#include "actualclass.h"

ActualClass::ActualClass(double value) 
    : mValue(value)
{}
double ActualClass::getValue() {
    return mValue;
}
double ActualClass::add(double value) {
    mValue += value;
    return mValue;
}
double ActualClass::subtract(double value) {
    mValue -= value;
    return mValue;
}