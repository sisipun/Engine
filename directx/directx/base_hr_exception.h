#ifndef BASE_HR_EXCEPTION
#define BASE_HR_EXCEPTION

#include "win_api.h"
#include "base_exception.h"

class BaseHrException : public BaseException
{
public:
	BaseHrException(int line, const char* file, HRESULT hResult) noexcept;
	const char* what() const noexcept override;
	virtual const char* getType() const noexcept override;
	static std::string translateErrorCode(HRESULT hResult) noexcept;
	HRESULT getErrorCode() const noexcept;
	std::string getErrorString() const noexcept;

private:
	HRESULT hResult;
};

#endif
