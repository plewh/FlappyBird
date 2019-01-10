#include "system.h"
#include "entity.h"
#include "renderer.h"
#include "component.h"
#include "event.h"

void BlitSpriteSystem(EntityManager* entMan, Renderer* renderer) {

	for (int j = 0; j < entMan->entCount; ++j)
		if (entMan->position[j] && entMan->sprite[j]) {

			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			SpriteComponent*   spr = (SpriteComponent*)entMan->sprite[j];
			Texture* tex  = renderer->GetTexture(spr->tName);

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

void AngleTickSystem(EntityManager* entMan) {

	for (int j = 0; j < entMan->entCount; ++j) {

		if (entMan->angle[j]) {

			RotateComponent* r = (RotateComponent*)entMan->angle[j];
			r->angle += r->angleAcc;

		}

	}

}

void SplashTickSystem(EntityManager* entMan, EventManager* eventManager) {

	for (int j = 0; j < entMan->entCount; ++j) {

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

	for (int j = 0; j < entMan->entCount; ++j) {
		
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

	for (int j = 0; j < entMan->entCount; ++j) {

		if (entMan->flappyPhysics[j]) {
			
			FlappyPhysicsComponent* flap = 
				(FlappyPhysicsComponent*)entMan->flappyPhysics[j];
			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			RotateComponent* rot = (RotateComponent*)entMan->angle[j];

			flap->yAcc += flap->grav;
			pos->y += flap->yAcc;
			rot->angle = flap->yAcc;

		}

	}

}

void FlappyInputSystem(EntityManager* entMan) {

	for (int j = 0; j < entMan->entCount; ++j) {

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

	for (int j = 0; j < entMan->entCount; ++j) {

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
