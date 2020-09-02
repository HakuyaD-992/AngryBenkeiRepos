#include "SceneController.h"
#include "Input.h"
#include "BaseScene.h"

SceneController::SceneController()
{
	postExecuter_ = []() {};
}

SceneController::~SceneController()
{
}

void SceneController::ChangeScene(std::shared_ptr<BaseScene> scene)
{
	postExecuter_ = [this, scene]()
	{
		scene_.pop_front();
		scene_.emplace_front(scene);
	};
}

void SceneController::UpdateScene(const std::vector<std::shared_ptr<Input>>& input)
{
	if (scene_.empty())
	{
		return;
	}
	scene_.front()->UpDate(input);
	auto rit = scene_.rbegin();
	for (; rit != scene_.rend(); rit++)
	{
		(*rit)->Draw();
	}
	postExecuter_();
	postExecuter_ = []() {};
}

void SceneController::PushScene(std::shared_ptr<BaseScene> scene)
{
	if (scene_.empty())
	{
		scene_.emplace_front(scene);
	}
	else
	{
		postExecuter_ = [this, scene]()
		{
			scene_.emplace_front(scene);
		};
	}
}

void SceneController::PopScene()
{
	postExecuter_ = [this]()
	{
		scene_.pop_front();
	};
}

void SceneController::CleanupAndChangewScene(std::shared_ptr<BaseScene> scene)
{
	postExecuter_ = [this, scene]()
	{
		scene_.clear();
		scene_.emplace_front(scene);
	};
}

