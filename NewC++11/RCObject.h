#ifndef RCOBJECT_H_H
#define RCOBJECT_H_H

class RCObject
{
public:
	RCObject();
	RCObject(const RCObject& other);
	RCObject& operator=(const RCObject& other);
	virtual ~RCObject();

	void addRef();
	void release();
	
	void markUnshareable();
	bool isShareable() const;
	bool isShared() const;


private:
	int ref_;
	bool shareable_;
};







#endif /* RCOBJECT_H_H */
