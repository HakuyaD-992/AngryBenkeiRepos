#include <EffekseerForDXLib.h>

#include "EffectManager.h"

void EffectManager::UpDate(void)
{
	UpdateEffekseer2D();

	auto itr = std::remove_if(playList_.begin(), playList_.end(),
		[](int handle) { return !IsEffekseer2DEffectPlaying(handle);
		});
	playList_.erase(itr, playList_.end());
}

void EffectManager::Draw(void)
{
	DrawEffekseer2D();
}


bool EffectManager::StopAll(void)
{
	for (auto handle : playList_)
	{
		StopEffekseer2DEffect(handle);
	}

	return false;
}

bool EffectManager::Play(std::string effectName, const Vector2I& pos)
{
	playList_.push_front(PlayEffekseer2DEffect(GetHandle(effectName)));
	SetPosPlayingEffekseer2DEffect(*(playList_.begin()),
		static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
	return true;
}

bool EffectManager::Init(const Vector2I& size)
{
	if (Effekseer_Init(8000) == -1)
	{
		return false;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	Effekseer_Set2DSetting(size.x, size.y);

	SetUseZBuffer3D(TRUE);

	SetWriteZBuffer3D(TRUE);

	return true;
}

const int& EffectManager::IsPlayingEffect(std::string effectName)
{
	return IsEffekseer2DEffectPlaying(handles_[effectName]);
}

const int& EffectManager::GetHandle(std::string effectName)
{
	return handles_[effectName];
}

void EffectManager::Load(std::string effectName)
{
	auto filepath = effectName + ".efk";
	handles_.try_emplace(effectName, LoadEffekseerEffect(filepath.c_str(), 1.0f));
}
