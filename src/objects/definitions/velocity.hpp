#ifndef VELOCITY_HPP
#define VELOCITY_HPP

class Velocity
{
private:
    float deltaX;
    float deltaY;
public:

    //getters 
    float getDeltaX() const;
    float getDeltaY() const;

    //setters
    void setDeltaX(float value);
    void setDeltaY(float value);

    //constructor
    Velocity(float deltaX = 0.0, float deltaY = 0.0);

    //destructor
    ~Velocity();
};


#endif // VELOCITY_HPP