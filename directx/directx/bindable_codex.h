#ifndef BINDABLE_CODEX_H
#define BINDABLE_CODEX_H

#include <memory>
#include <unordered_map>

#include "bindable.h"

class Codex
{
public:
	static std::shared_ptr<Bindable> resolve(std::shared_ptr<Bindable> bindable) noexcept
	{
		return get().resolveBindable(bindable);
	}
private:
	std::shared_ptr<Bindable> resolveBindable(std::shared_ptr<Bindable> bindable) noexcept
	{
		if (!bindable->isCacheable())
		{
			return bindable;
		}

		const auto key = bindable->getUid();
		auto iter = bindables.find(key);
		if (iter == bindables.end())
		{
			bindables[key] = bindable;
			return bindable;
		}
		
		return iter->second;
	}

	static Codex& get()
	{
		static Codex codex;
		return codex;
	}

	std::unordered_map<std::string, std::shared_ptr<Bindable>> bindables;
};

#endif 