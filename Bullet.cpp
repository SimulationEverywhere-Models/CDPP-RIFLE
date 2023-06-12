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

/** include files **/
#include "Bullet.h"			// class Bullet
#include "message.h"		// class ExternalMessage, InternalMessage
#include "mainsimu.h"		// MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Bullet
* Description: This model represents a simplistic bullet. A bullet
* is either a good bullet, or a Dud. This is approximated by a simple
* random function.
********************************************************************/

Bullet::Bullet( const string &name )
: Atomic( name )
, in_bulletReady( addInputPort( "in_bulletReady") )
, out_isDud( addOutputPort( "out_isDud") )
, out_bulletReady( addOutputPort( "out_bulletReady") )

, preparationTime( 0, 0, 0, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;
	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Initializes the current function parameters
********************************************************************/
Model &Bullet::initFunction()
{
	bulletRdy = 0;
	isDud = 0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: response to the receptions of external event. This model only
* outputs Dud-rate of a bullet, no inputs.
********************************************************************/
Model &Bullet::externalFunction( const ExternalMessage &msg )
{
	bulletRdy = (int) msg.value ();

	if( bulletRdy == 1 )		//don't need to check the port name, as there is only one port
	{
		if ((double)rand() / (double)RAND_MAX < 0.95)	//5% of all bullets will be duds
			isDud = 0;
		else isDud = 1;
		holdIn( active, preparationTime );
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: invoked after the end of external function to do internal transition
********************************************************************/
Model &Bullet::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: performs the output function
********************************************************************/
Model &Bullet::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out_isDud, isDud);
	sendOutput (msg.time(), out_bulletReady, bulletRdy);
	return *this ;
}
