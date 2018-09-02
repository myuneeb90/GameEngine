#ifndef MATRIX4X4D_H
#define MATRIX4X4D_H

class Matrix4x4d
{
	public:
			double M[4][4];
	public:
			// Constructors
			Matrix4x4d()
			{
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						M[row][col] = 0;
					}
				}
			}

			Matrix4x4d(double m00, double m01, double m02, double m03,
					   double m10, double m11, double m12, double m13,
					   double m20, double m21, double m22, double m23,
					   double m30, double m31, double m32, double m33)
			{
				M[0][0] = m00; M[0][1] = m01, M[0][2] = m02; M[0][3] = m03;
				M[1][0] = m10; M[1][1] = m11, M[1][2] = m12; M[1][3] = m13;
				M[2][0] = m20; M[2][1] = m21, M[2][2] = m22; M[2][3] = m23;
				M[3][0] = m30; M[3][1] = m31, M[3][2] = m32; M[3][3] = m33;
			}

			Matrix4x4d(const Matrix4x4d &m)
			{
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						M[row][col] = m.M[row][col];
					}
				}
			}

			// Operators
			Matrix4x4d operator+(const Matrix4x4d &m) const
			{
				Matrix4x4d res;
				
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = this->M[row][col] + m.M[row][col];
					}
				}

				return res;
			}

			Matrix4x4d operator-(const Matrix4x4d &m) const
			{
				Matrix4x4d res;
				
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = this->M[row][col] - m.M[row][col];
					}
				}

				return res;
			}

			Matrix4x4d operator*(const Matrix4x4d &m) const
			{
				Matrix4x4d res;
				
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = this->M[row][0] * m.M[0][col] +
										  this->M[row][1] * m.M[1][col] +
										  this->M[row][2] * m.M[2][col] +
										  this->M[row][3] * m.M[3][col];
					}
				}

				return res;
			}

			Vector3d operator*(const Vector3d &v) const
			{
				Vector3d res;

				double fInvW = 1.0f / (M[3][0] * v.X + M[3][1] * v.Y + M[3][2] * v.Z + M[3][3]);

				res.X = (M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z + M[0][3]) * fInvW;
				res.Y = (M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z + M[1][3]) * fInvW;
				res.Z = (M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z + M[2][3]) * fInvW;

				return res;
			}

			Vector4d operator*(const Vector4d &v) const
			{
				Vector4d res;

				res.X = (M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z + M[0][3] * v.W);
				res.Y = (M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z + M[1][3] * v.W);
				res.Z = (M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z + M[2][3] * v.W);

				return res;
			}

			// Functions
			void Identity()
			{
				M[0][0] = 1; M[0][1] = 0, M[0][2] = 0; M[0][3] = 0;
				M[1][0] = 0; M[1][1] = 1, M[1][2] = 0; M[1][3] = 0;
				M[2][0] = 0; M[2][1] = 0, M[2][2] = 1; M[2][3] = 0;
				M[3][0] = 0; M[3][1] = 0, M[3][2] = 0; M[3][3] = 1;
			}

			Matrix4x4d Transpose()
			{
				Matrix4x4d res;

				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = M[col][row];
					}
				}

				return res;
			}

			static Matrix4x4d Translate(Vector3d v)
			{
				Matrix4x4d t;

				t.M[0][0] = 1;   t.M[0][1] = 0;   t.M[0][2] = 0;   t.M[0][3] = 0;
				t.M[1][0] = 0;   t.M[1][1] = 1;   t.M[1][2] = 0;   t.M[1][3] = 0;
				t.M[2][0] = 0;   t.M[2][1] = 0;   t.M[2][2] = 1;   t.M[2][3] = 0;
				t.M[3][0] = v.X; t.M[3][1] = v.Y; t.M[3][2] = v.Z; t.M[3][3] = 1;

				return t;
			}

			static Matrix4x4d Scale(Vector3d v)
			{
				Matrix4x4d s;

				s.M[0][0] = v.X; s.M[0][1] = 0;   s.M[0][2] = 0;   s.M[0][3] = 0;
				s.M[1][0] = 0;   s.M[1][1] = v.Y; s.M[1][2] = 0;   s.M[1][3] = 0;
				s.M[2][0] = 0;   s.M[2][1] = 0;   s.M[2][2] = v.Z; s.M[2][3] = 0;
				s.M[3][0] = 0;   s.M[3][1] = 0;   s.M[3][2] = 0;   s.M[3][3] = 1;

				return s;
			}

			static Vector3d Vec3TransformNormal(Vector3d v, Matrix4x4d m)
			{
				Vector3d res;

				res.X = m.M[0][0] * v.X + m.M[1][0] * v.Y + m.M[2][0] * v.Z;
				res.Y = m.M[0][1] * v.X + m.M[1][1] * v.Y + m.M[2][1] * v.Z;
				res.Z = m.M[0][2] * v.X + m.M[1][2] * v.Y + m.M[2][2] * v.Z;

				return res;
			}

			static Matrix4x4d RotationAxis(Vector3d v, double angle)
			{
				Vector3d nv;
				Matrix4x4d m;

				nv = v.Normalize();

				double cosAngle = cos(angle);
				double sinAngle = sin(angle);

				m.M[0][0] = (1.0f - cosAngle) * v.X * v.X + cosAngle;
				m.M[1][0] = (1.0f - cosAngle) * v.X * v.Y - sinAngle * v.Z;
				m.M[2][0] = (1.0f - cosAngle) * v.X * v.Z + sinAngle * v.Y;
				m.M[0][1] = (1.0f - cosAngle) * v.Y * v.X + sinAngle * v.Z;
				m.M[1][1] = (1.0f - cosAngle) * v.Y * v.Y + cosAngle;
				m.M[2][1] = (1.0f - cosAngle) * v.Y * v.Z - sinAngle * v.X;
				m.M[0][2] = (1.0f - cosAngle) * v.Z * v.X - sinAngle * v.Y;
				m.M[1][2] = (1.0f - cosAngle) * v.Z * v.Y + sinAngle * v.X;
				m.M[2][2] = (1.0f - cosAngle) * v.Z * v.Z + cosAngle;

				return m;
			}

			static Matrix4x4d RotateX(double angle)
			{
				double cA = cos(Mathf::DegreeToRadian(angle));
				double sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4d rX;

				rX.M[0][0] = 1;   rX.M[0][1] = 0;   rX.M[0][2] = 0;   rX.M[0][3] = 0;
				rX.M[1][0] = 0;   rX.M[1][1] = cA;  rX.M[1][2] = -sA; rX.M[1][3] = 0;
				rX.M[2][0] = 0;   rX.M[2][1] = sA;  rX.M[2][2] = cA;  rX.M[2][3] = 0;
				rX.M[3][0] = 0;   rX.M[3][1] = 0;   rX.M[3][2] = 0;   rX.M[3][3] = 1;

				return rX;
			}

			static Matrix4x4d RotateY(double angle)
			{
				double cA = cos(Mathf::DegreeToRadian(angle));
				double sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4d rY;

				rY.M[0][0] = cA;   rY.M[0][1] = 0;   rY.M[0][2] = sA;   rY.M[0][3] = 0;
				rY.M[1][0] = 0;    rY.M[1][1] = 1;   rY.M[1][2] = 0;    rY.M[1][3] = 0;
				rY.M[2][0] = -sA;  rY.M[2][1] = 0;   rY.M[2][2] = cA;   rY.M[2][3] = 0;
				rY.M[3][0] = 0;    rY.M[3][1] = 0;   rY.M[3][2] = 0;    rY.M[3][3] = 1;

				return rY;
			}

			static Matrix4x4d RotateZ(double angle)
			{
				double cA = cos(Mathf::DegreeToRadian(angle));
				double sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4d rZ;

				rZ.M[0][0] = cA;   rZ.M[0][1] = -sA; rZ.M[0][2] = 0;    rZ.M[0][3] = 0;
				rZ.M[1][0] = sA;   rZ.M[1][1] = cA;  rZ.M[1][2] = 0;    rZ.M[1][3] = 0;
				rZ.M[2][0] = 0;    rZ.M[2][1] = 0;   rZ.M[2][2] = 1;    rZ.M[2][3] = 0;
				rZ.M[3][0] = 0;    rZ.M[3][1] = 0;   rZ.M[3][2] = 0;    rZ.M[3][3] = 1;

				return rZ;
			}

			static Matrix4x4d RotateYawPitchRoll(double yaw, double pitch, double roll)
			{
				Matrix4x4d res;

				res.Identity();

				res = RotateZ(roll) * RotateX(pitch) * RotateY(yaw);

				return res;
			}

			static Matrix4x4d Perspective(double fov, double aspect, double zNear, double zFar)
			{
				double f = 1.0f / tanf(Mathf::DegreeToRadian(fov) / 2.0f);
				Matrix4x4d p;

				p.M[0][0] = f / aspect; p.M[0][1] = 0;   p.M[0][2] = 0;								   p.M[0][3] = 0;
				p.M[1][0] = 0;          p.M[1][1] = f;   p.M[1][2] = 0;								   p.M[1][3] = 0;
				p.M[2][0] = 0;          p.M[2][1] = 0;   p.M[2][2] = zFar / (zFar - zNear);            p.M[2][3] = 1;
				p.M[3][0] = 0;          p.M[3][1] = 0;   p.M[3][2] = (-zNear * zFar) / (zFar - zNear); p.M[3][3] = 0;

				return p;
			}

			static Matrix4x4d Orthographic(double xRight, double xLeft, double yTop, double yBottom, double zNear, double zFar)
			{
				Matrix4x4d o;

				o.M[0][0] = 2.0f / (xRight - xLeft); o.M[0][1] = 0;                       o.M[0][2] = 0;                      o.M[0][3] = 0;
				o.M[1][0] = 0;                       o.M[1][1] = 2.0f / (yTop - yBottom); o.M[1][2] = 0;                      o.M[1][3] = 0;
				o.M[2][0] = 0;						 o.M[2][1] = 0;                       o.M[2][2] = 2.0f / (zFar - zNear);  o.M[2][3] = 0;
				o.M[3][0] = 0;						 o.M[3][1] = 0;                       o.M[3][2] = zNear / (zNear - zFar); o.M[3][3] = 1;

				return o;
			}

			static Matrix4x4d LookAtLH(Vector3d eye, Vector3d lookAt, Vector3d worldUp)
			{
				Vector3d view;
				view = lookAt - eye;
				view.Normalize();

				double dotProduct = Vector3d::Dot(worldUp, view);
				Vector3d up = worldUp - view * dotProduct;
				double length = up.Length();

				if(length < 1e-6f)
				{
					up = Vector3d(0 - view.Y * view.X, 1.0f - view.Y * view.Y, 0 - view.Y * view.Z);
					length = up.Length();

					if(length < 1e-6f)
					{
						up = Vector3d(0 - view.Z * view.X, 0 - view.Z * view.Y, 1.0f - view.Z * view.Z);
						length = up.Length();

						if(length < 1e-6f)
						{
							up = Vector3d(1.0f - view.X * view.X, 0 - view.X * view.Y, 0 - view.X * view.Z);
							length = up.Length();
							if(length < 1e-6)
							{
								length = 0.001f;
							}
						}
					}
				}

				double recip = 1.0f / length;

				up = up * recip;
				
				Vector3d right;

				right = Vector3d::Cross(up, view);

				Matrix4x4d v;

				v.M[0][0] = right.X;                    v.M[0][1] = up.X;                    v.M[0][2] = view.X;                    v.M[0][3] = 0;
				v.M[1][0] = right.Y;                    v.M[1][1] = up.Y;                    v.M[1][2] = view.Y;                    v.M[1][3] = 0;
				v.M[2][0] = right.Z;                    v.M[2][1] = up.Z;                    v.M[2][2] = view.Z;                    v.M[2][3] = 0;
				v.M[3][0] = -Vector3d::Dot(eye, right); v.M[3][1] = -Vector3d::Dot(eye, up); v.M[3][2] = -Vector3d::Dot(eye, view); v.M[3][3] = 1;

				return v;
			}

			static Matrix4x4d LookAtLH(Vector3d eye, Vector3d right, Vector3d up, Vector3d look)
			{
				Matrix4x4d v;

				v.M[0][0] = right.X;                    v.M[0][1] = up.X;                    v.M[0][2] = look.X;                    v.M[0][3] = 0;
				v.M[1][0] = right.Y;                    v.M[1][1] = up.Y;                    v.M[1][2] = look.Y;                    v.M[1][3] = 0;
				v.M[2][0] = right.Z;                    v.M[2][1] = up.Z;                    v.M[2][2] = look.Z;                    v.M[2][3] = 0;
				v.M[3][0] = -Vector3d::Dot(eye, right); v.M[3][1] = -Vector3d::Dot(eye, up); v.M[3][2] = -Vector3d::Dot(eye, look); v.M[3][3] = 1;

				return v;
			}

			Matrix4x4f ConvertToMatrix4x4f()
			{
				Matrix4x4f m;

				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						m.M[row][col] = (float)M[row][col];
					}
				}

				return m;
			}
};

#endif