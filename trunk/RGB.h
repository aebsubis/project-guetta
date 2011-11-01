#ifndef RGB_H
#define	RGB_H

class RGB
{
    public:
        
        RGB(float r, float g, float b)
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
        
        RGB()
        {
            this->r = 255;
            this->g = 0;
            this->b = 0;
        }   
        
        RGB& operator=(const RGB &rgb)
        {
            if(this != &rgb)
            {
                this->r = rgb.r;
                this->g = rgb.g;
                this->b = rgb.b;
            }
            return *this;
        }
                    
        float r;
        float g;
        float b;
};

#endif	/* RGB_H */
