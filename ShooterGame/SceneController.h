#pragma once
#include <vector>
#include <stack>
#include <functional>
#include <memory>

class BaseScene;
struct Input;

class SceneController
{
public:
	SceneController();
	~SceneController();

	void UpdateScene(const std::vector<std::shared_ptr<Input>>& input);

	void PushScene(std::shared_ptr<BaseScene> scene);

	void PopScene(void);

	void CleanupAndChangewScene(std::shared_ptr<BaseScene> scene);

	void ChangeScene(std::shared_ptr<BaseScene> scene);

private:
	std::deque<std::shared_ptr<BaseScene>> scene_;
	std::function<void(void)> postExecuter_;

};

