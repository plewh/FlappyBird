#include "system.h"
#include "entity.h"
#include "renderer.h"
#include "component.h"

void BlitSpriteSystem(Renderer* renderer, EntityManager* entMan) {

	for (int j = 0; j < entMan->entCount; ++j)
		if (entMan->position[j] && entMan->sprite[j]) {
			PositionComponent* pos = (PositionComponent*)entMan->position[j];
			SpriteComponent*   spr = (SpriteComponent*)entMan->sprite[j];
			renderer->Blit(
				pos->x,
				pos->y,
				renderer->GetTexture(spr->tName)
			);
		}

}


