#ifndef RGB_H
#define RGB_H

class RGB{
    public:
        float GetDistanceTo(const RGB& rhs) const;

        void SetChannel(int ch, unsigned char val);
        unsigned char GetChannel(int ch) const;

    private:
        unsigned char p[3];
};

#endif