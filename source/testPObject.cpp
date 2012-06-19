#include "../ExGine/pobject.h"

#include <iostream>

int main(int argc, char** argv)
{

PObject *ob1, *ob2, *ob3;
ob1 = new POSphere();
ob2 = new POSphere();
ob3 = new POPlane();
bool done = false;
char choice;
double tx,ty,tz;

Vector<double> pos1(0.0,0.0,0.0);
Vector<double> pos2(0.0,1.0,0.0);
Vector<double> pos3(0.0,-1.0,0.0);
varList radius1;
varList radius2;
varList plane1;

radius1.push_back(0.5);//trash field that is hardcoded in the object, but we still need to push something in that field
radius1.push_back(0.5);

radius2.push_back(0.5);//trash field that is hardcoded in the object, but we still need to push something in that field
radius2.push_back(0.5);

plane1.push_back(0.0);//trash field that is hardcoded in the object, but we still need to push something in that field
plane1.push_back(0.0);
plane1.push_back(1.0);
plane1.push_back(0.0);
plane1.push_back(2.0);
plane1.push_back(2.0);

while(!done)
{
	ob1->setPoM(pos1);
	ob2->setPoM(pos2);
	ob3->setPoM(pos3);
	ob1->setStats(radius1);
	ob2->setStats(radius2);
	ob3->setStats(plane1);

	std::cout.precision(4);

	std::cout<<"Object1: x="<<pos1.x<<" y="<<pos1.y<<" z="<<pos1.z<<" r="<<radius1[1]<<"\n"; 
	std::cout<<"Object2: x="<<pos2.x<<" y="<<pos2.y<<" z="<<pos2.z<<" r="<<radius2[1]<<"\n";
	std::cout<<"Object3: x="<<pos3.x<<" y="<<pos3.y<<" z="<<pos3.z<<" n="<<plane1[1]<<","<<plane1[2]<<","<<plane1[3]<<"\n\n";

	if (ob1->detectCollision(ob2)<=0.0)
		std::cout<<"spheres hit\n"<<std::endl;
	else
		std::cout<<"spheres no hit\n"<<std::endl;
	
	if (ob1->detectCollision(ob3)<=0.0)
		std::cout<<"sphere1+P hit\n"<<std::endl;
	else
		std::cout<<"sphere1+P no hit\n"<<std::endl;
	
	if (ob3->detectCollision(ob2)<=0.0)
		std::cout<<"sphere2+P hit\n"<<std::endl;
	else
		std::cout<<"sphere2+P no hit\n"<<std::endl;

	std::cout<<"What would you like to do?\n";
	std::cout<<"1)Change object #1's position.\n";
	std::cout<<"2)Change object #1's radius.\n";
	std::cout<<"3)Change object #2's position.\n";
	std::cout<<"4)Change object #2's radius.\n";
	std::cout<<"5)Change object #3's position.\n";
	std::cout<<"6)Change object #3's normal.\n";
	std::cout<<"7)Change object #3's L&W.\n";

	std::cout<<"0)Quit"<<std::endl;

	std::cin>>choice;

	switch(choice)
	{
	
		case '1':
			std::cout<<"\nobj1 x:";
			std::cin>>tx;
			std::cout<<"\nobj1 y:";
			std::cin>>ty;
			std::cout<<"\nobj1 z:";
			std::cin>>tz;
			pos1.x=tx;
			pos1.y=ty;
			pos1.z=tz;
			break;	
		case '2':
			std::cout<<"\nobj1 r:";
			std::cin>>tx;
			radius1[1]=tx;
			break;
		case '3':
			std::cout<<"\nobj2 x:";
			std::cin>>tx;
			std::cout<<"\nobj2 y:";
			std::cin>>ty;
			std::cout<<"\nobj2 z:";
			std::cin>>tz;
			pos2.x=tx;
			pos2.y=ty;
			pos2.z=tz;	
			break;	
		case '4':
			std::cout<<"\nobj2 r:";
			std::cin>>tx;
			radius2[1]=tx;
			break;
		case '5':
			std::cout<<"\nobj3 x:";
			std::cin>>tx;
			std::cout<<"\nobj3 y:";
			std::cin>>ty;
			std::cout<<"\nobj3 z:";
			std::cin>>tz;
			pos3.x=tx;
			pos3.y=ty;
			pos3.z=tz;	
			break;	
		case '6':
	  		std::cout<<"\nobj3 nx:";
			std::cin>>tx;
			std::cout<<"\nobj3 ny:";
			std::cin>>ty;
			std::cout<<"\nobj3 nz:";
			std::cin>>tz;
			plane1[1]=tx;
			plane1[2]=ty;
			plane1[3]=tz;	
			break;	
		case '7':
			std::cout<<"\nobj3 length:";
			std::cin>>tx;
			std::cout<<"\nobj3 width:";
			std::cin>>ty;
			plane1[4]=tx;
			plane1[5]=ty;
			break;	
		case '0':
			done = true;
			break;	
		default:
			std::cout<<"\nInvalid entry"<<std::endl;
	}
}

return 0;
}
