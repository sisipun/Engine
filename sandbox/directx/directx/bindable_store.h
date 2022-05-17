#ifndef BINDABLE_STORE_H
#define BINDABLE_STORE_H

#include <memory>
#include <unordered_map>

#include "bindable.h"

class BindableStore
{
public:
	template<typename T, typename ...Params>
	static std::shared_ptr<T> resolve(const Renderer& renderer, Params&&...params) noexcept
	{
		return get().resolveBindable<T, Params...>(renderer, std::forward<Params>(params)...);
	}
private:
	template<class T, typename ...Params>
	std::shared_ptr<T> resolveBindable(const Renderer& renderer, Params&&...params) noexcept
	{
		const auto key = T::getUid(std::forward<Params>(params)...);
		auto iter = bindables.find(key);
		if (iter == bindables.end())
		{
			auto bindable = std::make_shared<T>(renderer, std::forward<Params>(params)...);
			bindables[key] = bindable;
			return bindable;
		}

		return std::static_pointer_cast<T>(iter->second);
	}

	static BindableStore& get()
	{
		static BindableStore codex;
		return codex;
	}

	std::unordered_map<std::string, std::shared_ptr<Bindable>> bindables;
};

#endif 