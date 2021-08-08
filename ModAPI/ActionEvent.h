#pragma once
#include <functional>
#include <vector>

namespace ModAPI
{
	class ActionEvent {
	public:
		void AddListener(std::function<void()> funcToAdd);
		void RemoveListener(std::function<void()> funcToRemove);
		void Invoke();
		int GetListenersCount() const;
		

	private:
		std::vector<std::function<void()>> listeners;
	};
}
