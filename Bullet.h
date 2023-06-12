/*******************************************************************
*
*  DESCRIPTION: Atomic Model Bullet
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#ifndef __BULLET_H
#define __BULLET_H

#include "atomic.h"     // class Atomic

class Bullet : public Atomic
{
public:
	Bullet( const string &name = "Bullet" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_bulletReady;
	Port &out_isDud, &out_bulletReady;
	Time preparationTime;
	int bulletRdy;
	int isDud;

};	// class Bullet

// ** inline ** //
inline string Bullet::className() const
{
	return "Bullet" ;
}

#endif   //__BULLET_H
