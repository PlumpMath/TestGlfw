#pragma once

// Any class that inherits from this class will not be able
// to be copied.  This should be the default behavior for 
// MOST classes.
class NonCopyable
{
protected:
	NonCopyable() {}
private:
	NonCopyable(const NonCopyable&) = delete;
	const NonCopyable& operator=(const NonCopyable&) = delete;
};