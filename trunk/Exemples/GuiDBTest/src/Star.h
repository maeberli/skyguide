#ifndef STAR_H
#define STAR_H

class Star
{
private:
    double _rightAscension;
    double _declinaison;
    double _magnitude;
public:
    Star();
    Star(double rightAscension, double declinaison, double magnitude);
    double getRightAscension()
    {
        return _rightAscension;
    }
    double getDeclinaison()
    {
        return _declinaison;
    }
    double getMagnitude()
    {
        return _magnitude;
    }

    void setRightAscension(int rightAscension)
    {
        _rightAscension = (3.14 * rightAscension) / 180;
    }
    void setDeclinaison(int declinaison)
    {
        _declinaison = (3.14 * declinaison) / 180;
    }
    void setMagnitude(int magnitude)
    {
        _magnitude = magnitude;
    }
};

#endif // STAR_H
