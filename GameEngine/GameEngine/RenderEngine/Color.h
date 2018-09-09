#ifndef COLOR_H
#define COLOR_H

class Color
{
	public:
		   float Red;
		   float Green;
		   float Blue;
		   float Alpha;
	public:
		   Color() {}
		   Color(float red, float green, float blue, float alpha) : Red(red), Green(green), Blue(blue), Alpha(alpha) {}
		   ~Color() {}

		   	void operator=(const Color &c)
			{
				this->Red   = c.Red;
				this->Green = c.Green;
				this->Blue  = c.Blue;
				this->Alpha = c.Alpha;
			}

		   	void operator*(const Color &c)
			{
				this->Red   = this->Red * c.Red;
				this->Green = this->Green * c.Green;
				this->Blue  = this->Blue * c.Blue;
				this->Alpha = this->Alpha * c.Alpha;
			}
};

#endif