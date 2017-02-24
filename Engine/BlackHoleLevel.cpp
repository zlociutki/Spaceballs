#include "BlackHoleLevel.h"

BlackHoleLevel::BlackHoleLevel(AnimationFrames & background, AnimationFrames& cometAnim)
	:
	backGround(background, 2)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 765.0f);
	for (int i = 0; i < nCometsMax; ++i)
		comet.emplace_back<Comet>(Comet{ xDist(rng), cometAnim });
}

void BlackHoleLevel::Draw(Graphics & gfx)
{
	backGround.Draw(0, 0, gfx);
	for (int i = 0; i < nComets; ++i)
	{
		if (!comet[i].IsActive())
			continue;
		else
			comet[i].Draw(gfx);
	}
}

void BlackHoleLevel::Update(float dt)
{
	backGround.Advance();
	if (backGround.AnimEnd())
	{
		backGround.Reset();
	}

	for (int i = 0; i < nComets; ++i)
	{
		if (!comet[i].IsActive())
			continue;
		else
			comet[i].Update(dt);
	}

	if (((cometTimer += dt) > newComet) && nComets != nCometsMax)
	{
		++nComets;
		cometTimer = 0.0f;
	}
}

RectF BlackHoleLevel::GetCollisionRect()
{
	return RectF(holePos, dimension, dimension);
}

Comet & BlackHoleLevel::GetComet(int Idx)
{
	return comet[Idx];
}

const Comet & BlackHoleLevel::GetComet(int Idx) const
{
	return comet[Idx];
}

void BlackHoleLevel::Reset()
{
	for (int i = 0; i < nCometsMax; ++i)
	{
		comet[i].Reset();
		nComets = 0;
		cometTimer = 0.0f;
	}
}
