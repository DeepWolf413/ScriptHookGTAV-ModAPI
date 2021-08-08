#include "ActionEvent.h"

void ModAPI::ActionEvent::AddListener(std::function<void()> funcToAdd)
{ listeners.push_back(funcToAdd); }

void ModAPI::ActionEvent::RemoveListener(std::function<void()> funcToRemove)
{
	// TODO: Implement RemoveListener.
	//listeners.erase(std::remove(listeners.begin(), listeners.end(), funcToRemove), listeners.end());
}

void ModAPI::ActionEvent::Invoke()
{
	for(auto listener : listeners)
	{ listener(); }
}

int ModAPI::ActionEvent::GetListenersCount() const
{ return listeners.size(); }
