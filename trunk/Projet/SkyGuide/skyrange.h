#ifndef SKYRANGE_H
#define SKYRANGE_H


class SkyRange
{
public:
    SkyRange(int azimut, int inclinasion);

    int getAzimut();
    int getInclinasion();
private:
    int p_azimut;
    int p_inclinasion;

};

#endif // SKYRANGE_H
