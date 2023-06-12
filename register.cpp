/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Erik Esselaar
*
*  EMAIL: esselaar@sce.carleton.ca
*
*  DATE: 03/11/2009
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "queue.h"      // class Queue

#include "BoltAssy.h"
#include "Bullet.h"
#include "Chamber.h"
#include "Magazine.h"
#include "TrigAssy.h"

void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BoltAssy>() ,"BoltAssy" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Bullet>() ,"Bullet" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Chamber>() ,"Chamber" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Magazine>() ,"Magazine" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<TrigAssy>() ,"TrigAssy" ) ;
}
