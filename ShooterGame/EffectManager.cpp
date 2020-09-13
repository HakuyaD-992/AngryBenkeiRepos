#include <EffekseerForDXLib.h>
#include "EffectManager.h"


void EffectManager::UpDate(void)
{
	UpdateEffekseer2D();
}

void EffectManager::Draw(void)
{
	DrawEffekseer2D();
}


bool EffectManager::StopAll(void)
{
	for (auto handle : playList_)
	{
		StopEffekseer2DEffect(handle.second);
	}
	return false;
}

void EffectManager::SetPos(std::string effectName, const Vector2I& pos)
{
	auto playit = playList_.find(effectName);

	SetPosPlayingEffekseer2DEffect(playit->second,
		static_cast<float>(pos.x), static_cast<float>(pos.y), 0.0f);
}

bool EffectManager::Play(std::string effectName, const Vector2I& pos, std::string num)
{
	auto name = effectName + num;
	playList_.emplace(name,PlayEffekseer2DEffect(GetHandle(effectName)));
	auto it = playList_.find(name);

	SetPosPlayingEffekseer2DEffect(it->second,
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

void EffectManager::DeleteEffect(std::string effectName,const bool& flg)
{
	if ((IsPlayingEffect(effectName) == -1)/* || flg*/)
	{
		auto delItr = playList_.find(effectName);
		playList_.erase(delItr);
	}
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
