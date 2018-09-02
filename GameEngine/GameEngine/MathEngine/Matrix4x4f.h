#ifndef MATRIX4X4F_H
#define MATRIX4X4F_H

class Matrix4x4f
{
	public:
			float M[4][4];
	public:
			// Constructors
			Matrix4x4f()
			{
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						M[row][col] = 0;
					}
				}
			}

			Matrix4x4f(float m00, float m01, float m02, float m03,
					   float m10, float m11, float m12, float m13,
					   float m20, float m21, float m22, float m23,
					   float m30, float m31, float m32, float m33)
			{
				M[0][0] = m00; M[0][1] = m01, M[0][2] = m02; M[0][3] = m03;
				M[1][0] = m10; M[1][1] = m11, M[1][2] = m12; M[1][3] = m13;
				M[2][0] = m20; M[2][1] = m21, M[2][2] = m22; M[2][3] = m23;
				M[3][0] = m30; M[3][1] = m31, M[3][2] = m32; M[3][3] = m33;
			}

			Matrix4x4f(const Matrix4x4f &m)
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
			Matrix4x4f operator+(const Matrix4x4f &m) const
			{
				Matrix4x4f res;
				
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = this->M[row][col] + m.M[row][col];
					}
				}

				return res;
			}

			Matrix4x4f operator-(const Matrix4x4f &m) const
			{
				Matrix4x4f res;
				
				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = this->M[row][col] - m.M[row][col];
					}
				}

				return res;
			}

			Matrix4x4f operator*(const Matrix4x4f &m) const
			{
				Matrix4x4f res;
				
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

			Vector3f operator*(const Vector3f &v) const
			{
				Vector3f res;

				float fInvW = 1.0f / (M[3][0] * v.X + M[3][1] * v.Y + M[3][2] * v.Z + M[3][3]);

				res.X = (M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z + M[0][3]) * fInvW;
				res.Y = (M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z + M[1][3]) * fInvW;
				res.Z = (M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z + M[2][3]) * fInvW;

				return res;
			}

			Vector4f operator*(const Vector4f &v) const
			{
				Vector4f res;

				res.X = (M[0][0] * v.X + M[0][1] * v.Y + M[0][2] * v.Z + M[0][3] * v.W);
				res.Y = (M[1][0] * v.X + M[1][1] * v.Y + M[1][2] * v.Z + M[1][3] * v.W);
				res.Z = (M[2][0] * v.X + M[2][1] * v.Y + M[2][2] * v.Z + M[2][3] * v.W);

				return res;
			}

			// temp functions
			static D3DXMATRIX ConvertToD3DXMatrix(Matrix4x4f m)
			{
				D3DXMATRIX res;

				res._11 = m.M[0][0]; res._12 = m.M[0][1]; res._13 = m.M[0][2]; res._14 = m.M[0][3];
				res._21 = m.M[1][0]; res._22 = m.M[1][1]; res._23 = m.M[1][2]; res._24 = m.M[1][3];
				res._31 = m.M[2][0]; res._32 = m.M[2][1]; res._33 = m.M[2][2]; res._34 = m.M[2][3];
				res._41 = m.M[3][0]; res._42 = m.M[3][1]; res._43 = m.M[3][2]; res._44 = m.M[3][3];

				return res;
			}

			static Matrix4x4f ConvertToMatrix4x4f(D3DXMATRIX m)
			{
				Matrix4x4f res;

				res.M[0][0] = m._11; res.M[0][1] = m._12; res.M[0][2] = m._13; res.M[0][3] = m._14;
				res.M[1][0] = m._21; res.M[1][1] = m._22; res.M[1][2] = m._23; res.M[1][3] = m._24;
				res.M[2][0] = m._31; res.M[2][1] = m._32; res.M[2][2] = m._33; res.M[2][3] = m._34;
				res.M[3][0] = m._41; res.M[3][1] = m._42; res.M[3][2] = m._43; res.M[3][3] = m._44;

				return res;
			}

			// Functions
			void Print()
			{					
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<"| m00 = "<< M[0][0] << " m01 = " << M[0][1] << " m02 = " << M[0][2] << " m03 = " << M[0][3] <<" |" <<endl;
				cout<<"| m10 = "<< M[1][0] << " m11 = " << M[1][1] << " m12 = " << M[1][2] << " m13 = " << M[1][3] <<" |" <<endl;
				cout<<"| m20 = "<< M[2][0] << " m21 = " << M[2][1] << " m22 = " << M[2][2] << " m23 = " << M[2][3] <<" |" <<endl;
				cout<<"| m30 = "<< M[3][0] << " m31 = " << M[3][1] << " m32 = " << M[3][2] << " m33 = " << M[3][3] <<" |" <<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;			
			}

			void Identity()
			{
				M[0][0] = 1; M[0][1] = 0, M[0][2] = 0; M[0][3] = 0;
				M[1][0] = 0; M[1][1] = 1, M[1][2] = 0; M[1][3] = 0;
				M[2][0] = 0; M[2][1] = 0, M[2][2] = 1; M[2][3] = 0;
				M[3][0] = 0; M[3][1] = 0, M[3][2] = 0; M[3][3] = 1;
			}

			Matrix4x4f Transpose()
			{
				Matrix4x4f res;

				for(int row = 0; row < 4; row++)
				{
					for(int col = 0; col < 4; col++)
					{
						res.M[row][col] = M[col][row];
					}
				}

				return res;
			}

			static float Determinant(Matrix4x4f m)
			{
				Vector4f minor, v1, v2, v3;
				float det = 0;

				v1.X = m.M[0][0]; v1.Y = m.M[1][0]; v1.Z = m.M[2][0]; v1.W = m.M[3][0];
				v2.X = m.M[0][1]; v2.Y = m.M[1][1]; v2.Z = m.M[2][1]; v2.W = m.M[3][1];
				v3.X = m.M[0][2]; v3.Y = m.M[1][2]; v3.Z = m.M[2][2]; v3.W = m.M[3][2];

				minor = Vector4f::Cross(v1, v2, v3);
				det = -(m.M[0][3] * minor.X + m.M[1][3] * minor.Y + m.M[2][3] * minor.Z + m.M[3][3] * minor.W);
				
				return det;
			}

			static Matrix4x4f Inverse(Matrix4x4f m)
			{
				int a, i, j;
				Vector4f v, vec[3];
				float cofactor, det;
				Matrix4x4f res;

				det = Determinant(m);

				if(det == 0)
				{
					cout<<"determinant is equal to zero"<<endl;
					return m;
				}

				for(i = 0; i < 4; i++)
				{
					for(j = 0; j < 4; j++)
					{
						if(j != i)
						{
							a = j;

							if(j > i)
							{
								a = a - 1;
							}

							vec[a].X = m.M[j][0];
							vec[a].Y = m.M[j][1];
							vec[a].Z = m.M[j][2];
							vec[a].W = m.M[j][3];
						}
					}

					v = Vector4f::Cross(vec[0], vec[1], vec[2]);

					for(j = 0; j < 4; j++)
					{
						switch(j)
						{
							case 0 : cofactor = v.X; break;
							case 1 : cofactor = v.Y; break;
							case 2 : cofactor = v.Z; break;
							case 3 : cofactor = v.W; break;
						}

						res.M[j][i] = (pow(-1.0f, i) * cofactor) / det;
					}
				}

				return res;
			}

			static Matrix4x4f Translate(Vector3f v)
			{
				Matrix4x4f t;

				t.M[0][0] = 1;   t.M[0][1] = 0;   t.M[0][2] = 0;   t.M[0][3] = 0;
				t.M[1][0] = 0;   t.M[1][1] = 1;   t.M[1][2] = 0;   t.M[1][3] = 0;
				t.M[2][0] = 0;   t.M[2][1] = 0;   t.M[2][2] = 1;   t.M[2][3] = 0;
				t.M[3][0] = v.X; t.M[3][1] = v.Y; t.M[3][2] = v.Z; t.M[3][3] = 1;

				return t;
			}

			static Matrix4x4f Scale(Vector3f v)
			{
				Matrix4x4f s;

				s.M[0][0] = v.X; s.M[0][1] = 0;   s.M[0][2] = 0;   s.M[0][3] = 0;
				s.M[1][0] = 0;   s.M[1][1] = v.Y; s.M[1][2] = 0;   s.M[1][3] = 0;
				s.M[2][0] = 0;   s.M[2][1] = 0;   s.M[2][2] = v.Z; s.M[2][3] = 0;
				s.M[3][0] = 0;   s.M[3][1] = 0;   s.M[3][2] = 0;   s.M[3][3] = 1;

				return s;
			}

			static Vector3f Vec3TransformCoord(Vector3f v, Matrix4x4f m)
			{
				float norm;
				Vector3f res;

				norm = m.M[0][3] * v.X + m.M[1][3] * v.Y + m.M[2][3] * v.Z + m.M[3][3];

				if(norm)
				{
					res.X = (m.M[0][0] * v.X + m.M[1][0] * v.Y + m.M[2][0] * v.Z + m.M[3][0]) / norm;
					res.Y = (m.M[0][1] * v.X + m.M[1][1] * v.Y + m.M[2][1] * v.Z + m.M[3][1]) / norm;
					res.Z = (m.M[0][2] * v.X + m.M[1][2] * v.Y + m.M[2][2] * v.Z + m.M[3][2]) / norm;
				}
				else
				{
					res.X = 0;
					res.Y = 0;
					res.Z = 0;
				}

				return res;
			}

			static Vector3f Vec3TransformNormal(Vector3f v, Matrix4x4f m)
			{
				Vector3f res;

				res.X = m.M[0][0] * v.X + m.M[1][0] * v.Y + m.M[2][0] * v.Z;
				res.Y = m.M[0][1] * v.X + m.M[1][1] * v.Y + m.M[2][1] * v.Z;
				res.Z = m.M[0][2] * v.X + m.M[1][2] * v.Y + m.M[2][2] * v.Z;

				return res;
			}

			static Matrix4x4f RotationAxis(Vector3f v, float angle)
			{
				Vector3f nv;
				Matrix4x4f m;

				nv = v.Normalize();

				float cosAngle = cos(angle);
				float sinAngle = sin(angle);

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

			static Matrix4x4f RotateX(float angle)
			{
				float cA = cos(Mathf::DegreeToRadian(angle));
				float sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4f rX;

				rX.M[0][0] = 1;   rX.M[0][1] = 0;   rX.M[0][2] = 0;   rX.M[0][3] = 0;
				rX.M[1][0] = 0;   rX.M[1][1] = cA;  rX.M[1][2] = -sA; rX.M[1][3] = 0;
				rX.M[2][0] = 0;   rX.M[2][1] = sA;  rX.M[2][2] = cA;  rX.M[2][3] = 0;
				rX.M[3][0] = 0;   rX.M[3][1] = 0;   rX.M[3][2] = 0;   rX.M[3][3] = 1;

				return rX;
			}

			static Matrix4x4f RotateY(float angle)
			{
				float cA = cos(Mathf::DegreeToRadian(angle));
				float sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4f rY;

				rY.M[0][0] = cA;   rY.M[0][1] = 0;   rY.M[0][2] = sA;   rY.M[0][3] = 0;
				rY.M[1][0] = 0;    rY.M[1][1] = 1;   rY.M[1][2] = 0;    rY.M[1][3] = 0;
				rY.M[2][0] = -sA;  rY.M[2][1] = 0;   rY.M[2][2] = cA;   rY.M[2][3] = 0;
				rY.M[3][0] = 0;    rY.M[3][1] = 0;   rY.M[3][2] = 0;    rY.M[3][3] = 1;

				return rY;
			}

			static Matrix4x4f RotateZ(float angle)
			{
				float cA = cos(Mathf::DegreeToRadian(angle));
				float sA = sin(Mathf::DegreeToRadian(angle));

				Matrix4x4f rZ;

				rZ.M[0][0] = cA;   rZ.M[0][1] = -sA; rZ.M[0][2] = 0;    rZ.M[0][3] = 0;
				rZ.M[1][0] = sA;   rZ.M[1][1] = cA;  rZ.M[1][2] = 0;    rZ.M[1][3] = 0;
				rZ.M[2][0] = 0;    rZ.M[2][1] = 0;   rZ.M[2][2] = 1;    rZ.M[2][3] = 0;
				rZ.M[3][0] = 0;    rZ.M[3][1] = 0;   rZ.M[3][2] = 0;    rZ.M[3][3] = 1;

				return rZ;
			}

			static Matrix4x4f RotateYawPitchRoll(float yaw, float pitch, float roll)
			{
				Matrix4x4f res;

				res.Identity();

				res = RotateZ(roll) * RotateX(pitch) * RotateY(yaw);

				return res;
			}

			static Matrix4x4f Perspective(float fov, float aspect, float zNear, float zFar)
			{
				float f = 1.0f / tanf(Mathf::DegreeToRadian(fov) / 2.0f);
				Matrix4x4f p;

				p.M[0][0] = f / aspect; p.M[0][1] = 0;   p.M[0][2] = 0;								   p.M[0][3] = 0;
				p.M[1][0] = 0;          p.M[1][1] = f;   p.M[1][2] = 0;								   p.M[1][3] = 0;
				p.M[2][0] = 0;          p.M[2][1] = 0;   p.M[2][2] = zFar / (zFar - zNear);            p.M[2][3] = 1;
				p.M[3][0] = 0;          p.M[3][1] = 0;   p.M[3][2] = (-zNear * zFar) / (zFar - zNear); p.M[3][3] = 0;

				return p;
			}

			static Matrix4x4f Orthographic(float xLeft, float xRight, float yTop, float yBottom, float zNear, float zFar)
			{
				Matrix4x4f o;

				o.M[0][0] = 2.0f / (xRight - xLeft); o.M[0][1] = 0;                       o.M[0][2] = 0;                      o.M[0][3] = 0;
				o.M[1][0] = 0;                       o.M[1][1] = 2.0f / (yBottom - yTop); o.M[1][2] = 0;                      o.M[1][3] = 0;
				o.M[2][0] = 0;						 o.M[2][1] = 0;                       o.M[2][2] = 2.0f / (zFar - zNear);  o.M[2][3] = 0;
				o.M[3][0] = 0;						 o.M[3][1] = 0;                       o.M[3][2] = zNear / (zNear - zFar); o.M[3][3] = 1;

				return o;
			}

			static Matrix4x4f LookAtLH(Vector3f eye, Vector3f lookAt, Vector3f worldUp)
			{
				Vector3f view;
				view = lookAt - eye;
				view.Normalize();

				float dotProduct = Vector3f::Dot(worldUp, view);
				Vector3f up = worldUp - view * dotProduct;
				float length = up.Length();

				if(length < 1e-6f)
				{
					up = Vector3f(0 - view.Y * view.X, 1.0f - view.Y * view.Y, 0 - view.Y * view.Z);
					length = up.Length();

					if(length < 1e-6f)
					{
						up = Vector3f(0 - view.Z * view.X, 0 - view.Z * view.Y, 1.0f - view.Z * view.Z);
						length = up.Length();

						if(length < 1e-6f)
						{
							up = Vector3f(1.0f - view.X * view.X, 0 - view.X * view.Y, 0 - view.X * view.Z);
							length = up.Length();
							if(length < 1e-6)
							{
								length = 0.001f;
							}
						}
					}
				}

				float recip = 1.0f / length;

				up = up * recip;
				
				Vector3f right;

				right = Vector3f::Cross(up, view);

				Matrix4x4f v;

				v.M[0][0] = right.X;                    v.M[0][1] = up.X;                    v.M[0][2] = view.X;                    v.M[0][3] = 0;
				v.M[1][0] = right.Y;                    v.M[1][1] = up.Y;                    v.M[1][2] = view.Y;                    v.M[1][3] = 0;
				v.M[2][0] = right.Z;                    v.M[2][1] = up.Z;                    v.M[2][2] = view.Z;                    v.M[2][3] = 0;
				v.M[3][0] = -Vector3f::Dot(eye, right); v.M[3][1] = -Vector3f::Dot(eye, up); v.M[3][2] = -Vector3f::Dot(eye, view); v.M[3][3] = 1;

				return v;
			}
};

#endif