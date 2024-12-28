#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class animal
{
public:
    animal(const int face,
           const int body,
           const bool stripes,
           const int ears,
           const bool bandana,
           const std::string& color,
           const int lifespan);

    int getFace() const;
    int getBody() const;
    bool getStripes() const;
    int getEars() const;
    bool getBandana() const;
    std::string getColor() const;
    int getLifespan() const;

    void setFace(const int newFace);
    void setBody(const int newBody);
    void setStripes(const bool newStripes);
    void setEars(const int newEars);
    void setBandana(const bool newBandana);
    void setColor(const std::string& newColor);
    void setLifespan(const int newLifespan);

private:
    int face;
    int body;
    bool stripes;
    int ears;
    bool bandana;
    std::string color;
    int lifespan;
};

#endif
