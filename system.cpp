#include "system.h"
#include "entity.h"
#include "renderer.h"
#include "component.h"
#include "event.h"
#include "renderer.h"
#include <cmath>

void BlitSpriteSystem(EntityManager* entMan, Renderer* renderer, int layer) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->position[j] && entMan->sprite[j] ) {

			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			SpriteComponent*   spr = (SpriteComponent*)entMan->sprite[j];
			Texture* tex  = renderer->GetTexture(spr->tName);

			if ( spr->layer != layer )
				continue;

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

			if (entMan->angle[j]) {
				RotateComponent* r = (RotateComponent*)entMan->angle[j];
				angle = r->angle;
			}

			if (entMan->spriteSpan[j]) {
				SpriteSpanComponent* spn = 
					(SpriteSpanComponent*)entMan->spriteSpan[j];

				repeat = spn->repeat;

			}

			if (entMan->anim[j]) {

				AnimComponent* anm = (AnimComponent*)entMan->anim[j];
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

}

void AngleTickSystem(EntityManager* entMan) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if (entMan->angle[j]) {

			RotateComponent* r = (RotateComponent*)entMan->angle[j];
			r->angle += r->angleAcc;

		}

	}

}

void SplashTickSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if (entMan->splashTick[j]) {

			PositionComponent* pos   = (PositionComponent*)entMan->position[j];
			SizeComponent* size      = (SizeComponent*)entMan->size[j];
			SpriteComponent* spr     = (SpriteComponent*)entMan->sprite[j];
			SplashTickComponent* stc = (SplashTickComponent*)entMan->splashTick[j];
			RotateComponent* rot     = (RotateComponent*)entMan->angle[j];

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

}

void MaskTickSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < MAX_ENTS; ++j) {
		
		if (entMan->maskTick[j]) {
			
			MaskTickComponent* msk = (MaskTickComponent*)entMan->maskTick[j];
			SpriteComponent* spr   = (SpriteComponent*)entMan->sprite[j];
			
			msk->value += msk->decay;

			if (msk->value < 0.0) {
				msk->value = 0.0;
			}

			spr->alpha = msk->value;

		}

	}

}

void FlappyPhysicsSystem(EntityManager* entMan) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if (entMan->flappyPhysics[j]) {
			
			FlappyPhysicsComponent* flap = 
				(FlappyPhysicsComponent*)entMan->flappyPhysics[j];
			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			RotateComponent* rot = (RotateComponent*)entMan->angle[j];

			flap->yAcc += flap->grav;
			pos->y += flap->yAcc;
			rot->angle = flap->yAcc;

			if ( entMan->size[j] ) {

				SizeComponent* siz = (SizeComponent*)entMan->size[j];

				pos->centreX = pos->x + (siz->w / 2.0);
				pos->centreY = pos->y + (siz->h / 2.0);

			}

		}

	}

}

void FlappyInputSystem(EntityManager* entMan) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if (entMan->flappyInput[j]) {

			FlappyInputComponent* fIn = 
				(FlappyInputComponent*)entMan->flappyInput[j];
			FlappyPhysicsComponent* flap = 
				(FlappyPhysicsComponent*)entMan->flappyPhysics[j];

			flap->yAcc += fIn->lift;

		}

	}

}

void PipeSpawnerTickSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if (entMan->pipeSpawn[j]) {
			
			PipeSpawnerComponent* pip = 
				(PipeSpawnerComponent*)entMan->pipeSpawn[j];

			pip->value += pip->decay;
			if ( pip->value <= 0.0 ) {
				pip->value = 1.0;
				eventManager->Post(new Event(SPAWN_PIPE, "q"));
			}

		}

	}

}

void PipeTickSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->pipe[j] ) {

			PipeComponent* pip = (PipeComponent*)entMan->pipe[j];
			PositionComponent* pos = (PositionComponent*)entMan->position[j];

			pos->y = pip->offset; //top of gap
			pos->x += pip->xAcc;

			if ( entMan->size[j] ) {

				SizeComponent* siz = (SizeComponent*)entMan->size[j];

				pos->centreX = pos->x + (siz->w / 2.0);
				pos->centreY = pos->y + (siz->h / 2.0);

			}


			if ( pos->x + 160.0 < 0.0 )
				entMan->KillEntity(j);

		}

	}

}

void PipeSpriteSystem(EntityManager* entMan, Renderer* renderer) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		if ( entMan->pipe[j] ) {

			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			PipeSpriteComponent* psp = 
				(PipeSpriteComponent*)entMan->pipeSprite[j];
			Texture* tex = renderer->GetTexture(psp->tName);
			//PipeComponent* pip = (PipeComponent*)entMan->pipe[j];

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

}

void CollisionHandlerSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		// find flappy
		if ( entMan->flappyPhysics[j] ) {

			PositionComponent* aPos = 
				(PositionComponent*)entMan->position[j];
			SizeComponent* aSize = 
				(SizeComponent*)entMan->size[j];

			if ( aPos->y + aSize->h >= WIN_Y - 160.0 ) {

				eventManager->Post(new Event(GAME_RESTART, "q"));
				return;

			}

			// find pipes
			for ( int i = 0; i < MAX_ENTS; ++i ) {

				if ( entMan->collidable[i] && j != i ) {

					PositionComponent* bPos = 
						(PositionComponent*)entMan->position[i];
					SizeComponent* bSize = 
						(SizeComponent*)entMan->size[i];

					// top pipe
					double topX = bPos->x;
					double topY = 0.0;
					double topW = 160.0;
					double topH = bPos->y;
					double tCnX = topX + (topW / 2.0);
					double tCnY = topY + (topH / 2.0);
					double tSpX = tCnX - aPos->centreX;
					double tSpY = tCnY - aPos->centreY;
					double tHfX = tCnX - topX;
					double tHfY = tCnY - topY;

					// bottom pipe
					double botX = bPos->x;
					double botY = bPos->y + bSize->h;
					double botW = 160.0;
					double botH = (WIN_Y - 160.0) - (botY);
					double bCnX = botX + (botW / 2.0);
					double bCnY = botY + (botH / 2.0);
					double bSpX = bCnX - aPos->centreX;
					double bSpY = bCnY - aPos->centreY;
					double bHfX = bCnX - botX;
					double bHfY = bCnY - botY;

					double aHalfX = aPos->centreX - aPos->x;
					double aHalfY = aPos->centreY - aPos->y;

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

			// prevent each collision being handled twice (A->B, B->A)
			return;

			}

		}}

	}

}

void HudSystem(EntityManager* entMan, Renderer* renderer) {

	for (int j = 0; j < MAX_ENTS; ++j) {

		// find flappy
		if ( entMan->flappyPhysics[j] ) {

			PositionComponent* aPos = 
				(PositionComponent*)entMan->position[j];

			// find pipes
			for ( int i = 0; i < MAX_ENTS; ++i ) {

				if ( entMan->collidable[i] && j != i ) {

					PositionComponent* bPos = 
						(PositionComponent*)entMan->position[i];
					SizeComponent* bSize = 
						(SizeComponent*)entMan->size[i];

					double topX = bPos->x;
					double topY = 0.0;
					double topW = 160.0;
					double topH = bPos->y;
					double tCnX = topX + (topW / 2.0);
					double tCnY = topY + (topH / 2.0);

					double botX = bPos->x;
					double botY = bPos->y + bSize->h;
					double botW = 160.0;
					double botH = (WIN_Y - 160.0) - (botY);
					double bCnX = botX + (botW / 2.0);
					double bCnY = botY + (botH / 2.0);

					renderer->DrawLine(
						tCnX, 
						tCnY, 
						aPos->centreX, 
						aPos->centreY
					);
					
					renderer->DrawLine(
						bCnX, 
						bCnY, 
						aPos->centreX, 
						aPos->centreY
					);

				}

			}

			// prevent each collision being handled twice (A->B, B->A)
			return;

		}

	}

}

