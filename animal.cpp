#include "animal.h"

animal::animal(const int face,
               const int body,
               const bool stripes,
               const int ears,
               const bool bandana,
               const std::string& color,
               const int lifespan)
    : face(face), body(body), stripes(stripes), ears(ears), bandana(bandana), color(color), lifespan(lifespan) {}

int animal::getFace() const {
    return face;
}

int animal::getBody() const {
    return body;
}

bool animal::getStripes() const {
    return stripes;
}

int animal::getEars() const {
    return ears;
}

bool animal::getBandana() const {
    return bandana;
}

std::string animal::getColor() const {
    return color;
}

int animal::getLifespan() const {
    return lifespan;
}

void animal::setFace(const int newFace) {
    face = newFace;
}

void animal::setBody(const int newBody) {
    body = newBody;
}

void animal::setStripes(const bool newStripes) {
    stripes = newStripes;
}

void animal::setEars(const int newEars) {
    ears = newEars;
}

void animal::setBandana(const bool newBandana) {
    bandana = newBandana;
}

void animal::setColor(const std::string& newColor) {
    color = newColor;
}

void animal::setLifespan(const int newLifespan) {
    lifespan = newLifespan;
}
