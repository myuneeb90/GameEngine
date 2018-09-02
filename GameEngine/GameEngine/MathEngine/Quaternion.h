#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
	public:
			float X;
			float Y;
			float Z;
			float W;
	public:
			Quaternion()
			{
				X = 0;
				Y = 0;
				Z = 0;
				W = 1;
			}

			Quaternion(float x, float y, float z, float w)
			{
				X = x;
				Y = y;
				Z = z;
				W = w;
			}

			Quaternion(Vector3f axis, float angle)
			{
				this->Rotate(axis, angle);
			}

			~Quaternion()
			{

			}

			// Operators
			Quaternion operator*(const Quaternion &q)
			{
				float w = W * q.W - X * q.X - Y * q.Y - Z * q.Z;
				float x = X * q.W + W * q.X + Y * q.Z - Z * q.Y;
				float y = Y * q.W + W * q.Y + Z * q.X - X * q.Z;
				float z = Z * q.W + W * q.Z + X * q.Y - Y * q.X;

				return Quaternion(x, y, z, w);
			}

			Quaternion operator*(const Vector3f &v)
			{
				float w = -X * v.X - Y * v.Y - Z * v.Z;
				float x =  W * v.X + Y * v.Z - Z * v.Y;
				float y =  W * v.Y + Z * v.X - X * v.Z;
				float z =  W * v.Z + X * v.Y - Y * v.X;

				return Quaternion(x, y, z, w);
			}

			// Static Functions
			static float Dot(const Quaternion q1, const Quaternion q2)
			{
				return (q1.X * q2.X) + (q1.Y * q2.Y) + (q1.Z * q2.Z) + (q1.W * q2.W);
			}

			static Quaternion Slerp(const Quaternion q1, const Quaternion q2, float t)
			{
				float dot, epsilon;
				Quaternion q;

				epsilon = 1.0f;
				dot = Dot(q1, q2);
				if(dot < 0.0f)
				{
					epsilon = -1;
				}

				q.X = (1.0f - t) * q1.X + epsilon * t * q2.X;
				q.Y = (1.0f - t) * q1.Y + epsilon * t * q2.Y;
				q.Z = (1.0f - t) * q1.Z + epsilon * t * q2.Z;
				q.W = (1.0f - t) * q1.W + epsilon * t * q2.W;

				return q;
			}

			static Quaternion RotateYawPitchRoll(float yaw, float pitch, float roll)
			{
				Quaternion q;

				q.X = sin(yaw / 2.0f) * cos(pitch / 2.0f) * sin(roll / 2.0f) + cos(yaw / 2.0f) * sin(pitch / 2.0f) * cos(roll / 2.0f);
				q.Y = sin(yaw / 2.0f) * cos(pitch / 2.0f) * cos(roll / 2.0f) - cos(yaw / 2.0f) * sin(pitch / 2.0f) * sin(roll / 2.0f);
				q.Z = cos(yaw / 2.0f) * cos(pitch / 2.0f) * sin(roll / 2.0f) - sin(yaw / 2.0f) * sin(pitch / 2.0f) * cos(roll / 2.0f);
				q.W = cos(yaw / 2.0f) * cos(pitch / 2.0f) * cos(roll / 2.0f) + sin(yaw / 2.0f) * sin(pitch / 2.0f) * sin(roll / 2.0f);
			
				return q;
			}

			// Functions
			void Identity()
			{
				this->X = 0;
				this->Y = 0;
				this->Z = 0;
				this->W = 1;
			}

			float Length()
			{
				return sqrtf(X * X + Y * Y + Z * Z + W * W);
			}

			Quaternion Normalize()
			{
				float length = Length();

				X /= length;
				Y /= length;
				Z /= length;
				W /= length;

				return *this;
			}

			Quaternion Conjugate()
			{
				return Quaternion(-X, -Y, -Z, W);
			}

			void Rotate(Vector3f axis, float angle)
			{
				float sinHalfAngle = sin(angle / 2);
				float cosHalfAngle = cos(angle / 2);

				X = axis.X * sinHalfAngle;
				Y = axis.Y * sinHalfAngle;
				Z = axis.Z * sinHalfAngle;
				W = cosHalfAngle;
			}

			Vector3f RotateV(Vector3f axis, float angle)
			{
				float sinHalfAngle = sin(angle / 2);
				float cosHalfAngle = cos(angle / 2);

				X = axis.X * sinHalfAngle;
				Y = axis.Y * sinHalfAngle;
				Z = axis.Z * sinHalfAngle;
				W = cosHalfAngle;

				Quaternion rotation = Quaternion(X, Y, Z, W);
				Quaternion conjugate = rotation.Conjugate();

				Quaternion w = rotation * *this * conjugate;

				Vector3f rotationVector = Vector3f(w.X, w.Y, w.Z);

				return rotationVector;
			}

			Matrix4x4f ToRotationMatrixf()
			{
				Vector3f forward = Vector3f(2.0f * (X * Z - W * Y), 2.0f * (Y * Z + W * X), 1.0f - 2.0f * (X * X + Y * Y));
				Vector3f up = Vector3f(2.0f * (X * Y + W * Z), 1.0f - 2.0f * (X * X + Z * Z), 2.0f * (Y * Z - W * X));
				Vector3f right = Vector3f(1.0f - 2.0f * (Y * Y + Z * Z), 2.0f * (X * Y - W * Z), 2.0f * (X * Z + W * Y));

				Matrix4x4f r;

				r.M[0][0] = right.X;   r.M[0][1] = right.Y;   r.M[0][2] = right.Z;   r.M[0][3] = 0;
				r.M[1][0] = up.X;      r.M[1][1] = up.Y;      r.M[1][2] = up.Z;      r.M[1][3] = 0;
				r.M[2][0] = forward.X; r.M[2][1] = forward.Y; r.M[2][2] = forward.Z; r.M[2][3] = 0;
				r.M[3][0] = 0;         r.M[3][1] = 0;         r.M[3][2] = 0;         r.M[3][3] = 1;

				return r;
			}

			Matrix4x4d ToRotationMatrixd()
			{
				Vector3f forward = Vector3f(2.0f * (X * Z - W * Y), 2.0f * (Y * Z + W * X), 1.0f - 2.0f * (X * X + Y * Y));
				Vector3f up = Vector3f(2.0f * (X * Y + W * Z), 1.0f - 2.0f * (X * X + Z * Z), 2.0f * (Y * Z - W * X));
				Vector3f right = Vector3f(1.0f - 2.0f * (Y * Y + Z * Z), 2.0f * (X * Y - W * Z), 2.0f * (X * Z + W * Y));

				Matrix4x4d r;

				r.M[0][0] = right.X;   r.M[0][1] = right.Y;   r.M[0][2] = right.Z;   r.M[0][3] = 0;
				r.M[1][0] = up.X;      r.M[1][1] = up.Y;      r.M[1][2] = up.Z;      r.M[1][3] = 0;
				r.M[2][0] = forward.X; r.M[2][1] = forward.Y; r.M[2][2] = forward.Z; r.M[2][3] = 0;
				r.M[3][0] = 0;         r.M[3][1] = 0;         r.M[3][2] = 0;         r.M[3][3] = 1;

				return r;
			}

			Quaternion ToQuaternion(Matrix4x4f r)
			{
				int i, maxi;
				float maxDiag, S, trace;
				Quaternion q;

				trace = r.M[0][0] + r.M[1][1] + r.M[2][2] + 1.0f;

				if(trace > 0.0f)
				{
					q.X = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.Y = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.Z = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.W = sqrt(trace) / 2.0f;
				}

				maxi = 0;
				maxDiag = r.M[0][0];

				for(i = 1; i < 3; i++)
				{
					if(r.M[i][i] > maxDiag)
					{
						maxi = i;
						maxDiag = r.M[i][i];
					}
				}

				if(maxi == 0)
				{
					S = 2.0f * sqrt(1.0f + r.M[0][0] - r.M[1][1] - r.M[2][2]);
					q.X = 0.25f * S;
					q.Y = (r.M[0][1] + r.M[1][0]) / S;
					q.Z = (r.M[0][2] + r.M[2][0]) / S;
					q.W = (r.M[1][2] + r.M[2][1]) / S;
				}
				else
				if(maxi == 1)
				{
					S = 2.0f * sqrt(1.0f + r.M[1][1] - r.M[0][0] - r.M[2][2]);
					q.X = (r.M[0][1] + r.M[1][0]) / S;
					q.Y = 0.25f * S;
					q.Z = (r.M[1][2] + r.M[2][1]) / S;
					q.W = (r.M[2][0] - r.M[0][2]) / S;
				}
				else
				if(maxi == 2)
				{
					S = 2.0f * sqrt(1.0f + r.M[2][2] - r.M[0][0] - r.M[1][1]);
					q.X = (r.M[0][2] + r.M[2][0]) / S;
					q.Y = (r.M[1][2] + r.M[2][1]) / S;
					q.Z = 0.25f * S;
					q.W = (r.M[0][1] - r.M[1][0]) / S;
				}
				
				return q;
			}

			Quaternion ToQuaternion(Matrix4x4d r)
			{
				int i, maxi;
				float maxDiag, S, trace;
				Quaternion q;

				trace = r.M[0][0] + r.M[1][1] + r.M[2][2] + 1.0f;

				if(trace > 0.0f)
				{
					q.X = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.Y = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.Z = (r.M[1][2] - r.M[2][1]) / (2.0f * sqrt(trace));
					q.W = sqrt(trace) / 2.0f;
				}

				maxi = 0;
				maxDiag = r.M[0][0];

				for(i = 1; i < 3; i++)
				{
					if(r.M[i][i] > maxDiag)
					{
						maxi = i;
						maxDiag = r.M[i][i];
					}
				}

				if(maxi == 0)
				{
					S = 2.0f * sqrt(1.0f + r.M[0][0] - r.M[1][1] - r.M[2][2]);
					q.X = 0.25f * S;
					q.Y = (r.M[0][1] + r.M[1][0]) / S;
					q.Z = (r.M[0][2] + r.M[2][0]) / S;
					q.W = (r.M[1][2] + r.M[2][1]) / S;
				}
				else
				if(maxi == 1)
				{
					S = 2.0f * sqrt(1.0f + r.M[1][1] - r.M[0][0] - r.M[2][2]);
					q.X = (r.M[0][1] + r.M[1][0]) / S;
					q.Y = 0.25f * S;
					q.Z = (r.M[1][2] + r.M[2][1]) / S;
					q.W = (r.M[2][0] - r.M[0][2]) / S;
				}
				else
				if(maxi == 2)
				{
					S = 2.0f * sqrt(1.0f + r.M[2][2] - r.M[0][0] - r.M[1][1]);
					q.X = (r.M[0][2] + r.M[2][0]) / S;
					q.Y = (r.M[1][2] + r.M[2][1]) / S;
					q.Z = 0.25f * S;
					q.W = (r.M[0][1] - r.M[1][0]) / S;
				}
				
				return q;
			}
};

#endif