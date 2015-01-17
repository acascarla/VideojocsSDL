#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D(){
}
Vector2D::Vector2D(float x, float y){
	m_x = x;
	m_y = y;
}
Vector2D::~Vector2D(void){

}
float Vector2D::getX(){
	return m_x;
}
float Vector2D::getY(){
	return m_y;
}
void Vector2D::setX(float x){
	m_x = x;
}
void Vector2D::setY(float y){
	m_y = y;
}
Vector2D Vector2D::operator+(const Vector2D& v2) const{
	Vector2D vector_return;
	vector_return.m_x = m_x + v2.m_x;
	vector_return.m_y = m_y + v2.m_y;
	return vector_return;
}
Vector2D& Vector2D::operator+=(const Vector2D& v2){
	Vector2D vector_return;
	vector_return.m_x = m_x + v2.m_x;
	vector_return.m_y = m_y + v2.m_y;
	return vector_return;
}
Vector2D Vector2D::operator*(float scalar){
	Vector2D vector_return;
	vector_return.m_x = m_x * scalar;
	vector_return.m_y = m_y * scalar;
	return vector_return;
}
Vector2D& Vector2D::operator*=(float scalar){
	Vector2D vector_return;
	vector_return.m_x = m_x * scalar;
	vector_return.m_y = m_y * scalar;
	return vector_return;
}
Vector2D Vector2D::operator-() const{
	Vector2D vector_return;
	vector_return.m_x = -m_x;
	vector_return.m_y = -m_y;
	return vector_return;
}
Vector2D Vector2D::operator-(const Vector2D& v2) const{
	Vector2D vector_return;
	vector_return.m_x = m_x - v2.m_x;
	vector_return.m_y = m_y - v2.m_y;
	return vector_return;
}
Vector2D& Vector2D::operator-=(const Vector2D& v2){
	Vector2D vector_return;
	vector_return.m_x = m_x - v2.m_x;
	vector_return.m_y = m_y - v2.m_y;
	return vector_return;
}
Vector2D Vector2D::operator/(float scalar){
	Vector2D vector_return;
	vector_return.m_x = m_x / scalar;
	vector_return.m_y = m_y / scalar;
	return vector_return;
}
Vector2D& Vector2D::operator/=(float scalar){
	Vector2D vector_return;
	vector_return.m_x = m_x / scalar;
	vector_return.m_y = m_y / scalar;
	return vector_return;
}

float Vector2D::length(){
	float valor = sqrt((m_x*m_x) + (m_y*m_y));
	return valor;
}

void Vector2D::normalize(){
	float mida = length();
	m_x = (m_x / mida);
	m_y = (m_y / mida);
}

Vector2D& Vector2D::operator=(const Vector2D& v2){
	Vector2D vector_return;
	vector_return.m_x = v2.m_x;
	vector_return.m_y = v2.m_y;
	return vector_return;
}