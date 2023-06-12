/*******************************************************************
*
*  DESCRIPTION: Atomic Model Chamber
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#ifndef __CHAMBER_H
#define __CHAMBER_H

#include "atomic.h"     // class Atomic

class Chamber : public Atomic
{
public:
	Chamber ( const string &name = "Chamber" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_isDud, &in_bulletLoaded;
	Port &out_bulletFired, &out_casing, &out_boltBack;

	Time preparationTime;
	int dudBullet;			//0 if it is a good bullet, 1 if it is a Dud Bullet
	int bulletIn;			//0 if no bullet is in chamber, 1 if one is in chamber

};	// class Chamber

// ** inline ** //
inline string Chamber::className() const
{
	return "Chamber" ;
}

#endif   //__CHAMBER_H
