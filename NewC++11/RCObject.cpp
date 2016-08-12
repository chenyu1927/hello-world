#include "RCObject.h"

RCObject::RCObject()
	: ref_(0), shareable_(true)
{

}

RCObject::RCObject(const RCObject& other)
	: ref_(0), shareable_(true)
{

}

RCObject& RCObject::operator=(const RCObject& other)
{
	return *this;
}

RCObject::~RCObject()
{

}

void RCObject::addRef()
{
	++ ref_;
}

void RCObject::release()
{
	if (-- ref_ == 0)
		delete this;
}

void RCObject::markUnshareable()
{
	shareable_ = false;
}

bool RCObject::isShareable() const
{
	return shareable_;
}

bool RCObject::isShared() const
{
	return ref_ > 0;
}
