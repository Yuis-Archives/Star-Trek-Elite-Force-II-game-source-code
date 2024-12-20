//-----------------------------------------------------------------------------
//
//  $Logfile:: /Code/DLLs/game/closeInOnEnemy.hpp				              $
// $Revision:: 169                                                            $
//   $Author:: sketcher														  $
//     $Date:: 4/26/02 2:22p                                                  $
//
// Copyright (C) 2002 by Ritual Entertainment, Inc.
// All rights reserved.
//
// This source may not be distributed and/or modified without
// expressly written permission by Ritual Entertainment, Inc.
//
//
// DESCRIPTION:
// CloseInOnEnemy Behavior Definition
//
//--------------------------------------------------------------------------------

//==============================
// Forward Declarations
//==============================
class CloseInOnEnemy;

#ifndef __CLOSE_IN_ON_ENEMY_HPP__
#define __CLOSE_IN_ON_ENEMY_HPP__

#include "behavior.h"
#include "behaviors_general.h"

//------------------------- CLASS ------------------------------
//
// Name:           CloseInOnEnemy
// Base Class:     Behavior
//
// Description:    Makes the actor move closer to its current enemy
//
// Method of Use:  Called From State Machine
//--------------------------------------------------------------
class CloseInOnEnemy : public Behavior
{
	//------------------------------------
	// States
	//------------------------------------
	public:
		typedef enum
		{	
			CLOSE_IN_ON_ENEMY_APPROACH,
			CLOSE_IN_ON_ENEMY_SUCCESS,
			CLOSE_IN_ON_ENEMY_FAILED
		} closeInOnEnemyStates_t;

	//------------------------------------
	// Parameters
	//------------------------------------
	private: // Parameters
		str							_anim;  
		str							_torsoAnim;
		float						_dist;

	//-------------------------------------
	// Internal Functionality
	//-------------------------------------
	protected:
		void	transitionToState	( closeInOnEnemyStates_t state );
		void	setInternalState	( closeInOnEnemyStates_t state , const str &stateName );
		void	init				( Actor &self );
		void	think				();
		void	updateEnemy			();
		void	setTorsoAnim		();	

		void					setupStateApproach		();
		BehaviorReturnCode_t	evaluateStateApproach	();
		void					failureStateApproach	( const str& failureReason );

	//-------------------------------------
	// Public Interface
	//-------------------------------------
	public:
		CLASS_PROTOTYPE( CloseInOnEnemy );

												CloseInOnEnemy();
											   ~CloseInOnEnemy();

		void									SetArgs		( Event *ev     );      
		void									Begin		( Actor &self   );		
		BehaviorReturnCode_t					Evaluate	( Actor &self   );
		void									End			( Actor &self   );
		virtual void							Archive		( Archiver &arc );

		void									setAnim		( const str &animName );
		void									setTorsoAnim( const str &animName );
		void									setDist		( float distance      );

	//-------------------------------------
	// Components
	//-------------------------------------
	private:      
		GotoEntity								_chaseEnemy;

	//-------------------------------------
	// Member Variables
	//-------------------------------------
	private: 
		closeInOnEnemyStates_t					_state;
		EntityPtr								_currentEnemy;
		Actor								   *_self;

};

inline void CloseInOnEnemy::setAnim( const str &animName )
{
	_anim = animName;
}

inline void CloseInOnEnemy::setTorsoAnim( const str &animName )
{
	_torsoAnim = animName;
}

inline void CloseInOnEnemy::setDist( float distance )
{
	_dist = distance;
}

inline void CloseInOnEnemy::Archive( Archiver &arc	)
{
	Behavior::Archive( arc );	 
   
   // Archive Parameters
	arc.ArchiveString ( &_anim );
	arc.ArchiveString ( &_torsoAnim );
	arc.ArchiveFloat  ( &_dist );

   // Archive Components
	arc.ArchiveObject ( &_chaseEnemy );

   // Archive Member Variables
	ArchiveEnum					( _state, closeInOnEnemyStates_t);
	arc.ArchiveSafePointer		( &_currentEnemy				);
	arc.ArchiveObjectPointer	( ( Class ** )&_self			);
}  

#endif /* CLOSE_IN_ON_ENEMY_HPP */
