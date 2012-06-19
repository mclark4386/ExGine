#ifndef __EXO_KEYBOARD_H__
#define __EXO_KEYBOARD_H__

#define EXO_MAXKEYS 1024

class Keyboard
{
public:
	static Keyboard* getInstance();
	Keyboard* operator=(const Keyboard&){return singleton;};
	void delInstance();
	Keyboard();
	~Keyboard();
	void setKeyDown(int key){if(key>=EXO_MAXKEYS)return;map[key]=true;};
	void setKeyUp(int key){if(key>=EXO_MAXKEYS)return;map[key]=false;};
	bool getKey(int key){if(key>=EXO_MAXKEYS)return false;return map[key];};
protected:
	bool map[EXO_MAXKEYS];
	static Keyboard* singleton;
};

Keyboard* Keyboard::singleton = 0;
Keyboard* Keyboard::getInstance()
{
	if(singleton == 0)
		singleton = new Keyboard();
	
	return singleton;
}

void Keyboard::delInstance()
{
	Keyboard* tmp = singleton;
	singleton = 0;
	delete tmp;
}

Keyboard::Keyboard()
{	
	for(int i=0; i<EXO_MAXKEYS; i++)
		map[i] = false;
}

Keyboard::~Keyboard()
{
}

#endif
