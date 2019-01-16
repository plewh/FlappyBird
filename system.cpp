#include "system.h"
#include "entity.h"
#include "renderer.h"
#include "component.h"
#include "event.h"
#include "renderer.h"
#include <cmath>

void BlitSpriteSystem(
	EntityManager* entMan, int id, Renderer* renderer, int layer) {

	if ( entMan->position[id] && entMan->sprite[id] ) {

		PositionComponent* pos = (PositionComponent*)entMan->position[id];
		SpriteComponent*   spr = (SpriteComponent*)entMan->sprite[id];
		Texture* tex  = renderer->GetTexture(spr->tName);

		if ( spr->layer != layer )
			return;

		double x      = pos->x;
		double y      = pos->y;
		int    w      = tex->w;
		int    h      = tex->h;
		double scale  = spr->scale;
		double angle  = 0.0;
		double alpha  = spr->alpha;
		int    repeat = 1;
		int    frame  = 0;
		int    offset = -1;

		if (entMan->angle[id]) {
			RotateComponent* r = (RotateComponent*)entMan->angle[id];
			angle = r->angle;
		}

		if (entMan->spriteSpan[id]) {
			SpriteSpanComponent* spn = 
				(SpriteSpanComponent*)entMan->spriteSpan[id];

			repeat = spn->repeat;

		}

		if (entMan->anim[id]) {

			AnimComponent* anm = (AnimComponent*)entMan->anim[id];
			w = anm->w;
			h = anm->h;

			anm->value += anm->decay;
			if (anm->value <= 0.0) {
				anm->value = 1.0;
				anm->currFrame = (anm->currFrame + 1) % anm->fCount;
			}

			frame = anm->currFrame;
			if (anm->offset != -1)
				offset = anm->offset;

		}

		for (int j = 0; j < repeat; ++j) {
			renderer->Blit(
				x + (j * w), y, w, h, angle, 
				tex,
				scale,
				alpha,
				frame,
				offset
			);

		}

	}

}

void AngleTickSystem(EntityManager* entMan, int id) {

	if (entMan->angle[id]) {

		RotateComponent* r = (RotateComponent*)entMan->angle[id];
		r->angle += r->angleAcc;

	}

}

void SplashTickSystem(EntityManager* entMan, int id, EventManager* eventManager) {

	if (entMan->splashTick[id]) {

		PositionComponent* pos   = (PositionComponent*)entMan->position[id];
		SizeComponent* size      = (SizeComponent*)entMan->size[id];
		SpriteComponent* spr     = (SpriteComponent*)entMan->sprite[id];
		SplashTickComponent* stc = (SplashTickComponent*)entMan->splashTick[id];
		RotateComponent* rot     = (RotateComponent*)entMan->angle[id];

		if (!stc->ended) {
			rot->angleAcc = stc->rotAcc;
			spr->scale += stc->scaleAcc;

			if (spr->scale > 1.0) {
				spr->scale    = 1.0;
				rot->angleAcc = 0.0;
				rot->angle    = 0.0;
				stc->ended    = true;
				eventManager->Post(new Event(TITLE_SPLASH_DONE, ""));
			}

			pos->x = (WIN_X - (size->w * spr->scale)) / 2;
			pos->y = (WIN_Y - (size->h * spr->scale)) / 2;
		}

	}

}

void MaskTickSystem(EntityManager* entMan, int id, EventManager* eventManager) {

	if (entMan->maskTick[id]) {
		
		MaskTickComponent* msk = (MaskTickComponent*)entMan->maskTick[id];
		SpriteComponent* spr   = (SpriteComponent*)entMan->sprite[id];
		
		msk->value += msk->decay;

		if (msk->value < 0.0) {
			msk->value = 0.0;
		}

		spr->alpha = msk->value;

	}

}

void FlappyPhysicsSystem(EntityManager* entMan, int id) {

	if (entMan->flappyPhysics[id]) {
		
		FlappyPhysicsComponent* flap = 
			(FlappyPhysicsComponent*)entMan->flappyPhysics[id];
		PositionComponent* pos = (PositionComponent*)entMan->position[id];
		RotateComponent* rot = (RotateComponent*)entMan->angle[id];
		SizeComponent* size  = (SizeComponent*)entMan->size[id];

		flap->yAcc += flap->grav;
		pos->y += flap->yAcc;
		if ( (pos->y + size->h) > (WIN_Y - 160) )
			pos->y = WIN_Y - 160 - size->h;
		rot->angle = flap->yAcc;

	}

}

void FlappyInputSystem(EntityManager* entMan, int id) {

	if (entMan->flappyInput[id]) {

		FlappyInputComponent* fIn = 
			(FlappyInputComponent*)entMan->flappyInput[id];
		FlappyPhysicsComponent* flap = 
			(FlappyPhysicsComponent*)entMan->flappyPhysics[id];

		flap->yAcc += fIn->lift;
		if ( flap->yAcc < -20.0 ) {
			flap->yAcc = -20.0;
		}

		if ( flap->yAcc > 2.0 ) {
			flap->yAcc = 2.0;
		}

	}

}

void PipeSpawnerTickSystem(EntityManager* entMan, int id, EventManager* eventManager) {

	if (entMan->pipeSpawn[id]) {
		
		PipeSpawnerComponent* pip = 
			(PipeSpawnerComponent*)entMan->pipeSpawn[id];

		pip->value += pip->decay;
		if ( pip->value <= 0.0 ) {
			pip->value = 1.0;
			eventManager->Post(new Event(SPAWN_PIPE, "q"));
		}

	}

}

void PipeTickSystem(EntityManager* entMan, int id, EventManager* eventManager) {

	if ( entMan->pipe[id] ) {

		PipeComponent* pip = (PipeComponent*)entMan->pipe[id];
		PositionComponent* pos = (PositionComponent*)entMan->position[id];

		pos->y = pip->offset; //top of gap
		pos->x += pip->xAcc;

		if ( pos->x + 160.0 < 0.0 )
			entMan->KillEntity(id);

	}

}

void PipeSpriteSystem( EntityManager* entMan, int id, Renderer* renderer ) {

	if (entMan->pipeSprite[id]) {

		PositionComponent* pos = (PositionComponent*)entMan->position[id];
		PipeSpriteComponent* psp = 
			(PipeSpriteComponent*)entMan->pipeSprite[id];
		Texture* tex = renderer->GetTexture(psp->tName);

		// pipe top
		renderer->Blit(
			pos->x,
			pos->y - 800,
			tex->w,
			tex->h,
			0.0,
			tex,
			1.0,
			255.0,
			0,
			-1
		);

		// pipe bottom
		renderer->Blit(
			pos->x,
			pos->y + PIPE_GAP,
			tex->w,
			tex->h,
			0.0,
			tex,
			1.0,
			255.0,
			0,
			-1
		);

	}

}

void CollisionHandlerSystem(EntityManager* entMan, int id, EventManager* eventManager) {

	// find flappy
	if ( entMan->flappyPhysics[id] ) {

		PositionComponent* aPos = 
			(PositionComponent*)entMan->position[id];
		SizeComponent* aSize = 
			(SizeComponent*)entMan->size[id];

		if ( aPos->y + aSize->h >= WIN_Y - 160.0 ) {

			eventManager->Post(new Event(GAME_RESTART, "q"));
			return;

		}

		// find pipes
		for ( int i = 0; i < MAX_ENTS; ++i ) {

			if ( entMan->collidable[i] && id != i ) {

				PositionComponent* bPos = 
					(PositionComponent*)entMan->position[i];
				SizeComponent* bSize = 
					(SizeComponent*)entMan->size[i];

				// top pipe
				double topX = bPos->x; // origin x
				double topY = 0.0; // origin y
				double topW = 160.0; // width
				double topH = bPos->y; // height
				double tCnX = topX + (topW / 2.0); // centre x
				double tCnY = topY + (topH / 2.0); // centre y
				double tSpX = tCnX - ( aPos->x + ( aSize->w / 2.0 ) ); // seperation x
				double tSpY = tCnY - ( aPos->y + ( aSize->h / 2.0 ) ); // seperation y
				double tHfX = tCnX - topX; // half width origin x
				double tHfY = tCnY - topY; // half width origin y

				// bottom pipe
				double botX = bPos->x;
				double botY = bPos->y + bSize->h;
				double botW = 160.0;
				double botH = (WIN_Y - 160.0) - (botY);
				double bCnX = botX + (botW / 2.0);
				double bCnY = botY + (botH / 2.0);
				double bSpX = bCnX - ( aPos->x + ( aSize->w / 2.0 ) ); // seperation x
				double bSpY = bCnY - ( aPos->y + ( aSize->h / 2.0 ) ); // seperation y
				double bHfX = bCnX - botX;
				double bHfY = bCnY - botY;

				double aHalfX = ( aPos->x + ( aSize->w / 2.0 ) ) - aPos->x;
				double aHalfY = ( aPos->y + ( aSize->h / 2.0 ) ) - aPos->y;

				double topPenX = abs(tSpX) - (aHalfX + tHfX);
				if ( topPenX > 0.0 )
					topPenX = 0.0;
				double topPenY = abs(tSpY) - (aHalfY + tHfY);
				if ( topPenY > 0.0 )
					topPenY = 0.0;

				double botPenX = abs(bSpX) - (aHalfX + bHfX);
				if ( botPenX > 0.0 )
					botPenX = 0.0;
				double botPenY = abs(bSpY) - (aHalfY + bHfY);
				if ( botPenY > 0.0 )
					botPenY = 0.0;

				if (topPenX != 0.0 && topPenY != 0.0) {

					eventManager->Post(new Event(GAME_RESTART, "q"));
					return;

				}

				if (botPenX != 0.0 && botPenY != 0.0) {

					eventManager->Post(new Event(GAME_RESTART, "q"));
					return;

				}

				// check for score trigger collision
				if ( (aPos->x + aSize->w) > bPos->x + ((160.0 / 3.0) * 2) ) {

					PipeComponent* pip = (PipeComponent*)entMan->pipe[i];

					if ( pip->hasScore ) {
						pip->hasScore = false;
						eventManager->Post(new Event(INC_SCORE, " "));
					}
				}

				// prevent flappy going over pipes
				if ( aPos->y + aSize->h <= 0 ) {

					if ( (aPos->x + aSize->w > bPos->x) && 
						 (aPos->x + aSize->w < bPos->x + bSize->w) )
						eventManager->Post(new Event(GAME_RESTART, "q"));
				}

				return;

			}

		}
	
	}

}

void HudSystem(EntityManager* entMan, int id, Renderer* renderer) {

	if ( entMan->score[id] ) {

		PositionComponent* pos = 
			(PositionComponent*)entMan->position[id];
		ScoreComponent* scr = 
			(ScoreComponent*)entMan->score[id];
		
		char buff[10];
		sprintf(buff, "%d / %d", scr->score, scr->maxScore);
		renderer->Print(pos->x, pos->y, buff);

	}

}
