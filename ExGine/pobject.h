#ifndef __POBJECT_H__
#define __POBJECT_H__

#include "base_elements.h"
#include "timer.h"
#include <vector>
//for debug
#include <iostream>

#define CHECK_INTRIVAL 50

//#define DEBUG_PHYSICS 

typedef std::vector<Scalar> varList;///< type for the varable list of stats for the objects

/// @brief The base class for all Physics Objects
///
/// This is the math base for the mathematic simplistic
/// representation of all physics based objects

class PObject
{
public:
	PObject(){timer.start();};///< default base constructer
	~PObject(){};///< default base destructer
	virtual void update()=0;///< pure virtual update
	/// @brief pure virtual detect collision
	///
	/// This is the function that we will use to figure
	/// out the distance from another object and thus if
	/// we collided with it
	/// @return Scalar value that is >0 if there is no collision
	/// =0 if they are just touching and
	/// <0 if they have hit to intersection(hit with force)
	/// @param brings in a pointer to a physics object to test
	/// for distance/collision
	virtual Scalar detectCollision(PObject* object)=0;
	
	/// @brief pure virtual get Statistics for the object
	///
	/// This is the function that we will use to get the object's
	/// data for the objects
	/// @return returns a list of stats. The first is the type ID.
	/// @param none
	virtual varList getStats()=0;
	virtual void setStats(varList _stats)=0;///< pure virtual set stats
	
	Vector<Scalar> getPoM(){return PoM;};///< get Point of Mass
	void setPoM(Vector<Scalar> _PoM){PoM = _PoM;};///< set Point of Mass
	Scalar getMass(){return mass;};///< get Mass
	void setMass(Scalar _m){mass = _m;};///< set Mass
	Vector<Scalar> getVelocity(){return velocity;};///< get Velocity
	void setVelocity(Vector<Scalar> _vel){velocity = _vel;};///< set Velocity
	Scalar getAccel(){return acceloration;};///< get Acceloration
	void setAccel(Scalar _accel){acceloration = _accel;};///< set Acceloration
	Scalar getMMoI(){return MassMomentOfInertia;};///< get Mass Moment of Inertia
	void setMMoI(Scalar _mmoi){MassMomentOfInertia = _mmoi;}; ///< set Mass Moment of Inertia
	void addForce(Vector<Scalar> newForce){forces.push_back(newForce);};
	std::vector<Vector<Scalar> > getForce(){return forces;};
	void runVelocity();
protected:
	Vector<Scalar> PoM;///< Point of Mass
	Scalar mass;///< Mass
	Vector<Scalar> velocity;///< Velocity
	Scalar acceloration;///< Acceloration
	Scalar MassMomentOfInertia;///< Mass Moment of Inertia
	std::vector<Vector<Scalar> > forces;
	Timer timer;
};

void PObject::runVelocity()
{
	if(!timer.isRunning())
		timer.start();
	
	Scalar deltaTimer = Scalar(timer.delta());
	if(deltaTimer>CHECK_INTRIVAL)
	{
		timer.reset();
		deltaTimer /= 1000;
		Vector<Scalar> tempVec = velocity * deltaTimer;
		PoM += tempVec;
	}
}

/// @brief Class for sphere Physics Objects
///
/// This is the math base for the mathematic simplistic
/// representation of spherical physics based objects

class POSphere:public PObject
{
public:
	POSphere(){};
	~POSphere(){};
	void update();
	Scalar detectCollision(PObject* object);
	varList getStats();
	void setStats(varList _stats);
protected:
	Scalar radius;
};

void POSphere::update()
{
	if(!timer.isRunning())
		timer.start();
	
	Scalar deltaTimer = Scalar(timer.delta());
	if(deltaTimer>CHECK_INTRIVAL)
	{
		timer.reset();
		deltaTimer /= 1000;
		Vector<Scalar> tempVec = velocity * deltaTimer;
		Vector<Scalar> tempForce;
		unsigned int i;
		#pragma omp parallel for private(i)
		for(i=0; i<forces.size(); i++)
		{
			tempForce = forces[i];
			tempForce *= deltaTimer;
			tempVec += tempForce;
			//std::clog<<"apply force: "<<forces.size()<<" vel "<<tempVec.x<<", "<<tempVec.y<<", "<<tempVec.z<<std::endl;
		}
		PoM += tempVec;
	}
}

Scalar POSphere::detectCollision(PObject* object)
{
	varList temp = object->getStats();
	Vector<Scalar> otherPoM = object->getPoM();
	Scalar dist = 0.0;
	
	if (temp[0] > 0.999&&temp[0]<1.001)//if a Scalar "equal" to 1.0 it's a sphere too
	{
		dist = DIST(otherPoM.x,otherPoM.y,otherPoM.z,PoM.x,PoM.y,PoM.z);

#ifdef DEBUG_PHYSICS		
		std::clog.precision(4);
		std::clog<<"SvS r1:"<<radius<<" r2:"<<temp[1]<<" dist:"<<dist<<" r1+r2="<<(radius+temp[1])<<(dist<=radius+temp[1]?" hit":" no hit")<<std::endl;
#endif		

		if (dist<=radius+temp[1])
		  return dist-(radius+temp[1]);
	}
	else if (temp[0] > 1.999&&temp[0]<2.001)//if a Scalar "equal" to 2.0 it's a plane too
	{
		Scalar d = temp[6];
		// this is a bad check for angular planes so need to take it out/change it when figure that out
		if (temp[2] == 1.0)//ground
		{
			if (PoM.z<(otherPoM.z-temp[4]/2)||PoM.x<(otherPoM.x-temp[5]/2)||PoM.z>(otherPoM.z+temp[4]/2)||PoM.x>(otherPoM.x+temp[5]/2))
				return 1.0;
			Scalar planeY = ((temp[1]*PoM.x)+(temp[3]*PoM.z)-d)/(-temp[2]);
			//dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			dist = (PoM.y - planeY) - radius;
			//dist = ((d - otherPoM.dot(normal))/ ( direction.dot(normal)));//+(temp[1]);
		}
		else if (temp[1] == 1.0)//wall in x
		{
			if (PoM.z<(otherPoM.z-temp[5]/2)||PoM.y<(otherPoM.y-temp[4]/2)||PoM.z>(otherPoM.z+temp[5]/2)||PoM.y>(otherPoM.y+temp[4]/2))
				return 1.0;
			Scalar planeX = ((temp[2]*PoM.y)+(temp[3]*PoM.z)-d)/(-temp[1]);
			//dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			dist = (PoM.x - planeX) - radius;
			//dist = ((d - otherPoM.dot(normal))/ ( direction.dot(normal)));//+(temp[1]);
		}
		else if (temp[3] == 1.0)//wall in z
		{
			if (PoM.y<(otherPoM.y-temp[4]/2)||PoM.x<(otherPoM.x-temp[5]/2)||PoM.y>(otherPoM.y+temp[4]/2)||PoM.x>(otherPoM.x+temp[5]/2))
				return 1.0;
			Scalar planeZ = ((temp[1]*PoM.x)+(temp[2]*PoM.y)-d)/(-temp[3]);
			//dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			dist = (PoM.z - planeZ) - radius;
			//dist = ((d - otherPoM.dot(normal))/ ( direction.dot(normal)));//+(temp[1]);
		}
		else
		{
			dist = ((temp[1]*(otherPoM.x-PoM.x)+temp[2]*(otherPoM.y-PoM.y)+temp[3]*(otherPoM.z-PoM.z))/(sqrt(temp[1]*temp[1]+temp[2]*temp[2]+temp[3]*temp[3])))-radius;
		}
		
		//std::clog.precision(4);
		//std::clog<<"SvP r1:"<<radius<<" n:"<<temp[1]<<","<<temp[2]<<","<<temp[3]<<" dist:"<<dist<<std::endl;
	}
	return dist;
}

varList POSphere::getStats()
{
	varList temp;
	
	temp.push_back(1.0);
	temp.push_back(radius);
	return temp;
}

void POSphere::setStats(varList _stats)
{
	if(_stats.size()>=3)
		return;
	radius = _stats[1];
	//std::clog<<"Set Sphere radius: "<<radius<<std::endl;
	//std::clog<<"Set Sphere radius: "<<_stats[1]<<std::endl;
}

/*
 *Ground Detection:
 * single plane(Point dot norm = d or Xnx +Yny+ Znz + -d = 0) = easy
 * just load 1point and the norm and you have the equation for the plane and can shoot a ray down from the PoM and do it that way...
 * dist = (d - PoM dot norm)/(dir{should be 0,-1,0} dot norm)
 * mesh terrain != easy
 * ... how do I want to do it? .... how should I detect a seperate poly?... 
 * ...what if I loaded the mesh in and then didn't do that plane/intersect calcs till I determined which poly it was over and then only calcing off of it...
 * 
 */

class POPlane:public PObject
{
public:
	POPlane(){length = width = d = 0.0;};
	~POPlane(){};
	void update();
	Scalar detectCollision(PObject* object);
	varList getStats();
	void setStats(varList _stats);
protected:
	Vector<Scalar> normal;
	Scalar length;
	Scalar width;
	Scalar d;
};

void POPlane::update()
{
	if(!timer.isRunning())
		timer.start();
	
	Scalar deltaTimer = Scalar(timer.delta());
	if(deltaTimer>CHECK_INTRIVAL)
	{
		timer.reset();
		deltaTimer /= 1000;
		Vector<Scalar> tempVec = velocity * deltaTimer;
		Vector<Scalar> tempForce;
		unsigned int i;
		#pragma omp parallel for private(i)
		for(i=0; i<forces.size(); i++)
		{
			tempForce = forces[i];
			tempForce *= deltaTimer;
			tempVec += tempForce;
			//std::clog<<"apply force: "<<forces.size()<<" vel "<<tempVec.x<<", "<<tempVec.y<<", "<<tempVec.z<<std::endl;
		}
		PoM += tempVec;
	}
}

Scalar POPlane::detectCollision(PObject* object)
{
	varList temp = object->getStats();
	Vector<Scalar> otherPoM = object->getPoM();
	Scalar dist = 0.0;
	//Vector<Scalar> direction(0.0, -1.0, 0.0);
	//Scalar planeY;
	
	if (temp[0] > 0.999&&temp[0]<1.001)//if a Scalar "equal" to 1.0 it's a sphere
	{
		//if(normal.y == 1.0)//ground
		//{
			//// this is a bad check for angular planes so need to take it out/change it when figure that out
			//if (otherPoM.z<(PoM.z-length/2)||otherPoM.x<(PoM.x-width/2)||otherPoM.z>(PoM.z+length/2)||otherPoM.x>(PoM.x+width/2))
				//return 1.0;
			
			//planeY = ((normal.x*otherPoM.x)+(normal.z*otherPoM.z)-d)/(-normal.y);
			////dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			//dist = (otherPoM.y - planeY) - temp[1];
		//}
		//else if(normal.x == 1.0)//wall in Z
		//{
			//// this is a bad check for angular planes so need to take it out/change it when figure that out
			//if (otherPoM.z<(PoM.z-width/2)||otherPoM.y<(PoM.y-length/2)||otherPoM.z>(PoM.z+width/2)||otherPoM.y>(PoM.y+length/2))
				//return 1.0;
			
			//planeY = ((normal.y*otherPoM.y)+(normal.z*otherPoM.z)-d)/(-normal.x);
			////dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			//dist = (otherPoM.x - planeY) - temp[1];
		//}
		//else if(normal.z == 1.0)//wall in X
		//{
			//// this is a bad check for angular planes so need to take it out/change it when figure that out
			//if (otherPoM.y<(PoM.y-length/2)||otherPoM.x<(PoM.x-width/2)||otherPoM.y>(PoM.y+length/2)||otherPoM.x>(PoM.x+width/2))
				//return 1.0;
			
			//planeY = ((normal.x*otherPoM.x)+(normal.y*otherPoM.y)-d)/(-normal.z);
			////dist = DIST(PoM.x,PoM.y,PoM.z,otherPoM.x,planeY,otherPoM.z);
			
			//dist = (otherPoM.z - planeY) - temp[1];
		//}
		//else
		//{			
			dist = ((normal.x*(otherPoM.x-PoM.x)+normal.y*(otherPoM.y-PoM.y)+normal.z*(otherPoM.z-PoM.z))/(sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z)))-temp[1];
			if(DIST(otherPoM.x,otherPoM.y,otherPoM.z,PoM.x,PoM.y,PoM.z)>sqrt(((length/2)*(length/2))+((width/2)*(width/2))))
				return 1.0;
			//std::clog<<"pt: "<<sqrt(((length/2)*(length/2))+((width/2)*(width/2)))<<std::endl;
		//}
		
		//dist = ((d - otherPoM.dot(normal))/ ( direction.dot(normal)));//+(temp[1]);
		//std::clog.precision(4);
		//std::clog<<"PvS r1:"<<temp[1]<<" n:"<<normal.x<<","<<normal.y<<","<<normal.z<<"--d:"<<d<<" dist:"<<dist<<std::endl;
		return dist;
	}
	else if (temp[0] > 1.999&&temp[0]<2.001)//if a Scalar "equal" to 2.0 it's a plane too
	{
		//std::clog.precision(4);
		//std::clog<<"PvP n1:"<<normal.x<<","<<normal.y<<","<<normal.z<<" n2:"<<temp[1]<<","<<temp[2]<<","<<temp[3]<<"--d:"<<d<<" dist:"<<dist<<std::endl;
		
		return dist;
	}
	return dist;
}

varList POPlane::getStats()
{
	varList temp;
	
	temp.push_back(2.0);
	temp.push_back(normal.x);
	temp.push_back(normal.y);
	temp.push_back(normal.z);
	temp.push_back(length);
	temp.push_back(width);
	temp.push_back(d);
	return temp;
}

void POPlane::setStats(varList _stats)
{
	if(_stats.size()>=6)
	{
		normal.x = _stats[1];
		normal.y = _stats[2];
		normal.z = _stats[3];
		
		length = _stats[4];
		width  = _stats[5];
		
		normal.normalize();
		
		d = (normal.x*PoM.x)+(normal.y*PoM.y)+(normal.z*PoM.z);
		
		//std::clog<<"set Plane Object to n:"<<_stats[1]<<","<<_stats[2]<<","<<_stats[3]<<" L:"<<_stats[4]<<" W:"<<_stats[5]<<std::endl;
		//std::clog<<"set Plane Object to n:"<<normal.x<<","<<normal.y<<","<<normal.z<<" L:"<<length<<" W:"<<width<<std::endl;
	}
}


#endif
