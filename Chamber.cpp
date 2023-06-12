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

/** include files **/
#include "Chamber.h"	// class Chamber
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name:	Chamber
* Description:
********************************************************************/
Chamber::Chamber( const string &name )
: Atomic( name )
, in_isDud( addInputPort( "in_isDud" ) )
, in_bulletLoaded( addInputPort( "in_bulletLoaded" ) )
, out_boltBack( addOutputPort( "out_boltBack" ) )
, out_bulletFired( addOutputPort( "out_bulletFired" ) )
, out_casing( addOutputPort( "out_casing" ) )
, preparationTime( 0, 0, 0, 5 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;

}

/*******************************************************************
* Function Name: initFunction
* Description: Initializes the current function parameters
********************************************************************/
Model &Chamber::initFunction()
{
	dudBullet = 2; 			//by default, set first bullet to a false value
	bulletIn = 0;			//by default, there is no bullet in the chamber

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: response to the receptions of external event
********************************************************************/

Model &Chamber::externalFunction( const ExternalMessage &msg )
{
	if ( msg.port() == in_isDud )
	{
		dudBullet = (int)msg.value();
	}
	else if( msg.port() == in_bulletLoaded )
	{
		bulletIn = (int)msg.value();
		holdIn( active, preparationTime );		//only pass time for the actual firing event if a bullet has been loaded.
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: invoked after the end of external function to do internal transition
********************************************************************/
Model &Chamber::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: performs the output function
********************************************************************/
Model &Chamber::outputFunction( const InternalMessage &msg )
{
	if ((dudBullet == 0) && (bulletIn == 1))				//a good /non-dud bullet is loaded and fired!
	{
		sendOutput( msg.time(), out_boltBack, 1 ) ;			//the bolt is pushed back
		sendOutput( msg.time(), out_bulletFired, 1 ) ;		//a bullet exits the weapon
		sendOutput( msg.time(), out_casing, 1 ) ;			//a casing is ejected from the chamber
		dudBullet = 2;										//clear the dudBullet variable, until next value is received
		bulletIn = 0;										//clear the bulletIn variable, until next bullet is loaded
	}

return *this ;
}
