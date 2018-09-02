#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f
{
	public:
			float X;
			float Y;
			float Z;
	public:
			Vector3f() : X(0), Y(0), Z(0) {}
			Vector3f(float x, float y, float z) : X(x), Y(y), Z(z) {}
		//	Vector3f(btVector3 btvec) : X(btvec.getX()), Y(btvec.getY()), Z(btvec.getZ()) {}
			~Vector3f() {}

			// Operators
			Vector3f operator+(const Vector3f &v) const
			{
				return Vector3f(this->X + v.X, this->Y + v.Y, this->Z + v.Z);
			}

			Vector3f operator-(const Vector3f &v) const
			{
				return Vector3f(this->X - v.X, this->Y - v.Y, this->Z - v.Z);
			}

			Vector3f operator*(float scalar) const
			{
				return Vector3f(this->X * scalar, this->Y * scalar, this->Z * scalar);
			}

			void operator=(const Vector3f &v)
			{
				this->X = v.X;
				this->Y = v.Y;
				this->Z = v.Z;
			}

			Vector3f operator+=(const Vector3f &v)
			{
				this->X = X + v.X;
				this->Y = Y + v.Y;
				this->Z = Z + v.Z;

				return Vector3f(X, Y, Z);
			}

			Vector3f operator-=(const Vector3f &v)
			{
				this->X = X - v.X;
				this->Y = Y - v.Y;
				this->Z = Z - v.Z;

				return Vector3f(X, Y, Z);
			}

			bool operator==(const Vector3f &v) const
			{
				return (this->X == v.X && this->Y == v.Y && this->Z == v.Z);
			}

			// Functions
			float Length()
			{
				return sqrtf((this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z));
			}

			Vector3f Normalize()
			{
				float length = this->Length();

				X /= length;
				Y /= length;
				Z /= length;

				return *this;
			}

			float Dot(const Vector3f &v) const
			{
				return (this->X * v.X + this->Y * v.Y + this->Z + v.Z);
			}

			static float Dot(const Vector3f &v1, const Vector3f &v2)
			{
				return (v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z);
			}

			Vector3f Cross(const Vector3f &v) const
			{
				return Vector3f(this->Y * v.Z - this->Z * v.Y,
								this->Z * v.X - this->X * v.Z,
								this->X * v.Y - this->Y * v.X);
			}

			static Vector3f Cross(const Vector3f &v1, const Vector3f &v2)
			{
				return Vector3f(v1.Y * v2.Z - v1.Z * v2.Y,
								v1.Z * v2.X - v1.X * v2.Z,
								v1.X * v2.Y - v1.Y * v2.X);
			}		

			static float Distance(const Vector3f &v1, const Vector3f &v2)
			{
				return sqrt((v1.X - v2.X) * (v1.X - v2.X) + 
							(v1.Y - v2.Y) * (v1.Y - v2.Y) + 
							(v1.Z - v2.Z) * (v1.Z - v2.Z));
			}

			static Vector3f Lerp(Vector3f start, Vector3f end, float percent)
			{
				return (start + (end - start) * percent);
			}

			//btVector3 GetbtVector3()
			//{
			//	return btVector3(this->X, this->Y, this->Z);
			//}

			void Print()
			{
				cout<<"("<<X<<", "<<Y<<", "<<Z<<")"<<endl;
			}
};

#endif

// Some important points regarding vectors

// 1. Dot Product
//		(a) If the angle < 90 degrees result will be a positive no.
//      (b) If the angle = 90 degrees result will be zero.
//      (c) If the angle > 90 degrees result will be a negative no.