#include "system.h"
#include "entity.h"
#include "renderer.h"
#include "component.h"
#include "event.h"

void BlitSpriteSystem(Renderer* renderer, EntityManager* entMan) {

	for (int j = 0; j < entMan->entCount; ++j)
		if (entMan->position[j] && entMan->sprite[j]) {

			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			SpriteComponent*   spr = (SpriteComponent*)entMan->sprite[j];

			double x     = pos->x;
			double y     = pos->y;
			double scale = spr->scale;
			double angle = 0.0;
			double alpha = spr->alpha;

			if (entMan->angle[j]) {
				RotateComponent* r = (RotateComponent*)entMan->angle[j];
				angle = r->angle;
			}

			renderer->Blit(
				x, y, angle, 
				renderer->GetTexture(spr->tName),
				scale,
				alpha
			);

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
