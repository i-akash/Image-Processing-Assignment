#if !defined(MY_COLOR)
#define MY_COLOR

struct RGBColor
{
    float red, green, blue, alpha;
    RGBColor() {}
    RGBColor(float red, float green, float blue, float alpha = 0)
    {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
    }
};

#endif // MY_COLOR
