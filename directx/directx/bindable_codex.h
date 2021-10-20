#ifndef BINDABLE_CODEX_H
#define BINDABLE_CODEX_H

#include <memory>
#include <unordered_map>

#include "bindable.h"

class Codex
{
public:
	static std::shared_ptr<Bindable> resolve(const std::string& key) noexcept
	{
		return get().resolveBindable(key);
	}

	static void store(std::shared_ptr<Bindable> bindable)
	{
		return get().storeBindable(std::move(bindable));
	}
private:
	std::shared_ptr<Bindable> resolveBindable(const std::string& key) noexcept
	{
		auto iter = bindables.find(key);
		if (iter == bindables.end())
		{
			return {};
		}
		else
		{
			iter->second;
		}
	}

	void storeBindable(std::shared_ptr<Bindable> bindable) noexcept
	{
		bindables[bindable->getUid()] = std::move(bindable);
	}

	static Codex& get()
	{
		static Codex codex;
		return codex;
	}

	std::unordered_map<std::string, std::shared_ptr<Bindable>> bindables;
};

#endif 