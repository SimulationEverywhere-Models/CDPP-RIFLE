/*******************************************************************
*
*  DESCRIPTION: Atomic Model BoltAssy
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#ifndef __BOLTASSY_H
#define __BOLTASSY_H

#include "atomic.h"     // class Atomic

class BoltAssy : public Atomic
{
public:
	BoltAssy( const string &name = "BoltAssy" ); //Default constructor
	virtual string className() const ;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in_bulletReady, &in_releaseBolt, &in_boltBack;
	Port &out_boltPosn, &out_bulletLoaded;
	Time preparationTime;

	int tempMsgVal;
	int boltFree;		//0 if it is not free, 1 if it is free
	int readyBullet;	//0 if it is not ready, 1 if it is ready
	int boltState; 		//0 if it is forward, 1 if it is back, 2 if it is obstructed

};	// class BoltAssy

// ** inline ** //
inline string BoltAssy::className() const
{
	return "BoltAssy" ;
}

#endif   //__BOLTASSY_H
