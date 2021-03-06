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
	// 初期化関係
	bool Initialize(void);
	// 終了
	void Exit(void);

	void Run(void);

	void Terminate(void);
	// 画面ｻｲｽﾞ取得
	const Viewport& GetViewport(void) const;
	// ｹﾞｰﾑｺﾝﾄﾛｰﾗｰ取得
	std::shared_ptr<Input>& GetInput(const PLAYER& player);
private:
	Application() = default;
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	// ｹﾞｰﾑｺﾝﾄﾛｰﾗｰ
	std::vector<std::shared_ptr<Input>> input_;
	// ｼｰﾝｺﾝﾄﾛｰﾗｰ
	std::shared_ptr<SceneController> sceneCtl_;

	bool isExit_ = false;
};

