#pragma once
#include <memory>
#include <vector>
#include "Player.h"
#include "Geometory.h"


class Viewport
{
public:
	Vector2I GetSize(void)const;
};

class SceneController;
struct Input;

class Application
{
public:
	static Application& Instance(void)
	{
		static Application sInstance;
		return sInstance;
	}
	Viewport viewport_;
	// ‰Šú‰»ŠÖŒW
	bool Initialize(void);
	// I—¹
	void Exit(void);

	void Run(void);

	void Terminate(void);
	// ‰æ–Ê»²½Şæ“¾
	const Viewport& GetViewport(void) const;
	// ¹Ş°ÑºİÄÛ°×°æ“¾
	std::shared_ptr<Input>& GetInput(const PLAYER& player);
private:
	Application() = default;
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	// ¹Ş°ÑºİÄÛ°×°
	std::vector<std::shared_ptr<Input>> input_;
	// ¼°İºİÄÛ°×°
	std::shared_ptr<SceneController> sceneCtl_;

	bool isExit_ = false;
};

