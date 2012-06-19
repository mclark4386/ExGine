#ifndef __BASE_ELEMENTS_H__
#define __BASE_ELEMENTS_H__

#include "base_functions.h"

typedef double Scalar;

template <class T>
class Vector
{
public:
	Vector(){normalized=false;};
	Vector(T _x,T _y,T _z):x(_x),y(_y),z(_z){normalized=false;};
	~Vector(){};
	
	Vector<T>& operator=(const Vector<T> &vec){x = vec.x; y = vec.y; z = vec.z; return *this;};
	
	Vector<T>& operator*=(Vector<T> v2){normalized=false;return *(this);};
	Vector<T> operator*=(T s){x*=s;y*=s;z*=s;normalized=false;return *(this);};
	Vector<T> operator*(T s){Vector<T> temp = *(this);temp.x*=s; temp.y*=s; temp.z*=s;return temp;};

	Vector<T>& operator+=(Vector<T> v2){x+=v2.x;y+=v2.y;z+=v2.z;normalized=false;return *(this);};
	Vector<T> operator+(Vector<T> v2){Vector<T> temp = *(this);temp.x+=v2.x; temp.y+=v2.y; temp.z+=v2.z;return temp;};
	
	Vector<T>& operator-=(Vector<T> v2){x-=v2.x;y-=v2.y;z-=v2.z;normalized=false;return *(this);};
	Vector<T> operator-(Vector<T> v2){Vector<T> temp = *(this);temp.x-=v2.x; temp.y-=v2.y; temp.z-=v2.z;return temp;};

	T dot(Vector v2){return DOT(x,y,z,v2.x,v2.y,v2.z);};

	T angle(Vector v2){/*if(normalized) return acos(DOT(x,y,z,v2.x,v2.y,v2.z));*/ return ((acos(DOT(x,y,z,v2.x,v2.y,v2.z)))/(MAG(x,y,z)*MAG(v2.x,v2.y,v2.z)));};
	void normalize(){/*if(normalized) return;*/T temp = MAG(x,y,z); x /= temp;y /= temp;z /= temp;normalized=true;};
	T x,y,z;
protected:
	bool normalized;
};

//class Matrix4x4;

template <class T>
class Q
{
public:
	Q(T angle, T axis_x, T axis_y, T axis_z){T temp = sin(angle/2);x = axis_x * temp;y = axis_y * temp;z = axis_z * temp;w = cos(angle/2);};
	//Q(Q<T> q){w = q.w; x = q.x; y = q.y; z = q.z;};
	~Q(){};
	
	//void operator=(Matrix4x4* mat){};
	
	T w, x, y, z;
};

template <class T>
class Matrix3x3
{
public:
	Matrix3x3(){
	  #pragma omp parallel for
	  for(int i=0;i<9;i++){m[i] = (T)0;}m[0]=(T)1;m[4]=(T)1;m[8]=(T)1;};
	Matrix3x3(Vector<T> _x, Vector<T> _y, Vector<T> _z){m[0]=_x.x;m[1]=_x.y;m[2]=_x.z;m[3]=_y.x;m[4]=_y.y;m[5]=_y.z;m[6]=_z.x;m[7]=_z.y;m[8]=_z.z;};
	~Matrix3x3(){};

	T m[9];
};

template <class T>
class Matrix2x2
{
public:
	Matrix2x2():x1((T)1),y1((T)0),x2((T)0),y2((T)1){};
	Matrix2x2(T _x1, T _y1, T _x2, T _y2):x1(_x1),y1(_y1),x2(_x2),y2(_y2){};
	~Matrix2x2(){};

	T x1, y1, x2, y2;
};

/*
 * [0 4  8 12]
 * [1 5  9 13]
 * [2 6 10 14]
 * [3 7 11 15]
 */
template <class T>
class Matrix4x4
{
public:
	Matrix4x4(){
	  #pragma omp parallel for
	  for(int i=0;i<16;i++){m[i] = (T)0;}m[0]=(T)1;m[5]=(T)1;m[10]=(T)1;m[15]=(T)1;};
	Matrix4x4(T _m[16]){
	  #pragma omp parallel for
	  for(int i=0;i<16;i++){m[i] = _m[i];}};
	Matrix4x4(Q<T> Q1, Q<T> Q2, Q<T> Q3, Q<T> Q4){};
	//Matrix4x4(Matrix3x3<T> _m, Vector<T> last = new Vector<T>((T)0,(T)0,(T)0), T fill = (T)0){matrix[0]=_m.x.x;matrix[1]=_m.x.y;matrix[2]=_m.x.z;matrix[3]=(T)0;
	//											matrix[4]=_m.y.x;matrix[5]=_m.y.y;matrix[6]=_m.y.z;matrix[7]=(T)0;
	//											matrix[8]=_m.z.x;matrix[9]=_m.z.y;matrix[10]=_m.z.z;matrix[11]=(T)0;
	//											matrix[12]= last.x;matrix[13]= last.y;matrix[14]= last.z;matrix[15]=(T)0; delete last;};
	~Matrix4x4(){};

	Matrix4x4 operator+(Matrix4x4 b){Matrix4x4 temp;
                                            #pragma omp parallel for 
                                            for(int i=0;i<16;i++) temp.m[i]=m[i]+b.m[i];
                                            return temp;};
	Matrix4x4 operator-(Matrix4x4 b){Matrix4x4 temp;
                                            #pragma omp parallel for 
                                            for(int i=0;i<16;i++) temp.m[i]=m[i]-b.m[i];
                                            return temp;};
	Matrix4x4 operator+=(Matrix4x4 b){Matrix4x4 temp;
                                            #pragma omp parallel for 
                                            for(int i=0;i<16;i++) temp.m[i]=m[i]+b.m[i];
                                            *(this) = temp;return *(this);};
	Matrix4x4 operator-=(Matrix4x4 b){Matrix4x4 temp;
                                            #pragma omp parallel for 
                                            for(int i=0;i<16;i++) temp.m[i]=m[i]-b.m[i];
                                            *(this) = temp;return *(this);};
	Matrix4x4 operator*(Matrix4x4 b){Matrix4x4 temp;int i,j;
	  #pragma omp parallel for default(none) shared(temp,b) private(i,j)
	  for(i=0;i<4;i++)
	    {
	      for(j=0; j<4;j++)
		{
		  temp.m[i+(j*4)]=(m[i]*b.m[j*4]+m[i+4]*b.m[(j*4)+1]+m[i+8]*b.m[(j*4)+2]+m[i+12]*b.m[(j*4)+3]);
		}
	    }
            return temp;};
	Matrix4x4 operator*=(Matrix4x4 b){Matrix4x4 temp;int i,j;
#pragma omp parallel for default(none) shared(temp,b) private(i,j)
	  for(i=0;i<4;i++)
	    {
	      for(j=0; j<4;j++)
		{
		  temp.m[i+(j*4)]=(m[i]*b.m[j*4]+m[i+4]*b.m[(j*4)+1]+m[i+8]*b.m[(j*4)+2]+m[i+12]*b.m[(j*4)+3]);
		}
	    }
	  *(this)=temp;
	  return *(this);};
	Matrix4x4 operator^(int power){if(power<-1) return Matrix4x4(); if(power == -1){*(this) *= Matrix4x4();return *(this);}if(power==0) return Matrix4x4();if(power == 1) return *(this);else for(int i=1;i<power;i++) *(this) *= *(this);return *(this);};


	T m[16];
};

#endif
