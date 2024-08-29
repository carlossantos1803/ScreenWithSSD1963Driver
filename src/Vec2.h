#pragma once

#include <Arduino.h>

class Vec2 
{

	public:
		float x = 0.0f;
		float y = 0.0f;
		
		Vec2();
		Vec2(float xin, float yin);
		
		bool operator == (const Vec2& rhs) const;
		bool operator != (const Vec2& rhs) const; 
		
		Vec2 operator + (const Vec2& rhs) const ;
		Vec2 operator - (const Vec2& rhs) const ;
		Vec2 operator / (const float val) const ;
		Vec2 operator * (const float val) const ;

		void operator += (const Vec2& rhs);
		void operator -= (const Vec2& rhs);
		void operator *= (const float val);
		void operator /= (const float val);
		//void operator *  (const int32_t val);

		//void map_float_to_int(float value = 10); //float value)
		void setMag( float magnitud );
		float mag() const;
		float dot(const Vec2& rhs) const; 
		float distance(const Vec2& rhs) const;
		
		void normalize(float dist);

		void speed(int32_t _velocity, int32_t _tita);
		void printVec(const char *_msg = " "); //String *_msg);
		//void printVec(const String _msg);
};
