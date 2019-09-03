#ifndef __UNCOPYABLE_H__
#define __UNCOPYABLE_H__


class Uncopyable
{
public:
	Uncopyable(){};
	~Uncopyable(){};
	
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};


#endif//__UNCOPYABLE_H__