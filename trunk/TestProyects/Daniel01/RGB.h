#ifndef RGB_H
#define	RGB_H

class RGB
{
    public:
        
        RGB(int r, int g, int b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }
        
        RGB(const RGB &rgb)
        {
            this->r = rgb.r;
            this->g = rgb.g;
            this->b = rgb.b;
        }
   
        int r;
        int g;
        int b;
};

#endif	/* RGB_H */
