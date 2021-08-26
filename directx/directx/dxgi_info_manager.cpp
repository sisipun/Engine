#include <dxgidebug.h>
#include <memory>

#include "base_hr_exception.h"
#include "dxgi_info_manager.h"

DxgiInfoManager::DxgiInfoManager()
{
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
	{
		throw BaseHrException::BaseHrException(__LINE__, __FILE__, GetLastError());
	}

	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")));
	if (DxgiGetDebugInterface == nullptr)
	{
		throw BaseHrException::BaseHrException(__LINE__, __FILE__, GetLastError());
	}

	HRESULT hResult;
	if (FAILED(hResult = DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &dxgiInfoQueue)))
	{
		throw BaseHrException::BaseHrException(__LINE__, __FILE__, hResult);
	}
}

void DxgiInfoManager::set() noexcept
{
	next = dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::getMessages() const
{
	std::vector<std::string> messages;
	const auto end = dxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; i++)
	{
		HRESULT hResult;
		SIZE_T messageLength;
		if (FAILED(hResult = dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength)))
		{
			throw BaseHrException::BaseHrException(__LINE__, __FILE__, hResult);
		}
		
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		if (FAILED(hResult = dxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength)))
		{
			throw BaseHrException::BaseHrException(__LINE__, __FILE__, hResult);
		}
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}